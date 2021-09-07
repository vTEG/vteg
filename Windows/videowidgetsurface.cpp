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

#include "videowidgetsurface.h"

#include <QtWidgets>
#include <qabstractvideosurface.h>
#include <qvideosurfaceformat.h>

VideoWidgetSurface::VideoWidgetSurface(QWidget *widget, QObject *parent)
        : QAbstractVideoSurface(parent)
        , widget(widget)
        , imageFormat(QImage::Format_Invalid)
{
}

VideoWidgetSurface::~VideoWidgetSurface() = default;

//! [0]
QList<QVideoFrame::PixelFormat> VideoWidgetSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}
//! [0]

//! [1]
bool VideoWidgetSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid
           && !size.isEmpty()
           && format.handleType() == QAbstractVideoBuffer::NoHandle;
}
//! [1]

//! [2]
bool VideoWidgetSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {
        this->imageFormat = imageFormat;
        sourceRect = format.viewport();

        QAbstractVideoSurface::start(format);

        widget->updateGeometry();
        updateVideoRect();

        return true;
    } else {
        return false;
    }
}
//! [2]

//! [3]
void VideoWidgetSurface::stop()
{
    currentFrame = QVideoFrame();
    targetRect = QRect();

    QAbstractVideoSurface::stop();

    widget->update();
}
//! [3]

//! [4]
bool VideoWidgetSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
        || surfaceFormat().frameSize() != frame.size()) {
        setError(IncorrectFormatError);
        stop();

        return false;
    } else {
        currentFrame = frame;

        QImage image(
                currentFrame.bits(),
                currentFrame.width(),
                currentFrame.height(),
                currentFrame.bytesPerLine(),
                imageFormat);

        widget->repaint(targetRect);

        return true;
    }
}
//! [4]

//! [5]
void VideoWidgetSurface::updateVideoRect()
{
    QSize size = surfaceFormat().sizeHint();
    size.scale(widget->size().boundedTo(size), Qt::KeepAspectRatio);

    targetRect = QRect(QPoint(0, 0), size);
    targetRect.moveCenter(widget->rect().center());
}
//! [5]

//! [6]
void VideoWidgetSurface::paint(QPainter *painter)
{
    if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        const QTransform oldTransform = painter->transform();

        if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
            painter->scale(1, -1);
            painter->translate(0, -widget->height());
        }

        QImage image(
                currentFrame.bits(),
                currentFrame.width(),
                currentFrame.height(),
                currentFrame.bytesPerLine(),
                imageFormat);

        lastSavedImage = image;


        painter->drawImage(targetRect, image, sourceRect);

        painter->setTransform(oldTransform);

        currentFrame.unmap();
    }
}

QImage VideoWidgetSurface::getLastFrame() {
    return lastSavedImage;
}
