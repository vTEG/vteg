//
// Created by Xida on 25.06.2021.
//

#ifndef VTEG_VIDEOTAGCATEGORY_H
#define VTEG_VIDEOTAGCATEGORY_H

#include "Utilities/VideoTag.h"
#include <QDebug>
#include <QList>
#include <QHash>
#include <QDataStream>

class VideoTagCategory {

private:
    QString categoryName;
    QList<VideoTag *> *tagList;
    QHash<VideoTag *, Qt::Key> *hotkeys;


public:
    explicit VideoTagCategory();
    ~VideoTagCategory() = default;

    void setHotkey(VideoTag *tag, Qt::Key key);
    void unsetHotkey(Qt::Key key);

    void addTag(VideoTag *tag);
    void removeTag(VideoTag *tag);

    QList<VideoTag*>* getTagsByKey(Qt::Key key);
    void setCategoryName(QString name);
    QString getCategoryName();

    void save(QDataStream &stream);
    void load(QDataStream &stream);


};




#endif //VTEG_VIDEOTAGCATEGORY_H
