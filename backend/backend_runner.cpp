
#include <thread>
 #include "VideoServer.h"  

#include "BackendProcessor.h"
#include "Logger/Logger.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world480d.lib")
#else
#pragma comment(lib, "opencv_world480.lib")
#endif

int main(int argc, char* argv[]) {
    std::string videoPath = "C:/Users/Moshe Sayada/Documents/MobileyeBootcamp_ASO/ProjectKamatec/ProjectKamatec/BLK-HDPTZ12 Security Camera Parkng Lot Surveillance Video.mp4";
    std::string outputDB = "C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO/ProjectKamatec/ProjectKamatec/Database/output.db";
    std::string outputCSV = "C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO/ProjectKamatec/ProjectKamatec/Database/output.csv";

    // Initialize the custom logger
    Logger::Init();
 

    // Create the backend processor
    size_t lastSlash = videoPath.find_last_of("/\\");
    std::string videoFileName = (lastSlash != std::string::npos) ? videoPath.substr(lastSlash + 1) : videoPath;
    BackendProcessor backendProcessor(outputCSV, outputDB, videoFileName);
    ////LOG_INFO("Starting program...");
    VideoServer server("0.0.0.0:50051");
    std::thread serverThread(&VideoServer::run, &server);
    backendProcessor.start();
    ////LOG_INFO("Starting backend processing...");
 
    backendProcessor.start();
    ////LOG_INFO("Backend processing finished.");
 
    ////join
    //serverThread.join();
    // Shutdown the logger
    spdlog::shutdown();

    return 0;
}
