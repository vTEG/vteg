//
// Created by Xida on 02.07.2021.
//

#ifndef VTEG_VIDEOPREVIEW_H
#define VTEG_VIDEOPREVIEW_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QPixmap>


class VideoPreview : public QGraphicsView {

private:
    QImage latestImage;
    QMediaPlayer *player;

public:
    explicit VideoPreview(QWidget *parent);

public slots:
    void update(QImage image);

protected:
    void drawForeground(QPainter *painter, const QRectF &rect) override;

};




#endif //VTEG_VIDEOPREVIEW_H
