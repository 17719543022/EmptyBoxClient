#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Common/constants.h"
#include "Common/paramdef.h"
#include "Controls/roilabel.h"
#include "Service/detectemptyboxser.h"
#include "Service/httpclientser.h"
#include "Service/httpserverser.h"
#include "Worker/httpclientworker.h"
#include "formresult.h"

#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void OnDeviceStatusResult(const DevStatDisplay &dsd);
  void OnVideoFrame(const QImage &image, const int &camId);
  void OnBoxRecoServerResult(const BoxRecogResult &data);
  void OnBoxTrackWorkerResult(const BoxTrackData &data);
  void on_ROISetBtn_clicked();

  void on_ResultTxt_textChanged();

signals:
  void BoxTrackWorkerResult(const BoxTrackData &data);

private:
  void OnDisplayResult(const BoxRecogResult &data);

private:
  Ui::MainWindow *ui;

private:
  QList<BoxRecogResult> m_curBRResultList;
  QList<FormResult *> m_curFormResultList;

  bool m_isSettingROI;
};
#endif // MAINWINDOW_H
