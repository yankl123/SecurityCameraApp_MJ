#pragma once

#include <iostream>
#include <string>
#include "CameraGlobalDef.h"
#include "CameraJson.h" 
#include "CameraProcessor.h"
#include "VideoClient.h"


using namespace std;

#include <iostream>
#include <string>

int main() {
    // Print the provided arguments
    loadJsonFile("../settings.json");

    string colon = ":";
    string  socket = SERVER_ADDRESS + colon + PORT;
    cout << socket;
    // Create the client
    VideoClient client(socket);

    CameraProcessor processor(VIDEO_PATH, &client);
    processor.start();
    processor.saveSelectedFrames(FRAMES_DIR);
    //processor.displaySelectedFrames();
     std::cout << "Finished sending all frames." << std::endl;
    return 0;
}