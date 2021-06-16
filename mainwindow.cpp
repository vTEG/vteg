#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    /*
     * Default settings
     */
    ui->setupUi(this);
    this->setMinimumSize(1024,768);

    /*
     * Creating objects
     */
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    slider = new QSlider(this);
    volume = new QSlider(this);
    timeLabel = new QLabel(this);
    mainWidget = new QWidget(this);
    tagWidget = new QWidget(mainWidget);
    tagButtonWidget = new QWidget(tagWidget);
    addTag = new QPushButton("+", tagButtonWidget);
    removeTag = new QPushButton("-", tagButtonWidget);
    jumpToTag = new QPushButton("->", tagButtonWidget);
    listView = new QListWidget(this);
    timestamps = new QList<int>;

    /*
     * Size of the media player Window and output setting
     */
    vw->setMinimumSize(160, 90);
    vw->setMaximumSize(1920, 1080);
    ui->statusbar->showMessage("Select a video file");
    player->setVideoOutput(vw);

    /*
     * Size and flow direction of the tag-list
     */
    listView->setFlow(QListView::TopToBottom);
    listView->setMaximumHeight(960);
    listView->setMaximumWidth(200);

    /*
     * Size of the buttons for the tag list
     */
    addTag->setFixedSize(30, 30);
    removeTag->setFixedSize(30, 30);
    jumpToTag->setFixedSize(30, 30);

    /*
     * Parenting objects and layouts
     */
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(new QHBoxLayout);
    tagWidget->setLayout(new QVBoxLayout);
    tagButtonWidget->setLayout(new QHBoxLayout);

    vw->setMinimumSize(this->size()*0.75);
    mainWidget->layout()->addWidget(vw);
    mainWidget->layout()->addWidget(tagWidget);

    tagWidget->layout()->addWidget(listView);
    tagWidget->layout()->addWidget(tagButtonWidget);

    tagButtonWidget->layout()->addWidget(addTag);
    tagButtonWidget->layout()->addWidget(removeTag);
    tagButtonWidget->layout()->addWidget(jumpToTag);

    slider->setOrientation(Qt::Horizontal);
    volume->setOrientation(Qt::Horizontal);
    volume->setValue(50);

    ui->statusbar->addPermanentWidget(volume);
    ui->statusbar->addPermanentWidget(slider);
    ui->statusbar->addPermanentWidget(timeLabel);

    /*
     * ToDo: Calculate the value out and work with percentage
     */
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    connect(volume, &QSlider::valueChanged, player, &QMediaPlayer::volumeChanged);
    connect(volume, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);

    connect(addTag, &QPushButton::clicked, this, &MainWindow::addTagToList);
    connect(removeTag, &QPushButton::clicked, this, &MainWindow::removeTagFromList);
    connect(jumpToTag, &QPushButton::clicked, this, &MainWindow::jumpToSelectedTag);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::changeLabelTime);

    // Single & Double click events
    connect(listView, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onTagEntryClicked(QListWidgetItem * )));
    connect(listView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(
            onTagEntryDoubleClicked(QListWidgetItem * )));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    qDebug() << "Opening file..";
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "*.*");
    on_actionStop_triggered();

    player->setMedia(QUrl::fromLocalFile(filename));
    currentTime = 0;
    on_actionPlay_triggered();
}
void MainWindow::on_actionPlay_triggered() {
    player->play();

    ui->statusbar->showMessage("Playing");
}
void MainWindow::on_actionPause_triggered() {
    player->pause();
    ui->statusbar->showMessage("Paused");
}
void MainWindow::on_actionStop_triggered() {
    player->stop();
    ui->statusbar->showMessage("Stopped");
    timeLabel->clear();
}

/*
 * ToDo: Vorschaubilder an Tags in Liste anzeigen
 */
void MainWindow::addTagToList() const {
    timestamps->append(currentTime);
    qSort(timestamps->begin(), timestamps->end());
    int secs = currentTime/1000;
    int mins = secs/60;
    secs = secs%60;
    listView->insertItem(timestamps->indexOf(currentTime), QString::asprintf("%02d:%02d", mins, secs));
    qDebug() << "Appended Element to list";
}

void MainWindow::removeTagFromList() const {
    auto rml = listView->selectionModel()->selectedIndexes();
    if(rml.isEmpty()) return;
    for(auto r : rml)
        timestamps->removeAt(r.row());
    qDeleteAll(listView->selectedItems());
    
    for(auto i : *timestamps)
        qDebug() << i;

    qDebug() << "Removed selected Elements from list";
}

void MainWindow::jumpToSelectedTag() const {
    auto rml = listView->selectionModel()->selectedIndexes();
    if(rml.isEmpty()) return;
    player->setPosition(timestamps->value(rml.first().row()));

    int secs = currentTime/1000;
    int mins = secs/60;
    secs = secs%60;

    timeLabel->setText(QString::asprintf("%02d:%02d", mins, secs));

    qDebug() << "Jumped to: " + QString::asprintf("%02d:%02d", mins, secs);
}

void MainWindow::changeLabelTime(qint64 i) {
    int j = static_cast<int>(i);
    currentTime = j;
    int secs = j/1000;
    int mins = secs/60;
    secs = secs%60;

    timeLabel->setText(QString::asprintf("%02d:%02d", mins, secs));
}

/**
 * Event being called once the user clicks (1) on a timestamp in the listview.
 * Note: actual implementation in MainWindow::tagEntryClickTimeout()
 * @param item: The selected entry
 */
void MainWindow::onTagEntryClicked(QListWidgetItem *item) {
    if (!mDoubleClicked){
        QTimer::singleShot(300, this, SLOT(tagEntryClickTimeout()));
        tagListClickedItem = item;
    }
}

/**
 * Event being called once the user double clicks on a timestamp in the listview
 * @param item: The selected entry
 */
void MainWindow::onTagEntryDoubleClicked(QListWidgetItem *item) {
    mDoubleClicked = true;

    qDebug() << "Double click." << item->text();
}

/**
 * Helper function to prevent MainWindow::onTagEntryClicked from being called twice on a double click.
 */
void MainWindow::tagEntryClickTimeout() {
    if (!mDoubleClicked){
        qDebug() << "Single Click." << tagListClickedItem->text();
    } else {
        mDoubleClicked = false;
    }
}



