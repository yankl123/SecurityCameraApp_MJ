#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include "JQueue.h"
#include <fstream>

#ifdef _WIN32
#undef ACCESS_MASK // Undefine ACCESS_MASK to avoid conflict
#include <windows.h> // Include Windows headers after undefining
#endif

// Namespaces.
using namespace cv;
using namespace std;
using namespace cv::dnn;

// Constants.
const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.5;
const float NMS_THRESHOLD = 0.45;
const float CONFIDENCE_THRESHOLD = 0.45;

// Text parameters.
const float FONT_SCALE = 0.7;
const int FONT_FACE = FONT_HERSHEY_SIMPLEX;
const int THICKNESS = 1;

 

class Detection {

public:
 
 	vector<Mat> pre_process(Mat& input_image);
 	vector<Rect> post_process_to_rects(Mat& input_image, vector<Mat>& outputs);

	Detection();

private:
	bool  processDetection(const float* detectionData, const cv::Mat& inputImage, std::vector<Rect>& resultRects);
	std::vector<Rect> extractBoundingBoxes(const cv::Mat& inputImage, const std::vector<Mat>& outputs);
 

	vector<string> class_list;
	Net net;
};

 
 
