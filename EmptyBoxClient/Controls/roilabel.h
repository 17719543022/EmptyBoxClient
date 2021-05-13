#ifndef ROILABEL_H
#define ROILABEL_H

#include <QLabel>

class ROILabel :public QLabel
{
public:
    ROILabel(QWidget *parent = nullptr);

    inline void showROI(){
        isRectShow = true;
        update();
    }

    inline void hideROI(){
        isRectShow = false;
        update();
    }

    inline QRect getROI(){return ROI_rect;}

    inline void setROI_rect(const QRect &rc){
        ROI_rect = (rc&this->rect())==QRect(0,0,0,0)?QRect(0,0,20,20):(rc&this->rect());
    }

    inline void setROI_width(const int w){
        ROI_width = w;
    }
    inline void setROI_color(const QColor &color){
        ROI_color = color;
    }

private:
    enum Direction{None, Inside, Left, Top, Right, Bottom, TopLeft, TopRight, BottonLeft, BottonRight};

    QRect ROI_rect;

    int ROI_width; //pixel of rect line width
    QColor ROI_color;

    bool isRectShow{false};

    bool isMousePressed{false};

    QPoint ptDiff_pressPos_ROIcenter; //鼠标按下时的位置与按下时ＲＯＩ中心点的差值

    Direction movePolicy{None}; //移动策略

private:
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // ROILABEL_H
