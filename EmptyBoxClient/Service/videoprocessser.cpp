#include "videoprocessser.h"

#include <QDebug>
#include <QThread>

VideoProcessSer::VideoProcessSer(QObject *parent) : QObject(parent) {}

VideoProcessSer::~VideoProcessSer() {}

int VideoProcessSer::Init(int camPort, QString sourceType, QString param,
                          int decodeType) {
  int res = -1;
  try {
    m_videoId = -1;
    m_camPort = camPort;
    QByteArray videoTypebytes = sourceType.toLocal8Bit();
    strcpy(m_sourceType, videoTypebytes.constData());
    QByteArray videobytes = param.toLocal8Bit();
    strcpy(m_videoParam, videobytes.constData());
    m_decodeType = decodeType;
    m_testVideoTimer = new QTimer(this);
    m_timerConnection =
        connect(m_testVideoTimer, &QTimer::timeout, this,
                &VideoProcessSer::TestVideoOnline, Qt::QueuedConnection);
    m_videoConnection =
        connect(this, &VideoProcessSer::StartVideosignals, this,
                &VideoProcessSer::OnStartVideo, Qt::QueuedConnection);

    res = OnStartVideo();
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

int VideoProcessSer::UnInit() {
  int res = -1;
  try {
    if (m_testVideoTimer != nullptr) {
      m_testVideoTimer->stop();
      m_testVideoTimer = nullptr;
    }
    if (m_timerConnection != nullptr) {
      disconnect(m_timerConnection);
    }
    if (m_videoConnection != nullptr) {
      disconnect(m_videoConnection);
    }
    if (m_videoId >= 0) {
      res = videoDecodeStop(m_videoId);
    }
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

QString VideoProcessSer::GetVersion() {
  try {
    return QString::fromUtf8(videoDecodeGetVersion());
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return QString("");
  }
}

int VideoProcessSer::OnStartVideo() {
  int res = -1;
  try {
    if (m_videoId >= 0) {
      res = videoDecodeStop(m_videoId);
      if (res == 0) {
        m_videoId = -1;
        QThread::msleep(100);
      }
    }
    if (m_videoId < 0) {
      res = videoDecodeStart2(m_sourceType, m_videoParam, nullptr, m_decodeType,
                              onImageData, this, &m_videoId);
      if (res == 0) {
        m_currentFrame = -1;
        GetVideoInfo();
        if (m_testVideoTimer != nullptr && !m_testVideoTimer->isActive()) {
          m_testVideoTimer->start(10000);
        }
        emit VideoStatusResult(m_camPort, 0);
        qInfo() << QString("video decode start success，fileName-%1,ID-%2")
                       .arg(m_videoParam)
                       .arg(m_videoId);
      }
    }
    return res;
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    return res;
  }
}

void VideoProcessSer::TestVideoOnline() {
  try {
    int currentFrame = -1;
    m_mutex.lock();
    currentFrame = m_currentFrame;
    m_mutex.unlock();

    //普通摄像头是否被拔出
    if (currentFrame > 0) {
      //帧数未变  摄像头已暂停 重启摄像头
      if (currentFrame == m_frameFlag) {
        m_frameFlag = -1;
        qCritical() << QString("VideoId:%1 pulled out!").arg(m_videoId);
        emit StartVideosignals();
        //提示摄像头故障
        emit VideoStatusResult(m_camPort, 1);
      } else {
        m_frameFlag = currentFrame;
      }
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void VideoProcessSer::onImageData(long frameIndex, char *data, int len,
                                  int format, void *userData) {
  Q_UNUSED(format)
  try {
    auto videoProcessSer = static_cast<VideoProcessSer *>(userData);
    if (videoProcessSer->m_videoWidth == 0 ||
        videoProcessSer->m_videoHeight == 0) {
      videoProcessSer->GetVideoInfo();
    }
    if (videoProcessSer->m_videoData.isNull() ||
        videoProcessSer->m_videoData.isEmpty() ||
        videoProcessSer->m_videoData.size() != len) {
      videoProcessSer->m_videoData = QByteArray(len, 0);
    }
    if (len != 0) {
      videoProcessSer->m_mutex.lock();
      videoProcessSer->m_currentFrame = int(frameIndex);
      videoProcessSer->m_mutex.unlock();

      videoProcessSer->m_videoData = QByteArray(data, len);

      emit videoProcessSer->VideoFrame(
          videoProcessSer->m_camPort, int(frameIndex),
          videoProcessSer->m_videoData, len, videoProcessSer->m_videoWidth,
          videoProcessSer->m_videoHeight);
    }

  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void VideoProcessSer::GetVideoInfo() {
  if (m_videoId >= 0) {
    m_videoWidth = 0;
    m_videoHeight = 0;
    m_videoDuration = 0;
    m_videoFrameRate = 0.0;
    m_currentRate = 0.0;

    videoDecodeGetVideoInfo(m_videoId, &m_videoDuration, &m_videoFrameRate,
                            &m_videoWidth, &m_videoHeight);
    videoDecodeGetCurrentRate(m_videoId, &m_currentRate);
  }
}
