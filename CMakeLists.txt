cmake_minimum_required(VERSION 3.14)
project(SeleniumWebDriverCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ----------------------------
# GoogleTest (via FetchContent)
# ----------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ----------------------------
# CPR (fetches libcurl)
# ----------------------------
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.5
)

if(WIN32)
    # Windows / MinGW fix for curl non-blocking sockets
    set(HAVE_IOCTLSOCKET 1 CACHE INTERNAL "")
    set(HAVE_IOCTLSOCKET_FIONBIO 1 CACHE INTERNAL "")
    set(HAVE_O_NONBLOCK 0 CACHE INTERNAL "")
    set(HAVE_FCNTL_O_NONBLOCK 0 CACHE INTERNAL "")
    set(HAVE_WINSOCK2_H 1 CACHE INTERNAL "")
    set(HAVE_WS2TCPIP_H 1 CACHE INTERNAL "")
    add_definitions(-DCURL_USE_WIN32_NONBLOCKING)

    set(CPR_CURL_NOSIGNAL ON CACHE BOOL "Disable SIGPIPE handling" FORCE)
    set(CPR_FORCE_WINSSL_BACKEND OFF CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(cpr)

# ----------------------------
# WebDriverXX (header-only)
# ----------------------------
add_subdirectory(extern/webdriverx)

# ----------------------------
# Tests
# ----------------------------
add_executable(tests tests/login_tests.cpp)

target_include_directories(tests PRIVATE 
    extern/webdriverx/include
)

target_link_libraries(tests PRIVATE 
    cpr::cpr
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
