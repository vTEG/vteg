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

#include "VideoTagCategory.h"

#include <utility>

/**
 *
 */
VideoTagCategory::VideoTagCategory() {
    this->tagList = new QList<VideoTag*>;
    this->hotkeys = new QHash<VideoTag*, Qt::Key>;

}

/*
 *
 */
void VideoTagCategory::setHotkey(VideoTag *tag, Qt::Key key){
    if (!this->tagList->contains(tag)){
        this->tagList->append(tag);
        this->hotkeys->insert(tag, key);
    } else {
        this->hotkeys->remove(tag);
        this->hotkeys->insert(tag, key);
    }
}

void VideoTagCategory::unsetHotkey(Qt::Key key) {
    QHashIterator<VideoTag* ,Qt::Key> it(*this->hotkeys);
    while (it.hasNext()){
        it.next();
        if (it.value() == key){
            this->hotkeys->remove(it.key());
        }
    }
}


void VideoTagCategory::addTag(VideoTag *tag) {
    this->tagList->append(tag);
}

void VideoTagCategory::removeTag(VideoTag *tag){
    if (this->tagList->contains(tag))
        this->tagList->removeOne(tag);
}

QList<VideoTag*>* VideoTagCategory::getTagsByKey(Qt::Key key) {
    auto list = new QList<VideoTag*>;
    QHashIterator<VideoTag*, Qt::Key> it(*this->hotkeys);
    while (it.hasNext()){
        it.next();
        if (it.value() == key)
            list->append(it.key());
    }
    return list;
}

void VideoTagCategory::setCategoryName(QString name) {
    this->categoryName = std::move(name);
}

QString VideoTagCategory::getCategoryName() {
    return categoryName;
}


/**
 * Saves this category of video tags into a QDataStream
 * @param stream
 */
void VideoTagCategory::save(QDataStream &stream) {
    stream << tagList->size();
    for (auto t : *tagList){
        t->serialize(stream);
        if (hotkeys->contains(t)){
            stream << (qint64) Qt::Key_Escape; // Default for "No Shortcut"
        } else {
            stream << hotkeys->value(t);
        }
    }
}


/**
 * Resets the category and loads it from a given QDataStream
 * @param stream
 */
void VideoTagCategory::load(QDataStream &stream) {
    this->hotkeys->clear();

    int size = 0;
    stream >> size;
    for (int i = 0; i < size; i++){
        auto *tag = new VideoTag();
        tag->deserialize(stream);
        qint64 key;
        stream >> key;
        this->hotkeys->insert(tag, (Qt::Key) key);
    }
}















