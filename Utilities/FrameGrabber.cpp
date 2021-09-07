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

#include "FrameGrabber.h"

FrameGrabber::FrameGrabber(const QString& p) {
    this->path = p.toStdString();
    videoCapture.open(path);
}

/**
 * Grabs a frame from the opened video at the given timestamp
 * @param timestamp the timestamp we wan't to get the frame at
 * @return returns a QImage of the frame at the timestamp
 */
QImage FrameGrabber::grabFrame(qint64 timestamp) {
    if(!videoCapture.isOpened())
        if(!videoCapture.open(path)) {
            qDebug() << "OpenCV couldn't file at: " << QString::fromStdString(path);
            return {};
        }
    qDebug() << "VideoCapture set: " << videoCapture.set(cv::CAP_PROP_POS_MSEC, (double) timestamp);
    cv::Mat mat;
    videoCapture >> mat;
    return QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888).copy();
}
