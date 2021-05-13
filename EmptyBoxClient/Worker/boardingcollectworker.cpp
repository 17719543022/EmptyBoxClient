#include "httpclientworker.h"
#include <QDebug>

HttpClientWorker::HttpClientWorker()
{

}

HttpClientWorker::~HttpClientWorker()
{

}

void HttpClientWorker::process(const BoardingcollectData &data)
{
    try {
        BoardingcollectData result=HttpClientSer::instance()->PostBoardingCollect(data);
        result.faceImg=data.faceImg;
        int res=HttpClientSer::instance()->PostCollectResult(result);
        if(res!=0){
            result.netStatus=0;
        }
        emit HttpClientWorkerResult(result);
        emit finished();
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}
