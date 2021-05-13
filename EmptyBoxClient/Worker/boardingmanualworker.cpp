#include "boardingmanualworker.h"

#include <QDebug>

BoardingManualWorker::BoardingManualWorker()
{

}

BoardingManualWorker::~BoardingManualWorker()
{

}

void BoardingManualWorker::process(const BoardingManualData &data)
{
    try {
        BoardingInfoResult result=HttpClientSer::instance()->PostBoardingManual(data);
        result.faceImg=data.faceImg;
        result.controlType=data.controlType;
        int res=HttpClientSer::instance()->PostBoardingResult(result);
        if(res!=0){
            result.netStatus=0;
        }
        emit BoardingManualWorkerResult(result);
        emit finished();
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}
