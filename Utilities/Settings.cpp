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

#include "Settings.h"
Settings* Settings::instance = nullptr;
HotkeyManager* HotkeyManager::instance = nullptr;

/**
 * Deserializing our settings file in case there is one
 */
Settings::Settings() : additionToTag(0), showFrames(false), theme("dark"), csvPolicy(";"), imageRecognitionConfidence(0.7) {}

/**
 * Deleting the Settings object
 */
Settings::~Settings() {
    delete this;
}

/**
 * Serializing the settings object into a file for persistence
 * @return if saving was successful
 */
bool Settings::save() {
    QFile file(fileName);
    qDebug() << "Starting save";
    QDataStream outStream(&file);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Could not open file at path " + fileName;
        return false;
    }
    outStream << *(getInstance());
    file.flush();
    file.close();
    return true;
}

/**
 * Deserializing the settings file into our object
 * @return if saving was successful
 */
bool Settings::load() {
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Could not open file at path " + fileName;
        return false;
    }
    QDataStream inStream(&file);
    inStream >> *(getInstance());
    
    qDebug() << "Loaded settings";

    file.flush();
    file.close();
    return true;
}