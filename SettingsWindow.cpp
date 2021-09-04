//
// Created by Xida on 03.08.2021.
//

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
