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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-connect-by-name"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Including header
#include "Utilities/VideoTag.h"
#include "videowidget.h"
#include "videowidgetsurface.h"
#include "TagManager.h"
#include "Utilities/CustomVideoSlider.h"
#include "Utilities/VideoPreview.h"
#include "SettingsWidget.h"
#include "Utilities/Settings.h"
#include "libraries/csv.h"
#include "build/VTEg_autogen/include/ui/ui_mainwindow.h"
#include "Utilities/HotkeyManager.h"
#include "Utilities/FrameGrabber.h"
#include "Utilities/ObjectDetector.h"

//Including Qt dependencies
#include <QMainWindow>
#include <QWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QLabel>
#include <QGraphicsView>
#include <QRect>
#include <QSlider>
#include <QTimer>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <iterator>
#include <QProgressDialog>

// Includes for time. (Detection of single- vs double-click on ListItems)
#include <ctime>
#include <chrono>
#include <QVideoProbe>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    QListWidget *listView;

    void addExistingTagToList(VideoTag *tag) const;

private slots:

    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_actionSaveTags_triggered();

    void on_actionLoadTags_triggered();

    void on_actionSettings_triggered();

    void on_action_load_from_CSV_triggered();

    void on_action_write_to_CSV_triggered();

    void on_action_Analyze_Video_triggered();


    void tagEntryClickTimeout();

    void onTagEntryClicked(QListWidgetItem *item);

    void onTagEntryDoubleClicked(QListWidgetItem *item);

    void positionChanged(quint64);

    void durationChanged(quint64);

public slots:

    void setPosition(int);

    void handleMouseHover(int);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

    void resizeEvent(QResizeEvent *) override;

    void fireResizeEvent();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlayer::State playerState;
    VideoWidget *vw{};
    QWidget *mainWidget, *videoWidget, *videoControlsWidget, *videoTimeWidget, *videoButtonsWidget, *tagWidget, *tagButtonWidget;
    QSlider *volume;
    CustomVideoSlider *customSlider;
    QLabel *previewLabel;
    QLabel *timeLabel;
    QPushButton *addTag, *removeTag, *jumpToTag, *playButton, *pauseButton, *stopButton;
    QList<VideoTag *> *videoTags;
    QListWidgetItem *tagListClickedItem{};

    QString maxDuration;
    HotkeyManager *hotkeyManager;

    int currentTime = 0;
    bool mDoubleClicked{};

    void addTagToList() const;

    void removeTagFromList() const;

    void removeAllTagsFromList() const;

    void jumpToSelectedTag() const;

    void changeLabelTime(qint64);

    void save(const QString &filePath);

    void load(const QString &filePath);

};
#endif //MAINWINDOW_H
