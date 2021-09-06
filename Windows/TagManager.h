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

#ifndef VTEG_TAGMANAGER_H
#define VTEG_TAGMANAGER_H

#include "Utilities/VideoTagCategory.h"
#include "Utilities/CustomVideoSlider.h"

#include <QWindow>
#include <QWidget>
#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>
#include <QComboBox>
#include <QMouseEvent>

#include <QFileDialog>
#include <QMessageBox>


class TagManager : public QDialog {

    Q_OBJECT

private slots:
    // Window handling
    void dialogFinished(int);

    // MenuBar
    void onOpenActionClicked();
    void onSaveActionClicked();
    void onSaveAsActionClicked();
    void onExitClicked();
    void onOptionsActionClicked();

    // Buttons
    void onBtnFindCategoryImageClicked();
    void onBtnAddCategoryClicked();
    void onBtnRemoveCategoryClicked();

private:
    QWidget *parentWindow;
    QDialogButtonBox *buttonBox{};

    QGroupBox *groupBox{};
    QVBoxLayout *mainLayout;

    QMenuBar *menuBar{};
    QMenu *fileMenu{};
    QAction *optionsAction{};
    QAction *openAction{};
    QAction *saveAction{};
    QAction *saveAsAction{};
    QAction *exitAction{};

    QPushButton *btnAddCategory{};
    QPushButton *btnRemoveCategory{};
    QPushButton *btnFindCategoryImage{};

    QLabel *lblCategoryName{};
    QLabel *lblCategoryImage{};
    QLabel *lblTags{};

    QLineEdit *txtCategoryName{};
    QLineEdit *txtCategoryImagePath{};

    QComboBox *cbCategories{};
    QList<VideoTagCategory*> *categories;

    // Building the GUI
    void createMenu();
    void createGridGroupBox();
    void clearGUI();

    // Data handling
    void loadCategories();
    void saveCategories();



public:
    explicit TagManager(QWidget *parent);

    // Forward of CustomSlider::mouseMoveEvent
    void onSliderHover(QMouseEvent *event);
};


#endif //VTEG_TAGMANAGER_H
