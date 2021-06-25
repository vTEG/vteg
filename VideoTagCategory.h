//
// Created by Xida on 25.06.2021.
//

#ifndef VTEG_VIDEOTAGCATEGORY_H
#define VTEG_VIDEOTAGCATEGORY_H

#include "VideoTag.h"
#include <QList>
#include <QHash>
#include <QDataStream>

class VideoTagCategory {

private:
    QString categoryName;
    QList<VideoTag*> *tagList;
    QHash<VideoTag*, Qt::Key> *shotcuts;


public:
    explicit VideoTagCategory();
    ~VideoTagCategory() = default;

    void save(QDataStream &stream);
    void load(QDataStream &stream);

};


#endif //VTEG_VIDEOTAGCATEGORY_H
