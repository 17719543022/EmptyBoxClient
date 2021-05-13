#include "boardingrecogth.h"

#include <QDebug>

BoardingRecogTh::BoardingRecogTh(QObject *parent, BoardingRecogData data)
{
    m_data=data;
    m_object=parent;
}

BoardingRecogTh::~BoardingRecogTh()
{
    m_data=BoardingRecogData();
    delete m_object;
}

void BoardingRecogTh::run()
{
    try {
        BoardingInfoResult result=HttpClientSer::instance()->PostBoardingRecog(m_data);
        int res=HttpClientSer::instance()->PostBoardingResult(result);
    } catch (std::exception &ex) {
            qCritical()<<ex.what();
    }
}
