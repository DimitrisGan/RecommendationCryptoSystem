//
// Created by dimitrisgan on 31/12/2018.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H
#define RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H

#include <iostream>
#include <vector>
#include "Tweet.h"

using namespace std;



struct myCryptoVector { //a.k.a U={u1,u2,..,un where n = number of the cryptos in the assignment
    vector <float> CryptoScore;

};




void calculateUsersSentimentCryptoScoreMap(unordered_map <string , myCryptoVector > &userTweetsSentimScore_umap,
                                           const unordered_multimap <string ,string> &userTweetsRelation_ummap,
                                           const unordered_map <string , Tweet > &tweets_umap,
                                           const unordered_map<string ,float> &vaderLexicon_umap ,
                                           const unordered_map<string ,int> &coins_umap );



#endif //RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H
