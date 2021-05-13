#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Common/paramdef.h"
#include <QSettings>
#include <QString>

class Constants
{
public:
    static QSettings SysSetting;
    static QString SoftVersion;
    static QString SDKEmptyVersion;
    static QString SDKVideoVersion;
    static int DeviceStatus;
    static int DetectResult;
};

#endif // CONSTANTS_H
