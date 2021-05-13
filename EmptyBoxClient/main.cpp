#include "mainwindow.h"

#include "Common/constants.h"
#include "Logger/loghandler.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  try {
    // [[1]] 安装消息处理函数
    Singleton<LogHandler>::getInstance().installMessageHandler();
  } catch (std::exception &ex) {
    qCritical() << ex.what();
    qApp->exit();
  }

  MainWindow w;
  w.show();
  return a.exec();
}
