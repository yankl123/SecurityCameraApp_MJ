#include "JQueue.h"

// JQueue.cpp
JQueue::JQueue() {
    // Constructor implementation
}


JQueue& JQueue::getInstance() {
    static JQueue instance; // This will be created only once
    return instance;
}

void JQueue::push(const cv::Mat& frame) {
    std::unique_lock<std::mutex> lock(mtx);
    if (imageQueue.size() == 5) {
        imageQueue.pop();
    }
    imageQueue.push(frame);
    cv.notify_one();
}

cv::Mat JQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    while (imageQueue.empty()) {
        std::cout << "The queue is empty!\n";
        cv.wait(lock);
    }
    cv::Mat frame = imageQueue.front();
    imageQueue.pop();
    return frame;
}

bool JQueue::empty()   {
    std::unique_lock<std::mutex> lock(mtx);
    return imageQueue.empty();
}
