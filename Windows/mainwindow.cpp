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

#include "mainwindow.h"

#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , player(new QMediaPlayer(nullptr))
{
    /*
     * Default settings
     */
    ui->setupUi(this);
    this->setWindowTitle("VTEg");
    this->setWindowIcon(QIcon(QPixmap("images/speaker.png")));
    this->setMinimumSize(896,504);
    // Disable '?' Button in window titles
    //QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    /*
     * Creating objects
     */
    playerState = QMediaPlayer::StoppedState;
    vw = new VideoWidget;
    videoTags = new QList<VideoTag*>;

    mainWidget = new QWidget(this);
    volume = new QSlider(this);
    timeLabel = new QLabel(this);
    previewLabel = new QLabel(this);
    videoWidget = new QWidget(mainWidget);
    videoControlsWidget = new QWidget(videoWidget);
    videoTimeWidget = new QWidget(videoControlsWidget);
    videoButtonsWidget = new QWidget(videoControlsWidget);
    tagWidget = new QWidget(mainWidget);
    tagButtonWidget = new QWidget(tagWidget);
    addTag = new QPushButton("+", tagButtonWidget);
    QPixmap start("images/button_black_play.png"); QPixmap pause("images/button_black_pause.png"); QPixmap stop("images/button_black_stop.png");
    playButton = new QPushButton(start, nullptr, videoButtonsWidget);
    pauseButton = new QPushButton(pause, nullptr, videoButtonsWidget);
    stopButton = new QPushButton(stop, nullptr, videoButtonsWidget);
    removeTag = new QPushButton("-", tagButtonWidget);
    jumpToTag = new QPushButton("->", tagButtonWidget);
    listView = new QListWidget(this);
    hotkeyManager = HotKeyManager::getInstance();
    maxDuration = "/00:00";

    customSlider = new CustomVideoSlider(this, videoTags);

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
     * Setting the font-size of the timelabel and its default state to 00:00
     */
    timeLabel->setStyleSheet("QWidget{font-size:12px;}");
    timeLabel->setText("00:00" + maxDuration);

    /*
     * Size of the buttons for the tag list
     */
    playButton->setFixedSize(30, 30);
    pauseButton->setFixedSize(30, 30);
    stopButton->setFixedSize(30, 30);
    addTag->setFixedSize(30, 30);
    removeTag->setFixedSize(30, 30);
    jumpToTag->setFixedSize(30, 30);

    //previewLabel->setFixedSize(200, 100);
    //previewLabel->setText("Example");
    //preview->setFixedSize(200, 100);



#pragma region Parenting and layouting
    /*
     * Parenting objects and layouts
     */
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(new QHBoxLayout);
    videoWidget->setLayout(new QVBoxLayout);
    videoControlsWidget->setLayout(new QVBoxLayout);
    videoTimeWidget->setLayout(new QHBoxLayout);
    auto buttonsHbox = new QHBoxLayout; //cache the hbox of the videocontrolbutton layout, so we can add alignments later
    videoButtonsWidget->setLayout(buttonsHbox);
    tagWidget->setLayout(new QVBoxLayout);
    tagButtonWidget->setLayout(new QHBoxLayout);

    mainWidget->layout()->addWidget(videoWidget);
    mainWidget->layout()->addWidget(tagWidget);

    videoWidget->layout()->addWidget(vw);
    videoWidget->layout()->addWidget(videoControlsWidget);

    videoControlsWidget->layout()->addWidget(videoTimeWidget);
    videoControlsWidget->layout()->addWidget(videoButtonsWidget);

    videoTimeWidget->layout()->addWidget(customSlider);
    videoTimeWidget->layout()->addWidget(previewLabel);
    videoTimeWidget->layout()->addWidget(timeLabel);
    //add hbox alignments for videocontrolbutton
    buttonsHbox->addWidget(playButton, 0, Qt::AlignLeft);
    buttonsHbox->addWidget(pauseButton, 0, Qt::AlignLeft);
    buttonsHbox->addWidget(stopButton, 0, Qt::AlignLeft);
    buttonsHbox->addWidget(volume, 1, Qt::AlignRight);

    tagWidget->layout()->addWidget(listView);
    tagWidget->layout()->addWidget(tagButtonWidget);

    tagButtonWidget->layout()->addWidget(addTag);
    tagButtonWidget->layout()->addWidget(removeTag);
    tagButtonWidget->layout()->addWidget(jumpToTag);

    customSlider->setOrientation(Qt::Horizontal);
    volume->setOrientation(Qt::Horizontal);
    volume->setValue(50);
    player->audioOutput()->setVolume(50);


#pragma endregion Parenting and layouting
    /*
     * ToDo: Calculate the value out and work with percentage
     * connects the changing functions with each other so sliders will actually do something when used
     */
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::changeLabelTime);

    connect(customSlider, &QSlider::sliderMoved, this, &MainWindow::setPosition);
    connect(customSlider, &CustomVideoSlider::mouseHover, this, &MainWindow::handleMouseHover);

    connect(volume, &QSlider::valueChanged, player->audioOutput(), &QAudioOutput::volumeChanged);
    connect(volume, &QSlider::valueChanged, player->audioOutput(), &QAudioOutput::setVolume);

    /*
     * Button clicked events
     */
    connect(playButton, &QPushButton::clicked, this, &MainWindow::on_actionPlay_triggered);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::on_actionPause_triggered);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::on_actionStop_triggered);
    connect(addTag, &QPushButton::clicked, this, &MainWindow::addTagToList);
    connect(removeTag, &QPushButton::clicked, this, &MainWindow::removeTagFromList);
    connect(jumpToTag, &QPushButton::clicked, this, &MainWindow::jumpToSelectedTag);

    /*
     * Register Events for clicks
     */
    connect(listView, &QListWidget::itemClicked, this, &MainWindow::onTagEntryClicked);
    connect(listView, &QListWidget::itemDoubleClicked, this, &MainWindow::onTagEntryDoubleClicked);



    this->installEventFilter(this);

    //QCoreApplication::instance()->installEventFilter(this);

    /**
     * Triggers a resize event so the scaling of everything will be correct on startup
     */
    fireResizeEvent();
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
    int w = event->size().width(), h = event->size().height();
    videoWidget->setFixedSize(w * 70 / 100, h * 95 / 100);
    tagWidget->setFixedSize(w * 25 / 100, h * 90 / 100);
    vw->setFixedHeight(videoWidget->height() * 75 / 100);
    videoControlsWidget->setFixedHeight(videoWidget->height() * 20 / 100);

    //setHotkey tag-list property sizes based on the width/height of the application, so its always readable and looks fine
    listView->setStyleSheet("QWidget{font-size:" + QString::number(w / 100 > 12 ? w / 100 : 12) + "px;}");
    listView->setIconSize(QSize(16 * w / 100, 9 * h / 100));

    customSlider->setMinimumWidth(videoTimeWidget->width() * 80 / 100);

    timeLabel->setMinimumWidth(videoTimeWidget->width() * 15 / 100);
    volume->setFixedWidth(videoControlsWidget->width() * 20 / 100);
}

