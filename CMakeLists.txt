cmake_minimum_required(VERSION 3.14)
project(SeleniumWebDriverCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# libcurl (behövs för webdriverxx)
find_package(CURL REQUIRED)

# webdriverxx är submodule – inkludera det
add_subdirectory(extern/webdriverxx)

# Huvudprogram (valfritt, om du vill ha ett main för manuell test)
add_executable(main src/main.cpp)
target_include_directories(main PRIVATE extern/webdriverxx/include include)
target_link_libraries(main PRIVATE CURL::libcurl webdriverxx)

# Tester
add_executable(tests tests/login_tests.cpp)
target_include_directories(tests PRIVATE extern/webdriverxx/include include)
target_link_libraries(tests PRIVATE GTest::gtest_main CURL::libcurl webdriverxx)

enable_testing()
gtest_discover_tests(tests)