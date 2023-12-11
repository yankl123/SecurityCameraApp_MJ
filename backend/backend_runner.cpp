
#include <thread>
#include "VideoServer.h"  
#include "BackendGlobalDef.h"
#include "VideoServer.h"  
#include "BackendProcessor.h"
#include "Logger/Logger.h"
#include "BackendJson.h" 


int main(int argc, char* argv[]) {
    std::string outputCSV = "C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO/ProjectKamatec/ProjectKamatec/Database/output.csv";
    
    loadJsonFile("../settings.json");
    // Initialize the custom logger
    Logger::Init();
   
    //LOG_INFO("Starting program...");
  
    VideoServer server("0.0.0.0:" + PORT);
    // Create the backend processor
    BackendProcessor backendProcessor(outputCSV,DB_PATH,VIDEO_PATH);
  
    ////LOG_INFO("Starting program...");
    VideoServer server("0.0.0.0:50051");
    std::thread serverThread(&VideoServer::run, &server);
    
    backendProcessor.start();
    ////LOG_INFO("Starting backend processing...");
 
    /*backendProcessor.start();*/
    ////LOG_INFO("Backend processing finished.");
 
    ////join
    serverThread.join();
    // Shutdown the logger
    spdlog::shutdown();

    return 0;
}
