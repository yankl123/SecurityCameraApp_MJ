cmake_minimum_required(VERSION 3.10)

project(bootcamp_project)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OpenCV_DIR "${OPENCV_SRC_DIR}/build")
    set(Protobuf_DIR "${GRPC_SRC_DIR}/cmake")
    set(gRPC_DIR "${GRPC_SRC_DIR}/lib/cmake/grpc")
    set(absl_DIR "${GRPC_SRC_DIR}/lib/cmake/absl")
    set(utf8_range_DIR "${GRPC_SRC_DIR}/lib/cmake/utf8_range") 
endif()

option(WITH_TESTS "Enable build Gtest" OFF)
option(CAMERA_SIDE "build camera runner" OFF)
option(BACKEND_SIDE "build backend runner" OFF)


# Include subdirectories

if(CAMERA_SIDE)      
    add_subdirectory(camera)  
elseif(BACKEND_SIDE)
    add_subdirectory(backend) 
else()  
    add_subdirectory(backend) 
    add_subdirectory(camera)  
endif()

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

add_subdirectory(external_libs)  





