//
// Created by Xida on 25.06.2021.
//

#ifndef VTEG_TAGMANAGER_H
#define VTEG_TAGMANAGER_H

#include <QWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>
#include <QComboBox>


class TagManager : public QDialog {

    Q_OBJECT

private slots:
    void dialogFinished(int);

private:
    QWidget *parentWindow;
    QDialogButtonBox *buttonBox;
    QComboBox *categoryComboBox;



public:
    explicit TagManager(QWidget *parent);


};


#endif //VTEG_TAGMANAGER_H
