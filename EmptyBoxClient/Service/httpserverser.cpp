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
  m_listenPort = Constants::SysSetting.value("httpServer/httpServerPort", 8081).toInt();
  m_serialmessageUrl = Constants::SysSetting.value("httpServer/serverPath").toString();
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
                                       std::string &strResponse)
{
    qDebug() << QString("url %1, strRequstBody %2")
                .arg(QString::fromStdString(uri))
                .arg(QString::fromLocal8Bit(strRequstBody.c_str()));

    DevStatDisplay dsd;
    dsd.dType = DTNetwork;
    dsd.dStatus = DSNormal;
    emit DeviceStatusResult(dsd);

    QByteArray responseBytes;
    QJsonObject responseJson;

    try {
        if (m_serialmessageUrl.compare(QString::fromStdString(uri)) == 0) {
            QByteArray data = QString::fromLocal8Bit(strRequstBody.c_str()).toLocal8Bit();

            if (data != nullptr && !data.isEmpty()) {
                QJsonParseError jsonParseError;
                QJsonDocument document = QJsonDocument::fromJson(data, &jsonParseError);
                if (!document.isNull() && jsonParseError.error == QJsonParseError::NoError) {
                    QJsonObject json = document.object();
                    int heartbeat = json.value("heartbeat").toInt();
                    QString reqId = json.value("reqId").toString();

                    if (heartbeat == 0) {
                        responseJson.insert("status", 0);
                        responseJson.insert("reqId", reqId);
                        responseJson.insert("msg", "Success");
                        responseJson.insert("heartbeat", heartbeat);
                        responseJson.insert("data", QJsonObject());

                        responseBytes.append(QJsonDocument(responseJson).toJson());
                        strResponse = responseBytes.toStdString();
                    } else {
                        QJsonObject dataQ = json["data"].toObject();
                        SerialMessageType type = SerialMessageType(dataQ.value("data").toInt());

                        if (SMTEmptyBoxRecog == type) {
                            QString rfid = dataQ.value("rfid").toString();
                            int flag = dataQ.value("flag").toInt();
                            int mode = dataQ.value("mode").toInt();
                            int state = dataQ.value("state").toInt();
                            QString datetime = dataQ.value("datetime").toString().isEmpty()
                                    ? (QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz"))
                                    : (dataQ.value("datetime").toString());
                            QString weight = dataQ.value("weight").toString();

                            if ((rfid.isEmpty())
                                    || (rfid.size() != 4)
                                    || (rfid.compare(QString("FFFF")) == 0)
                                    || (flag < 0)
                                    || (flag > 1)
                                    || (mode < 0)
                                    || (mode > 1)) {
                                responseJson.insert("status", 205);
                                responseJson.insert("reqId", reqId);
                                responseJson.insert("msg", "Serial Message param error");
                                responseJson.insert("heartbeat", heartbeat);
                                responseJson.insert("data", QJsonObject());

                                responseBytes.append(QJsonDocument(responseJson).toJson());
                                strResponse = responseBytes.toStdString();
                            } else {
                                int camId = flag;
                                BoxRecogResult brResult;
                                brResult.camId = camId;
                                brResult.mode = mode;

                                if (mode == 0) {
                                    brResult = DetectEmptyBoxSer::instance()->SetBoxParam(camId, rfid);
                                } else if (mode == 1) {
                                    brResult = DetectEmptyBoxSer::instance()->AnaEmptyBox(camId, rfid);
                                }

                                responseJson.insert("status", 0);
                                responseJson.insert("reqId", reqId);
                                responseJson.insert("msg", "Success");
                                responseJson.insert("heartbeat", heartbeat);

                                QJsonObject dataP;
                                dataP.insert("type", type);
                                dataP.insert("rfid", rfid);
                                dataP.insert("state", state);
                                dataP.insert("flag", flag);
                                dataP.insert("mode", mode);
                                dataP.insert("datetime", datetime);
                                dataP.insert("weight", weight);

                                responseJson.insert("data", dataP);
                                responseBytes.append(QJsonDocument(responseJson).toJson());
                                strResponse = responseBytes.toStdString();

                                emit BoxRecoServerResult(brResult);
                            }
                        } else {
                            responseJson.insert("status", 205);
                            responseJson.insert("reqId", reqId);
                            responseJson.insert("msg", "Serial Message Type error");
                            responseJson.insert("heartbeat", heartbeat);
                            responseJson.insert("data", QJsonObject());

                            responseBytes.append(QJsonDocument(responseJson).toJson());
                            strResponse = responseBytes.toStdString();
                        }
                    }
                } else {
                    responseJson.insert("status", 204);
                    responseJson.insert("reqId", "");
                    responseJson.insert("msg", "No Content or Body Too Large");
                    responseJson.insert("heartbeat", 0);
                    responseJson.insert("data", QJsonObject());

                    responseBytes.append(QJsonDocument(responseJson).toJson());
                    strResponse = responseBytes.toStdString();
                }
            } else {
                responseJson.insert("status", 204);
                responseJson.insert("reqId", "");
                responseJson.insert("msg", "No Content or Body Too Large");
                responseJson.insert("heartbeat", 0);
                responseJson.insert("data", QJsonObject());

                responseBytes.append(QJsonDocument(responseJson).toJson());
                strResponse = responseBytes.toStdString();
            }
        } else {
            responseJson.insert("status", 400);
            responseJson.insert("reqId", "");
            responseJson.insert("msg", "Bad Params");
            responseJson.insert("heartbeat", 0);
            responseJson.insert("data", QJsonObject());

            responseBytes.append(QJsonDocument(responseJson).toJson());
            strResponse = responseBytes.toStdString();
        }

        qDebug() << QString("url %1, strResponse %2")
                    .arg(QString::fromStdString(uri))
                    .arg(QString::fromLocal8Bit(strResponse.c_str()));
        } catch (std::exception &ex) {
            qDebug() << ex.what();

            responseJson.insert("status", 500);
            responseJson.insert("reqId", "");
            responseJson.insert("msg", "Internal Server Error");
            responseJson.insert("heartbeat", 0);
            responseJson.insert("data", QJsonObject());

            responseBytes.append(QJsonDocument(responseJson).toJson());
            strResponse = responseBytes.toStdString();
        }
}
