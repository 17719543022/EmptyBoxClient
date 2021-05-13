#include "roilabel.h"

#include <QMouseEvent>
#include <QPainter>
ROILabel::ROILabel(QWidget *parent)
    : QLabel(parent), ROI_rect(0, 0, 20, 20), ROI_width(2),
      ROI_color("#FF0000") {}

void ROILabel::paintEvent(QPaintEvent *e) {
  if (isRectShow) {
    QPainter painter(this);

    QPen pen;
    pen.setWidth(ROI_width);
    pen.setColor(ROI_color);
    painter.setPen(pen);
    painter.drawRect(ROI_rect);
  }
  return QLabel::paintEvent(e);
}

void ROILabel::mousePressEvent(QMouseEvent *e) {
  ptDiff_pressPos_ROIcenter = e->pos() - ROI_rect.center();
  isMousePressed = true;

  return QLabel::mousePressEvent(e);
}

void ROILabel::mouseReleaseEvent(QMouseEvent *e) {
  isMousePressed = false;

  return QLabel::mouseReleaseEvent(e);
}

void ROILabel::mouseMoveEvent(QMouseEvent *e) {
  if (!isRectShow) {
    return QLabel::mouseMoveEvent(e);
  }

  const int swing =
      5; // ROI边框的鼠标可捕捉范围,ROI的边框值只有一个确定的像素点，通过swing使鼠标处于一定范围即可抓取边框

  if (!isMousePressed) {
    int posX = e->x();
    int posY = e->y();

    int left = ROI_rect.left(); // left top
    int top = ROI_rect.top();
    int right = ROI_rect.right(); // right botton
    int botton = ROI_rect.bottom();

    if (posX > left + swing && posX < right - swing && posY > top + swing &&
        posY < botton - swing) {
      movePolicy = Inside;
      setCursor(Qt::SizeAllCursor);
    } else if ((posX > left - swing && posX < left + swing) &&
               (posY > top + swing && posY < botton - swing)) {
      movePolicy = Left;
      setCursor(Qt::SizeHorCursor);
    } else if ((posX > left + swing && posX < right - swing) &&
               (posY > top - swing && posY < top + swing)) {
      movePolicy = Top;
      setCursor(Qt::SizeVerCursor);
    } else if ((posX > right - swing && posX < right + swing) &&
               (posY > top + swing && posY < botton - swing)) {
      movePolicy = Right;
      setCursor(Qt::SizeHorCursor);
    } else if ((posX > left + swing && posX < right - swing) &&
               (posY > botton - swing && posY < botton + swing)) {
      movePolicy = Bottom;
      setCursor(Qt::SizeVerCursor);
    } else if ((posX > left - swing && posX < left + swing) &&
               (posY > top - swing && posY < top + swing)) {
      movePolicy = TopLeft;
      setCursor(Qt::SizeFDiagCursor);
    } else if ((posX > right - swing && posX < right + swing) &&
               (posY > top - swing && posY < top + swing)) {
      movePolicy = TopRight;
      setCursor(Qt::SizeBDiagCursor);
    } else if ((posX > right - swing && posX < right + swing) &&
               (posY > botton - swing && posY < botton + swing)) {
      movePolicy = BottonRight;
      setCursor(Qt::SizeFDiagCursor);
    } else if ((posX > left - swing && posX < left + swing) &&
               (posY > botton - swing && posY < botton + swing)) {
      movePolicy = BottonLeft;
      setCursor(Qt::SizeBDiagCursor);
    } else {
      movePolicy = None;
      unsetCursor();
    }
  } else if (isMousePressed) {
    QPoint p(e->pos());
    if (p.x() < 0)
      p.setX(0);
    if (p.x() > this->width())
      p.setX(this->width());
    if (p.y() < 0)
      p.setY(0);
    if (p.y() > this->height())
      p.setY(this->height());

    switch (movePolicy) {
    case None:
      break;
    case Inside: {
      ROI_rect.moveCenter(p - ptDiff_pressPos_ROIcenter);
    } break;
    case Left:
      ROI_rect.setLeft(p.x());
      break;
    case Top:
      ROI_rect.setTop(p.y());
      break;
    case Right:
      ROI_rect.setRight(p.x());
      break;
    case Bottom:
      ROI_rect.setBottom(p.y());
      break;
    case TopLeft:
      ROI_rect.setTopLeft(p);
      break;
    case TopRight:
      ROI_rect.setTopRight(p);
      break;
    case BottonLeft:
      ROI_rect.setBottomLeft(p);
      break;
    case BottonRight:
      ROI_rect.setBottomRight(p);
      break;
    }

    if (ROI_rect.left() < 0) {
      ROI_rect.setLeft(0);
    }
    if (ROI_rect.top() < 0) {
      ROI_rect.setTop(0);
    }
    if (ROI_rect.left() > this->width() - 4 * swing) {
      ROI_rect.setLeft(this->width() - 4 * swing);
    }
    if (ROI_rect.top() > this->height() - 4 * swing) {
      ROI_rect.setTop(this->height() - 4 * swing);
    }
    if (ROI_rect.width() > this->width()) {
      ROI_rect.setWidth(this->width());
    }
    if (ROI_rect.height() > this->height()) {
      ROI_rect.setHeight(this->height());
    }
    if (ROI_rect.width() < 4 * swing) {
      ROI_rect.setWidth(4 * swing);
    }
    if (ROI_rect.height() < 4 * swing) {
      ROI_rect.setHeight(4 * swing);
    }

    update();
  }

  return QLabel::mouseMoveEvent(e);
}
