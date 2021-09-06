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

#include "SettingsWindow.h"


SettingsWindow::SettingsWindow(QWidget *parent) {
    this->parentWindow = parent;
    this->mainLayout = new QVBoxLayout;

    this->setLayout(mainLayout);
    this->setMinimumSize(700, 500);
    this->setModal(true);
    this->setWindowTitle(tr("Vteg - Settings"));

    createMenu();
    createGridGroupBox();

    loadSettings();
}

void SettingsWindow::createMenu() {
    menuBar = new QMenuBar;
    saveAction = menuBar->addAction(tr("&Save"));
    restoreDefaultAction = menuBar->addAction(tr("&Restore Defaults"));

    mainLayout->setMenuBar(menuBar);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(onSaveActionClicked()));
    connect(restoreDefaultAction, SIGNAL(triggered()), this, SLOT(onRestoreDefaultClicked()));
}

void SettingsWindow::createGridGroupBox() {
    groupBox = new QGroupBox(tr("Grid Layout")); // todo rename
    auto *layout = new QGridLayout();
    lblHeader = new QLabel(tr("Test"));




}
