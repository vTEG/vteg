//
// Created by tomme on 18.08.2021.
//

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

class SettingsWidget : public QDialog {
Q_OBJECT


public:
    explicit SettingsWidget(QWidget *parent = nullptr);

private:
    QWidget *parentWindow;
    QLineEdit *additionText;
    QComboBox *styleSelect;
    QCheckBox *showFrames;
    QPushButton *save, *cancel;
    QGridLayout *gridLayout;

    void saveSettings();
    void closeSettings();
};


#endif //VTEG_SETTINGSWIDGET_H
