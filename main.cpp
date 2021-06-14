#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto *player = new QMediaPlayer;
    auto *vw = new QVideoWidget;

    player->setVideoOutput(vw);

    player->setMedia(QUrl::fromLocalFile("C:/Users/tomme/Videos/Counter-strike  Global Offensive/Counter-strike  Global Offensive 2021.05.01 - 20.27.20.06.DVR.mp4"));

    vw->setGeometry(100,100,1024,768);
    vw->show();

    player->play();

    qDebug() << player->state();

    return QApplication::exec();
}