void MainWindow::fireResizeEvent() {
    QCoreApplication::postEvent(this, new QResizeEvent(size(), size()));
}


/**
 * Triggers when the file-open button is clicked
 * Will open a file dialog selection and open + play the selected video file
 */
void MainWindow::on_actionOpen_triggered() {
    qDebug() << "Opening file..";
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Videos file(*.mp4 *.mpeg *.avi *.wmv *.mov)");
    on_actionStop_triggered();

    QUrl media = QUrl::fromLocalFile(filename);

    player->setSource(media);
    currentTime = 0;
    playerState = QMediaPlayer::PlayingState;
    on_actionPlay_triggered();
}

/**
 * Triggers when the play button is clicked
 * Will play the video if there is one active
 */
void MainWindow::on_actionPlay_triggered() {
    if(playerState == QMediaPlayer::StoppedState) {
        qDebug() << "No Video";
        return;
    }
    player->play();
    playerState = QMediaPlayer::PlayingState;
    ui->statusbar->showMessage("Playing");
}

/**
 * Triggers when the pausae button is clicked
 * Will pause the video if there is one active
 */
void MainWindow::on_actionPause_triggered() {
    if(playerState == QMediaPlayer::StoppedState) {
        qDebug() << "No Video";
        return;
    }
    player->pause();
    playerState = QMediaPlayer::PausedState;
    ui->statusbar->showMessage("Paused");
}

/**
 * Triggers when the stop button is clicked
 * Will stop the video if there is one active
 */
