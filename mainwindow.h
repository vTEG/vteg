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

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *vw{};
    QWidget *mainWidget, *tagWidget, *tagButtonWidget;
    QSlider *slider{}, *volume;
    QLabel *timeLabel;
    QPushButton *addTag, *removeTag, *jumpToTag;
    QList<int> *timestamps;

    int currentTime = 0;

    void addTagToList() const;
    void removeTagFromList() const;
    void jumpToSelectedTag() const;
    void changeLabelTime(qint64);
};

#endif //MAINWINDOW_H
