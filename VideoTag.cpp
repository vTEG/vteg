//
// Created by Cyntho on 16.06.2021.
//

#include "VideoTag.h"

#include <utility>

/**
 * Constructor that overrides default constructor and sets the parameters for a VideoTag
 * @param title: Title of the tag
 * @param description: Description of whats happening at the tags position
 * @param image: copy of the frame at the timestamp
 * @param timestamp: timestamp of when the tag happened in milliseconds
 */
VideoTag::VideoTag(QString title, QString description, QImage image, qint64 timestamp) {
    this->title = std::move(title);
    this->description = std::move(description);
    this->image = std::move(image);
    this->timestamp = timestamp;
}

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
bool VideoTag::operator==(const VideoTag &other) {
    if(title.compare(other.getTitle()))
        if(description.compare(other.getDescription()))
            if(image == other.image)
                if(timestamp == other.timestamp)
                    return true;
   return false;

}

void VideoTag::serialize(QDataStream &stream){
    stream << title;
    stream << description;
    stream << iconPath;
    stream << colorCode;
    stream << colorCodeBackground;
    stream << timestamp;
    stream << autoStopOnJump;
}


void VideoTag::deserialize(QDataStream &stream){
    stream >> title >> description >> iconPath >> colorCode;
    stream >> colorCodeBackground >> timestamp >> autoStopOnJump;
}

QString VideoTag::toString() {
    QString retVal;
    retVal += "Title: ";
    retVal += title;
    retVal += " Timestamp: ";
    retVal += QString::number(timestamp);
    return retVal;
}
