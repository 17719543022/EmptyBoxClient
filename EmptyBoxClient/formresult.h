#ifndef FORMRESULT_H
#define FORMRESULT_H

#include "Common/paramdef.h"

#include <QWidget>

namespace Ui {
class FormResult;
}

class FormResult : public QWidget {
  Q_OBJECT

public:
  explicit FormResult(QWidget *parent = nullptr);
  ~FormResult();
  void SetParam(const BoxRecogResult &data);

private:
  Ui::FormResult *ui;
};

#endif // FORMRESULT_H
