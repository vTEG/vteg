#include "CustomVideoSlider.h"

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

    QPainterPath tagPaths;

    if (tags != nullptr){
        for (auto t : *tags){
            p = static_cast<float>(t->getTimestamp()) / static_cast<float>(maximum());
            border = static_cast<int>(static_cast<float>(width()) * p);
            if (p != 0){
                tagPaths.addRect(QRect(border-2, 0, 4, height()));
            } else {
                tagPaths.addRect(QRect(0, 0, 2, height()));
            }
        }
    }
    painter.fillPath(tagPaths, Qt::blue);
}

void CustomVideoSlider::mouseMoveEvent(QMouseEvent *event){

    // Handle dragging of progress bar
    if (mouseDown){
        mousePressEvent(event);
    } else {
        emit CustomVideoSlider::mouseHover(event->x());
    }
}

void CustomVideoSlider::mousePressEvent(QMouseEvent *event) {
    mouseDown = true;
    int mouseLeft = event->pos().x();

    float p = static_cast<float>(mouseLeft) / static_cast<float>(width());
    int pos = static_cast<float>(maximum()) * p;
    setSliderPosition(pos);

    // Important: Emit Signal so that MainWindow can set values to QMediaPlayer and Timestamp label
    emit QSlider::sliderMoved(pos);
}

void CustomVideoSlider::mouseReleaseEvent(QMouseEvent *ev) {
    mousePressEvent(ev);
    mouseDown = false;
}
