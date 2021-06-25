//
// Created by Xida on 25.06.2021.
//

#include "VideoTagCategory.h"

VideoTagCategory::VideoTagCategory() {

}

void VideoTagCategory::save(QDataStream &stream) {
    stream << tagList->size();
    for (auto t : *tagList){
        t->serialize(stream);
        if (shotcuts->contains(t)){
            stream << Qt::Key::Key_F35;
        } else {
            stream << shotcuts->value(t);
        }
    }
}

void VideoTagCategory::load(QDataStream &stream) {
    int size = 0;
    stream >> size;
    for (int i = 0; i < size; i++){
        auto *tag = new VideoTag();
        tag->deserialize(stream);
        auto key = Qt::Key::Key_F35;
        // ToDo: Deserialize Qt::Key
    }
}
