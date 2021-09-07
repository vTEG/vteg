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

#ifndef VTEG_OBJECTDETECTOR_H
#define VTEG_OBJECTDETECTOR_H

#include "libraries/opencv2/opencv.hpp"
#include "Utilities/Settings.h"
#include "Utilities/VideoTag.h"

#include <QDebug>

class ObjectDetector {
public:
    explicit ObjectDetector(const std::string&);
    QList<VideoTag*> AnalyzeVideo();
    std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);

private:
    cv::dnn::Net net;
    cv::VideoCapture videoCapture;
    float min_confidence;
    std::string pathToOd = "OD/", pathToVideo, classesFile = pathToOd + "coco.names";
};


#endif //VTEG_OBJECTDETECTOR_H
