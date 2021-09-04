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
    additionLabel = new QLabel("Added time when jumping");
    additionText = new QLineEdit;
    additionText->setValidator(new QRegExpValidator(QRegExp("-?[0-9]*"), additionText));
    themeLabel = new QLabel("Theme");
    themeSelect = new QComboBox;
    showFramesLabel = new QLabel("Display frames");
    showFrames = new QCheckBox;
    csvSelect = new QComboBox;
    csvpolicyLabel = new QLabel("Policy for CSV");
    save = new QPushButton("Save");
    cancel = new QPushButton("Cancel");
    
    gridLayout = new QGridLayout(this);
    setLayout(gridLayout);

    additionText->setText(QString::number(Settings::getInstance()->getAddition()));

    themeSelect->addItem("light");
    themeSelect->addItem("dark");
    themeSelect->setCurrentIndex(themeSelect->findText(Settings::getInstance()->getTheme()));

    csvSelect->addItem(",");
    csvSelect->addItem(";");
    csvSelect->setCurrentIndex(csvSelect->findText(Settings::getInstance()->getCsvPolicy()));
    
    showFrames->setChecked(Settings::getInstance()->getShowFrames());

    gridLayout->addWidget(additionLabel, 0, 0);
    gridLayout->addWidget(additionText, 0, 1);
    gridLayout->addWidget(showFramesLabel, 1,0);
    gridLayout->addWidget(showFrames, 1, 1);
    gridLayout->addWidget(themeLabel, 2, 0);
    gridLayout->addWidget(themeSelect, 2, 1);
    gridLayout->addWidget(csvpolicyLabel, 3, 0);
    gridLayout->addWidget(csvSelect, 3, 1);
    gridLayout->addWidget(save, 4, 0);
    gridLayout->addWidget(cancel, 4, 1);

    connect(save, &QPushButton::clicked, this, &SettingsWidget::saveSettings);
    connect(cancel, &QPushButton::clicked, this, &SettingsWidget::closeSettings);
}

void SettingsWidget::saveSettings() {
    Settings *ptr = Settings::getInstance();
    ptr->setAddition(additionText->displayText().toInt());
    ptr->setTheme(themeSelect->currentText().toLower());
    ptr->setShowFrames(showFrames->isChecked());
    ptr->setCsvPolicy(csvSelect->currentText());
    ptr->save();
    this->close();
}

void SettingsWidget::closeSettings() {
    this->close();
}