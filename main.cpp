#include "Windows/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(breeze_themes);
    QFile file(":/" + Settings::getInstance()->getTheme() + "/stylesheet.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    a.setStyleSheet(stream.readAll());
    MainWindow w;
    w.show();
    return QApplication::exec();
}