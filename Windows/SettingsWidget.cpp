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
    additionText->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9]*"), additionText));
    themeLabel = new QLabel("Theme (Restart needed)");
    themeSelect = new QComboBox;
    showFramesLabel = new QLabel("Display frames");
    showFrames = new QCheckBox;
    csvSelect = new QComboBox;
    csvpolicyLabel = new QLabel("Policy for CSV");
    save = new QPushButton("Save");
    cancel = new QPushButton("Cancel");
    imageRecognitionPolicyLabel = new QLabel("Percentage of confidence for analyzing video");
    imageRecognitionPolicyText = new QLineEdit;
    imageRecognitionPolicyText->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9]*"), imageRecognitionPolicyText));
    
    gridLayout = new QGridLayout(this);
    setLayout(gridLayout);

    additionText->setText(QString::number(Settings::getInstance()->getAddition()));
    imageRecognitionPolicyText->setText(QString::number(Settings::getInstance()->getImageRecognitionConfidence() * 100));

    themeSelect->addItem("classic");
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
    gridLayout->addWidget(imageRecognitionPolicyLabel, 4, 0);
    gridLayout->addWidget(imageRecognitionPolicyText, 4, 1);
    gridLayout->addWidget(save, 5, 0);
    gridLayout->addWidget(cancel, 5, 1);

    connect(save, &QPushButton::clicked, this, &SettingsWidget::saveSettings);
    connect(cancel, &QPushButton::clicked, this, &SettingsWidget::closeSettings);
}

void SettingsWidget::saveSettings() {
    Settings *ptr = Settings::getInstance();
    ptr->setAddition(additionText->displayText().toInt());
    ptr->setTheme(themeSelect->currentText().toLower());
    ptr->setShowFrames(showFrames->isChecked());
    ptr->setCsvPolicy(csvSelect->currentText());
    ptr->setImageRecognitionConfidence(imageRecognitionPolicyText->displayText().toFloat() / 100);
    ptr->save();
    this->close();
}

void SettingsWidget::closeSettings() {
    this->close();
}