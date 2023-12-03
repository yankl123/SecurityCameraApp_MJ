#include "AccidentDetection.h"
 

const float MIN_VEHICLE_SPEED = 10.0;  
const float MAX_COLLISION_DISTANCE = 50.0;  

AccidentDetection::AccidentDetection(const std::string& videoSource) : capture_(videoSource) {
    if (!capture_.isOpened()) {
        std::cerr << "Error: Could not open the video." << std::endl;
        exit(-1);
    }
}

void AccidentDetection::Run() {
    cv::Mat frame;
    std::vector<cv::Rect> prevRects;

    while (capture_.read(frame)) {
        std::vector<cv::Rect> currentRects = yoloDetector.post_process_to_rects(frame);

        if (!prevRects.empty()) {
            CheckForAccidents(prevRects, currentRects);
        }
        prevRects = currentRects;
     }

    capture_.release();
    cv::destroyAllWindows();
}

 

void AccidentDetection::CheckForAccidents(const std::vector<cv::Rect>& prevRects, const std::vector<cv::Rect>& currentRects) {
 
    for (const cv::Rect& prevRect : prevRects) {
        for (const cv::Rect& currentRect : currentRects) {
            float speed = CalculateSpeed(prevRect, currentRect, 1.0 / 30.0); // Assuming 30 frames per second
            float distance = CalculateDistance(prevRect, currentRect);

            if (IsPotentialAccident(speed, distance)) {
                HandleAccident();
                return; 
            }
        }
    }
}

float AccidentDetection::CalculateSpeed(const cv::Rect& prevRect, const cv::Rect& currentRect, float timeInSeconds) {


    return;
}

float AccidentDetection::CalculateDistance(const cv::Rect& rect1, const cv::Rect& rect2) {
 
    return;
}

bool AccidentDetection::IsPotentialAccident(float speed, float distance) {
 
    return (speed >= MIN_VEHICLE_SPEED) && (distance <= MAX_COLLISION_DISTANCE);
}

void AccidentDetection::HandleAccident() {
     std::cout << "Potential accident detected. Taking appropriate action." << std::endl;
}
 
