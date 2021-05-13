#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  qInfo() << QString("System Version:%1_EmptySDK%2_VideoSDK%3_%4")
                 .arg(Constants::SoftVersion)
                 .arg(Constants::SDKEmptyVersion)
                 .arg(Constants::SDKVideoVersion)
                 .arg(QCoreApplication::applicationDirPath());
  ui->versionLab->setText(Constants::SoftVersion);
  m_isSettingROI = false;

  try {
    //启动各个模块
    int res = -1;
    res = DetectEmptyBoxSer::instance()->Init();
    if (res != 0) {
      DetectEmptyBoxSer::instance()->UnInit();
      DevStatDisplay dsd;
      dsd.dType = DTCamera1;
      dsd.dStatus = DSFault;
      OnDeviceStatusResult(dsd);
      dsd.dType = DTCamera2;
      dsd.dStatus = DSFault;
      OnDeviceStatusResult(dsd);
      QString str = QString("DetectEmptyBoxSer res:%1").arg(res);
      qCritical() << str;
    } else {
      DevStatDisplay dsd;
      dsd.dType = DTCamera1;
      dsd.dStatus = DSNormal;
      OnDeviceStatusResult(dsd);
      dsd.dType = DTCamera2;
      dsd.dStatus = DSNormal;
      OnDeviceStatusResult(dsd);
      QString str = QString("DetectEmptyBoxSer res:%1,version:%2")
                        .arg(res)
                        .arg(DetectEmptyBoxSer::instance()->GetVersion());
      qInfo() << str;
    }

    res = HttpClientSer::instance()->Init();
    if (res != 0) {
      HttpClientSer::instance()->UnInit();
      DevStatDisplay dsd;
      dsd.dType = DTNetwork;
      dsd.dStatus = DSFault;
      OnDeviceStatusResult(dsd);
      QString str = QString("HttpClientSer res:%1").arg(res);
      qCritical() << str;
    } else {
      DevStatDisplay dsd;
      dsd.dType = DTNetwork;
      dsd.dStatus = DSNormal;
      OnDeviceStatusResult(dsd);
      QString str = QString("HttpClientSer res:%1").arg(res);
      qInfo() << str;
    }

    res = HttpServerSer::instance()->Init();
    if (res != 0) {
      HttpServerSer::instance()->UnInit();
      DevStatDisplay dsd;
      dsd.dType = DTNetwork;
      dsd.dStatus = DSFault;
      OnDeviceStatusResult(dsd);
      QString str = QString("HttpServerSer res:%1").arg(res);
      qCritical() << str;
    } else {
      DevStatDisplay dsd;
      dsd.dType = DTNetwork;
      dsd.dStatus = DSNormal;
      OnDeviceStatusResult(dsd);
      QString str = QString("HttpServerSer res:%1").arg(res);
      qInfo() << str;
    }

    connect(DetectEmptyBoxSer::instance(),
            &DetectEmptyBoxSer::DeviceStatusResult, this,
            &MainWindow::OnDeviceStatusResult, Qt::QueuedConnection);
    connect(DetectEmptyBoxSer::instance(), &DetectEmptyBoxSer::VideoFrame, this,
            &MainWindow::OnVideoFrame, Qt::QueuedConnection);
    connect(HttpClientSer::instance(), &HttpClientSer::DeviceStatusResult, this,
            &MainWindow::OnDeviceStatusResult, Qt::QueuedConnection);
    connect(HttpServerSer::instance(), &HttpServerSer::DeviceStatusResult, this,
            &MainWindow::OnDeviceStatusResult, Qt::QueuedConnection);
    connect(HttpServerSer::instance(), &HttpServerSer::BoxRecoServerResult,
            this, &MainWindow::OnBoxRecoServerResult, Qt::QueuedConnection);
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

MainWindow::~MainWindow() {
  try {
    for (int i = m_curBRResultList.size() - 1; i >= 0; i--) {
      QListWidgetItem *item = ui->listWidget->takeItem(i);
      delete item;
      delete m_curFormResultList[i];
      m_curFormResultList.removeAt(i);
      m_curBRResultList[i] = BoxRecogResult();
      m_curBRResultList.removeAt(i);
    }
    HttpServerSer::instance()->UnInit();
    HttpClientSer::instance()->UnInit();
    DetectEmptyBoxSer::instance()->UnInit();
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }

  delete ui;
}

void MainWindow::OnDeviceStatusResult(const DevStatDisplay &dsd) {
  try {
    switch (dsd.dType) {
    case DTCamera1: {
      if (dsd.dStatus == DSNormal) {
        ui->_StatCam1->setText(tr("摄像头1:正常"));
        ui->_StatCam1->setStyleSheet("font-family: \"Microsoft "
                                     "Yahei\";font-size:10px;background:"
                                     "transparent;color:#00ff00;");
      } else {
        ui->_StatCam1->setText(tr("摄像头1:故障"));
        ui->_StatCam1->setStyleSheet("font-family: \"Microsoft "
                                     "Yahei\";font-size:10px;background:"
                                     "transparent;color:#ff0000;");
      }
    } break;
    case DTCamera2: {
      if (dsd.dStatus == DSNormal) {
        ui->_StatCam2->setText(tr("摄像头2:正常"));
        ui->_StatCam2->setStyleSheet("font-family: \"Microsoft "
                                     "Yahei\";font-size:10px;background:"
                                     "transparent;color:#00ff00;");
      } else {
        ui->_StatCam2->setText(tr("摄像头2:故障"));
        ui->_StatCam2->setStyleSheet("font-family: \"Microsoft "
                                     "Yahei\";font-size:10px;background:"
                                     "transparent;color:#ff0000;");
      }
    } break;
    case DTNetwork: {
      if (dsd.dStatus == DSNormal) {
        ui->_StatNet->setText(tr("网络:正常"));
        ui->_StatNet->setStyleSheet("font-family: \"Microsoft "
                                    "Yahei\";font-size:10px;background:"
                                    "transparent;color:#00ff00;");
      } else {
        ui->_StatNet->setText(tr("网络:故障"));
        ui->_StatNet->setStyleSheet("font-family: \"Microsoft "
                                    "Yahei\";font-size:10px;background:"
                                    "transparent;color:#ff0000;");
      }
    } break;
    }

    if (dsd.dStatus == DSNormal) {
      Constants::DeviceStatus = 0;
    } else {
      Constants::DeviceStatus = 1;
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void MainWindow::OnVideoFrame(const QImage &image, const int &camId) {
  try {
    if (camId == 0) {
      QImage img =
          image.scaled(ui->VideoImg1->width(), ui->VideoImg1->height(),
                       Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
      ui->VideoImg1->setPixmap(QPixmap::fromImage(img));
    } else if (camId == 1) {
      QImage img =
          image.scaled(ui->VideoImg2->width(), ui->VideoImg2->height(),
                       Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
      ui->VideoImg2->setPixmap(QPixmap::fromImage(img));
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void MainWindow::OnBoxRecoServerResult(const BoxRecogResult &data) {
  try {
    BoxTrackData btData;
    btData.netStatus = 0;
    btData.mode = data.mode;
    btData.camId = data.camId;
    btData.baseDeviceId =
        Constants::SysSetting.value("Device/SubDeviceId").toString();
    btData.channelCode =
        Constants::SysSetting.value("Device/GateNo").toString();
    btData.rfid = data.rfid;
    btData.processNode = 3;
    if (data.camId == 0) {
      btData.processNode = 3;
    } else if (data.camId == 1) {
      btData.processNode = 4;
    }
    btData.ExtraInfoIsRecheck = -1;
    btData.ExtraInfoCheckResult = data.result;
    btData.ExtraInfoRfId = "";
    btData.ImgsPhotoName =
        QString("%1_%2_%3_%4.jpg")
            .arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz"))
            .arg(data.camId)
            .arg(data.rfid)
            .arg(data.result);
    btData.ImgsImgData = QByteArray(data.boxImage);
    btData.ImgsImgDataImg = QImage(data.boxImageImg);

    QThread *thread = new QThread;
    HttpClientWorker *worker = new HttpClientWorker();
    worker->moveToThread(thread);
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this, &MainWindow::BoxTrackWorkerResult, worker,
            &HttpClientWorker::process, Qt::QueuedConnection);
    connect(worker, &HttpClientWorker::BoxTrackWorkerResult, this,
            &MainWindow::OnBoxTrackWorkerResult, Qt::QueuedConnection);

    thread->start();
    emit BoxTrackWorkerResult(btData);
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void MainWindow::OnBoxTrackWorkerResult(const BoxTrackData &data) {
  try {

    BoxRecogResult brResult;
    brResult.camId = data.camId;
    brResult.rfid = data.rfid;
    brResult.mode = data.mode;
    brResult.result = data.ExtraInfoCheckResult;
    brResult.boxImage = QByteArray(data.ImgsImgData);
    brResult.boxImageImg = QImage(data.ImgsImgDataImg);
    brResult.time = QDateTime::currentDateTime();

    OnDisplayResult(brResult);

  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void MainWindow::OnDisplayResult(const BoxRecogResult &data) {
  try {
    if (data.mode == 0) {
      ui->WorkStatusLab->setStyleSheet(
          "background-image: url(:/Images/register.png);");
    } else if (data.mode == 1) {
      ui->WorkStatusLab->setStyleSheet(
          "background-image: url(:/Images/identify.png);");
    }

    for (int i = m_curBRResultList.size() - 1; i >= 0; i--) {
      if (data.camId == m_curBRResultList[i].camId &&
          data.mode == m_curBRResultList[i].mode &&
          data.rfid.compare(m_curBRResultList[i].rfid) == 0) {
        m_curBRResultList.removeAt(i);
        break;
      }
    }
    m_curBRResultList.insert(0, data);
    int maxNum = 10;
    if (m_curBRResultList.size() > maxNum) {
      m_curBRResultList.removeAt(maxNum);
    }

    if (m_curFormResultList.size() > 0) {
      qDeleteAll(m_curFormResultList);
      m_curFormResultList.clear();
    }

    for (int i = ui->listWidget->count() - 1; i >= 0; i--) {
      QListWidgetItem *item = ui->listWidget->takeItem(i);
      delete item;
    }
    ui->listWidget->clear();

    for (int i = 0; i < m_curBRResultList.size(); i++) {
      FormResult *form = new FormResult();
      form->SetParam(m_curBRResultList[i]);
      QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
      item->setSizeHint(QSize(250, 120));
      ui->listWidget->addItem(item);
      ui->listWidget->setItemWidget(item, form);
      m_curFormResultList.insert(0, form);
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void MainWindow::on_ROISetBtn_clicked() {
  try {
    if (m_isSettingROI) {
      for (int i = 0;
           i < Constants::SysSetting.value(QString("Video/CamNum"), 2).toInt();
           i++) {
        int videoWidth = DetectEmptyBoxSer::instance()->GetVideoWidth(i);
        int videoHeight = DetectEmptyBoxSer::instance()->GetVideoHeight(i);

        if (i == 0) {
          float Xrate = float(videoWidth) / float(ui->VideoImgRoi1->width());
          float Yrate = float(videoHeight) / float(ui->VideoImgRoi1->height());
          QRect rect = ui->VideoImgRoi1->getROI();
          QRect saveRect(int(Xrate * rect.x()), int(Yrate * rect.y()),
                         int(Xrate * rect.width()), int(Yrate * rect.height()));
          saveRect.setWidth(saveRect.width() -
                            saveRect.width() % 4); //算法要求宽度4像素对齐
          Constants::SysSetting.setValue(QString("Video/ROI%1").arg(i),
                                         saveRect);
          ui->VideoImgRoi1->hideROI();
          DetectEmptyBoxSer::instance()->SetCutVideoRect(saveRect, i);
        } else if (i == 1) {
          float Xrate = float(videoWidth) / float(ui->VideoImgRoi2->width());
          float Yrate = float(videoHeight) / float(ui->VideoImgRoi2->height());
          QRect rect = ui->VideoImgRoi2->getROI();
          QRect saveRect(int(Xrate * rect.x()), int(Yrate * rect.y()),
                         int(Xrate * rect.width()), int(Yrate * rect.height()));
          saveRect.setWidth(saveRect.width() -
                            saveRect.width() % 4); //算法要求宽度4像素对齐
          Constants::SysSetting.setValue(QString("Video/ROI%1").arg(i),
                                         saveRect);
          ui->VideoImgRoi2->hideROI();
          DetectEmptyBoxSer::instance()->SetCutVideoRect(saveRect, i);
        }
      }
      m_isSettingROI = false;
    } else {
      for (int i = 0;
           i < Constants::SysSetting.value(QString("Video/CamNum"), 2).toInt();
           i++) {
        int videoWidth = DetectEmptyBoxSer::instance()->GetVideoWidth(i);
        int videoHeight = DetectEmptyBoxSer::instance()->GetVideoHeight(i);
        QRect rect =
            QRect(Constants::SysSetting.value(QString("Video/ROI%1").arg(i))
                      .toRect());
        if (i == 0) {
          float Xrate = float(videoWidth) / float(ui->VideoImgRoi1->width());
          float Yrate = float(videoHeight) / float(ui->VideoImgRoi1->height());
          QRect loadRect(int(rect.x() / Xrate), int(rect.y() / Yrate),
                         int(rect.width() / Xrate), int(rect.height() / Yrate));
          ui->VideoImgRoi1->setROI_rect(loadRect);
          ui->VideoImgRoi1->showROI();
        } else if (i == 1) {
          float Xrate = float(videoWidth) / float(ui->VideoImgRoi2->width());
          float Yrate = float(videoHeight) / float(ui->VideoImgRoi2->height());
          QRect loadRect(int(rect.x() / Xrate), int(rect.y() / Yrate),
                         int(rect.width() / Xrate), int(rect.height() / Yrate));
          ui->VideoImgRoi2->setROI_rect(loadRect);
          ui->VideoImgRoi2->showROI();
        }
      }
      m_isSettingROI = true;
    }

  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}

void MainWindow::on_ResultTxt_textChanged() {
  try {
    QString str = ui->ResultTxt->toPlainText();
    if (!str.isEmpty()) {
      if (str.compare(QString("0")) == 0) {
        Constants::DetectResult = 0;
      } else if (str.compare(QString("1")) == 0) {
        Constants::DetectResult = 1;
      } else {
        Constants::DetectResult = 1;
      }
    } else {
      Constants::DetectResult = 1;
    }
  } catch (std::exception &ex) {
    qCritical() << ex.what();
  }
}