void MainWindow::on_actionStop_triggered() {
    if(playerState == QMediaPlayer::StoppedState) {
        qDebug() << "No Video";
        return;
    }
    removeAllTagsFromList();
    player->stop();
    playerState = QMediaPlayer::StoppedState;
    ui->statusbar->showMessage("Stopped");
    maxDuration = "/00:00";
    timeLabel->setText("00:00" + maxDuration);
}

void MainWindow::on_actionSaveTags_triggered(){
    if(playerState == QMediaPlayer::StoppedState) {
        qDebug() << "No Video";
        return;
    }
    qDebug() << "Saving tags..";
    QString filePath = QFileDialog::getSaveFileName(this, "save Tags", "", "VTeg files(*.vteg)");
    QMessageBox box;

    // FilePath valid?
    if (filePath == nullptr || filePath == ""){
        QMessageBox::information(this, "Warning", "Cannot save at this path.");
        box.show();
        return;
    }

    // Any video loaded and tags exist?
    if (videoTags->empty()){
        QMessageBox::information(this, "Info", "There are no tags.");
        box.show();
        return;
    }

    save(filePath);
}

void MainWindow::on_actionLoadTags_triggered(){
    if(playerState == QMediaPlayer::StoppedState) {
        qDebug() << "No Video";
        return;
    }
    qDebug() << "Loading tags..";
    QString filePath = QFileDialog::getOpenFileName(this, "load Tags", "", "VTeg files(*.vteg)");
    if (filePath == nullptr || filePath == "")
        return;

    load(filePath);
}

void MainWindow::on_actionSettings_triggered() {
    auto settingsWindow = new SettingsWidget(this);
    qDebug() << "Addition" << Settings::getInstance()->getAddition();
    settingsWindow->show();
}

/**
 * Read in a taglist from a CSV file
 */
void MainWindow::on_action_load_from_CSV_triggered() {
    if(playerState == QMediaPlayer::StoppedState) {
        qDebug() << "No Video";
        return;
    }
    qDebug() << "Loading from CSV";
    QString filePath;
    bool ok;
    filePath = QFileDialog::getOpenFileName(this, "Load from CSV", "", "CSV files(*.csv)");

    if(filePath.isEmpty()) return;

    auto readTitle = QInputDialog::getText(this->window(), "Title Row", "Input Text:", QLineEdit::Normal, "description",
                                           &ok, Qt::MSWindowsFixedSizeDialogHint);
    if(!ok || readTitle.isEmpty()) return;

    auto readTime = QInputDialog::getText(this->window(), "Timestamp Row", "Input Text:", QLineEdit::Normal, "timestamp",
                                          &ok, Qt::MSWindowsFixedSizeDialogHint);
    if(!ok || readTime.isEmpty()) return;

    /**
     * Exclaimer: This code below looks kinda dumb and indeed is duplicated code
     * but I couldn't get the constexpr for io::no_quote_escape<';' working otherwise
     *
     * Todo: find a better solution (maybe put it in its own function with a constexpr char as an argument
     */
    FrameGrabber frameGrabber(player->source().path().remove(0,1));
    if(Settings::getInstance()->getCsvPolicy() == ";") {
        io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in(filePath.toStdString());
        try {
            in.read_header(io::ignore_extra_column, readTitle.toStdString(), readTime.toStdString());
        }
        catch (std::exception &e) {
            qDebug() << "Exception: " << e.what();
            QMessageBox msg;
            msg.setText("Columns dont exist or CSV Policy is wrong(Settings)");
            msg.exec();
            return;
        }
        std::string title;
        int timestamp;

        qint64 previousPos = player->position();
        try {
            while (in.read_row(title, timestamp)) {
                if (timestamp <= player->duration()) {
                    int secs = timestamp / 1000;
                    int mins = secs / 60;
                    secs = secs % 60;
                    auto *tag = new VideoTag();
                    tag->setTitle(QString::asprintf("%02d:%02d", mins, secs));
                    tag->setDescription(QString::fromStdString(title));
                    tag->setTimestamp(timestamp);

                    tag->setImage(frameGrabber.grabFrame(timestamp));

                    addExistingTagToList(tag);
                }
            }
        }
        catch (...) {
            QMessageBox msg;
            msg.setText("An error occured, most likely one of your columns titles is wrong");
            msg.exec();
            return;
        }
    }
    else if(Settings::getInstance()->getCsvPolicy() == ",") {
        io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>> in(filePath.toStdString());
        try {
            in.read_header(io::ignore_extra_column, readTitle.toStdString(), readTime.toStdString());
        }
        catch (std::exception &e) {
            qDebug() << "Exception: " << e.what();
            QMessageBox msg;
            msg.setText("An error occured while reading from CSV (Could be columns not existing)");
            msg.exec();
            return;
        }
        std::string title;
        int timestamp;
        qint64 previousPos = player->position();
        try {
            while (in.read_row(title, timestamp)) {
                if (timestamp <= player->duration()) {
                    int secs = timestamp / 1000;
                    int mins = secs / 60;
                    secs = secs % 60;
                    auto *tag = new VideoTag();
                    tag->setTitle(QString::asprintf("%02d:%02d", mins, secs));
                    tag->setDescription(QString::fromStdString(title));
                    tag->setTimestamp(timestamp);

                    tag->setImage(frameGrabber.grabFrame(timestamp));

                    addExistingTagToList(tag);
                }
            }
        }
        catch (...) {
            QMessageBox msg;
            msg.setText("An error occured, most likely one of your columns titles is wrong");
            msg.exec();
            return;
        }
        player->setPosition(previousPos);
    }
}

