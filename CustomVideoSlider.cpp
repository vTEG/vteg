#include "CustomVideoSlider.h"
#include <iostream>

void CustomVideoSlider::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPainterPath pathAlreadyPlayed;
    QPainterPath pathBackground;

    painter.setRenderHint(QPainter::Antialiasing);

    // Calculate width of progress bar
    float p = static_cast<float>(value()) / static_cast<float>(maximum());
    int border = static_cast<int>(static_cast<float>(width()) * p);

    pathAlreadyPlayed.addRect(QRect(0, 0, border, height()));
    pathBackground.addRect(QRect(0, 0, width(), height()));

    painter.fillPath(pathBackground, Qt::gray);
    painter.fillPath(pathAlreadyPlayed, Qt::red);
    painter.drawPath(pathAlreadyPlayed);
}

void CustomVideoSlider::mouseMoveEvent(QMouseEvent *event){

    // Handle dragging of progress bar
    if (mouseDown){
        mousePressEvent(event);
    }

    // ToDo: somehow display a preview
}

void CustomVideoSlider::mousePressEvent(QMouseEvent *event) {
    mouseDown = true;
    int mouseLeft = event->pos().x();

    float p = static_cast<float>(mouseLeft) / static_cast<float>(width());
    int pos = static_cast<float>(maximum()) * p;
    setSliderPosition(pos);
}

void CustomVideoSlider::mouseReleaseEvent(QMouseEvent *ev) {
    mousePressEvent(ev);
    mouseDown = false;
}