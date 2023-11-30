cmake_minimum_required(VERSION 3.10)

project(external_libs)

add_subdirectory(image_grpc)
add_subdirectory(nlohmann_json)
add_subdirectory(spdlog-1.x)

if(WITH_TESTS)
    add_subdirectory(googletest-release-1.11.0)    
endif()





