#ifndef DETECTEMPTYBOXSER_H
#define DETECTEMPTYBOXSER_H

#include "Common/ISEmpty.h"
#include "Common/constants.h"
#include "Common/paramdef.h"
#include "Service/videoprocessser.h"

#include <QMutex>
#include <QObject>

class DetectEmptyBoxSer : public QObject {
  Q_OBJECT
public:
  explicit DetectEmptyBoxSer(QObject *parent = nullptr);
  virtual ~DetectEmptyBoxSer(void);
  static DetectEmptyBoxSer *instance();

public:
  int Init();
  int UnInit();
  int GetVideoWidth(const int &index);
  int GetVideoHeight(const int &index);
  void SetCutVideoRect(const QRect &rc, const int &index);

  BoxRecogResult SetBoxParam(const int &camId, const QString &rfid);
  BoxRecogResult AnaEmptyBox(const int &camId, const QString &rfid);
  QString GetVersion();

private:
  QImage CutImage(const QImage &image, const QRect &rect);

private slots:
  void OnVideoFrame(int camPort, int frmIndex, QByteArray bImgData, int nImgLen,
                    int nWidth, int nHeight);
  // Which camera's image to show;
  void OnVideoStatusResult(const int &camPort, const int &status);

signals:
  void VideoFrame(const QImage &image, const int &camId);
  void DeviceStatusResult(const DevStatDisplay &dsd);

private:
  QImage m_videoImg[2];
  QRect m_cutVideoImgRect[2];
  QImage m_cutVideoImg[2];
  QMutex m_mutex;

private:
  QMetaObject::Connection m_frameConnection[2];
  QMetaObject::Connection m_deviceConnection[2];

  int m_camNum;
  VideoProcessSer *m_videoProcessSer[2];
  int m_camId[2];
  bool m_isCamNormal[2];
  int m_VideoRestartMaxNum;

  int m_channel;
};

inline DetectEmptyBoxSer *DetectEmptyBoxSer::instance() {
  static DetectEmptyBoxSer debSer;
  return &debSer;
}

#endif // DETECTEMPTYBOXSER_H
