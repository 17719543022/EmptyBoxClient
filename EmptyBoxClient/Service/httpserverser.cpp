#include "httpserverser.h"

#include <QByteArray>
#include <QDateTime>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QtDebug>

HttpServerSer::HttpServerSer(QObject *parent) : QObject(parent) {
  m_listenPort =
      Constants::SysSetting.value("httpServer/httpServerPort", 8081).toInt();
  m_serialmessageUrl = "/api/v1/airport/baggage/serial-data";
}

HttpServerSer::~HttpServerSer() {}

int HttpServerSer::Init() {
  int res = -1;
  try {
    res = StartHTTPServer(m_listenPort, HttpServerSer::instance());
    if (res != 0) {
      qCritical() << QString("StartHTTPServer res:%1").arg(res);
      return res;
    }
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

int HttpServerSer::UnInit() {
  int res = -1;
  try {
    res = StopHTTPServer();
    if (res != 0) {
      qCritical() << QString("StopHTTPServer res:%1").arg(res);
      return res;
    }
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

void HttpServerSer::MultipartRequstListen(
    const std::string &uri, const std::map<std::string, DataInfo> &mapDataInfo,
    std::string &strResponse) {
  Q_UNUSED(uri)
  Q_UNUSED(mapDataInfo)
  Q_UNUSED(strResponse)
}

void HttpServerSer::CommonRequstListen(const std::string &uri,
                                       const std::string &strRequstBody,
                                       std::string &strResponse) {
  DevStatDisplay dsd;
  dsd.dType = DTNetwork;
  dsd.dStatus = DSNormal;
  emit DeviceStatusResult(dsd);

  QByteArray responseBytes;
  QJsonObject responsejson;
  responsejson.insert("status", 500);
  responsejson.insert("reqId", "");
  responsejson.insert("msg", tr("Internal Server Error"));
  responsejson.insert("heartbeat", 0);
  responsejson.insert("devicestatus", -1);
  responsejson.insert("content", QJsonObject());

  try {
    qInfo() << QString("url %1,data %2")
                   .arg(QString::fromStdString(uri))
                   .arg(QString::fromLocal8Bit(strRequstBody.c_str()));

    if (m_serialmessageUrl.compare(QString::fromStdString(uri)) == 0) {
      QByteArray data =
          QString::fromLocal8Bit(strRequstBody.c_str()).toLocal8Bit();
      if (data != nullptr && !data.isEmpty()) {
        QJsonParseError jsonParseError;
        QJsonDocument document = QJsonDocument::fromJson(data, &jsonParseError);
        if (!document.isNull() &&
            jsonParseError.error == QJsonParseError::NoError) {
          SerialMessage data;
          QJsonObject json = document.object();
          int heartbeat = json["heartbeat"].toInt();
          if (heartbeat == 0) {
            responsejson["status"] = 0;
            responsejson["reqId"] = json["reqId"].toString();
            responsejson["msg"] = QString("Success");
            responsejson["heartbeat"] = heartbeat;
            responsejson["devicestatus"] = Constants::DeviceStatus;
            responseBytes.append(QJsonDocument(responsejson).toJson());
            strResponse = responseBytes.toStdString();
          } else {
            QJsonObject json1 = json["content"].toObject();
            SerialMessageType type = SerialMessageType(json1["type"].toInt());
            if (SMTEmptyBoxRecog == type) {
              data.smType = type;
              data.smRFID = json1["rfid"].toString();
              data.smStatus = json1["status"].toInt();
              data.smPosition = json1["position"].toInt();
              data.smMode = json1["mode"].toInt();
              QString timeStr = json1["time"].toString();
              if (timeStr.isEmpty()) {
                data.smTime = QDateTime::currentDateTime();
              } else {
                try {
                  data.smTime =
                      QDateTime::fromString(timeStr, "yyyyMMddHHmmsszzz");
                } catch (std::exception &ex) {
                  qCritical() << ex.what();
                  data.smTime = QDateTime::currentDateTime();
                }
              }
              data.smWeight = json1["weight"].toString();

              if (data.smRFID.isEmpty() || data.smRFID.size() != 4 ||
                  data.smRFID.compare(QString("FFFF")) == 0 ||
                  data.smPosition < 0 || data.smPosition > 1 ||
                  data.smMode < 0 || data.smMode > 1) {
                responsejson["status"] = 205;
                responsejson["reqId"] = QString("");
                responsejson["msg"] = QString("Serial Message param error");
                responseBytes.append(QJsonDocument(responsejson).toJson());
                strResponse = responseBytes.toStdString();
              } else {
                QString rfid = data.smRFID;
                int camId = data.smPosition;
                int mode = data.smMode;
                BoxRecogResult brResult;
                brResult.camId = camId;
                brResult.mode = mode;
                if (mode == 0) {
                  brResult =
                      DetectEmptyBoxSer::instance()->SetBoxParam(camId, rfid);
                } else if (mode == 1) {
                  brResult =
                      DetectEmptyBoxSer::instance()->AnaEmptyBox(camId, rfid);
                }

                data.smStatus = brResult.result;
                data.smTime = QDateTime::currentDateTime();

                responsejson["status"] = 0;
                responsejson["reqId"] = json["reqId"].toString();
                responsejson["msg"] = QString("Success");
                responsejson["heartbeat"] = heartbeat;
                responsejson["devicestatus"] = Constants::DeviceStatus;
                QJsonObject responsejson1;
                responsejson1.insert("type", data.smType);
                responsejson1.insert("rfid", data.smRFID);
                responsejson1.insert("status", data.smStatus);
                responsejson1.insert("position", data.smPosition);
                responsejson1.insert("mode", data.smMode);
                responsejson1.insert("stime",
                                     data.smTime.toString("yyyyMMddHHmmsszzz"));
                responsejson1.insert("weight", data.smWeight);
                responsejson["content"] = responsejson1;
                responseBytes.append(QJsonDocument(responsejson).toJson());
                strResponse = responseBytes.toStdString();

                emit BoxRecoServerResult(brResult);
              }
            } else {
              responsejson["status"] = 205;
              responsejson["reqId"] = QString("");
              responsejson["msg"] = QString("Serial Message Type error");
              responseBytes.append(QJsonDocument(responsejson).toJson());
              strResponse = responseBytes.toStdString();
            }
          }
        } else {
          responsejson["status"] = 204;
          responsejson["reqId"] = QString("");
          responsejson["msg"] = QString("No Content or Body Too Large");
          responseBytes.append(QJsonDocument(responsejson).toJson());
          strResponse = responseBytes.toStdString();
        }

      } else {
        responsejson["status"] = 204;
        responsejson["reqId"] = QString("");
        responsejson["msg"] = QString("No Content or Body Too Large");
        responseBytes.append(QJsonDocument(responsejson).toJson());
        strResponse = responseBytes.toStdString();
      }
    } else {
      responsejson["status"] = 400;
      responsejson["reqId"] = QString("");
      responsejson["msg"] = QString("Bad Params");
      responseBytes.append(QJsonDocument(responsejson).toJson());
      strResponse = responseBytes.toStdString();
    }

    qInfo() << QString("url %1,response %2")
                   .arg(QString::fromStdString(uri))
                   .arg(QString::fromLocal8Bit(strResponse.c_str()));
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    responseBytes.append(QJsonDocument(responsejson).toJson());
    strResponse = responseBytes.toStdString();
  }
}
