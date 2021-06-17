//
// Created by tomme on 17.06.2021.
//

#ifndef VTEG_VIDEOWIDGETSURFACE_H
#define VTEG_VIDEOWIDGETSURFACE_H

#include <QAbstractVideoSurface>
#include <QImage>
#include <QRect>
#include <QVideoFrame>

class VideoWidgetSurface : public QAbstractVideoSurface
{
Q_OBJECT

public:
    explicit VideoWidgetSurface(QWidget *widget, QObject *parent = nullptr);

    ~VideoWidgetSurface() override;

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const override;

    bool start(const QVideoSurfaceFormat &format) override;
    void stop() override;

    bool present(const QVideoFrame &frame) override;

    QRect videoRect() const { return targetRect; }
    void updateVideoRect();

    void paint(QPainter *painter);

private:
    QWidget *widget;
    QImage::Format imageFormat;
    QRect targetRect;
    QRect sourceRect;
    QVideoFrame currentFrame;
};

#endif //VTEG_VIDEOWIDGETSURFACE_H
