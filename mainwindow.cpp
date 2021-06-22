#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTimer>
#include <QKeyEvent>
#include <QVideoProbe>


// ToDo: https://stackoverflow.com/questions/30800772/how-to-grab-video-frames-in-qt

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , player(new QMediaPlayer(nullptr, QMediaPlayer::VideoSurface))
{
    /*
     * Default settings
     */
    ui->setupUi(this);
    this->setMinimumSize(640,360);

    /*
     * Creating objects
     */
    playerState = QMediaPlayer::StoppedState;
    videoProbe = new QVideoProbe(this);
    vw = new VideoWidget;
    slider = new QSlider(this);
    volume = new QSlider(this);
    timeLabel = new QLabel(this);
    mainWidget = new QWidget(this);
    videoWidget = new QWidget(mainWidget);
    videoControlsWidget = new QWidget(videoWidget);
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
    ui->statusbar->showMessage("Select a video file");

    player->setVideoOutput(vw->videoSurface());


    /*
     * Size and flow direction of the tag-list
     */
    listView->setFlow(QListView::TopToBottom);
    listView->setLayoutDirection(Qt::RightToLeft);

    /*
     * Size of the buttons for the tag list
     */
    addTag->setFixedSize(30, 30);
    removeTag->setFixedSize(30, 30);
    jumpToTag->setFixedSize(30, 30);


#pragma region Parenting and layouting
    /*
     * Parenting objects and layouts
     */
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(new QHBoxLayout);
    videoWidget->setLayout(new QVBoxLayout);
    videoControlsWidget->setLayout(new QHBoxLayout);
    tagWidget->setLayout(new QVBoxLayout);
    tagButtonWidget->setLayout(new QHBoxLayout);

    mainWidget->layout()->addWidget(videoWidget);
    mainWidget->layout()->addWidget(tagWidget);
    
    videoWidget->layout()->addWidget(vw);
    videoWidget->layout()->addWidget(videoControlsWidget);

    videoControlsWidget->layout()->addWidget(volume);
    videoControlsWidget->layout()->addWidget(slider);
    videoControlsWidget->layout()->addWidget(timeLabel);

    tagWidget->layout()->addWidget(listView);
    tagWidget->layout()->addWidget(tagButtonWidget);

    tagButtonWidget->layout()->addWidget(addTag);
    tagButtonWidget->layout()->addWidget(removeTag);
    tagButtonWidget->layout()->addWidget(jumpToTag);

    slider->setOrientation(Qt::Horizontal);
    volume->setOrientation(Qt::Horizontal);
    volume->setValue(50);
    player->volumeChanged(50);


#pragma endregion Parenting and layouting
    /*
     * ToDo: Calculate the value out and work with percentage
     * connects the changing functions with each other so sliders will actually do something when used
     */
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::changeLabelTime);

    connect(slider, &QSlider::sliderMoved, this, &MainWindow::setPosition);

    connect(volume, &QSlider::valueChanged, player, &QMediaPlayer::volumeChanged);
    connect(volume, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);

    /*
     * Button clicked events
     */
    connect(addTag, &QPushButton::clicked, this, &MainWindow::addTagToList);
    connect(removeTag, &QPushButton::clicked, this, &MainWindow::removeTagFromList);
    connect(jumpToTag, &QPushButton::clicked, this, &MainWindow::jumpToSelectedTag);


    /*
     * Register Events for clicks
     */
    connect(listView, &QListWidget::itemClicked, this, &MainWindow::onTagEntryClicked);
    connect(listView, &QListWidget::itemDoubleClicked, this, &MainWindow::onTagEntryDoubleClicked);


    this->installEventFilter(this);
    
    /**
     * Triggers a resize event so the scaling of everything will be correct on startup
     */
    QCoreApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * Destructor deletes the namespace object
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

/**
 * Event being called when the window is resized
 * It will resize the widgets inside the window so it doesnt matter how big the window/screen is
 * @param event: The resize event
 */
void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    videoWidget->setMinimumSize(event->size().width() * 70 / 100, event->size().height() * 80 / 100);
    tagWidget->setMinimumSize(event->size().width() * 25 / 100, event->size().height() * 80 / 100);
    vw->setMinimumHeight(videoWidget->height() * 85 / 100);
    videoControlsWidget->setMinimumHeight(videoWidget->height() * 10 / 100);

    listView->setIconSize(QSize(100, 100));

    volume->setMinimumWidth(videoControlsWidget->width() * 20 / 100);
    slider->setMinimumWidth(videoControlsWidget->width() * 70 / 100);
    timeLabel->setMinimumWidth(videoControlsWidget->width() * 5 / 100);
}


/**
 * Triggers when the file-open button is clicked
 * Will open a file dialog selection and open + play the selected video file
 */
void MainWindow::on_actionOpen_triggered() {
    qDebug() << "Opening file..";
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Videos file(*.mp4 *.mpeg *.avi *.wmv *.mov)");
    on_actionStop_triggered();

    player->setMedia(QUrl::fromLocalFile(filename));
    currentTime = 0;
    on_actionPlay_triggered();
}

/**
 * Triggers when the play button is clicked
 * Will play the video if there is one active
 */
void MainWindow::on_actionPlay_triggered() {
    player->play();
    playerState = QMediaPlayer::PlayingState;
    ui->statusbar->showMessage("Playing");
}

/**
 * Triggers when the pausae button is clicked
 * Will pause the video if there is one active
 */
