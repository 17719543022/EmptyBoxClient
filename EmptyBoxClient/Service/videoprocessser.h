#ifndef VIDEOPROCESSSER_H
#define VIDEOPROCESSSER_H

#include "VideoDecodeImpl.h"
#include "VideoDecodeConfig.h"

#include <QObject>
#include <QTimer>
#include <QMutex>

class VideoProcessSer: public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessSer(QObject *parent = nullptr);
    virtual ~VideoProcessSer(void);

public:
    int Init(int camPort,QString sourceType,QString param,int decodeType);
    int UnInit();
    QString GetVersion();

signals:
    void VideoFrame(int camPort,long frameIndex,QByteArray data,int len, int nWidth, int nHeight);
    void VideoStatusResult(const int& camPort,const int& status);
    int StartVideosignals();

private slots:
    int OnStartVideo();
    void TestVideoOnline();

private:
    // Video decode call back function, called every frame.
    static void CALLBACK onImageData(long frameIndex, char *data, int len,int format, void *userData);

private:
    void GetVideoInfo();

private:
    QMetaObject::Connection m_timerConnection;
    QMetaObject::Connection m_videoConnection;

    int m_videoId;
    int m_camPort;
    char m_sourceType[64];		//源类型
    char m_videoParam[128];     //视频参数，字符串为空时，不打开视频
    int m_decodeType;
    QByteArray m_videoData;
    int m_videoWidth;
    int m_videoHeight;
    long m_videoDuration;       //total video length, unit: ms.
    double m_videoFrameRate;    //unit: frame / second.
    double m_currentRate;        //multiple of normal rate: 1.0, 2.0, 4.0 , 8.0...etc.
    int m_currentFrame;

    //定时器用于定时监控摄像头是否被拔出了
    QTimer *m_testVideoTimer;
    int m_frameFlag = -1;
    QMutex m_mutex;

};
#endif // VIDEOPROCESSSER_H
