#pragma once

#include <iostream>
#include "JQueue.h"
#include "Logger/Logger.h"
#include "Database/DatabaseManager.h"
#include "Detection.h"
#include "Semaphore.h"
#include <opencv2/opencv.hpp>
#include <fstream>
 

class BackendProcessor {
public:
     BackendProcessor(const std::string& outputCSV, const std::string& dbPath, const std::string& videoFileName );
    ~BackendProcessor();

    void start();
    void calculateAverageColor(const cv::Mat& image, float& R, float& G, float& B);
private:
    std::string dbPath;
    Detection detection;
    float R_sum = 0.0;
    float G_sum = 0.0;
    float B_sum = 0.0;
    int total_pixels = 0;
    void performObjectDetection(cv::Mat& frame);
    void processFrame(Semaphore& semaphore, JQueue& queue);
     void saveResultsToCSV(const cv::Rect& rect, float avgR, float avgG, float avgB);
    
    std::ofstream outputFile;
     std::string videoFileName;
    DatabaseManager databaseManager;
};



