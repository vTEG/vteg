//
// Created by Cyntho on 16.06.2021.
//

#include "VideoTag.h"


VideoTag::~VideoTag() = default;

const QString &VideoTag::getTitle() const {
    return title;
}

void VideoTag::setTitle(const QString &setTitle) {
    VideoTag::title = setTitle;
}

const QString &VideoTag::getDescription() const {
    return description;
}

const QImage &VideoTag::getImage() const {
    return image;
}

void VideoTag::setImage(const QImage &setImage) {
    VideoTag::image = setImage;
}

void VideoTag::setDescription(const QString &setDescription) {
    VideoTag::description = setDescription;
}

const QString &VideoTag::getIconPath() const {
    return iconPath;
}

void VideoTag::setIconPath(const QString &setIconPath) {
    VideoTag::iconPath = setIconPath;
}

const QString &VideoTag::getColorCode() const {
    return colorCode;
}

void VideoTag::setColorCode(const QString &setColorCode) {
    VideoTag::colorCode = setColorCode;
}

const QString &VideoTag::getColorCodeBackground() const {
    return colorCodeBackground;
}

void VideoTag::setColorCodeBackground(const QString &setColorCodeBackground) {
    VideoTag::colorCodeBackground = setColorCodeBackground;
}

qint64 VideoTag::getTimestamp() const {
    return timestamp;
}

void VideoTag::setTimestamp(qint64 setTimestamp) {
    VideoTag::timestamp = setTimestamp;
}

bool VideoTag::isAutoStopOnJump() const {
    return autoStopOnJump;
}

void VideoTag::setAutoStopOnJump(bool setAutoStop) {
    VideoTag::autoStopOnJump = setAutoStop;
}

VideoTag::VideoTag(const VideoTag &other) {

}

VideoTag &VideoTag::operator=(const VideoTag &other) {
    if (this == &other)
        return *this;

    title = other.getTitle();
    description = other.getDescription();
    iconPath = other.getIconPath();
    colorCode = other.getColorCode();
    colorCodeBackground = other.getColorCodeBackground();
    timestamp = other.getTimestamp();
    autoStopOnJump = other.isAutoStopOnJump();
    return *this;
}
