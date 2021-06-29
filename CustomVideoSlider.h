//
// Created by Xida on 28.06.2021.
//

#ifndef VTEG_CUSTOMVIDEOSLIDER_H
#define VTEG_CUSTOMVIDEOSLIDER_H

#include <QDebug>
#include <QSlider>
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QPaintEvent>
#include <QLabel>


class CustomVideoSlider : public QSlider {
    Q_OBJECT

private:
    bool mouseDown;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

public:
    explicit CustomVideoSlider(QWidget *parent) {
        this->setParent(parent);
        setFixedHeight(5);
        setMouseTracking(true);
        mouseDown = false;
    }

    ~CustomVideoSlider() override = default;

    Q_SIGNALS:
    void mouseMoved(int step);

public slots:
    void onMouseHover();
};


#endif //VTEG_CUSTOMVIDEOSLIDER_H
