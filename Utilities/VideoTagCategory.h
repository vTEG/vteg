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
