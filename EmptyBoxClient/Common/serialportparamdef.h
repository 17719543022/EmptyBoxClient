#ifndef SERIALPORTPARAMDEF_H
#define SERIALPORTPARAMDEF_H

#include <QDateTime>

//参数定义
//串口消息类型相关参数
enum SerialMessageType{
    SMTStatusExchange=0,        //双方状态交换
    SMTFaceBind,                //准备位人脸绑定
    SMTBoxArrivalXRay,          //行李框到达X光机传送带
    SMTBoxLeaveXRay,            //行李框离开X光机传送带
    SMTXRayTransporterStatus,   //X光机传送带状态
    SMTRecheckBoxAssignment,    //复查框指定
    SMTEmptyBoxRecog,           //空框识别
    SMTRecoveryBoxPreparation,  //回框准备
};

/*闸机消息结构体*/
typedef struct SerialMessage_s
{
    SerialMessageType smType;   //串口消息类型
    QString	smRFID;             //rfid号，四位，默认FFFF
    int smStatus;               //状态或结果，如双方状态中状态码、人脸绑定中绑定成功/失败/人工绑定标识、4、行李框离开X光机传送带中可疑状态、X光机传送带状态中停止/转动标识、空框注册与判别中识别状态，具体见通信接口定义
    int smPosition;             //位置、标志等，如人脸绑定中准备位编号、空框注册与判别中识别位置、回框准备中框标识，具体见通信接口定义
    int	smMode;                 //模式，如空框注册与判别中模式标识
    QDateTime smTime;           //时间，时间格式：yyyyMMddHHmmsszzz。如双方状态中时间戳、行李框到达X光机传送带中时间戳、行李框离开X光机传送带中时间戳间、复查框指定中时间戳
    QString smWeight;           //体重，默认00.00。如行李框到达X光机传送带中行李重量

    /*默认构造函数*/
    SerialMessage_s()
    {
        smType=SMTStatusExchange;
        smRFID=QString("FFFF");
        smStatus=-1;
        smPosition=-1;
        smMode=-1;
        smTime=QDateTime::currentDateTime();
        smWeight=QString("00.00");
    }
}SerialMessage;

#endif // SERIALPORTPARAMDEF_H