void MainWindow::on_actionPause_triggered() {
    player->pause();
    playerState = QMediaPlayer::PausedState;
    ui->statusbar->showMessage("Paused");
}

/**
 * Triggers when the stop button is clicked
 * Will stop the video if there is one active
 */
void MainWindow::on_actionStop_triggered() {
    removeAllTagsFromList();
    player->stop();
    playerState = QMediaPlayer::StoppedState;
    ui->statusbar->showMessage("Stopped");
    timeLabel->clear();
}

/**
 * Will add a tag to the list, if there is a video playing
 * ToDo: Vorschaubilder an Tags in Liste anzeigen
 */
void MainWindow::addTagToList() const {
    if(player->mediaStatus() == QMediaPlayer::MediaStatus::NoMedia)  {
        qDebug() << "No active Video";
        return;
    }
    timestamps->append(currentTime);
    qSort(timestamps->begin(), timestamps->end());
    int secs = currentTime/1000;
    int mins = secs/60;
    secs = secs%60;

    // prepare preview text
    // ToDo: Better format, pull info from VideoTag
    auto *tag = new VideoTag();
    tag->setTitle(QString::asprintf("%02d:%02d", mins, secs));
    QString previewText = QString::asprintf("%02d:%02d\nTest", mins, secs);

    // Fetch and copy preview image
    auto *itm = new QListWidgetItem(previewText);
    itm->setIcon(QPixmap::fromImage(vw->getSurface()->getLastFrame().copy()));
    listView->insertItem(timestamps->indexOf(currentTime), itm);


    auto *tag = new VideoTag();
    tag->setTitle(QString::asprintf("%02d:%02d", mins, secs));


}

/**
 * Will remove a tag from the list, if there is a tag selected
 */
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

/**
 * Will remove every tag from the list
 */
void MainWindow::removeAllTagsFromList() const {
    listView->clear();
    timestamps->clear();
}

/**
 * Jump to the currently selected tag, if there is one selected
 */
void MainWindow::jumpToSelectedTag() const {
    auto rml = listView->selectionModel()->selectedIndexes();
    if(rml.isEmpty()) return;
    player->setPosition(timestamps->value(rml.first().row()));
    int cur = static_cast<int>(timestamps->value(rml.first().row()));
    int secs = cur/1000;
    int mins = secs/60;
    secs = secs%60;

    timeLabel->setText(QString::asprintf("%02d:%02d", mins, secs));

    qDebug() << "Jumped to: " + QString::asprintf("%02d:%02d", mins, secs);
}

/**
 * Changes the time of the label next to the videoslider
 * @param i: the current time of the video player as an qint64 (in milliseconds)
 */
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
    jumpToSelectedTag();
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

/**
 * Change the position of the slider based on param position
 * @param position: the position the slider should change to
 */
void MainWindow::positionChanged(quint64 position)
{
    slider->setValue(static_cast<int>(position));
}

/**
 * Change the duration of the slider based on param duration
 * @param duration: the duration the slider should end at
 */
void MainWindow::durationChanged(quint64 duration)
{
    slider->setRange(0, static_cast<int>(duration));
}

/**
 * Change the position of the player based on param position
 * @param position: the position the player should play at
 */
void MainWindow::setPosition(int position)
{
    player->setPosition(position);
}


bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    QImage frame;
    if (event->type() == QEvent::KeyPress){
        auto *keyEvent = dynamic_cast<QKeyEvent*>(event);

        switch (keyEvent->key()){
            case Qt::Key_Space:
                switch (playerState){
                    case QMediaPlayer::StoppedState:
                        qDebug() << "Can't toggle play/pause on stopped video.";
                    case QMediaPlayer::PlayingState:
                        on_actionPause_triggered();
                        break;
                    case QMediaPlayer::PausedState:
                        on_actionPlay_triggered();
                        break;
                }
                break;
            case Qt::Key_S:
                if (keyEvent->modifiers().testFlag(Qt::ControlModifier) && keyEvent->modifiers().testFlag(Qt::AltModifier)) {
                    qDebug("Ctrl+Alt+S");
                } else if (keyEvent->modifiers().testFlag(Qt::AltModifier)) {
                    qDebug("Alt+S");
                } else if (keyEvent->modifiers().testFlag(Qt::ControlModifier)) {
                    qDebug("Ctrl+S");
                } else {
                    qDebug("'S'");
                }
                break;

            case Qt::Key_L:
                frame = vw->getSurface()->getLastFrame();
                if (frame.isNull()){
                    qDebug() << "Unable to load last frame.";
                } else {
                    if (frame.save("screenshot.png", 0, -1)){
                        qDebug() << "Saved!";
                    } else {
                        qDebug() << "Error while saving img.";
                    }
                }
                break;
            default:
                /*
                 * ignored
                 */
                break;
        }

        //qDebug() << "Ate key press: " << keyEvent->key();
        return true;
    }

    if (event->type() == QEvent::MouseMove){
        auto *m = dynamic_cast<QMouseEvent*>(event);

        QPoint p = this->mapFromGlobal(QCursor::pos());
        qDebug() << QString::asprintf("Global-X: %d, Global-Y: %d", p.x(), p.y());
        qDebug() << QString::asprintf("X: %d, Y: %d", m->pos().x(), m->pos().y());
        return true;
    }

    return QMainWindow::eventFilter(object, event);
}


