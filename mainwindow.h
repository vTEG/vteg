//
// Created by tomme on 14.06.2021.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>

// Includes for time. (Detection of single- vs double-click on ListItems)
#include <ctime>
#include <chrono>
#include <QVideoProbe>
#include "VideoTag.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
        Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;
    QListWidget *listView;

private slots:
    void on_actionOpen_triggered();
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();

    void tagEntryClickTimeout();
    void onTagEntryClicked(QListWidgetItem *item);
    void onTagEntryDoubleClicked(QListWidgetItem *item);

    void processFrame(const QVideoFrame& frame);

protected:
    bool eventFilter(QObject* object, QEvent* event);
    void resizeEvent(QResizeEvent*);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlayer::State playerState;
    QVideoProbe *videoProbe;
    QVideoFrame *lastVideoFrame{nullptr};
    QImage *lastVideoImage;
    QVideoWidget *vw{};
    QWidget *mainWidget, *videoWidget, *videoControlsWidget, *tagWidget, *tagButtonWidget;
    QSlider *slider{}, *volume;
    QLabel *timeLabel;
    QPushButton *addTag, *removeTag, *jumpToTag;
    QList<int> *timestamps;
    QListWidgetItem* tagListClickedItem;
    std::list<VideoTag*> tagList;

    int currentTime = 0;
    bool mDoubleClicked;
    bool saveNextFrame = false;

    void addTagToList() const;
    void removeTagFromList() const;
    void jumpToSelectedTag() const;
    void changeLabelTime(qint64);
};

#endif //MAINWINDOW_H
