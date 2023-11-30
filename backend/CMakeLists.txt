project(backend)

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/external_libs/image_grpc/common.cmake)  

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
    spdlog::spdlog
)

# Additional Include Directories
target_include_directories(${PROJECT_NAME}  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend_lib
    ${CMAKE_SOURCE_DIR}/external_libs/spdlog-1.x/include/spdlog
    ${CMAKE_SOURCE_DIR}/external_libs/image_grpc
    ${OpenCV_INCLUDE_DIRS} 
)
# Write the JSON content to a file
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/settings.json" "${JSON_CONTENT}")



