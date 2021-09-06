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

#ifndef VTEG_VIDEOTAG_H
#define VTEG_VIDEOTAG_H


#include <QString>
#include <QImage>
#include <QFile>

class VideoTag {

private:
    // Displayable information
    QString title;
    QString description;
    QImage image;
    bool imageIsStatic{};

    // Coloring and icon
    QString imagePath;
    QString colorCode;
    QString colorCodeBackground;

    // Necessary information
    qint64 timestamp{};
    bool autoStopOnJump{};

public:
    VideoTag() = default;
    VideoTag(QString, QString, QImage, qint64);
    VideoTag(const VideoTag &other);
    VideoTag &operator=(const VideoTag &other);
    bool operator==(const VideoTag&);


    virtual ~VideoTag();

    const QString &getTitle() const;

    void setTitle(const QString&);

    const QString &getDescription() const;

    void setDescription(const QString &description);

    bool isImageIsStatic() const;

    void setImageIsStatic(bool imageIsStatic);

    const QImage &getImage() const;

    void setImage(const QImage&);

    const QString &getIconPath() const;

    void setIconPath(const QString&);

    const QString &getColorCode() const;

    void setColorCode(const QString&);

    const QString &getColorCodeBackground() const;

    void setColorCodeBackground(const QString&);

    qint64 getTimestamp() const;

    void setTimestamp(qint64);

    bool isAutoStopOnJump() const;

    void setAutoStopOnJump(bool);

    // Serialization
    void serialize(QDataStream &stream);
    void deserialize(QDataStream &stream);

    // For testing purposes
    QString toString();
};


#endif //VTEG_VIDEOTAG_H
