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

#ifndef VTEG_SETTINGS_H
#define VTEG_SETTINGS_H

#include "HotkeyManager.h"

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
     * Outstream operator for QDataStreams when writing Settings objects
     * @param out outstream
     * @param s settings object
     * @return outstream
     */
    friend QDataStream& operator<<(QDataStream &out, const Settings &s) {
        Settings *ptr = Settings::getInstance();
        out << ptr->additionToTag << ptr->showFrames << ptr->csvPolicy << ptr->theme << ptr->imageRecognitionConfidence;
        return out;
    }

    /**
     * Instream operator for QDataStream when reading from a file into a settings object
     * @param in instream
     * @param s settings object
     * @return instream
     */
    friend QDataStream& operator>>(QDataStream &in, const Settings &s){
        Settings *ptr = Settings::getInstance();
        in >> ptr->additionToTag >> ptr->showFrames >> ptr->csvPolicy >> ptr->theme >> ptr->imageRecognitionConfidence;
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

    QString getTheme() {
        return theme;
    }

    void setTheme(QString st) {
        theme = std::move(st);
    }

    QString getCsvPolicy() const {
        return csvPolicy;
    }
    void setCsvPolicy(QString q) {
        csvPolicy = q;
    }

    float getImageRecognitionConfidence() const {
        return imageRecognitionConfidence;
    }
    void setImageRecognitionConfidence(float f) {
        imageRecognitionConfidence = f;
    }

private:
    Settings();
    ~Settings();

    qint64 additionToTag;
    bool showFrames;
    QString theme, csvPolicy;
    float imageRecognitionConfidence;

    QString defaultTagCategory; // Fußball/Handball/etc.
    // letztes Projekt automatisch beim Starten laden?
    /*
     * <"Key_CreateTag", 64>
     */



    static Settings* instance;
    QString fileName = "settings.dat";
};


#endif //VTEG_SETTINGS_H
