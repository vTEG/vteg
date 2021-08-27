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
    styleSelect = new QComboBox;
    gridLayout = new QGridLayout;
    setLayout(gridLayout);

    additionText->setPlaceholderText(QString::number(Settings::getInstance()->getAddition()));
    styleSelect->addItem("Light");
    styleSelect->addItem("Dark");

    gridLayout->addWidget(additionText);
    gridLayout->addWidget(styleSelect);

}