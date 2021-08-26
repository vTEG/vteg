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
#include <QGridLayout>

class SettingsWidget : public QDialog {
Q_OBJECT


public:
    explicit SettingsWidget(QWidget *parent = nullptr);

private:
    QWidget *parentWindow;
    QLineEdit *additionText;
    QGridLayout *gridLayout;
};


#endif //VTEG_SETTINGSWIDGET_H