/**
 * Write the current active taglist into a CSV file
 * Todo: move to static class for readability
 */
void MainWindow::on_action_write_to_CSV_triggered() {
    QMessageBox msg;
    if (playerState == QMediaPlayer::StoppedState || videoTags->empty()){
        msg.setText("No video loaded or tag list empty.");
        msg.exec();
        return;
    }

    auto filePath = QFileDialog::getSaveFileName(this,
                                                 "Save tags to *.csv",
                                                 QDir::currentPath(),
                                                 "CSV (*.csv)");

    auto delimiter = Settings::getInstance()->getCsvPolicy();
    VideoTag *t;
    bool forceSkip = false;

    // Iterate over all video tags to check their validity.
    for (int i = 0; i < videoTags->size(); i++){
        t = videoTags->value(i);
        if (!forceSkip && (t->getTitle().contains(delimiter) || t->getDescription().contains(delimiter))){
            msg.setText(QString::asprintf("The title/description of a tag contains the delimiter '%s'\n"
                                          "this <b>will</b> corrupt a later re-import.\n Continue?",
                                          delimiter.toStdString().c_str()));
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setIcon(QMessageBox::Warning);

            if (msg.exec() == QMessageBox::Yes){
                forceSkip = true;
            } else {
                return;
            }
        }
    }

    // Iterate again and actually save valid data this time.
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);

    // save header
    stream << "timestamp" << delimiter << "description" << Qt::endl;

    for (int i = 0; i < videoTags->size(); i++){
        t = videoTags->value(i);
        stream << t->getTimestamp() << delimiter << t->getDescription() << Qt::endl;
    }

    // Flush and close stream
    stream.flush();
    file.close();

    // Feedback
    msg.setText(QString::asprintf("Saved Data to '%s'", filePath.toStdString().c_str()));
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

/**
 * Analyzes currently playing video if there is one active
 */
void MainWindow::on_action_Analyze_Video_triggered() {
    if (playerState == QMediaPlayer::StoppedState){
        QMessageBox msg;
        msg.setText("No video loaded or tag list empty.");
        msg.exec();
        return;
    }

    auto *progressDialog = new QProgressDialog("Analyzing video", "Cancel",
                                               0, static_cast<int>(player->duration()), this);
    progressDialog->setAutoClose(true);
    if(Settings::getInstance()->getTheme() != "classic")
        progressDialog->setStyleSheet("QProgressBar {"
                                  "border: 2px solid grey;"
                                  "border-radius: 5px;"
                                  "margin-right: 30px;"
                                  "}");
    player->pause();
    TensorflowObjectDetection od(player->source().path().remove(0,1).toStdString());
    auto list = od.AnalyzeVideo(progressDialog);

    for(auto t : list)
        addExistingTagToList(t);
    player->play();
}


/**
 * Will add a tag to the list, if there is a video playing
 * ToDo: Vorschaubilder an Tags in Liste anzeigen
 */
