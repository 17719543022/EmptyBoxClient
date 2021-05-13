#ifndef HTTPCLIENTSER_H
#define HTTPCLIENTSER_H

#include "Common/constants.h"
#include "Common/paramdef.h"
#include "libHTTP.h"

#include <QObject>
#include <QUuid>

class HttpClientSer : public QObject {
  Q_OBJECT
public:
  explicit HttpClientSer(QObject *parent = nullptr);
  virtual ~HttpClientSer(void);
  static HttpClientSer *instance();

public:
  int Init();
  int UnInit();
  BoxTrackData PostBoxTrack(const BoxTrackData &data);

signals:
  void DeviceStatusResult(const DevStatDisplay &dsd);

private:
  bool m_isHttps;
  QString caPath;
  QString apiId;
  QString apiKey;
  QString boxTrackIpAddr;
  QString boxTrackApiAddr;
};

inline HttpClientSer *HttpClientSer::instance() {
  static HttpClientSer hcSer;
  return &hcSer;
}

#endif // HTTPCLIENTSER_H
