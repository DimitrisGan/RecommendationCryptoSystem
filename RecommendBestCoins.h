//
// Created by dimitrisgan on 5/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H
#define RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H


#include <unordered_map>
#include "MyVector.h"
#include <algorithm>
#include <map>
#include "LSH.h"
#include "Metrics.h"
#include "SearchingAlgorithms.h"


void printrecommendedCoins2Users(const map<string,vector<string>> &RecommendedCoins2Users);


double RateCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
                  const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                  const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, int i);




//todo prepei na kanw recommend coins pou den exei hdh
vector<pair<int, double>> EvaluateAllCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
                                            const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                                            const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


//todo prepei na kane iterate epanalipsi gia kathe u sto map na callarw evaluate kai meta na vriskw to katallhlo pou thelw
vector <string> recommendBestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const string &u_Id ,int number2recommend,
                                          const vector <string> &CoinsList,
                                          const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                                          const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
                                          const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);




void  RecommendationSystem(  map<string,vector<string>> &RecommendedCoins2Users,
//                            /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/ const vector<string> &bestP_u ,
        /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/ Lsh *lsh_ptr,
                             DistanceMetrics *metric,
                             int P, //number of best Neighbors
                             int numberOfCoins2recommend, //number2recommend
                             const vector <string> &CoinsList,
                             const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                             const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
                             unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);



//void  RecommendationSystem(  map<string,vector<string>> &RecommendedCoins2Users,
//                             const vector<string> &bestP_u ,int number2recommend,
//                             const vector <string> &CoinsList,
//                             const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
//                             const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
//                             unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
//
//


#endif //RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H