void MainWindow::addTagToList() const {
    int cTime = currentTime;
    if(player->mediaStatus() == QMediaPlayer::MediaStatus::NoMedia)  {
        qDebug() << "No active Video";
        return;
    }

    //Get Description via QInputDialog and add it to the list
    player->pause();
    auto description = QInputDialog::getText(this->window(), "Title", "Input Text:", QLineEdit::Normal, "",
                                             nullptr, Qt::MSWindowsFixedSizeDialogHint);
    player->play();

    // Calculate timestamp
    int secs = cTime/1000;
    int mins = secs/60;
    secs = secs%60;

    // create tag object so we can read info from it and add it to list
    auto *tag = new VideoTag(QString::asprintf("%02d:%02d", mins, secs), description, vw->getSurface()->getLastFrame().copy(), cTime);
    addExistingTagToList(tag);
}

/**
 * Will add an existing Tag to the list when one is loaded from file
 * or when a template is being used.
 * @param tag   predefined VideoTag
 */
void MainWindow::addExistingTagToList(VideoTag *tag) const {
    videoTags->push_back(tag);

    std::sort(videoTags->begin(), videoTags->end(),
          [] (const VideoTag* a, const VideoTag* b) {return a->getTimestamp() < b->getTimestamp();});

    auto *item = new QListWidgetItem(tag->getTitle() + "\n" + tag->getDescription());

    item->setIcon(QPixmap::fromImage(tag->getImage()));
    listView->insertItem(videoTags->indexOf(tag), item);
}

/**
 * Will remove a tag from the list, if there is a tag selected
 */
void MainWindow::removeTagFromList() const {
    auto rml = listView->selectionModel()->selectedIndexes();
    if(rml.isEmpty()) return;
    for(auto r : rml)
        videoTags->removeAt(r.row());
    qDeleteAll(listView->selectedItems());

    for(const auto& i : *videoTags)
        qDebug() << i->getTimestamp();

    qDebug() << "Removed selected Elements from list";
}

/**
 * Will remove every tag from the list and clear the listView
 */
void MainWindow::removeAllTagsFromList() const {
    listView->clear();
    videoTags->clear();
}

/**
 * Jump to the currently selected tag, if there is one selected
 */
void MainWindow::jumpToSelectedTag() const {
    auto rml = listView->selectionModel()->selectedIndexes();
    if(rml.isEmpty()) return;
    qint64 timestamp = videoTags->value(rml.first().row())->getTimestamp() + (Settings::getInstance()->getAddition() * 1000);
    if(timestamp < 0)
        timestamp = 0;
    else if(timestamp > player->duration())
        timestamp = player->duration();
    player->setPosition(timestamp);
    int cur = static_cast<int>(timestamp);
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

    timeLabel->setText(QString::asprintf("%02d:%02d", mins, secs) + maxDuration);
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
    jumpToSelectedTag();
}

/**
 * Helper function to prevent MainWindow::onTagEntryClicked from being called twice on a double click.
 */
void MainWindow::tagEntryClickTimeout() {
    if (!mDoubleClicked){
        //qDebug() << "Single Click." << tagListClickedItem->text();
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
    customSlider->setValue(static_cast<int>(position));
}

/**
 * Change the duration of the slider based on param duration
 * @param duration: the duration the slider should end at
 */
void MainWindow::durationChanged(quint64 duration)
{
    customSlider->setRange(0, static_cast<int>(duration));
    qDebug() << "Duration: " << duration;

    //calculate maxDuration for the playerLabel just after the duration actually changed cause player-setMedia is asynchronous
    int secs = static_cast<int>(player->duration())/1000;
    int mins = secs/60;
    secs = secs%60;
    maxDuration = QString::asprintf("/%02d:%02d", mins, secs);
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

    // unchangeable hotkeys
    if (event->type() == QEvent::KeyPress){

    }

    if (event->type() == QEvent::MouseButtonPress){
        return QMainWindow::eventFilter(object, event);
    }

    if (event->type() == QEvent::KeyPress){
        auto *keyEvent = dynamic_cast<QKeyEvent*>(event);
        auto *pTagManager = new TagManager(this);
        int returnValue = -1;
        int eventButton = keyEvent->key();

        /* Todo: correctly implement the hotkeymanager, cause its causing a nullptr crash rn
        auto *entry = new HotKeyEntry(eventButton,
                                             keyEvent->modifiers().testFlag(Qt::AltModifier),
                                             keyEvent->modifiers().testFlag(Qt::ControlModifier),
                                             keyEvent->modifiers().testFlag(Qt::ShiftModifier));

        HotKeyAction action = HotKeyManager::getInstance()->getAction(entry);

        switch (action){
            case OPEN_FILE:
                // ToDo..
                break;
            case NO_ACTION:
                break;
            case CLOSE_FILE:
                break;
            case SAVE_FILE:
                break;
            case SAVE_FILE_AS:
                break;
            case ADD_TAG:
                break;
            case REMOVE_TAG:
                break;
            case EDIT_TAG:
                break;
            default:
                break;
        }*/






        switch (eventButton){
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
                    if (frame.save("screenshot.png", nullptr, -1)){
                        qDebug() << "Saved!";
                    } else {
                        qDebug() << "Error while saving img.";
                    }
                }
                break;

            case Qt::Key_W:

                returnValue = pTagManager->exec();
                qDebug() << "TagManager finished with code " << returnValue;
                break;

            case Qt::Key_Left:
                if (playerState != QMediaPlayer::StoppedState){
                    setPosition(std::max(0, static_cast<int>(player->position()) - 5000));
                }
                break;

            case Qt::Key_Right:
                if (playerState != QMediaPlayer::StoppedState){
                    setPosition(std::min(static_cast<int>(player->duration()), static_cast<int>(player->position()) + 5000));
                }
                break;

            default:
                // ignored
                break;
        }
    }

    return QMainWindow::eventFilter(object, event);
}

