//
// Created by tomme on 26.08.2021.
//

#include "Settings.h"
Settings* Settings::instance = nullptr;

/**
 * Deserializing our settings file in case there is one
 */
Settings::Settings() : additionToTag(8), showFrames(false), style("dark") {}

/**
 * Deleting the Settings object
 */
Settings::~Settings() {
    delete this;
}

/**
 * Serializing the settings object into a file for persistence
 * @param file the file we should save to
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