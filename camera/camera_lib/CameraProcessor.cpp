 
#include "CameraProcessor.h"

CameraProcessor::CameraProcessor(const std::string& videoPath,  VideoClient* Client)
 {
    videoClient = Client;

     // Open the video file if a path is provided
    if (!videoPath.empty()) {
        capture.open(videoPath);
        if (!capture.isOpened()) {
            std::cout << videoPath << std::endl;
            std::cout << "Error: Could not open the video." << std::endl;
            //LOG_ERROR("Error: Could not open the video.");
        }
    }
    // If videoPath is empty or "0", open the default camera (webcam)
    else {
        capture.open(0);
        if (!capture.isOpened()) {
            std::cout << "Error: Could not open the default camera." << std::endl;
            //LOG_ERROR("Error: Could not open the default camera.");
        }
    }
}

bool CameraProcessor::isFrameSimilar(const cv::Mat& currentFrame, const cv::Mat& previousFrame) {
    double threshold = 1;
  
    // Ensure that the frames have the same size and type
    if (currentFrame.size() != previousFrame.size() || currentFrame.type() != previousFrame.type()) {
        return false; // Frames are not comparable
    }

    // Calculate the mean squared error (MSE) between the two frames
    cv::Mat difference;
    cv::absdiff(currentFrame, previousFrame, difference); 
    cv::Scalar mse = cv::mean(difference.mul(difference));

    // Compare the MSE with the threshold to determine similarity  
    double mseValue = mse[0] + mse[1] + mse[2];
    cout << "MSE: " << mseValue << std::endl;
    if (mseValue <= threshold) {
        
        return true; // Frames are similar
    }
    else {
        return false; // Frames are not similar
    }
}

//void CameraProcessor::pushUniqueFrame(const cv::Mat& frame) {
//    imageQueue.push(frame.clone());
//}


void CameraProcessor::start() {
 
    std::thread senderThread(&CameraProcessor::sendFrames, this);
    cv::Mat previousFrame;
    	capture >> previousFrame;

    int frameNumber = 0;
    while (true) {
        cv::Mat frame;
        capture >> frame;

        if (frame.empty())
            break;

        if (!isFrameSimilar(frame, previousFrame)) {
            // Enqueue the frame for sending
            selectedFramesQueue.push(frame.clone());

            frameQueue.push(frame.clone());
            previousFrame = frame.clone();

            // Increment the frame counter.
           
        }

        frameNumber++;
    }

    // Signal the sender thread to finish
    senderThread.join();
}


void CameraProcessor::sendFrames() {//line 78
    while (true) {
        cv::Mat frame;

        // Dequeue frames for sending
        frame = frameQueue.pop();

        frameCounter++;

        // Log or print the frame number and send the frame.
        std::cout << "Sending frame #" << frameCounter << std::endl;
        
        videoClient->sendMat(frame);
        saveSelectedFrames("C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO/ProjectKamatec/Camera/Logger");
        // Sleep for 1 second  
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

 

void CameraProcessor::saveSelectedFrames(const std::string& outputDirectory) {
    int frameCount = 0; // Initialize a frame counter

    while (!selectedFramesQueue.empty()) {
        // Save the frame to disk
        std::string outputFileName = outputDirectory + "/frame_" + std::to_string(frameCount) + ".png";
        cv::imwrite(outputFileName, selectedFramesQueue.front());

        selectedFramesQueue.pop();
        frameCount++; // Increment the frame counter
    }
}

void CameraProcessor::displaySelectedFrames() {
    int frameCount = 0; // Initialize a frame counter
    cv::namedWindow("Selected Frames", cv::WINDOW_NORMAL);
    cv::resizeWindow("Selected Frames", 800, 600);

    while (!selectedFramesQueue.empty()) {
        // Generate a dynamic title for each frame
        std::string frameTitle = "Frame " + std::to_string(frameCount);

        // Display the frame with the dynamic title
        cv::imshow(frameTitle, selectedFramesQueue.front());

        cv::waitKey(1000); // Wait for 1 second before showing the next frame
        selectedFramesQueue.pop();

        frameCount++; // Increment the frame counter
    }

    cv::destroyAllWindows(); // Close all windows when done
}

