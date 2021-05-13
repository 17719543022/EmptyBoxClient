#include "httpclientser.h"

#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QThread>
#include <QtDebug>

HttpClientSer::HttpClientSer(QObject *parent) : QObject(parent) {
  m_isHttps = false;
  caPath = QCoreApplication::applicationDirPath() + "/cacert.crt";
  apiId = "123456";
  apiKey = "1285384ddfb057814bad78127bc789be";
  boxTrackIpAddr =
      Constants::SysSetting.value("HttpClient/HttpClientURL").toString();
  boxTrackApiAddr = "/api/v1/airport/baggage/tracker";
}

HttpClientSer::~HttpClientSer() {}

int HttpClientSer::Init() {
  int res = -1;
  try {
    if (m_isHttps) {
      char *capathchr = caPath.toLatin1().data();
      res = LIBInit(capathchr);
    } else {
      res = LIBInit(nullptr);
    }

    if (res != 0) {
      qCritical() << QString("LIBInit res:%1").arg(res);
      return res;
    }

    QByteArray bytes0;
    QJsonObject json0;
    json0.insert("Content-Type", "application/json");
    json0.insert("apiId", apiId);
    json0.insert("apiKey", apiKey);
    json0.insert("url", boxTrackApiAddr);
    bytes0.append(QJsonDocument(json0).toJson());
    char *headchr0 = bytes0.data();
    QString url0 = boxTrackIpAddr + boxTrackApiAddr;
    QByteArray urlBytes0 = url0.toLatin1();
    char *urlchr0 = urlBytes0.data();
    res = LIBSetHeaderEx(urlchr0, headchr0);
    if (res != 0) {
      qCritical() << QString("LIBSetHeaderEx res:%1").arg(res);
    }
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

int HttpClientSer::UnInit() {
  int res = -1;
  try {
    QString url0 = boxTrackIpAddr + boxTrackApiAddr;
    char *urlchr0 = url0.toLatin1().data();
    res = LIBRemoveHeader(urlchr0);

    res = LIBUnInit();

    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

BoxTrackData HttpClientSer::PostBoxTrack(const BoxTrackData &data) {
  BoxTrackData result;
  try {
    result.netStatus = 0;
    result.mode = data.mode;
    result.camId = data.camId;
    result.baseDeviceId = data.baseDeviceId;
    result.channelCode = data.channelCode;
    result.rfid = data.rfid;
    result.processNode = data.processNode;
    result.ExtraInfoIsRecheck = data.ExtraInfoIsRecheck;
    result.ExtraInfoCheckResult = data.ExtraInfoCheckResult;
    result.ExtraInfoRfId = data.ExtraInfoRfId;
    result.ImgsPhotoName = data.ImgsPhotoName;
    result.ImgsImgData = QByteArray(data.ImgsImgData);
    result.ImgsImgDataImg = QImage(data.ImgsImgDataImg);
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }

  // 注册模式不上传服务器
  if (data.mode == 0) {
    result.netStatus = 1;
    return result;
  }

  try {
    int status = -1;
    QJsonObject json1;
    QByteArray bytes;
    QJsonObject json;

    json.insert("reqId", QString(QUuid::createUuid().toRfc4122().toHex()));
    json.insert("baseDeviceId", data.baseDeviceId);
    json.insert("channelCode", data.channelCode);
    json.insert("rfid", data.rfid);
    json.insert("processNode", data.processNode);

    QJsonObject extraInfojson;
    extraInfojson.insert("isRecheck", data.ExtraInfoIsRecheck);
    extraInfojson.insert("checkResult", data.ExtraInfoCheckResult);
    extraInfojson.insert("rfId", data.ExtraInfoRfId);
    json.insert("extraInfo", extraInfojson);
    if (data.ImgsImgData.isNull() || data.ImgsImgData.isEmpty()) {
      json.insert("imgs", QString(""));
    } else {
      QJsonObject imgsjson;
      imgsjson.insert("photoName", data.ImgsPhotoName);
      imgsjson.insert("imgData",
                      QString(QByteArray(data.ImgsImgData.toBase64())));
      QJsonArray imgsjsonArray;
      imgsjsonArray.insert(0, imgsjson);
      json.insert("imgs", imgsjsonArray);
    }

    bytes.append(QString(QJsonDocument(json).toJson()).toLocal8Bit());
    char *body = bytes.data();
    char *response;
    qInfo() << QString("PostBoxTrack data %1").arg(QString(bytes));

    int curNum = 0;
    do {
      curNum++;
      if (curNum >
          (Constants::SysSetting.value("HttpClient/ServerRequestMaxNum", 3)
               .toInt())) {
        break;
      }

      int resLen = 0;
      int res = -1;
      res = LIBPostSynEx(boxTrackIpAddr.toLatin1().data(),
                         boxTrackApiAddr.toLatin1().data(), body, &response,
                         &resLen, m_isHttps);
      if (res != 0 || resLen == 0) {
        qCritical() << QString("LIBPostSynEx res:%1").arg(res);
      } else {
        QByteArray data1 = QByteArray(response, resLen);
        if (data1 != nullptr) {
          QJsonParseError jsonParseError;
          QJsonDocument document =
              QJsonDocument::fromJson(data1, &jsonParseError);
          if (!document.isNull() &&
              jsonParseError.error == QJsonParseError::NoError) {
            json1 = document.object();
            status = json1["status"].toInt();
            qInfo() << QString("PostBoxTrack status %1,msg %2")
                           .arg(json1["status"].toInt())
                           .arg(json1["msg"].toString());
          }
        }
      }
      if (status == 0) {
        break;
      }
    } while (true);
    if (status != 0) {
      result.netStatus = 0;

      DevStatDisplay dsd;
      dsd.dType = DTNetwork;
      dsd.dStatus = DSFault;
      emit DeviceStatusResult(dsd);
    } else {
      result.netStatus = 1;

      DevStatDisplay dsd;
      dsd.dType = DTNetwork;
      dsd.dStatus = DSNormal;
      emit DeviceStatusResult(dsd);
    }
    return result;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return result;
  }
}
