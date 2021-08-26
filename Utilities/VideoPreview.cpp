//
// Created by Xida on 02.07.2021.
//

#include "VideoPreview.h"

#include <utility>

VideoPreview::VideoPreview(QWidget *parent) {
    this->setParent(parent);
    this->player = new QMediaPlayer(this);

}

void VideoPreview::update(QImage image) {
    this->latestImage = std::move(image);
}

void VideoPreview::drawForeground(QPainter *painter, const QRectF &rect) {
    painter->drawPixmap(0, 0, QPixmap::fromImage(this->latestImage));
}