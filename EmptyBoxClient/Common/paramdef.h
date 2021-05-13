#ifndef PARAMDEF_H
#define PARAMDEF_H

#include "Common/serialportparamdef.h"

#include <QDateTime>
#include <QJsonObject>
#include <QImage>

//设备类型
enum DeviceTypes{
    DTCamera1=0,    //摄像头1
    DTCamera2,      //摄像头2
    DTNetwork,      //网络
};

//设备状态
enum DeviceStatus{
    DSNormal=0,     //正常
    DSFault,        //故障
};

/*各类设备状态消息结构体*/
typedef struct DevStatDisplay_S
{
    DeviceTypes      dType;
    DeviceStatus    dStatus;
    QDateTime       dTime;

    DevStatDisplay_S()
    {
        dType=DTCamera1;
        dStatus=DSNormal;
        dTime=QDateTime::currentDateTime();
    }
}DevStatDisplay;


/*网络接口消息*/
/*行李轨迹绑定接口消息结构体*/
typedef struct BoxTrackData_S
{
    int             netStatus;          //网络状态 0-故障；1-正常
    int             mode;               //注册与判别模式，0-注册，1-判别
    int             camId;              //摄像头编号
    QString         baseDeviceId;       //设备编号
    QString         channelCode;        //通道编号
    QString         rfid;               //托盘rfid
    int             processNode;        //	托盘检查流程编号：0-准备位绑定（服务器自用）,1-进X光机前（带图片），2-出X光机后（带复查框指定结果+图片，3-空框注册与判别中最后一格（带判别结果+图片），4-空框注册与判别中倒框位置（带判别结果+图片）,5-回框准备中复查框位，6-回框准备中空框回流位，7-回框准备中空框开包位
    int             ExtraInfoIsRecheck;     //额外信息:节点=2，出x光机后填写。是否拆包复检 1: 是 0：否
    int             ExtraInfoCheckResult;   //额外信息:节点3和4空框检查填写。空框结果0-无物品 1-有物品
    QString         ExtraInfoRfId;          //额外信息:节点5填写。填写主的rfid
    QString         ImgsPhotoName;      //图片名称，方便后面X光机有多张图的时候，用于区分
    QByteArray      ImgsImgData;        //图片
    QImage          ImgsImgDataImg;     //图片


    BoxTrackData_S()
    {
        netStatus=0;
        mode=-1;
        camId=-1;
        baseDeviceId="";
        channelCode="";
        rfid="";
        processNode=-1;
        ExtraInfoIsRecheck=-1;
        ExtraInfoCheckResult=-1;
        ExtraInfoRfId="";
        ImgsPhotoName="";
        ImgsImgData=nullptr;
        ImgsImgDataImg=QImage();
    }
}BoxTrackData;

/*空框识别结果消息结构体*/
typedef struct BoxRecogResult_S
{
    int             camId;              //摄像头编号
    QString         rfid;               //托盘rfid
    QByteArray      boxImage;           //图片
    QImage          boxImageImg;        //图片
    int             mode;               //模式类型0-注册，1-判别
    int             result;             //结果，注册模式下0-成功，1-失败；判别模式下0-空框，1-非空框
    QDateTime       time;               //识别时间


    BoxRecogResult_S()
    {
        camId=-1;
        rfid="";
        boxImage=nullptr;
        boxImageImg=QImage();
        mode=-1;
        result=-1;
        time=QDateTime::currentDateTime();
    }
}BoxRecogResult;


#endif // PARAMDEF_H
