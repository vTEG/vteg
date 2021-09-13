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

#ifndef VTEG_SETTINGSWINDOW_H
#define VTEG_SETTINGSWINDOW_H


#include <QDialog>
#include <QDialogButtonBox>

#include <QGroupBox>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>

#include <QLabel>

using json = nlohmann::json;

class SettingsWindow : public QDialog {

    Q_OBJECT

private slots:
    // Window handling
    void dialogFinished(int);

    // MenuBar
    void onSaveActionClicked();
    void onExitClicked();
    void onRestoreDefaultClicked();

    // Buttons
    // ToDo

private:
    QWidget *parentWindow;
    QDialogButtonBox *confirmButtonBox;

    QGroupBox *groupBox;
    QVBoxLayout *mainLayout;

    QMenuBar *menuBar;
    QAction *saveAction;
    QAction *restoreDefaultAction;

    QPushButton *btnConfirm;

    QLabel *lblHeader;

    void createMenu();
    void createGridGroupBox();


    void loadSettings();
    void saveSettings();

public:

    explicit SettingsWindow(QWidget *parent);




};


#endif //VTEG_SETTINGSWINDOW_H
