cmake_minimum_required(VERSION 3.12)
project(RecommendationCryptoSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RecommendationCryptoSystem
    AssistantFunctions.cpp
    AssistantFunctions.h
    ClusterAPI.h
    main.cpp
    myCryptoVector.cpp
    myCryptoVector.h
    MyVector.cpp
    MyVector.h
    Tweet.cpp
    Tweet.h)
