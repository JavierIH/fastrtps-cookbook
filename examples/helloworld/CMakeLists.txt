cmake_minimum_required(VERSION 2.8.12)
project("helloworld")

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(--std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(--std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

add_executable(publisher publisher.cpp message.cpp messagePubSubTypes.cpp)
target_link_libraries(publisher fastrtps fastcdr)

add_executable(subscriber subscriber.cpp message.cpp messagePubSubTypes.cpp)
target_link_libraries(subscriber fastrtps fastcdr)
