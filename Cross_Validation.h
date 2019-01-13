//
// Created by dimitrisgan on 13/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_CROSS_VALIDATION_H
#define RECOMMENDATIONCRYPTOSYSTEM_CROSS_VALIDATION_H


#include <string>
#include <unordered_map>
#include "MyVector.h"

#include "ClusteringProxSearching.h"
#include "AssistantFunctions.h"


using namespace std;
//
//create if lsh:
//parameters
//=new LSH


double cross_validation(string configFileName, string type, unordered_map<string, myVector> userTweetsSentimScore_umap,
                        int P , int dimUserSentScoreVectors , int foldingTimes);
//
//
//        );


vector<string> keys2change(const vector<string> &keysU,int i,int foldIn10piecesNumber);


#endif //RECOMMENDATIONCRYPTOSYSTEM_CROSS_VALIDATION_H
