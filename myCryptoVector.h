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

#include "MyVector.h"
#include "Cluster.h"

#define ALPHA 15

using namespace std;


//
//
//struct myCryptoVector { //a.k.a U={u1,u2,..,un where n = number of the cryptos in the assignment
//    //todo fitaxnw constructor pou na arxikopoiei 100 theseis vector me apeiro
//    vector <double> CryptoScore;
//
//    myCryptoVector();
//
//    void setCryptoScore(const vector<double> &CryptoScore);
//
//    ~myCryptoVector() = default;
//
//    void printCryptoVector();
//
//    //todo ftiaxnw setCryptoVector()
//    void setMyCryptoVector(set<int> CoinsIndexes2addScoreInUser , double totalScore);
//
//
//
//    myCryptoVector operator+(const myCryptoVector& q) {
//
//        vector <double> NewCoords (this->CryptoScore.size() , 0);
////        NewCoords.resize(q.coords.size());
////        for ( auto &coor  : NewCoords ) {
////            cout << coor << "\t";
////        }
//        myCryptoVector result;//(NewCoords);
//        result.setCryptoScore(NewCoords);
//
//        assert(this->CryptoScore.size() == q.CryptoScore.size());
//
//        vector<double >::const_iterator  ItA, ItB;
//
//        ItA = this->CryptoScore.begin();
//        ItB = q.CryptoScore.begin();
//        double inf = std::numeric_limits<double>::infinity();
//
//
//        unsigned int index=0;
//        while(true)
//        {
//            //TODO EDW GRAFW
//
//            if (*ItA == inf && *ItB == inf){
//                result.CryptoScore[index] = inf;
//
//            }
//            if (*ItA == inf && *ItB != inf){// to current
//                result.CryptoScore[index] = *ItB;
//
//            }
//            if (*ItA != inf && *ItB == inf){// to current
//                result.CryptoScore[index] = *ItA;
//
//            }
//            if (*ItA != inf && *ItB != inf){// to current
//                result.CryptoScore[index] = *ItA + *ItB;
//
//            }
//
//            index++;
//
//
//            if(ItA != this->CryptoScore.end())
//            {
//                ++ItA;
//            }
//            if(ItB != q.CryptoScore.end())
//            {
//                ++ItB;
//            }
//            if(ItA == this->CryptoScore.end() && ItB == q.CryptoScore.end())
//            {
//                break;
//            }
//
//        }
//
//        return result;
//    }
//
//};

void changeInfsToAverageSentimentsAndDiscardZeroVectors(
        unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfs_umap,
        const unordered_map<string, myVector> &userTweetsSentimScore_umap,
        const unordered_map<string, double> &userTweetsAverageSentimScore_umap);


void calculateAverageU_umap(unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                            const unordered_map<string, myVector> &userTweetsSentimScore_umap);


void calculateUsersSentimentCryptoScoreMap(unordered_map<string, myVector> &userTweetsSentimScore_umap,
                                           const unordered_multimap<string, string> &userTweetsRelation_ummap,
                                           const unordered_map<string, Tweet> &tweets_umap,
                                           const unordered_map<string, double> &vaderLexicon_umap,
                                           const unordered_map<string, int> &coins_umap, int userVectorSize);



void calculateNormalizeUsersSentimentCryptoScoreMap(unordered_map <string , myVector > &userTweetsSentimScoreNormalized_umap,
                                                    const unordered_map <string , myVector > &userTweetsSentimScore_umap );


void calculateVirtualUsersFromTwitterCluster(unordered_map<string, myVector> &virtualUserTweetsSentimScore_umap,
                                             kClusters &TwitterCluster, const unordered_map<string, Tweet> &tweets_umap,
                                             const unordered_map<string, double> &vaderLexicon_umap,
                                             const unordered_map<string, int> &coins_umap, int userVectorSize);


void printUsersSentimentCryptoScoreMap(const unordered_map <string , myVector > &userTweetsSentimScore_umap);



double calculateAverageU(const myVector &u );


myVector  normalizeU(const myVector &u , const double& avrg);


int isZeroVector(const vector <double> &coords);



double calculateSentimentScore(double totalScore);




// Function to check if the key is present or not
string check_key(const unordered_map<string ,double> &m, const string &key); // m = vaderLexicon_umap




set<string> extractMultiMapKeys (const unordered_multimap <string ,string> &userTweetsRelation_ummap);

/*returns a vector of coins indexes to add and totalscore */
set<int>    calculateTweetsScore(const string &tweetId, double &totalScore ,const unordered_map <string , Tweet > &tweets_umap,
                                 const unordered_map<string ,double> &vaderLexicon_umap  , const unordered_map<string ,int> &coins_umap );





#endif //RECOMMENDATIONCRYPTOSYSTEM_MYCRYPTOVECTOR_H
