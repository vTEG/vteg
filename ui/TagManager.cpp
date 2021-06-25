//
// Created by Xida on 25.06.2021.
//

#include "TagManager.h"

TagManager::TagManager(QWidget *parent) : QDialog(parent){
    this->parentWindow = parent;

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(finished(int)), this, SLOT(dialogFinished(int)));

    auto *l = new QVBoxLayout;
    l->setSizeConstraint(QLayout::SetNoConstraint);
    l->addWidget(buttonBox);
    setLayout(l);

    // Modal := Window is forced to be focused window
    setModal(true);

    setWindowTitle(tr("Vteg - Tag Manager"));
}


void TagManager::dialogFinished(int) {
    if (result() == QDialog::Accepted){
        qDebug() << "Clicked okay";
    } else {
        qDebug() << "Clicked cancel.";
    }
}