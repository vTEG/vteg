//
// Created by Xida on 03.08.2021.
//

#ifndef VTEG_SETTINGSWINDOW_H
#define VTEG_SETTINGSWINDOW_H


#include <QDialog>
#include <QDialogButtonBox>

#include <QGroupBox>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>

#include <libraries/json.hpp>
#include <QLabel>

using json = nlohmann::json;

class SettingsWindow : public QDialog {

    Q_OBJECT

private slots:
    // Window handling
    void dialogFinished(int);

    // MenuBar
    void onSaveActionClicked();
    void onExitClicked();
    void onRestoreDefaultClicked();

    // Buttons
    // ToDo

private:
    QWidget *parentWindow;
    QDialogButtonBox *confirmButtonBox;

    QGroupBox *groupBox;
    QVBoxLayout *mainLayout;

    QMenuBar *menuBar;
    QAction *saveAction;
    QAction *restoreDefaultAction;

    QPushButton *btnConfirm;

    QLabel *lblHeader;

    void createMenu();
    void createGridGroupBox();


    void loadSettings();
    void saveSettings();

public:

    explicit SettingsWindow(QWidget *parent);




};


#endif //VTEG_SETTINGSWINDOW_H
