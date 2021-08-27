//
// Created by tomme on 17.06.2021.
//


#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "videowidgetsurface.h"

#include <QWidget>

//! [0]
class VideoWidget : public QWidget
{
Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget() override;

    QAbstractVideoSurface *videoSurface() const { return surface; }

    QSize sizeHint() const override;

    VideoWidgetSurface* getSurface();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    VideoWidgetSurface *surface;

};
//! [0]

#endif // VIDEOWIDGET_H