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
#include <QList>

#include "VideoTag.h"


class CustomVideoSlider : public QSlider {
    Q_OBJECT

private:
    bool mouseDown;
    QList<VideoTag*> *tags;

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
        tags = nullptr;
    }

    explicit CustomVideoSlider(QWidget *parent, QList<VideoTag*> *tags) {
        this->setParent(parent);
        setFixedHeight(10);
        setMouseTracking(true);
        mouseDown = false;
        this->tags = tags;
    }

    ~CustomVideoSlider() override = default;

Q_SIGNALS:
    void mouseHover(int position);

};


#endif //VTEG_CUSTOMVIDEOSLIDER_H
