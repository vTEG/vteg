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

#ifndef VTEG_VIDEOWIDGETSURFACE_H
#define VTEG_VIDEOWIDGETSURFACE_H

#include <QVideoSink>
#include <QImage>
#include <QRect>
#include <QVideoFrame>
#include <QMediaPlayer>

class VideoWidgetSurface : public QVideoSink
{
Q_OBJECT

public:
    explicit VideoWidgetSurface(QWidget *widget, QObject *parent = nullptr);

    ~VideoWidgetSurface() override;

    QList<QVideoFrameFormat::PixelFormat> supportedPixelFormats(
            QVideoFrame::HandleType handleType = QVideoFrame::NoHandle) const;
    bool isFormatSupported(const QVideoFrame &format) const;

    bool start(const QVideoFrameFormat &format);
    void stop();

    bool present(const QVideoFrame &frame);

    [[nodiscard]] QRect videoRect() const { return targetRect; }
    void updateVideoRect();

    void paint(QPainter *painter);
    QImage getLastFrame();

private:
    QWidget *widget;
    QImage::Format imageFormat;
    QRect targetRect;
    QRect sourceRect;
    QVideoFrame currentFrame;

    QImage lastSavedImage;
};

#endif //VTEG_VIDEOWIDGETSURFACE_H
