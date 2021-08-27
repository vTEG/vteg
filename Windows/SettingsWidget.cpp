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

    /**
     * Creating the objects necessary for displaying the settings widget
     */
    additionText = new QLineEdit;
    additionText->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), additionText));
    styleSelect = new QComboBox;
    gridLayout = new QGridLayout;
    save = new QPushButton("Save");
    cancel = new QPushButton("Cancel");

    setLayout(gridLayout);

    additionText->setText(QString::number(Settings::getInstance()->getAddition()));

    styleSelect->addItem("light");
    styleSelect->addItem("dark");
    styleSelect->setCurrentIndex(styleSelect->findText(Settings::getInstance()->getStyle()));

    gridLayout->addWidget(additionText);
    gridLayout->addWidget(styleSelect);
    gridLayout->addWidget(save);
    gridLayout->addWidget(cancel);

    connect(save, &QPushButton::clicked, this, &SettingsWidget::saveSettings);
    connect(cancel, &QPushButton::clicked, this, &SettingsWidget::closeSettings);
}

void SettingsWidget::saveSettings() {
    Settings *ptr = Settings::getInstance();
    ptr->setAddition(additionText->displayText().toInt());
    ptr->setStyle(styleSelect->currentText().toLower());
    ptr->save();
    this->close();
}

void SettingsWidget::closeSettings() {
    this->close();
}