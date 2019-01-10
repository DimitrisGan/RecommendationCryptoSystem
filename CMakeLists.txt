cmake_minimum_required(VERSION 3.12)
project(RecommendationCryptoSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RecommendationCryptoSystem
        AbstractLSH_CUBE.cpp
        AbstractLSH_CUBE.h
        Assignment.cpp
        Assignment.h
        AssistantFunctions.cpp
        AssistantFunctions.h
        Cluster.cpp
        Cluster.h
        ClusterAPI.cpp
        ClusterAPI.h
        CosineSimilarityCube.cpp
        CosineSimilarityCube.h
        CosineSimilarityLSH.cpp
        CosineSimilarityLSH.h
        CubeAbstract.h
        CubeFunctions.cpp
        CubeFunctions.h
        EuclideanSpaceCube.cpp
        EuclideanSpaceCube.h
        EuclideanSpaceLSH.cpp
        EuclideanSpaceLSH.h
        EvaluationMetric.cpp
        EvaluationMetric.h
        HashTablesStructures.cpp
        HashTablesStructures.h
        HyperCube.cpp
        HyperCube.h
        Initialization.cpp
        Initialization.h
        LSH.cpp
        LSH.h
        LshSimple.h
        main.cpp
        Metrics.cpp
        Metrics.h
        myCryptoVector.cpp
        myCryptoVector.h
        MyVector.cpp
        MyVector.h
        SearchingAlgorithms.cpp
        SearchingAlgorithms.h
        Tweet.cpp
        Tweet.h
        Update.cpp
        Update.h RecommendBestCoins.cpp RecommendBestCoins.h VirtualUsers.cpp VirtualUsers.h AbstractLSH_CLUSTER.cpp AbstractLSH_CLUSTER.h ClusteringProxSearching.cpp ClusteringProxSearching.h)
