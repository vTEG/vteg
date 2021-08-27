//
// Created by tomme on 27.08.2021.
//

#ifndef VTEG_HOTKEYMANAGER_H
#define VTEG_HOTKEYMANAGER_H

#include <QtGlobal>

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
        QMap<HotKeyEntry, HotKeyAction>::iterator iterator;

        for(iterator = actionMap->begin(); iterator != actionMap->end(); iterator++) {
            if (iterator.key().equals(*entry)){
                return iterator.value();
            }
        }
        return HotKeyAction::NO_ACTION;
    }


};





#endif //VTEG_HOTKEYMANAGER_H
