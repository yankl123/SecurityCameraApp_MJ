project(camera_lib)

cmake_minimum_required(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/external_libs/image_grpc/common.cmake)  

# Find Package
find_package(OpenCV REQUIRED)

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install it or provide its location.")
endif()

file(GLOB SOURCES 
    *.c *.cc *.cpp *.h *.hpp 
)
add_library(${PROJECT_NAME} STATIC
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    absl::flags
    image_grpc
    absl::flags_parse
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_directories(${PROJECT_NAME} PUBLIC ${OpenCV_DIR}/x64/vc16/lib)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses REQUIRED)
    
    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${OpenCV_LIBS}
        ${CURSES_LIBRARIES}
    )   
endif()

# additional include directories
target_include_directories(camera_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/external_libs/spdlog-1.x/include/spdlog
    ${CMAKE_SOURCE_DIR}/external_libs/image_grpc
    ${CMAKE_SOURCE_DIR}/external_libs/nlohmann_json
    ${Protobuf_INCLUDE_DIRS}
)
	

