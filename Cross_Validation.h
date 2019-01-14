//
// Created by dimitrisgan on 13/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_CROSS_VALIDATION_H
#define RECOMMENDATIONCRYPTOSYSTEM_CROSS_VALIDATION_H


#include <string>
#include <unordered_map>
#include "MyVector.h"

#include "myCryptoVector.h"
#include "LSH.h"
#include "ClusteringProxSearching.h"
#include "AssistantFunctions.h"


using namespace std;
//
//create if lsh:
//parameters
//=new LSH


double
cross_validation(string configFileName, string type,
                 const unordered_map<string, myVector> &userTweetsSentimScore_umapStartState,
                 int P,
                 unsigned dimUserSentScoreVectors, int foldingTimes, int crypto2hide);


double MAE(vector <pair<double,double>> predictedAndRealScorePair);//Mean Absolute Error

vector<string> keys2change(const vector<string> &keysU,int i,int foldIn10piecesNumber);

vector<pair<string,int>> changeDataset(unordered_map<string, myVector>  &userTweetsSentimScore_umap, const vector <string> &keysU2Change,int crypto2hide);

#endif //RECOMMENDATIONCRYPTOSYSTEM_CROSS_VALIDATION_H
