#include "httpclientworker.h"

#include <QDebug>
HttpClientWorker::HttpClientWorker() {}

HttpClientWorker::~HttpClientWorker() {}

void HttpClientWorker::process(const BoxTrackData &data) {
  try {
    BoxTrackData result = HttpClientSer::instance()->PostBoxTrack(data);
    emit BoxTrackWorkerResult(result);
    emit finished();
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}
