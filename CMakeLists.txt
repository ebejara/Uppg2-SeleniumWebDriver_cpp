cmake_minimum_required(VERSION 3.14)
project(SeleniumWebDriverCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# GoogleTest
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
    GIT_TAG 1.10.5  # stable version
)
FetchContent_MakeAvailable(cpr)

# webdriverxx
FetchContent_Declare(
    webdriverxx
    GIT_REPOSITORY https://github.com/GermanAizek/webdriverxx.git
    GIT_TAG master
)
FetchContent_MakeAvailable(webdriverxx)

add_executable(tests tests/login_tests.cpp)

target_include_directories(tests PRIVATE 
    ${webdriverxx_SOURCE_DIR}/include
)

target_link_libraries(tests PRIVATE 
    webdriverxx 
    cpr::cpr          # This includes libcurl automatically
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)