/**
 * Serialize tagList to a filePath
 *
 * File format:
 *  1)      videoTags->size()
 *  2..n)   videoTag::serialize()
 * @param filePath: The path where the file should be stored
 */
void MainWindow::save(const QString& filePath){
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);

    stream << videoTags->size();
    for (int i = 0; i < videoTags->size(); i++){
        videoTags->value(i)->serialize(stream);
    }

    qDebug() << QString::asprintf("Saved Video-Tags to ") << filePath;
}

/**
 * load serialized tagList from a filePath
 * @param filePath: The path where the file is stored
 */
void MainWindow::load(const QString& filePath){

    // Plausibility checks
    bool append = false;
    player->pause();

    if (!videoTags->empty()){
        QMessageBox msgBox(this);
        msgBox.setModal(true);
        msgBox.setText("Video Tags already exist");
        msgBox.setInformativeText("Would you like to append loaded tags?");
        msgBox.setStandardButtons(
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
                );
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setMinimumSize(200, 200);

        int retValue = msgBox.exec();

        switch (retValue){
            case QMessageBox::Yes:
                append = true;
                break;
            case QMessageBox::No:
                append = false;
                break;
            default:
                return;
        }
    }

    // Open file and load data
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);

    int size;
    stream >> size;

    auto *list = new QList<VideoTag*>;

    qint64 previousPosition = player->position();
    quint16 failedEntries = 0;
    player->audioOutput()->setMuted(true);

    FrameGrabber frameGrabber(player->source().path().remove(0,1));

    for (int i = 0; i < size; i++){
        auto tag = new VideoTag();
        // Deserialize from stream
        tag->deserialize(stream);

        // plausibility check
        if (tag->getTimestamp() > player->duration()){
            qDebug() << "Invalid Timestamp for tag: " << tag->getTimestamp() << " > " << player->duration();
            failedEntries++;
            continue;
        }
        tag->setImage(frameGrabber.grabFrame(tag->getTimestamp()));

        // Add to temporary list
        list->push_back(tag);
    }

    // Check if there have been any errors. If so, ask user to continue or not
    if (failedEntries > 0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QString t = QString::asprintf("There %s %d %s with out-of-scope timestamps.\nWould you like to continue anyways?",
                                      failedEntries == 1 ? "is" : "are",
                                      failedEntries,
                                      failedEntries == 1 ? "issue" : "issues");

        msgBox.setText(t);
        msgBox.setModal(true);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setMinimumSize(300, 200);

        if (msgBox.exec() == QMessageBox::No)
            return;
    }

    // Clear previous existing tags if needed
    if (!append){
        removeAllTagsFromList();
    }

    // Add tags to view
    for (auto i : *list){
        addExistingTagToList(i);
    }

    // Restore player state
    player->play();
    player->audioOutput()->setMuted(false);

    // Debug: feedback
    qDebug() << list->size() << " Tags loaded from file at " << filePath;
}


void MainWindow::handleMouseHover(int position) {

    if (previewLabel != nullptr){
        previewLabel->updateGeometry();
        qDebug() << "Hovering over: " << position;
    }
}
