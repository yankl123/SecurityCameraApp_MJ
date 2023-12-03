
#include "BackendProcessor.h"



 

BackendProcessor::BackendProcessor(const std::string& outputCSV, const std::string& dbPath, const std::string& videoFileName )
    : dbPath(dbPath), videoFileName(videoFileName)  {

    int rc = sqlite3_initialize();
    databaseManager.openDatabase(dbPath);
    databaseManager.prepareStatements(); // Prepare SQLite statements


    outputFile.open(outputCSV);
    if (!outputFile.is_open()) {
        //std::cout << "Error: Could not open the CSV file '" << outputCSV << "'." << std::endl;
        LOG_ERROR("Could not open the CSV file '{}'.", outputCSV);
    }
    else {
        outputFile << "Time,Top,Left,Width,Height,AvgR,AvgG,AvgB" << std::endl;
    }

    // Initialize sum counters for average color calculation
    R_sum = 0.0;
    G_sum = 0.0;
    B_sum = 0.0;
    total_pixels = 0;
}

BackendProcessor::~BackendProcessor()
{
    databaseManager.closeDatabase(); // Close the SQLite database
    outputFile.close();
}

void BackendProcessor::processFrame(Semaphore& semaphore, JQueue& queue) {
    while (true) {
        semaphore.wait(); // Wait on semaphore before processing frame

        cv::Mat frame = queue.pop(); // Dequeue frame
        performObjectDetection(frame); // Process the frame

        semaphore.notify(); // Notify semaphore after processing
    }
}

void BackendProcessor::start() {
    std::cout << "Starting backend processor..." << std::endl;

    Semaphore frame_semaphore(5); // Initialize semaphore
    JQueue& queue = JQueue::getInstance(); // Assuming JQueue is a singleton

    std::vector<std::thread> spiders; // Vector to hold worker threads

    // Create worker threads (spiders)
    for (int i = 0; i < 5; ++i) {
        //spiders.emplace_back(processFrame, std::ref(frame_semaphore), std::ref(queue));
        spiders.push_back(std::thread(&BackendProcessor::processFrame, this, std::ref(frame_semaphore), std::ref(queue)));

    }

    // Optionally, join threads if you want to wait for them to finish
    for (auto& spider : spiders) {
        if (spider.joinable()) {
            spider.join();
        }
    }
}




//void BackendProcessor::start() {
//    LOG_INFO("Starting backend processor...");
//    while (true) {
//        std::cout << "Waiting for frame..." << std::endl;
//        time_t curr_time;
//        curr_time = time(NULL);
//
//        char* tm = ctime(&curr_time);
//        cout << "Today is : " << tm;
//
//
// 
//        cv::Mat frame = JQueue::getInstance().pop();
//        performObjectDetection(frame);
//    }
//}

void BackendProcessor::performObjectDetection(cv::Mat& frame) {
    // Log that object detection is starting.
    LOG_INFO("Performing object detection...");

    // Log the size of the input frame.
    LOG_INFO("Frame size: {}x{}", frame.cols, frame.rows);

    // Display the input frame using OpenCV.
    //imshow("Detected Objects", frame);
    //cv::waitKey(1);  // Wait for a short time to update the display.

    // Variables to store average color values (Red, Green, Blue).
    float avgR, avgG, avgB;

    // Vector to store detection results.
    vector<Mat> detections;

    // Preprocess the input frame for object detection.
    detections = detection.pre_process(frame);

    // Check if any objects were detected.
    if (detections.empty()) {
        LOG_ERROR("Error: No objects detected in the frame.");
        return;
    }

    // Vector to store detected regions as rectangles.
    vector<Rect> detectedRegions = detection.post_process_to_rects(frame, detections);

    // Check if any objects were detected after post-processing.
    if (detectedRegions.empty()) {
        LOG_ERROR("Error: No objects detected in the frame after post-processing.");
        return;
    }

    // Process each detected region individually.
    for (const cv::Rect& detectedRegion : detectedRegions) {
        // Display the detected region within the original frame.
       // imshow("Detected Object", frame(detectedRegion));
        cv::waitKey(1);  // Wait for a short time to update the display.

        // Calculate average color values (Red, Green, Blue) for the detected region.
        calculateAverageColor(frame(detectedRegion), avgR, avgG, avgB);

        // Save detection results to a CSV file.
        /*saveResultsToCSV(detectedRegion, avgR, avgG, avgB);*/

        // Store detection results in a database.
        databaseManager.executeInsertStatement(detectedRegion, avgR, avgG, avgB);

        // Reset average color variables for the next iteration.
        avgR = avgG = avgB = 0.0;
    }

    // Log that frame processing is complete.
    LOG_INFO("Finished processing frame.");
}


void BackendProcessor::saveResultsToCSV(const cv::Rect & rect, float avgR, float avgG, float avgB) {


    int left = rect.x;
    int top = rect.y;
    int width = rect.width;
    int height = rect.height;
    // Write the results to the CSV file.
    outputFile << std::to_string(time(NULL)) << "," << std::to_string(top) << "," << std::to_string(left) << ","
        << std::to_string(width) << "," << std::to_string(height) << ","
        << std::to_string(avgR) << "," << std::to_string(avgG) << "," << std::to_string(avgB) << std::endl;

}

void BackendProcessor::calculateAverageColor(const cv::Mat& image, float& R, float& G, float& B) {
    R = G = B = 0.0;

    // Loop through each pixel in the image and accumulate color values
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            R_sum += pixel[2]; // Red channel
            G_sum += pixel[1]; // Green channel
            B_sum += pixel[0]; // Blue channel
            total_pixels++;
        }
    }

    // Calculate the average color values
    if (total_pixels > 0) {
        R = R_sum / total_pixels;
        G = G_sum / total_pixels;
        B = B_sum / total_pixels;
    }
}



