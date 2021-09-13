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

#include "ObjectDetector.h"

/**
 * Creates an ObjectDetector object
 * @param video the path to the video as a std::string
 */
ObjectDetector::ObjectDetector(const std::string& video) : min_confidence(Settings::getInstance()->getImageRecognitionConfidence()) {
    net = cv::dnn::readNetFromDarknet(pathToOd + "yolov3-tiny.cfg", pathToOd + "yolov3-tiny.weights");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    videoCapture.open(video);
    pathToVideo = video;
}

/**
 * Analyzes the videofile of the ObjectDetector and writes all recognized objects into a .CSV
 */
QList<VideoTag*> ObjectDetector::AnalyzeVideo(QProgressDialog* progressDialog) {
    if (!videoCapture.isOpened())
        if (!videoCapture.open(pathToVideo)) {
            qDebug() << "OpenCV couldn't open video at: " << QString::fromStdString(pathToVideo);
            return {};
        }

    qDebug() << "Analyzing video started";

    progressDialog->open();
    // Keep track of which class has been detected in the last x seconds
    auto *detectionMap = new QMap<int, int>(); // <classID, timestamp>
    auto *tagList = new QList<VideoTag*>();
    int inpWidth = 320;        // Width of network's input image
    int inpHeight = 320;       // Height of network's input image

    int iterations = 1, skipper = 1;

    std::vector<std::string> class_names;
    std::ifstream ifs(classesFile.c_str());
    std::string line;

    while(std::getline(ifs, line))
        class_names.push_back(line);

    while (videoCapture.isOpened()) {
        videoCapture.set(cv::CAP_PROP_POS_MSEC, skipper += 250);

        qDebug() << "Skipped to ms " << skipper << " on iteration " << iterations++;
        cv::Mat img;
        videoCapture >> img;

        if (img.empty()) {
            qDebug() << "Couldn't load frame, we're probably done";
            break;
        }
        else if(progressDialog->wasCanceled())
            break;

        // create Blob
        cv::Mat blob = cv::dnn::blobFromImage(img, 1/255.0, cv::Size(inpWidth, inpHeight), cv::Scalar(0,0,0), true, false);
        //throw Matrix into neural network
        net.setInput(blob);

        cv::Mat out;
        net.forward(out);

        int rowsNoOfDetection = out.rows;
        int colsCoordinatesPlusClassScore = out.cols;

        for (int i = 0; i < rowsNoOfDetection; ++i) {            // for each row, the score is from element 5 up to number of classes index
            progressDialog->setValue(skipper);

            //(5 - N columns)
            cv::Mat scores = out.row(i).colRange(5, colsCoordinatesPlusClassScore);
            cv::Point PositionOfMax;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &PositionOfMax);

            if(confidence > min_confidence) {
                // Check if this class has already been detected in the last x seconds
                int lastDetection = detectionMap->value(PositionOfMax.x, -1);
                qDebug() << QString::asprintf("Confidence: %.2f", confidence);

                if (lastDetection == -1 || (skipper - lastDetection) > 2000) {
                    int secs = skipper/1000;
                    int mins = secs/60;
                    secs = secs%60;
                    tagList->append(new VideoTag(QString::asprintf("%02d:%02d", mins, secs),
                                                 QString::fromStdString(class_names[PositionOfMax.x]),
                                                 QImage(img.data, img.cols, img.rows, static_cast<int>(img.step),
                                                        QImage::Format_RGB888).copy(),
                                                 skipper));
                }
                detectionMap->insert(PositionOfMax.x, skipper);
            }
        }

        std::vector<double> layersTimes;
        double freq = cv::getTickFrequency() / 1000;
        double t = (double) net.getPerfProfile(layersTimes) / freq;
        qDebug() << QString::asprintf("Inference time for a frame : %.2f ms", t);
    }
    progressDialog->setValue(progressDialog->maximum());
    return *(tagList);
}