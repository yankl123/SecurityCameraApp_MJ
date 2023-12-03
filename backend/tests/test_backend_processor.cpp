//#include "gtest/gtest.h"
//#include "opencv2/opencv.hpp"
//
//#include "../BackendProcessor.h"
//#include "../CameraProcessor.h"
//#include "../JQueue.h"
//
//// Namespaces.
//using namespace cv;
//using namespace std;
//using namespace cv::dnn;
//
//#ifdef _DEBUG
//#pragma comment(lib, "opencv_world480d.lib")
//#else
//#pragma comment(lib, "opencv_world480.lib")
//#endif
////
//TEST(BackendProcessorTest, General) {
//  	//JQueue queue;
//	//std::string videoPath = "C:/Users/Moshe Sayada/Documents/MobileyeBootcamp_ASO/ProjectKamatec/ProjectKamatec/BLK-HDPTZ12 Security Camera Parkng Lot Surveillance Video.mp4";
//
//	//CameraProcessor cameraProcessor(videoPath, queue);
//	//std::thread cameraThread(&CameraProcessor::start, &cameraProcessor);
//
//	////BackendProcessor backendProcessor("output_test.csv", queue);
// //
//	////backendProcessor.start();
// 	//cameraThread.join();
//     BackendProcessor backendProcessor("output_test.csv", "output_test.db", "test_video.mp4", queue);
//
//    // Add appropriate initialization and start logic for BackendProcessor
//    // For example:
//    // backendProcessor.prepareStatements();
//    // std::thread backendThread(&BackendProcessor::start, &backendProcessor);
//    // backendThread.join();
//}
// 
//TEST(BackendProcessorTest, PerformObjectDetectionTest) {
//    cv::Mat testFrame(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
//    JQueue queue;
//    BackendProcessor backendProcessor("output_test.csv", "output_test.db", "test_video.mp4", queue);
//
//    // You can't directly call performObjectDetection from here
//    // You need to design your test so that you can simulate the call to performObjectDetection
//    // For example, by mocking the necessary dependencies and actions
//    // Then, you can assert whether the expected behavior occurs
//    // For now, you can leave this test case empty
//}
//
//
//
