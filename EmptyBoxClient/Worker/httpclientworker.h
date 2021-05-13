#ifndef HttpClientWorker_H
#define HttpClientWorker_H

#include <QObject>
#include "Common/paramdef.h"
#include "Service/httpclientser.h"

class HttpClientWorker : public QObject {
  Q_OBJECT
 public:
  HttpClientWorker();
  ~HttpClientWorker();
 public slots:
  void process(const BoxTrackData &data);
 signals:
  void finished();
  void BoxTrackWorkerResult(const BoxTrackData &data);
};

Q_DECLARE_METATYPE(BoxTrackData)

#endif  // HttpClientWorker_H
