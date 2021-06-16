//
// Created by Cyntho on 16.06.2021.
//

#include "VideoTag.h"


VideoTag::~VideoTag() = default;

const QString &VideoTag::getTitle() const {
    return title;
}

void VideoTag::setTitle(const QString &title) {
    VideoTag::title = title;
}

const QString &VideoTag::getDescription() const {
    return description;
}

void VideoTag::setDescription(const QString &description) {
    VideoTag::description = description;
}

const QString &VideoTag::getIconPath() const {
    return iconPath;
}

void VideoTag::setIconPath(const QString &iconPath) {
    VideoTag::iconPath = iconPath;
}

const QString &VideoTag::getColorCode() const {
    return colorCode;
}

void VideoTag::setColorCode(const QString &colorCode) {
    VideoTag::colorCode = colorCode;
}

const QString &VideoTag::getColorCodeBackground() const {
    return colorCodeBackground;
}

void VideoTag::setColorCodeBackground(const QString &colorCodeBackground) {
    VideoTag::colorCodeBackground = colorCodeBackground;
}

qint64 VideoTag::getTimestamp() const {
    return timestamp;
}

bool VideoTag::isAutoStopOnJump() const {
    return autoStopOnJump;
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
