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
    this->imageIsStatic = false;
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
    return imagePath;
}

void VideoTag::setIconPath(const QString &setIconPath) {
    VideoTag::imagePath = setIconPath;
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


bool VideoTag::isImageIsStatic() const {
    return imageIsStatic;
}


VideoTag::VideoTag(const VideoTag &other) {

}

VideoTag &VideoTag::operator=(const VideoTag &other) {
    if (this == &other)
        return *this;

    title = other.getTitle();
    description = other.getDescription();
    imagePath = other.getIconPath();
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
    stream << imagePath;
    stream << colorCode;
    stream << colorCodeBackground;
    stream << timestamp;
    stream << autoStopOnJump;
}


void VideoTag::deserialize(QDataStream &stream){
    stream >> title >> description >> imagePath >> colorCode;
    stream >> colorCodeBackground >> timestamp >> autoStopOnJump;
}

QString VideoTag::toString() {
    QString retVal;
    retVal += "Title: ";
    retVal += title;
    retVal += " Timestamp: ";
    retVal += QString::number(timestamp);
    retVal += " Description: ";
    retVal += description;
    return retVal;
}

void VideoTag::setImageIsStatic(bool imageIsStatic) {
    this->imageIsStatic = imageIsStatic;
}
