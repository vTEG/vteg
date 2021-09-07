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

ObjectDetector::ObjectDetector(const std::string& p) : min_confidence(Settings::getInstance()->getImageRecognitionConfidence()) {
    net = cv::dnn::readNet(pathToOd + "frozen_inference_graph.pb", pathToOd + "ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt", "TensorFlow");
    videoCapture.open(p);
    pathToVideo = p;
}

/**
 * Analyzes the videofile of the ObjectDetector and writes all recognized objects into a .CSV
 */
QList<VideoTag> ObjectDetector::AnalyzeVideo() {
    if (!videoCapture.isOpened())
        if (!videoCapture.open(pathToVideo)) {
            qDebug() << "OpenCV couldn't open video at: " << QString::fromStdString(pathToVideo);
            return {};
        }

    qDebug() << "Analyzing video started";
    // Keep track of which class has been detected in the last x seconds
    auto *detectionMap = new QMap<int, qint64>(); // <classID, timestamp>
    auto *tagList = new QList<VideoTag*>();

    //QList<VideoTag *> *videoTags;

    qint64 timestamp = 1;

    while (videoCapture.isOpened()) {
        cv::Mat img;

        bool isSuccess = videoCapture.read(img);

        if (!isSuccess) {
            qDebug() << "Couldn't load frame";
            break;
        }

        int imgHeight = img.cols;
        int imgWidth = img.rows;

        auto start = cv::getTickCount();

        // create Blob
        cv::Mat blob = cv::dnn::dnn4_v20210301::blobFromImage(img, 1.0, cv::Size(300, 300),
                                                              cv::Scalar(127.5, 127.5, 127.5), true, false);

        //throw Matrix into neural network
        net.setInput(blob);

        cv::Mat output = net.forward();
        auto end = cv::getTickCount();

        // Matrix with all class detections
        cv::Mat results(output.size[2], output.size[3], CV_32F, output.ptr<float>());


        // Iterate over detection classes to determine weather one meets the detection threshold
        for (int i = 0; i < results.rows; i++) {

            // Pick selected class and check if confidence exceeds threshold
            int classID = int(results.at<float>(i, 1));
            float confidence = results.at<float>(i, 2);

            // If a class was detected, display a border around the object
            if (confidence > min_confidence) {

                // Check if this class has already been detected in the last x seconds
                int lastDetection = static_cast<int>(detectionMap->value(classID, -1));

                timestamp = (end - start) / (qint64) cv::getTickFrequency();

                if (lastDetection == -1 || (timestamp - lastDetection) > 5) {

                    // Add new VideoTag to the list
                    tagList->append(new VideoTag(QString::asprintf("ClassID: %d", classID),
                                                 "Description: ",
                                                 QImage(img.data, img.cols, img.rows, static_cast<int>(img.step),
                                                        QImage::Format_RGB888).copy(),
                                                 timestamp));

                    // Set last reference
                    detectionMap->insert(classID, timestamp);

                    // Debug
                    qDebug() << "Detection of class " << classID << " at: " << timestamp;
                }
            }
        }
    }
}