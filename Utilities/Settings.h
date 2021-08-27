//
// Created by tomme on 26.08.2021.
//

#ifndef VTEG_SETTINGS_H
#define VTEG_SETTINGS_H

#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QFileInfo>
#include <utility>

class Settings {
public:
    /**
     * returning our instance if there is one already and if not, creating one
     * @return the singleton instance
     */
    static Settings* getInstance() {
        if(!instance) {
            instance = new Settings();
            if(QFileInfo::exists("settings.dat"))
                instance->load();
            else
                instance->save();
        }
        return instance;
    }

    /**
     * deleting functions that are not needed in a singleton pattern so we're save
     */
    Settings(const Settings&) = delete;
    Settings(Settings&) = delete;

    bool save();
    bool load();

    /**
     * Overwrites the outstream operator for QDataStreams when writing Settings objects
     * @param out outstream
     * @param s settings object
     * @return outstream
     */
    friend QDataStream& operator<<(QDataStream &out, const Settings &s) {
        Settings *ptr = Settings::getInstance();
        out << ptr->additionToTag << ptr->showFrames << ptr->style;
        return out;
    }
    friend QDataStream& operator>>(QDataStream &in, const Settings &s){
        Settings *ptr = Settings::getInstance();
        in >> ptr->additionToTag >> ptr->showFrames >> ptr->style;
        return in;
    }

    qint64 getAddition() const {
        return additionToTag;
    }

    void setAddition(qint64 add) {
        additionToTag = add;
    }

    bool getShowFrames() {
        return showFrames;
    }

    void setShowFrames(bool s) {
        showFrames = s;
    }

    QString getStyle() {
        return style;
    }

    void setStyle(QString st) {
        style = std::move(st);
    }

private:
    Settings();
    ~Settings();

    qint64 additionToTag;
    bool showFrames;
    QString style;

    static Settings* instance;
    QString fileName = "settings.dat";
};


#endif //VTEG_SETTINGS_H
