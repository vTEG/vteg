//
// Created by Xida on 25.06.2021.
//

#ifndef VTEG_TAGMANAGER_H
#define VTEG_TAGMANAGER_H

#include "VideoTagCategory.h"
#include "CustomVideoSlider.h"

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
    QDialogButtonBox *buttonBox;

    QGroupBox *groupBox;
    QVBoxLayout *mainLayout;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *optionsAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QPushButton *btnAddCategory;
    QPushButton *btnRemoveCategory;
    QPushButton *btnFindCategoryImage;

    QLabel *lblCategoryName;
    QLabel *lblCategoryImage;
    QLabel *lblTags;

    QLineEdit *txtCategoryName;
    QLineEdit *txtCategoryImagePath;

    QComboBox *cbCategories;
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
