//
// Created by tomme on 17.06.2021.
//

#include "videowidget.h"

#include <QtWidgets>
#include <qvideosurfaceformat.h>

//! [0]
VideoWidget::VideoWidget(QWidget *parent)
        : QWidget(parent)
        , surface(new VideoWidgetSurface(this))
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoSystemBackground, true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    setPalette(palette);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}
//! [0]

//! [1]
VideoWidget::~VideoWidget()
{
    delete surface;
}
//! [1]

//! [2]
QSize VideoWidget::sizeHint() const
{
    return surface->surfaceFormat().sizeHint();
}
//! [2]


//! [3]
void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (surface->isActive()) {
        const QRect videoRect = surface->videoRect();

        if (!videoRect.contains(event->rect())) {
            QRegion region = event->region();
            region = region.subtracted(videoRect);

            QBrush brush = palette().window();

            for (const QRect &rect : region)
                painter.fillRect(rect, brush);
        }

        surface->paint(&painter);
    } else {
        painter.fillRect(event->rect(), palette().window());
    }
}
//! [3]

//! [4]
void VideoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    surface->updateVideoRect();
}
//! [4]

VideoWidgetSurface* VideoWidget::getSurface()
{
    return surface;
}