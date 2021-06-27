//
// Created by Xida on 25.06.2021.
//


#include "TagManager.h"

TagManager::TagManager(QWidget *parent) : QDialog(parent){
    this->parentWindow = parent;
    this->categories = new QList<VideoTagCategory>;
    this->mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    /*
     * Initialize GUI objects
     */
    // Buttons
    btnAddCategory = new QPushButton;
    btnRemoveCategory = new QPushButton;
    btnFindCategoryImage = new QPushButton;

    // Boxes and Layout
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // Labels
    lblCategoryName = new QLabel;
    lblCategoryImage = new QLabel;
    lblTags = new QLabel;

    // Text fields
    txtCategoryName = new QLineEdit;
    txtCategoryImagePath = new QLineEdit;


    /*
     * Assign attributes to GUI objects
     */
    setMinimumSize(1250, 300);

    lblCategoryName->setText(tr("Category name:"));
    lblTags->setText(tr("Video Tags:"));
    lblCategoryImage->setPixmap(QPixmap("images/icon_unknown").scaled(200, 100, Qt::KeepAspectRatioByExpanding));

    btnAddCategory->setText(tr("+"));
    btnAddCategory->setFixedSize(30, 30);

    btnRemoveCategory->setText(tr("-"));
    btnRemoveCategory->setFixedSize(30, 30);

    btnFindCategoryImage->setIcon(QIcon(QPixmap("images/icon_search.png")));



    /*
     * Connect Buttons
     */
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(finished(int)), this, SLOT(dialogFinished(int)));
    connect(btnFindCategoryImage, SIGNAL(clicked(bool)), this, SLOT(onBtnFindCategoryImageClicked()));



    // Create layout
    createMenu();
    createGridGroupBox();

    // Modal := Window is forced to be focused window
    setModal(true);
    setWindowTitle(tr("Vteg - Tag Manager"));

    // Load categories if any exist
    loadCategories();
}

/*
 * --------------------------------------------------------------------------
 * -------                        PRIVATE SLOTS                       -------
 * --------------------------------------------------------------------------
 */
#pragma region PRIVATE_SLOTS




void TagManager::dialogFinished(int) {
    if (result() == QDialog::Accepted){
        qDebug() << "Clicked okay";
    } else {
        qDebug() << "Clicked cancel.";
    }
}


/*
 * --------------------------------------------------------------------------
 * -------                      MENU BAR HANDLING                     -------
 * --------------------------------------------------------------------------
 */

void TagManager::onOpenActionClicked() {
    qDebug() << "Clicked 'File/Open'";
}

void TagManager::onSaveActionClicked() {
    qDebug() << "Clicked 'File/Save'";
}

void TagManager::onSaveAsActionClicked() {
    qDebug() << "Clicked 'File/Save as'";
}

void TagManager::onExitClicked() {
    qDebug() << "Clicked 'File/Exit'";
}

void TagManager::onOptionsActionClicked() {
    qDebug() << "Clicked 'Options'";
}


/*
 * --------------------------------------------------------------------------
 * -------                         GUI BUTTONS                        -------
 * --------------------------------------------------------------------------
 */

void TagManager::onBtnFindCategoryImageClicked() {
    auto filePath = QFileDialog::getOpenFileName(this, "Select preview Image", "", "");
    try {
        QPixmap img(filePath);
        img.scaled(200, 100,Qt::KeepAspectRatioByExpanding);
        this->lblCategoryImage->setPixmap(img);
        this->lblCategoryImage->setFixedSize(200, 100);
    } catch (...){
        auto *msg = new QMessageBox;
        QMessageBox::information(this, tr("Information"), "Unable to load selected file as preview image.");
        msg->show();
    }
}


void TagManager::onBtnAddCategoryClicked() {

}

void TagManager::onBtnRemoveCategoryClicked() {

}


#pragma endregion PRIVATE_SLOTS


/*
 * --------------------------------------------------------------------------
 * -------                       PRIVATE METHODS                      -------
 * --------------------------------------------------------------------------
 */
#pragma region PRIVATE_METHODS

#pragma region GENERATE_UI

void TagManager::createMenu() {
    // Instantiate
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"), this);

    // Assign texts
    openAction = fileMenu->addAction(tr("&Open"));
    saveAction = fileMenu->addAction(tr("&Save"));
    saveAsAction = fileMenu->addAction(tr("Save &as.."));
    exitAction = fileMenu->addAction(tr("E&xit"));

    // Set hotkeys
    openAction->setShortcut(QKeySequence(tr("ctrl+o","Open")));
    saveAction->setShortcut(QKeySequence(tr("ctrl+s", "Save")));
    saveAsAction->setShortcut(QKeySequence(tr("ctrl+shift+s", "Save As")));
    exitAction->setShortcut(QKeySequence(tr("ctrl+w", "Exit")));

    // Add to layout
    menuBar->addMenu(fileMenu);
    optionsAction = menuBar->addAction(tr("&Options"));
    mainLayout->setMenuBar(menuBar);

    // Connect menu
    connect(openAction, SIGNAL(triggered()), this, SLOT(onOpenActionClicked()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(onSaveActionClicked()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(onSaveAsActionClicked()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));

    connect(optionsAction, SIGNAL(triggered()), this, SLOT(onOptionsActionClicked()));
}
void TagManager::createGridGroupBox() {
    groupBox = new QGroupBox(tr("Grid Layout"));
    categoryComboBox = new QComboBox();
    auto *layout = new QGridLayout();

    // Labels and preview image
    lblCategoryName = new QLabel(tr("Category name: "));
    lblCategoryImage = new QLabel();
    lblCategoryImage->setPixmap(QPixmap("images/icon_unknown").scaled(100, 100, Qt::KeepAspectRatioByExpanding));
    lblTags = new QLabel(tr("Video Tags: "));

    // Buttons
    btnAddCategory = new QPushButton();
    btnFindCategoryImage = new QPushButton();
    btnRemoveCategory = new QPushButton();

    // Add gui objects to the layout
    layout->addWidget(lblCategoryName, 0, 0);
    layout->addWidget(lblCategoryImage, 1, 0, 1, 2);

    // Assign layout to window
    groupBox->setLayout(layout);
    mainLayout->addWidget(groupBox);
}


#pragma endregion GENERATE_UI



#pragma region DATA_HANDLING



void TagManager::loadCategories() {
    // load existing categories (if any exist)
    auto filePath = "data/categories.vtc";
    auto cbEntries = new QStringList;

    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);

        qint16 categorySize;
        stream >> categorySize;

        for (int i = 0; i < categorySize; i++){
            auto category = new VideoTagCategory();
            category->load(stream);

            categories->append(*category);
            cbEntries->append(category->getCategoryName());
        }
    }

    categoryComboBox->addItems(*cbEntries);
}

void TagManager::saveCategories() {

}


#pragma endregion DATA_HANDLING


#pragma endregion PRIVATE_METHODS































