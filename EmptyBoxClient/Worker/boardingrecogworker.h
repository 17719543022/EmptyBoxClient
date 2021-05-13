#ifndef BOARDINGRECOGWORKER_H
#define BOARDINGRECOGWORKER_H

#include "Common/paramdef.h"
#include "Service/httpclientser.h"
#include <QObject>

class BoardingRecogWorker : public QObject
{
    Q_OBJECT
public:
    BoardingRecogWorker();
    ~BoardingRecogWorker();
public slots:
    void process(const BoardingRecogData& data);
signals:
    void finished();
    void BoardingRecogWorkerResult(const BoardingInfoResult& data);
};

Q_DECLARE_METATYPE(BoardingInfoResult)

#endif // BOARDINGRECOGWORKER_H
