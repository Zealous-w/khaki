PROJECT(main)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(echo "./echo.cpp")
ADD_EXECUTABLE(mamba "./Mamba.h" "./Mamba.cpp")

#LINK_DIRECTORIES("/home/khaki/item/khaki")
SET(LIB_SOURCE "/home/khaki/item/khaki")

TARGET_LINK_LIBRARIES(echo ${LIB_SOURCE}/libkhaki.a)
TARGET_LINK_LIBRARIES(mamba ${LIB_SOURCE}/libkhaki.a)