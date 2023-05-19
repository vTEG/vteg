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

#ifndef VTEG_CUSTOMVIDEOSLIDER_H
#define VTEG_CUSTOMVIDEOSLIDER_H

#include <QDebug>
#include <QSlider>
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QPaintEvent>
#include <QLabel>
#include <QList>
#include <QPainterPath>

#include "Utilities/VideoTag.h"


class CustomVideoSlider : public QSlider {
    Q_OBJECT

private:
    bool mouseDown;
    QList<VideoTag*> *tags;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

public:
    explicit CustomVideoSlider(QWidget *parent) {
        this->setParent(parent);
        setFixedHeight(5);
        setMouseTracking(true);
        mouseDown = false;
        tags = nullptr;
    }

    explicit CustomVideoSlider(QWidget *parent, QList<VideoTag*> *tags) {
        this->setParent(parent);
        setFixedHeight(10);
        setMouseTracking(true);
        mouseDown = false;
        this->tags = tags;
    }

    ~CustomVideoSlider() override = default;

Q_SIGNALS:
    void mouseHover(int position);

};


#endif //VTEG_CUSTOMVIDEOSLIDER_H
