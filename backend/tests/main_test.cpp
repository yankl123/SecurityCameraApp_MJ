#include "gtest/gtest.h"
#include "opencv2/opencv.hpp"

#include "../Backend/BackendProcessor.h"
#include "../Backend/JQueue.h"
#include "../Backend/Logger/Logger.h"
#include <iostream>
#include <thread>

#include "test_backend_processor.cpp"
#include "test_camera_processor.cpp"

 


int main(int argc, char** argv) {
    Logger::DisableLogging();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}