cmake_minimum_required(VERSION 3.14)
project(SeleniumWebDriverCpp)

# Tvinga statisk build överallt
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Specifikt för curl (som CPR bygger in):
set(CURL_ZLIB OFF CACHE BOOL "" FORCE)        # Stänger av zlib helt
set(CURL_USE_OPENSSL OFF CACHE BOOL "" FORCE) # Undvik OpenSSL-DLL:er om du inte behöver HTTPS (Selenium localhost är HTTP)

# MinGW statisk runtime (för att undvika libgcc/libstdc++ DLL:er)
if(MINGW)
    add_link_options(-static -static-libgcc -static-libstdc++)
endif()

# Konsekvent output till bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

#
set(GTEST_FOUND TRUE)
set(GTEST_LIBRARIES GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
set(GTEST_INCLUDE_DIRS ${googletest_SOURCE_DIR}/googletest/include ${googletest_SOURCE_DIR}/googlemock/include)


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
#gtest_discover_tests(tests)