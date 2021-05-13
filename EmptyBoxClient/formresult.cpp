#include "formresult.h"
#include "ui_formresult.h"

#include <QDebug>

FormResult::FormResult(QWidget *parent)
    : QWidget(parent), ui(new Ui::FormResult) {
  ui->setupUi(this);
}

FormResult::~FormResult() { delete ui; }

void FormResult::SetParam(const BoxRecogResult &data) {
  try {
    if (!data.boxImageImg.isNull()) {
      QImage img = data.boxImageImg.scaled(
          ui->PhotoLab->width(), ui->PhotoLab->height(), Qt::IgnoreAspectRatio,
          Qt::SmoothTransformation);
      ui->PhotoLab->setPixmap(QPixmap::fromImage(img));
    }
    ui->rfidLab->setText(QString("RFID号:%1").arg(data.rfid));
    ui->camLab->setText(QString("位置:摄像头%1").arg(data.camId));
    if (data.mode == 0) {
      ui->modeLab->setText(QString("模式:注册"));
      if (data.result == 0) {
        ui->resultLab->setText(QString("结果:成功"));
      } else {
        ui->resultLab->setText(QString("结果:失败"));
        ui->resultLab->setStyleSheet(QString(
            "font-family: \"Microsoft "
            "Yahei\";font-size:13px;background:transparent;color:#ff0000;"));
      }
    } else {
      ui->modeLab->setText(QString("模式:判别"));
      if (data.result == 0) {
        ui->resultLab->setText(QString("结果:空框"));
      } else {
        ui->resultLab->setText(QString("结果:非空框"));
        ui->resultLab->setStyleSheet(QString(
            "font-family: \"Microsoft "
            "Yahei\";font-size:13px;background:transparent;color:#ff0000;"));
      }
    }
    ui->timeLab->setText(
        QString("时间:%1").arg(data.time.toString("HH:mm:ss")));
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}
