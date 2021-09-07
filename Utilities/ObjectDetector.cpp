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

#include <fstream>
#include "ObjectDetector.h"

ObjectDetector::ObjectDetector(const std::string& p) : min_confidence(Settings::getInstance()->getImageRecognitionConfidence()) {
    net = cv::dnn::readNetFromDarknet(pathToOd + "yolov3-tiny.cfg", pathToOd + "yolov3-tiny.weights");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    videoCapture.open(p);
    pathToVideo = p;
}

/**
 * Analyzes the videofile of the ObjectDetector and writes all recognized objects into a .CSV
 */
QList<VideoTag*> ObjectDetector::AnalyzeVideo() {
    if (!videoCapture.isOpened())
        if (!videoCapture.open(pathToVideo)) {
            qDebug() << "OpenCV couldn't open video at: " << QString::fromStdString(pathToVideo);
            return {};
        }

    qDebug() << "Analyzing video started";
    // Keep track of which class has been detected in the last x seconds
    auto *detectionMap = new QMap<int, int>(); // <classID, timestamp>
    auto *tagList = new QList<VideoTag*>();
    int inpWidth = 416;        // Width of network's input image
    int inpHeight = 416;       // Height of network's input image

    int iterations = 1, skipper = 1;

    std::vector<std::string> class_names;
    std::ifstream ifs(classesFile.c_str());
    std::string line;

    while(std::getline(ifs, line))
        class_names.push_back(line);

    while (videoCapture.isOpened()) {
        cv::Mat img;
        videoCapture >> img;

        videoCapture.set(cv::CAP_PROP_POS_MSEC, skipper += 500);

        qDebug() << "Skipped to ms " << skipper << " on iteration " << iterations++;

        if (img.empty()) {
            qDebug() << "Couldn't load frame, we're probably done";
            break;
        }

        // create Blob
        cv::Mat blob = cv::dnn::blobFromImage(img, 1/255.0, cv::Size(inpWidth, inpHeight), cv::Scalar(0,0,0), true, false);
        //throw Matrix into neural network
        net.setInput(blob);

        std::vector<cv::Mat> outs;
        net.forward(outs, getOutputsNames(net));

        for (size_t i = 0; i < outs.size(); i += 10) {
            auto* data = (float*)outs[i].data;
            for(int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
                cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
                cv::Point classIdPoint;
                double confidence;

                cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

                if(confidence > min_confidence) {
                    // Check if this class has already been detected in the last x seconds
                    int lastDetection = detectionMap->value(classIdPoint.x, -1);

                    qDebug() << QString::asprintf("Confidence: %.2f", confidence);

                    if (lastDetection == -1 || (skipper - lastDetection) > 5000) {
                        int secs = skipper/1000;
                        int mins = secs/60;
                        secs = secs%60;
                        tagList->append(new VideoTag(QString::asprintf("%02d:%02d", mins, secs),
                                                     QString::fromStdString(class_names[classIdPoint.x]),
                                                     QImage(img.data, img.cols, img.rows, static_cast<int>(img.step),
                                                            QImage::Format_RGB888).copy(),
                                                     skipper));
                    }
                    detectionMap->insert(classIdPoint.x, skipper);
                }
            }
        }

        std::vector<double> layersTimes;
        double freq = cv::getTickFrequency() / 1000;
        double t = (double) net.getPerfProfile(layersTimes) / freq;
        qDebug() << QString::asprintf("Inference time for a frame : %.2f ms", t);
        /*

        // Matrix with all class detections
        cv::Mat results(output.size[2], output.size[3], CV_32F, output.ptr<float>());


        // Iterate over detection classes to determine weather one meets the detection threshold
        for (int i = 0; i < results.rows; i++) {

            // Pick selected class and check if confidence exceeds threshold
            int classID = int(results.at<float>(i, 1));
            float confidence = results.at<float>(i, 2);

            // If a class was detected, create a tag and add it to our list
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
                    qDebug() << "Appended a tag to the list";

                    // Set last reference
                    detectionMap->insert(classID, timestamp);

                    // Debug
                    qDebug() << "Detection of class " << classID << " at: " << timestamp;
                }
            }
        }*/
    }
    return *(tagList);
}

std::vector<cv::String> ObjectDetector::getOutputsNames(const cv::dnn::Net& n) {
    static std::vector<cv::String> names;

    if (names.empty()) {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> outLayers = n.getUnconnectedOutLayers();

        //get the names of all the layers in the network
        std::vector<cv::String> layersNames = n.getLayerNames();

        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}