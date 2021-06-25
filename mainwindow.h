#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-connect-by-name"
//
// Created by tomme on 14.06.2021.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Including header
#include "VideoTag.h"
#include "videowidget.h"
#include "videowidgetsurface.h"

//Including Qt dependencies
#include <QMainWindow>
#include <QWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>

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

private slots:
    void on_actionOpen_triggered();
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();
    void on_actionSaveTags_triggered();
    void on_actionLoadTags_triggered();
    

    void tagEntryClickTimeout();
    void onTagEntryClicked(QListWidgetItem *item);
    void onTagEntryDoubleClicked(QListWidgetItem *item);

    void positionChanged(quint64);
    void durationChanged(quint64);
    void setPosition(int);

protected:
    bool eventFilter(QObject* object, QEvent* event) override;
    void resizeEvent(QResizeEvent*) override;
    void fireResizeEvent();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlayer::State playerState;
    VideoWidget *vw{};
    QWidget *mainWidget, *videoWidget, *videoControlsWidget, *videoTimeWidget,*videoButtonsWidget, *tagWidget, *tagButtonWidget;
    QSlider *slider{}, *volume;
    QLabel *timeLabel;
    QPushButton *addTag, *removeTag, *jumpToTag, *playButton, *pauseButton, *stopButton;
    QList<VideoTag*> *videoTags;
    QListWidgetItem* tagListClickedItem{};

    QString maxDuration;


    int currentTime = 0;
    bool mDoubleClicked{};

    void addTagToList() const;
    void removeTagFromList() const;
    void removeAllTagsFromList() const;
    void jumpToSelectedTag() const;
    void changeLabelTime(qint64);

    void save(const QString& filePath);
    void load(const QString& filePath);
};

#endif //MAINWINDOW_H