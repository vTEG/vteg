//
// Created by Cyntho on 16.06.2021.
//

#ifndef VTEG_VIDEOTAG_H
#define VTEG_VIDEOTAG_H


#include <QString>

class VideoTag {

private:
    // Displayable information
    QString title;
    QString description;

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

    void setTitle(const QString &title);

    const QString &getDescription() const;

    void setDescription(const QString &description);

    const QString &getIconPath() const;

    void setIconPath(const QString &iconPath);

    const QString &getColorCode() const;

    void setColorCode(const QString &colorCode);

    const QString &getColorCodeBackground() const;

    void setColorCodeBackground(const QString &colorCodeBackground);

    qint64 getTimestamp() const;

    void setTimestamp(qint64 timestamp);

    bool isAutoStopOnJump() const;

    void setAutoStopOnJump(bool autoStopOnJump);
};


#endif //VTEG_VIDEOTAG_H
