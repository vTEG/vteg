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

#ifndef VTEG_HOTKEYMANAGER_H
#define VTEG_HOTKEYMANAGER_H

#include <QtGlobal>
#include <QMap>

enum HotKeyAction {
    NO_ACTION,
    OPEN_FILE,
    CLOSE_FILE,
    SAVE_FILE,
    SAVE_FILE_AS,
    ADD_TAG,
    REMOVE_TAG,
    EDIT_TAG
};

class HotKeyEntry {
private:
    qint64 key;
    bool altModifier;
    bool ctrlModifier;
    bool shiftModifier;

public:
    HotKeyEntry(qint64 key, bool altModifier = false, bool ctrlModifier = false, bool shiftModifier = false) : key{key}, altModifier{altModifier}, ctrlModifier{ctrlModifier}, shiftModifier{shiftModifier}{}
    ~HotKeyEntry() = default;

    bool equals(HotKeyEntry &other) const{
        return (key == other.key && altModifier == other.altModifier && ctrlModifier == other.ctrlModifier && shiftModifier == other.shiftModifier);
    }
};

class HotkeyManager {

private:
    QMap<HotKeyEntry, HotKeyAction> *actionMap;
    static HotkeyManager *instance;


public:
    static HotkeyManager* getInstance() {
        if(!instance) {
            instance = new HotkeyManager();
        }
        return instance;
    }

    HotKeyAction getAction(HotKeyEntry *entry){
        for(auto it = actionMap->constBegin(); it != actionMap->constEnd(); it++) {
            if (it.key().equals(*entry)){
                return it.value();
            }
        }
        return HotKeyAction::NO_ACTION;
    }


};





#endif //VTEG_HOTKEYMANAGER_H
