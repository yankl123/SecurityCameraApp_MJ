project(backend)

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(JSON_CONTENT 
  "{
    \"VIDEO_PATH\" : \"\",
    \"LOG_FILE_PATH\" : \"logs.txt\",
    \"NUM_CHANNELS\" : 3,
    \"SIGNIFICAT_IMG_CHANGE\" : 1,
    \"SERVER_ADDRESS\" : \"localhost\",
    \"PORT\" : \"50051\",
    \"YOLO_PATH\" : \"C:/SecurityCameraApp_MJ/backend/Yolo/yolov5s.onnx\",
    \"DB_PATH\" : \"./output.db\"
}" 
)

# Find Package
find_package(OpenCV REQUIRED)

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install it or provide its location.")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(EXECUTABLE_OUTPUT_PATH "bin")
endif()

add_subdirectory(backend_lib)
add_subdirectory(sqlite)

add_executable(${PROJECT_NAME} backend_runner.cpp) 

target_link_libraries(${PROJECT_NAME} PRIVATE
    backend_lib
)

# Additional Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend_lib
)
# Write the JSON content to a file
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Yolo/coco.names"  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/settings.json" "${JSON_CONTENT}")



