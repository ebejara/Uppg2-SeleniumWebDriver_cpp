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


# FIX FÖR MINWG/WINDOWS: Tvinga curl att använda Windows socket-API
set(HAVE_IOCTLSOCKET 1 CACHE INTERNAL "")
set(HAVE_IOCTLSOCKET_FIONBIO 1 CACHE INTERNAL "")
set(HAVE_O_NONBLOCK 0 CACHE INTERNAL "")
set(HAVE_FCNTL_O_NONBLOCK 0 CACHE INTERNAL "")
set(HAVE_WINSOCK2_H 1 CACHE INTERNAL "")
set(HAVE_WS2TCPIP_H 1 CACHE INTERNAL "")


# Hämta CPR – det hämtar och bygger libcurl automatiskt (precis som i Uppg3!)
set(CPR_CURL_NOSIGNAL ON CACHE BOOL "Disable SIGPIPE handling" FORCE)
set(CPR_FORCE_WINSSL_BACKEND OFF CACHE BOOL "" FORCE)  # Använd Schannel istället om WinSSL krånglar
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.5  # Stabil version
)
FetchContent_MakeAvailable(cpr)

# webdriverxx som submodule
add_subdirectory(extern/webdriverxx)

# Main (om du har)
add_executable(main src/main.cpp)
target_include_directories(main PRIVATE 
    include 
    extern/webdriverxx/include
)

target_link_libraries(main PRIVATE cpr::cpr )

# Tester
add_executable(tests tests/login_tests.cpp)
target_include_directories(tests PRIVATE 
    include 
    extern/webdriverxx/include   # ← KRITISK RAD!
)
target_link_libraries(tests PRIVATE GTest::gtest_main cpr::cpr )

enable_testing()
gtest_discover_tests(tests)