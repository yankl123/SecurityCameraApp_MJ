cmake_minimum_required(VERSION 3.14.2)
project(BackendTests)


if(WIN32)
    set(BASE_PATH "C:/Users/Moshe Sayada/Documents/repos/MobileyeBootcamp_ASO")
    set(SQLite3_LIBRARIES "${BASE_PATH}/sqlite/lib/sqlite3.lib")
    set(Spdlog_LIBRARIES "${BASE_PATH}/spdlog/out/build/x64-Debug/spdlogd.lib")
else() # Assuming Linux for now
    set(BASE_PATH "/home/moshe_sayada/projects/MobileyeBootcamp_ASO")
     set(Spdlog_LIBRARIES "spdlog::spdlog_header_only")
endif()


# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(BackendTests
    main_test.cpp
 
)
 
 
target_link_libraries(BackendTests
${OpenCV_LIBS}
${SQLite3_LIBRARIES}
${Spdlog_LIBRARIES}
$<$<BOOL:${MINGW}>:ws2_32>
    gtest
    gtest_main
    Backend  
    GTest::GTest
 )

 add_test(BackendTests   test_backend_processor.cpp)



# Add test(s) using CTest
include(GoogleTest)
gtest_discover_tests(BackendTests)
