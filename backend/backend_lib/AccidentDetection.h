 #pragma once
#include <semaphore>

#include "Detection.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class AccidentDetection {
public:
    AccidentDetection(const std::string& videoSource);
    void Run();

private:
    cv::VideoCapture capture_;
     Detection yoloDetector;
    //DetectObjects is gets the current frame and returns a vector of rectangles
   std::vector<cv::Rect> DetectObjects(cv::Mat& frame);

   //  gets the previous and current rectangles and checks if there is an accident
    void CheckForAccidents(const std::vector<cv::Rect>& prevRects, const std::vector<cv::Rect>& currentRects);

    // gets the previous and current rectangles and calculates the speed of the object
    float CalculateSpeed(const cv::Rect& prevRect, const cv::Rect& currentRect, float timeInSeconds);

    //  gets two rectangles and calculates the distance between them
    float CalculateDistance(const cv::Rect& rect1, const cv::Rect& rect2);

    //  gets the speed and distance and checks if there is a potential accident
    bool IsPotentialAccident(float speed, float distance);

    //  handles the accident 
    void HandleAccident();
 };

 