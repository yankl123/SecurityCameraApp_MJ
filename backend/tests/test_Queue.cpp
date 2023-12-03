#include "gtest/gtest.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include "JQueue.h"
#include <thread>
#include <atomic>

// Function to simulate pushing images into the queue  
void pushImages() {
    for (int i = 0; i < 10; ++i) {
        cv::Mat image(100, 100, CV_8UC3, cv::Scalar(i));
        JQueue::getInstance().push(image);
    }
}

// Function to simulate popping images from the queue  
void popImages(std::atomic<int>& count) {
    for (int i = 0; i < 10; ++i) {
        cv::Mat image = JQueue::getInstance().pop();
         count++;
    }
}

// Test case to ensure correctness and behavior of JQueue with limited size and waiting
TEST(JQueueTest, LimitedQueueSizeAndWaiting) {
    const int numThreads = 4;   
    std::atomic<int> count(0); // Atomic counter for retrieved images

    // Create multiple threads for pushing and popping images
    std::vector<std::thread> threads;

    // Start the pushImages function in a separate thread
    threads.emplace_back(pushImages);

    // Start multiple threads for popImages
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(popImages, std::ref(count));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check if the total number of retrieved images matches the expected count
    const int expectedCount = 10 * numThreads;
    EXPECT_EQ(count.load(), expectedCount);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
