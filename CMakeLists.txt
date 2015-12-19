cmake_minimum_required(VERSION 3.3)
project(T7_Computer_Architecture_Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lboost_unit_test_framework -pthread")

FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


set(SOURCE_FILES main.cpp Decoder/Decoder.hpp)
add_executable(Main ${SOURCE_FILES})

#set(SOURCE_FILES Decoder/Decoder.hpp Tests/Tests.cpp)
#add_executable(Tests ${SOURCE_FILES})
#
#
#TARGET_LINK_LIBRARIES(Tests ${Boost_LIBRARIES})
