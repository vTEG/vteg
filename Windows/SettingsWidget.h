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

#ifndef VTEG_SETTINGSWIDGET_H
#define VTEG_SETTINGSWIDGET_H

#include "Utilities/Settings.h"

#include <QWindow>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

class SettingsWidget : public QDialog {
Q_OBJECT


public:
    explicit SettingsWidget(QWidget *parent = nullptr);

private:
    QWidget *parentWindow;
    QLabel *additionLabel, *showFramesLabel, *themeLabel, *csvpolicyLabel, *imageRecognitionPolicyLabel;
    QLineEdit *additionText, *imageRecognitionPolicyText;
    QComboBox *themeSelect, *csvSelect;
    QCheckBox *showFrames;
    QPushButton *save, *cancel;
    QGridLayout *gridLayout;

    void saveSettings();
    void closeSettings();
};


#endif //VTEG_SETTINGSWIDGET_H
