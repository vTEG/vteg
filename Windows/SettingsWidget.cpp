//
// Created by tomme on 18.08.2021.
//

#include "SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent): QDialog(parent) {
    this->parentWindow = parent;

    // Modal := Window is forced to be focused window
    setModal(true);
    setWindowTitle(tr("Settings"));
    setMinimumSize(200, 200);

    additionText = new QLineEdit;
    gridLayout = new QGridLayout;
    setLayout(gridLayout);

    additionText->setPlaceholderText(QString::number(Settings::getInstance()->getAddition()));

    gridLayout->addWidget(additionText);

}