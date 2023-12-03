#pragma once

//#include "spdlog/spdlog.h"

#include "JQueue.h"
#include <thread>
#include <chrono>

#include <iostream>
#include <queue>
#include <opencv2/opencv.hpp>
//#include "Logger/Logger.h"
#include "VideoClient.h"


 
class CameraProcessor {
public:
    CameraProcessor(const std::string& videoPath,   VideoClient* Client);
 
    void start();
    bool isFrameSimilar(const cv::Mat& currentFrame, const cv::Mat& previousFrame);
    void sendFrames();
    void displaySelectedFrames();
    void saveSelectedFrames(const std::string& outputDirectory);

    ~CameraProcessor() {
        std::cout << "Total frames sent: " << frameCounter << std::endl;
    }

private:
    VideoClient* videoClient;
    cv::VideoCapture capture;
    mutex mutex;  // Mutex for protecting previousFrame
    JQueue frameQueue;
    int frameCounter = 0;
    std::queue<cv::Mat> selectedFramesQueue; // Queue to store selected frames
    //JQueue& imageQueue;
    //std::shared_ptr<spdlog::logger> logger;
    //void pushUniqueFrame(const cv::Mat& frame);
    //distractor

};
