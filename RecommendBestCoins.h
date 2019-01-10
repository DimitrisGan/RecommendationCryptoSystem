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


class RecommendCoins{
private:
    ;

    Lsh *lsh_ptr;
    int P; //number of best Neighbors;
    int numberOfCoins2recommend; //number2recommend
    const vector <string> CoinsList;
    unordered_map <string , myVector > userTweetsSentimScore_umap;  //we need it to not a recommend an laready existing coin that user has spoken about

    unordered_map<string, double> U_userTweetsAverageSentimScore_umap;
    unordered_map<string, myVector> U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;

    const unordered_map<string, double> V_userTweetsAverageSentimScore_umap;
    unordered_map<string, myVector> V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;

public:
    void operator()(map<string,vector<string>>  &RecommendedCoins2Users ,DistanceMetrics *metric );

    RecommendCoins(Lsh *lsh_ptr, int P, int numberOfCoins2recommend, const vector<string> &CoinsList,
                   const unordered_map<string, myVector> &userTweetsSentimScore_umap,
                   const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                    unordered_map<string, myVector> &U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                   const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                    unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

    virtual ~RecommendCoins() = default;
};




//==============================================================================================
//==============================================================================================

void printrecommendedCoins2Users(const map<string,vector<string>> &RecommendedCoins2Users);


double RateCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
                  const unordered_map<string, double> &U_rating_umap,
                  const unordered_map<string,double> &V_rating_umap,
                  const unordered_map<string, myVector> &V_users_umap, int i);



/*from all the neighbors calculate all the crypto's the Sentiment Score*/
vector <string> recommendBestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const string &u_Id ,int number2recommend,
                                          const vector <string> &CoinsList,
                                          const unordered_map <string , myVector > &userTweetsSentimScore_umap ,

                                          const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                                          const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                                          const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


//todo prepei na kane iterate epanalipsi gia kathe u sto map na callarw evaluate kai meta na vriskw to katallhlo pou thelw
vector <string> recommendBestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const string &u_Id ,int number2recommend,
                                          const vector <string> &CoinsList,
                                          const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                                          const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
                                          const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);




//void  RecommendationSystem(  map<string,vector<string>> &RecommendedCoins2Users,
////                            /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/ const vector<string> &bestP_u ,
//        /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/ Lsh *lsh_ptr,
//                             DistanceMetrics *metric,
//                             int P, //number of best Neighbors
//                             int numberOfCoins2recommend, //number2recommend
//                             const vector <string> &CoinsList,
//                             const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
//                             const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
//                             unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);



void  RecommendationSystem(  map<string,vector<string>> &RecommendedCoins2Users,
//                            /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/ const vector<string> &bestP_u ,
        /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/
                             Lsh *lsh_ptr,
                             DistanceMetrics *metric,
                             int P, //number of best Neighbors
                             int numberOfCoins2recommend, //number2recommend
                             const vector <string> &CoinsList,
                             const unordered_map <string , myVector > &userTweetsSentimScore_umap , //we need it to not a recommend an laready existing coin that user has spoken about

                             const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                             const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                             unordered_map<string, myVector> &U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                             unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap
);


#endif //RECOMMENDATIONCRYPTOSYSTEM_RECOMMENDBESTCOINS_H
