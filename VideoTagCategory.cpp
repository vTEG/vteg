//
// Created by Xida on 25.06.2021.
//

#include "VideoTagCategory.h"

/**
 *
 */
VideoTagCategory::VideoTagCategory(MainWindow *mw) {
    this->mainWindow = mw;
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
        this->hotkeys.insert(tag, (Qt::Key) key);
    }
}


bool VideoTagCategory::fireHotKey(Qt::Key key){
    // Hotkey setHotkey?
    QHashIterator<VideoTag*, Qt::Key> it(*this->hotkeys);
    while (it.hasNext()){
        it.next();
        if (it.value() == key){
            this->mainWindow->addExistingTagToList(it.key());
            return true;
        }
    }
    return false;
}













