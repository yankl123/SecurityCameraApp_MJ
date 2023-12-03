#pragma once

#include <iostream>
#include <string>

#include "CameraProcessor.h"
#include "VideoClient.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world480d.lib")
#else
#pragma comment(lib, "opencv_world480.lib")
#endif


using namespace std;

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <video_path> <server_address>" << std::endl;
        return 1;
    }

    // Extract the command-line arguments
    std::string video_path = argv[1];
   // std::string video_path = "/app/mp4file";
    std::string server_address = argv[2];

    // Print the provided arguments
    std::cout << "Video Path: " << video_path << std::endl;
    std::cout << "Server Address: " << server_address << std::endl;
    server_address = "10.222.78.56:50051";
    video_path = "C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO/ProjectKamatec/Camera/BLK-HDPTZ12 Security Camera Parkng Lot Surveillance Video.mp4";

    // Create the client
    VideoClient client(server_address);

    CameraProcessor processor(video_path, &client);
    processor.start();
    processor.saveSelectedFrames("C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO/ProjectKamatec/Camera/Logger");
    //processor.displaySelectedFrames();
     std::cout << "Finished sending all frames." << std::endl;
    return 0;
}