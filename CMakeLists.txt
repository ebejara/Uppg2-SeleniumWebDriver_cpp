cmake_minimum_required(VERSION 3.14)
project(SeleniumWebDriverCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# GoogleTest (still using FetchContent)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# CPR (fetches libcurl automatically)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.5
)
FetchContent_MakeAvailable(cpr)

# webdriverxx – now using local submodule (with your patch!)
add_subdirectory(extern/webdriverx)

add_executable(tests tests/login_tests.cpp)

target_include_directories(tests PRIVATE 
    extern/webdriverx/include
)

target_link_libraries(tests PRIVATE 
    webdriverxx 
    cpr::cpr 
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)