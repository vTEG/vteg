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

#include "TensorflowObjectDetection.h"

/**
 * Creates an ObjectDetector object
 * @param video the path to the video as a std::string
 */
TensorflowObjectDetection::TensorflowObjectDetection(const std::string& video) : min_confidence(Settings::getInstance()->getImageRecognitionConfidence()) {
    net = cv::dnn::readNetFromTensorflow(pathToOd + "frozen_inference_graph.pb", pathToOd + "ssd_mobilenet_v1_ppn_coco.pbtxt");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    videoCapture.open(video);
    pathToVideo = video;
}

/**
 * Analyzes the videofile of the ObjectDetector and writes all recognized objects into a .CSV
 * @param progressDialog QProgressDialog where we update the user on the analyzing progress
 */
QList<VideoTag*> TensorflowObjectDetection::AnalyzeVideo(QProgressDialog* progressDialog) {
    if (!videoCapture.isOpened())
        if (!videoCapture.open(pathToVideo)) {
            qDebug() << "OpenCV couldn't open video at: " << QString::fromStdString(pathToVideo);
            return {};
        }

    qDebug() << "Analyzing video started";

    progressDialog->open();

    std::vector<std::string> class_names;
    std::ifstream ifs(classesFile.c_str());
    std::string line;

    while(std::getline(ifs, line))
        class_names.push_back(line);

    int skipper = 1;

    auto *detectionMap = new QMap<int, int>(); // <classID, timestamp>
    auto *tagList = new QList<VideoTag*>();

    while(videoCapture.isOpened()) {

        videoCapture.set(cv::CAP_PROP_POS_MSEC, skipper += 250);

        progressDialog->setValue(skipper);
        cv::Mat image;

        bool isSuccess = videoCapture.read(image);

        // Check if image is loaded in correctly
        if (!isSuccess){
            std::cout << "Could not load the image!" << std::endl;
            break;
        }

        // Create a blob from the image
        cv::Mat blob = cv::dnn::blobFromImage(image, 1.0, cv::Size(300, 300), cv::Scalar(127.5, 127.5, 127.5),
                                 true, false);


        // Set the blob to be input to the neural network
        net.setInput(blob);

        // Forward pass of the blob through the neural network to get the predictions
        cv::Mat output = net.forward();



        // Matrix with all the detections
        cv::Mat results(output.size[2], output.size[3], CV_32F, output.ptr<float>());

        // Run through all the predictions
        for (int i = 0; i < results.rows; i++) {


            int class_id = int(results.at<float>(i, 1));
            class_id--;
            float confidence = results.at<float>(i, 2);

            if (confidence > min_confidence) {
                // Check if this class has already been detected in the last x seconds
                int lastDetection = detectionMap->value(class_id, -1);
                qDebug() << QString::asprintf("Confidence: %.2f", confidence);

                if (lastDetection == -1 || (skipper - lastDetection) > 2000) {
                    int secs = skipper / 1000;
                    int mins = secs / 60;
                    secs = secs % 60;
                    tagList->append(new VideoTag(QString::asprintf("%02d:%02d", mins, secs),
                                                 QString::fromStdString(class_names[class_id]),
                                                 QImage(image.data, image.cols, image.rows,
                                                        static_cast<int>(image.step),
                                                        QImage::Format_RGB888).copy(),
                                                 skipper));
                }
                detectionMap->insert(class_id, skipper);
            }
        }
        std::vector<double> layersTimes;
        double freq = cv::getTickFrequency() / 1000;
        double t = (double) net.getPerfProfile(layersTimes) / freq;
        qDebug() << QString::asprintf("Inference time for a frame : %.2f ms", t);
    }
    videoCapture.release();
    progressDialog->setValue(progressDialog->maximum());
    return *(tagList);
}