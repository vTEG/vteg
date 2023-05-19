/*
    Copyright (C) 2021, Tom-Niklas Metz, Malte Königstein

    This file is part of vTEG.

    vTEG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    vTEG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with vTEG.  If not, see <https://www.gnu.org/licenses/>.

    vTEG  Copyright (C) 2021, Tom-Niklas Metz, Malte Königstein
    This program comes with ABSOLUTELY NO WARRANTY.
    This is free software, and you are welcome to redistribute it
    under certain conditions.
*/

#include "videowidget.h"

#include <QtWidgets>
#include <QVideoFrameFormat>

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
//    return surface->surfaceFormat().sizeHint();
    return surface->videoSize();
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