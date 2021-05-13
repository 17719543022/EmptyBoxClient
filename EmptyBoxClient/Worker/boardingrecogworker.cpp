#include "boardingrecogworker.h"

#include <QDebug>
BoardingRecogWorker::BoardingRecogWorker()
{

}

BoardingRecogWorker::~BoardingRecogWorker()
{
}

void BoardingRecogWorker::process(const BoardingRecogData &data)
{
    try {
        BoardingInfoResult result=HttpClientSer::instance()->PostBoardingRecog(data);
        result.faceImg=data.faceImg;
        result.controlType=0;
        int res=HttpClientSer::instance()->PostBoardingResult(result);
        if(res!=0){
            result.netStatus=0;
        }
        emit BoardingRecogWorkerResult(result);
        emit finished();
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}
