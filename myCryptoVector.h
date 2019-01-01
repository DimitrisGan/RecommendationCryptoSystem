//
// Created by dimitrisgan on 31/12/2018.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H
#define RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H

#include <iostream>
#include <vector>
#include "Tweet.h"
#include <unordered_map>
#include <set>
#include <assert.h>
#include <limits>

using namespace std;



struct myCryptoVector { //a.k.a U={u1,u2,..,un where n = number of the cryptos in the assignment
    //todo fitaxnw constructor pou na arxikopoiei 100 theseis vector me apeiro
    vector <float> CryptoScore;

    myCryptoVector();
    ~myCryptoVector() = default;

    void printCryptoVector();

    //todo ftiaxnw setCryptoVector()
    void setMyCryptoVector(set<int> CoinsIndexes2addScoreInUser , float totalScore);


};




void calculateUsersSentimentCryptoScoreMap(unordered_map <string , myCryptoVector > &userTweetsSentimScore_umap,
                                           const unordered_multimap <string ,string> &userTweetsRelation_ummap,
                                           const unordered_map <string , Tweet > &tweets_umap,
                                           const unordered_map<string ,float> &vaderLexicon_umap ,
                                           const unordered_map<string ,int> &coins_umap );



#endif //RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H
