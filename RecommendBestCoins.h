//
// Created by dimitrisgan on 5/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H
#define RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H


#include <unordered_map>
#include "MyVector.h"

//todo meta tha kanw kai ena recommend for all u's pou tha kanei recommend gia ola ta u
void recommend5BestCoinsForUser();
void recommend2BestCoinsForUser();


vector <int> recommend5BestCoinsForUser(const myVector &u ,const vector<string> &bestP_u ,const  unordered_map <string , myVector > &userTweetsSentimScoreNormalized_umap  );


#endif //RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H
