#pragma once

#include <queue>
#include <mutex>
#include <opencv2/opencv.hpp>

class JQueue {
public:
    static JQueue& getInstance();

    void push(const cv::Mat& frame);
    cv::Mat pop();
    bool empty()  ;

/*private*/
    JQueue(); // Private constructor to prevent instantiation
    JQueue(const JQueue&) = delete; // Delete copy constructor
    JQueue& operator=(const JQueue&) = delete; // Delete assignment operator

    std::queue<cv::Mat> imageQueue;
    std::mutex mtx;
    std::condition_variable cv;
};
