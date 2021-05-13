#include "detectemptyboxser.h"

#include <QBuffer>
#include <QCoreApplication>
#include <QtDebug>

DetectEmptyBoxSer::DetectEmptyBoxSer(QObject *parent) : QObject(parent) {
  m_camNum = Constants::SysSetting.value(QString("Video/CamNum"), 2).toInt();
}

DetectEmptyBoxSer::~DetectEmptyBoxSer() {}

int DetectEmptyBoxSer::Init() {
  int res = -1;
  try {
    // m_channel=ISCreateEmptyChannel();
    m_channel = 0;
    res = m_channel;
    if (res < 0) {
      qCritical() << QString("ISCreateEmptyChannel res:%1").arg(res);
      return res;
    }

    for (int i = 0; i < m_camNum; i++) {
      m_camId[i] = i;
      m_isCamNormal[i] = false;
      m_videoImg[i] = QImage();
      m_cutVideoImg[i] = QImage();

      try {
        m_cutVideoImgRect[i] =
            QRect(Constants::SysSetting.value(QString("Video/ROI%1").arg(i))
                      .toRect());
      } catch (std::exception &ex) {
        qCritical() << ex.what();
        m_cutVideoImgRect[i] = QRect(0, 0, 640, 480);
      }
      Constants::SysSetting.setValue(QString("Video/ROI%1").arg(i),
                                     m_cutVideoImgRect[i]);

      QString camParam =
          QString("USB-Camera,%1,640,480,%2")
              .arg(Constants::SysSetting.value(QString("Video/Port%1").arg(i))
                       .toString())
              .arg(Constants::SysSetting
                       .value(QString("Video/UsbFrame%1").arg(i))
                       .toString());
      m_videoProcessSer[i] = new VideoProcessSer(this);
      if (m_videoProcessSer[i] != nullptr) {
        m_frameConnection[i] =
            connect(m_videoProcessSer[i], &VideoProcessSer::VideoFrame, this,
                    &DetectEmptyBoxSer::OnVideoFrame, Qt::QueuedConnection);
        m_deviceConnection[i] = connect(
            m_videoProcessSer[i], &VideoProcessSer::VideoStatusResult, this,
            &DetectEmptyBoxSer::OnVideoStatusResult,
            Qt::QueuedConnection); // connect Test videoOnline on other thread

        qInfo() << QString("VideoProcessSer Init[%1]->%2,version:%3")
                       .arg(i)
                       .arg(camParam)
                       .arg(m_videoProcessSer[i]->GetVersion());
        res = m_videoProcessSer[i]->Init(i, "usb", camParam,
                                         VideoDecodeType_NOSHOW);
        if (res != 0) {
          m_isCamNormal[i] = false;
          qCritical() << QString("%1 res:%2").arg(camParam).arg(res);
          return res;
        }
        m_isCamNormal[i] = true;
      }
    }
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

int DetectEmptyBoxSer::UnInit() {
  int res = -1;
  try {
    for (int i = 0; i < m_camNum; i++) {
      if (m_frameConnection[i] != nullptr) {
        disconnect(m_frameConnection[i]);
      }
      if (m_deviceConnection[i] != nullptr) {
        disconnect(m_deviceConnection[i]);
      }
      if (m_videoProcessSer[i] != nullptr) {
        res = m_videoProcessSer[i]->UnInit();
        delete m_videoProcessSer[i];
        m_videoProcessSer[i] = nullptr;
      }
      m_videoImg[i] = QImage();
      m_cutVideoImgRect[i] = QRect();
      m_cutVideoImg[i] = QImage();

      m_camId[i] = -1;
      m_isCamNormal[i] = false;
    }

    // res=ISDestroyEmptyChannel(m_channel);
    res = 0;
    m_channel = -1;

    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

int DetectEmptyBoxSer::GetVideoWidth(const int &index) {
  try {
    return m_videoImg[index].width();
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return 0;
  }
}

int DetectEmptyBoxSer::GetVideoHeight(const int &index) {
  try {
    return m_videoImg[index].height();
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return 0;
  }
}

void DetectEmptyBoxSer::SetCutVideoRect(const QRect &rc, const int &index) {
  try {
    m_cutVideoImgRect[index] = QRect(rc);
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

BoxRecogResult DetectEmptyBoxSer::SetBoxParam(const int &camId,
                                              const QString &rfid) {
  BoxRecogResult result;
  result.camId = camId;
  result.rfid = rfid;
  result.mode = 0;
  result.result = 1;
  try {
    if (m_isCamNormal[camId]) {
      m_cutVideoImg[camId] = QImage();
      QImage image;
      m_mutex.lock();
      { image = QImage(m_videoImg[camId]); }
      m_mutex.unlock();

      m_cutVideoImg[camId] = QImage(CutImage(image, m_cutVideoImgRect[camId]));

      if (!m_cutVideoImg[camId].isNull()) {

        QImage img = QImage(m_cutVideoImg[camId]);

        result.boxImageImg = QImage(img.rgbSwapped());
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        result.boxImageImg.save(&buffer, "Jpg");
        result.boxImage = QByteArray(ba);

        QByteArray rfidArry = rfid.toLatin1();
        // int res=ISSetBoxParam(m_channel,rfidArry.data(),
        // reinterpret_cast<char *>(img.bits()) ,img.width(),img.height(),3);
        int res = 0;
        if (res != 0) {
          qCritical() << QString("ISSetBoxParam res:%1").arg(res);
        } else {
          result.result = res;
        }
        result.time = QDateTime::currentDateTime();
      }
    }
    result.result = Constants::DetectResult;
    qInfo() << QString("SetBoxParam camId:%1 rifd:%2 result:%3")
                   .arg(result.camId)
                   .arg(result.rfid)
                   .arg(result.result);
    return result;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return result;
  }
}

BoxRecogResult DetectEmptyBoxSer::AnaEmptyBox(const int &camId,
                                              const QString &rfid) {
  BoxRecogResult result;
  result.camId = camId;
  result.rfid = rfid;
  result.mode = 1;
  result.result = 1;
  try {
    if (m_isCamNormal[camId]) {
      m_cutVideoImg[camId] = QImage();
      QImage image;
      m_mutex.lock();
      { image = QImage(m_videoImg[camId]); }
      m_mutex.unlock();

      m_cutVideoImg[camId] = QImage(CutImage(image, m_cutVideoImgRect[camId]));

      if (!m_cutVideoImg[camId].isNull()) {

        QImage img(m_cutVideoImg[camId]);

        result.boxImageImg = QImage(img.rgbSwapped());
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        result.boxImageImg.save(&buffer, "Jpg");
        result.boxImage = QByteArray(ba);

        QByteArray rfidArry = rfid.toLatin1();
        int recogresult = 1;
        // int res=ISAnaEmptyBoxRgb(m_channel,reinterpret_cast<char
        // *>(img.bits())
        // ,img.width(),img.height(),3,rfidArry.data(),&recogresult);
        int res = 0;
        if (res != 0) {
          qCritical() << QString("ISAnaEmptyBoxRgb res:%1,recog res:%2")
                             .arg(res)
                             .arg(recogresult);
        } else {
          result.result = recogresult;
        }
        result.time = QDateTime::currentDateTime();
      }
    }
    result.result = Constants::DetectResult;
    qInfo() << QString("AnaEmptyBox camId:%1 rifd:%2 result:%3")
                   .arg(result.camId)
                   .arg(result.rfid)
                   .arg(result.result);
    return result;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return result;
  }
}

QString DetectEmptyBoxSer::GetVersion() {
  try {
    QString version = QString("V1.0.0");
    return version;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return QString("");
  }
}

QImage DetectEmptyBoxSer::CutImage(const QImage &image, const QRect &rect) {
  QImage img(image);
  QRect rc(rect);
  try {
    if (rc.isNull() || rc.isEmpty()) {
      return img;
    } else {
      rc.setWidth(img.width() - img.width() % 4); //算法要求宽度4像素对齐
      rc = rc & img.rect();
      if (rect != img.rect()) {
        return img.copy(rc);
      } else {
        return img;
      }
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return img;
  }
}

void DetectEmptyBoxSer::OnVideoFrame(int camPort, int frmIndex,
                                     QByteArray bImgData, int nImgLen,
                                     int nWidth, int nHeight) {
  try {
    Q_UNUSED(frmIndex)

    if (nImgLen != 0 && nWidth != 0 && nHeight != 0) {
      QImage image(reinterpret_cast<uchar *>(bImgData.data()), nWidth, nHeight,
                   QImage::Format_RGB888);

      m_mutex.lock();
      { m_videoImg[camPort] = image.copy(); }
      m_mutex.unlock();

      emit VideoFrame(QImage(image.rgbSwapped()), camPort);
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void DetectEmptyBoxSer::OnVideoStatusResult(const int &camPort,
                                            const int &status) {
  try {
    DevStatDisplay dsd;
    if (camPort == 0) {
      dsd.dType = DTCamera1;
      if (status == 0) {
        dsd.dStatus = DSNormal;
        m_isCamNormal[0] = true;
      } else {
        dsd.dStatus = DSFault;
        m_isCamNormal[0] = false;
      }
    } else if (camPort == 1) {
      dsd.dType = DTCamera2;
      if (status == 0) {
        dsd.dStatus = DSNormal;
        m_isCamNormal[1] = true;
      } else {
        dsd.dStatus = DSFault;
        m_isCamNormal[1] = false;
      }
    }
    emit DeviceStatusResult(dsd);
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}
