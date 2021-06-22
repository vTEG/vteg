//
// Created by Cyntho on 16.06.2021.
//

#ifndef VTEG_VIDEOTAG_H
#define VTEG_VIDEOTAG_H


#include <QString>
#include <QImage>

class VideoTag {

private:
    // Displayable information
    QString title;
    QString description;
    QImage image;

    // Coloring and icon
    QString iconPath;
    QString colorCode;
    QString colorCodeBackground;

    // Necessary information
    qint64 timestamp{};
    bool autoStopOnJump{};

public:
    VideoTag() = default;;
    VideoTag(const VideoTag &other);
    VideoTag &operator=(const VideoTag &other);

    virtual ~VideoTag();

    const QString &getTitle() const;

    void setTitle(const QString&);

    const QString &getDescription() const;

    void setDescription(const QString &description);

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


};


#endif //VTEG_VIDEOTAG_H
