#ifndef HTTPSERVERSER_H
#define HTTPSERVERSER_H

#include "Common/constants.h"
#include "Common/paramdef.h"
#include "Service/detectemptyboxser.h"
#include "HTTPServerExp.h"

#include <QObject>

class HttpServerSer :  public QObject ,public RequstListener
{
    Q_OBJECT
public:
    explicit HttpServerSer(QObject *parent = nullptr);
    virtual ~HttpServerSer(void);
    static HttpServerSer* instance();

public:
    int Init();
    int UnInit();
    virtual void MultipartRequstListen(const std::string& uri, const std::map<std::string, DataInfo>& mapDataInfo, std::string& strResponse);
    virtual void CommonRequstListen(const std::string& uri, const std::string& strRequstBody, std::string& strResponse);

signals:
    void BoxRecoServerResult(const BoxRecogResult& data);
    void DeviceStatusResult(const DevStatDisplay& dsd);

private:
    int m_listenPort;
    QString m_serialmessageUrl;
};

inline HttpServerSer* HttpServerSer::instance()
{
    static HttpServerSer hsSer;
    return &hsSer;
}

Q_DECLARE_METATYPE(BoxRecogResult)

#endif // HTTPSERVERSER_H
