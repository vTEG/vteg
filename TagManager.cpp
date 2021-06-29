//
// Created by Xida on 25.06.2021.
//


#include "TagManager.h"

TagManager::TagManager(QWidget *parent) : QDialog(parent){
    this->parentWindow = parent;
    this->categories = new QList<VideoTagCategory*>;
    this->mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    setMinimumSize(700, 500);

    // Modal := Window is forced to be focused window
    setModal(true);
    setWindowTitle(tr("Vteg - Tag Manager"));

    // Load categories if any exist
    //loadCategories();

    auto c = new VideoTagCategory();
    c->setCategoryName("Test Category");

    auto t = new VideoTag();
    t->setTitle("Test Tag");
    c->addTag(t);

    categories->append(c);


    // Create layout
    createMenu();
    createGridGroupBox();

    loadCategories();
}

/*
 * --------------------------------------------------------------------------
 * -------                        PRIVATE SLOTS                       -------
 * --------------------------------------------------------------------------
 */
#pragma region PRIVATE_SLOTS




void TagManager::dialogFinished(int) {
    if (result() == QDialog::Accepted)
        saveCategories();
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
    cbCategories = new QComboBox();
    auto *layout = new QGridLayout();

    // Labels and preview image
    lblCategoryName = new QLabel(tr("Category name: "));
    lblCategoryImage = new QLabel();
    lblCategoryImage->setPixmap(QPixmap("images/icon_unknown").scaled(100, 100, Qt::KeepAspectRatioByExpanding));
    lblTags = new QLabel(tr("Video Tags: "));

    // Text fields
    txtCategoryName = new QLineEdit();
    txtCategoryImagePath = new QLineEdit();
    txtCategoryName->setPlaceholderText("The name of your category");
    txtCategoryImagePath->setPlaceholderText("/path/to/your/image");

    // Create buttons
    btnAddCategory = new QPushButton();
    btnFindCategoryImage = new QPushButton();
    btnRemoveCategory = new QPushButton();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    btnAddCategory->setText("+");
    btnRemoveCategory->setText("-");
    btnAddCategory->setFixedSize(30, 30);
    btnRemoveCategory->setFixedSize(30, 30);
    btnFindCategoryImage->setIcon(QIcon(QPixmap("images/icon_search.png")));
    btnFindCategoryImage->setFixedSize(30, 30);

    // ToDo: Remove slider test
    auto *slider = new CustomVideoSlider(this);

    slider->setOrientation(Qt::Horizontal);
    layout->addWidget(slider, 5, 0);

    // Connect buttons
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(btnAddCategory, SIGNAL(clicked(bool)), this, SLOT(onBtnAddCategoryClicked()));
    connect(btnRemoveCategory, SIGNAL(clicked(bool)), this, SLOT(onBtnRemoveCategoryClicked()));
    connect(btnFindCategoryImage, SIGNAL(clicked(bool)), this, SLOT(onBtnFindCategoryImageClicked()));

    // Connect dialog handler
    connect(this, SIGNAL(finished(int)), this, SLOT(dialogFinished(int)));

    // Add gui objects to the layout
    layout->addWidget(lblCategoryName, 0, 0);
    layout->addWidget(txtCategoryName, 0, 1);

    layout->addWidget(txtCategoryImagePath, 1, 1);
    layout->addWidget(btnFindCategoryImage, 1, 2);

    layout->addWidget(lblCategoryImage, 2, 0);
    layout->addWidget(cbCategories, 3, 0);

    layout->addWidget(btnAddCategory, 4, 0);
    layout->addWidget(btnRemoveCategory, 4, 1);

    layout->addWidget(buttonBox, 6, 0);

    // Assign layout to window
    groupBox->setLayout(layout);
    mainLayout->addWidget(groupBox);
}
void TagManager::clearGUI(){
    menuBar->clear();
    createMenu();

    txtCategoryName->setText("");
    txtCategoryImagePath->setText("");
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
            categories->append(category);
        }
    }

    for (auto category : *categories){
        cbEntries->append(category->getCategoryName());
    }

    cbCategories->addItems(*cbEntries);
}

void TagManager::saveCategories() {

    auto filePath = "data/categories.vtc";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);

        stream << categories->size();
        for (VideoTagCategory *c : *categories){
            c->save(stream);
        }
    }
}


#pragma endregion DATA_HANDLING


#pragma endregion PRIVATE_METHODS


void TagManager::onSliderHover(QMouseEvent *event) {
    qDebug() << "X: " << event->x() << " Y: " << event->y();
}




























