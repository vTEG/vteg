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

class HotKeyActionWrapper : QObject {
    Q_OBJECT
public:
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
    Q_ENUM(HotKeyAction)
};


class HotKeyManager {
    Q_OBJECT

private:
    static HotKeyManager *instance;
    QMap<QKeySequence*, HotKeyActionWrapper::HotKeyAction> *hotkeys;
    QMap<QString, HotKeyActionWrapper::HotKeyAction> map = {
        {"NO_ACTION", HotKeyActionWrapper::NO_ACTION},
        {"OPEN_FILE", HotKeyActionWrapper::OPEN_FILE},
        {"CLOSE_FILE", HotKeyActionWrapper::CLOSE_FILE},
        {"SAVE_FILE", HotKeyActionWrapper::SAVE_FILE},
        {"SAVE_FILE_AS", HotKeyActionWrapper::SAVE_FILE_AS},
        {"ADD_TAG", HotKeyActionWrapper::ADD_TAG},
        {"REMOVE_TAG", HotKeyActionWrapper::REMOVE_TAG},
        {"EDIT_TAG", HotKeyActionWrapper::EDIT_TAG}
    };

    HotKeyManager() {
        hotkeys = new QMap<QKeySequence*, HotKeyActionWrapper::HotKeyAction>();
    };
    ~HotKeyManager(){
        delete hotkeys;
    };


public:
    static HotKeyManager* getInstance() {
        if(!instance) {
            instance = new HotKeyManager();
        }
        return instance;
    }
    HotKeyManager(const HotKeyManager&) = delete;
    HotKeyManager(HotKeyManager&) = delete;

    HotKeyActionWrapper::HotKeyAction getAction(QKeySequence &sequence){
        QMap<QKeySequence*, HotKeyActionWrapper::HotKeyAction>::iterator it;
        for (it = hotkeys->begin(); it != hotkeys->end(); ++it){
            if (sequence.matches(*it.key())){
                return it.value();
            }
        }
        // Default return for no combination found
        return HotKeyActionWrapper::HotKeyAction::NO_ACTION;
    }

    bool sub(QKeySequence &sequence, HotKeyActionWrapper::HotKeyAction action){
        if (!hotkeys->contains(&sequence)){
            hotkeys->insert(&sequence, action);
            return true;
        }
        return false;
    }

    bool unsub(QKeySequence &sequence){
        return hotkeys->remove(&sequence) > 0;
    }
};

QDataStream& operator>>(QDataStream &in, const HotKeyActionWrapper::HotKeyAction &action){

}


// Operator overloading for saving/loading Hotkey settings
QDataStream& operator>>(QDataStream &in, const HotKeyManager &manager){
    HotKeyManager *ptr = HotKeyManager::getInstance();
    int size;
    in >> size;

    for (int i = 0; i < size; i++){
        QKeySequence s;
        in >> s;
        HotKeyActionWrapper::HotKeyAction action;
        in >> action;
    }
}

#endif //VTEG_HOTKEYMANAGER_H
