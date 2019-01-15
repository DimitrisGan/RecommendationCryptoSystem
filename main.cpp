#include <iostream>
#include <unordered_map>
#include <fstream>

#include "AssistantFunctions.h"
#include "Tweet.h"
#include "myCryptoVector.h"
#include "ClusterAPI.h"
#include "SearchingAlgorithms.h"
#include "RecommendBestCoins.h"
#include "ClusteringProxSearching.h"
#include "Cross_Validation.h"
#include <cmath>


int main(int argc , char** argv) {

    string inCoinsFileName = "./inputs/coins_queries.csv";
    string inVadarLexinconFile = "./inputs/vader_lexicon.csv";
    string inTweetsDatasetFile = "./inputs/tweets_dataset_small.csv";

    string configFileNameForLsh1 = "./configs/lsh1.conf";
    string configFileNameForLsh2 = "./configs/lsh2.conf";
    string configFileNameForCluster1 = "./configs/cluster1.conf";
    string configFileNameForCluster2 = "./configs/cluster2.conf";
    string configFileNameForCluster3 = "./configs/cluster3.conf";

    string inFileName = "./inputs/twitter_dataset_small_v2.csv";
    string OutFileName = "./outputs/OutputProject3";


    int validateFlag=0 ;//todo change me
//    ReadHandleArgms( argc,  argv , inFileName , OutFileName , validateFlag);

    vector <string> CoinsList;
    unordered_map<string ,int> coins_umap;
    unordered_map<string ,double> vaderLexicon_umap;

    ReadCoinsFile_saveIt(inCoinsFileName , CoinsList , coins_umap );

    unsigned  dimUserSentScoreVectors = static_cast<int>(CoinsList.size());

    ReadVaderLexicon_saveIt(inVadarLexinconFile , vaderLexicon_umap);

    unordered_map <string , Tweet > Tweets_umap;
    unordered_multimap <string ,string> userTweetsRelation_ummap;
    int P ;

    ReadTweetsInputDat_saveIt(inTweetsDatasetFile, Tweets_umap, userTweetsRelation_ummap, P);

    cout << "P: "<<P<<endl;

    unordered_map <string , myVector > userTweetsSentimScore_umap;

    /*U USERS-VECTORS*/
    calculateUsersSentimentCryptoScoreMap(userTweetsSentimScore_umap, userTweetsRelation_ummap, Tweets_umap,
                                          vaderLexicon_umap,
                                          coins_umap, dimUserSentScoreVectors);

    /*U USERS-VECTORS CHANGED THE INFS TO AVRG SENTIMENT*/
    unordered_map <string , myVector > userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
    unordered_map <string , double > userTweetsAverageSentimScore_umap;

    calculateAverageU_umap(userTweetsAverageSentimScore_umap, userTweetsSentimScore_umap);

    changeInfsToAverageSentimentsAndDiscardZeroVectors(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                       userTweetsSentimScore_umap, userTweetsAverageSentimScore_umap);

//    printUsersSentimentCryptoScoreMap(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

    //================== making the virtual clusters ================

    unsigned int dimTfIdfVec = 0;

    unordered_map<string, myVector> in_Tf_Idf_Tweets_umap; //in_umap from project2

    ReadInFile_save2umap(inFileName, in_Tf_Idf_Tweets_umap, dimTfIdfVec );


    kClusters TwitterCluster;
    ClusterProcedure(TwitterCluster, in_Tf_Idf_Tweets_umap, configFileNameForCluster1, dimTfIdfVec, 0);


/*C VIRTUAL-USERS-VECTORS*/

    unordered_map <string , myVector > virtualUserTweetsSentimScore_umap;

    calculateVirtualUsersFromTwitterCluster(virtualUserTweetsSentimScore_umap, TwitterCluster, Tweets_umap,
                                            vaderLexicon_umap,
                                            coins_umap, dimUserSentScoreVectors);



/*C USERS-VECTORS CHANGED THE INFS TO AVRG SENTIMENT*/


    unordered_map <string , myVector > virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
    unordered_map <string , double > virtualUserTweetsAverageSentimScore_umap;


    calculateAverageU_umap(virtualUserTweetsAverageSentimScore_umap, virtualUserTweetsSentimScore_umap);

    changeInfsToAverageSentimentsAndDiscardZeroVectors(virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                       virtualUserTweetsSentimScore_umap, virtualUserTweetsAverageSentimScore_umap);
//    printUsersSentimentCryptoScoreMap(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


//    ============================ U-V LSH's ====================================


    /*SAVE THE nonInf&zero U's IN THE LSH*/

    Lsh *lsh_Users_ptr = new Lsh(configFileNameForLsh1, userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                 dimUserSentScoreVectors); //lsh-cosine for  u's

    /*SAVE THE nonInf&zero C's IN THE LSH*/
    Lsh *lsh_virtualUsers_ptr = new Lsh(configFileNameForLsh2,
                                        virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                        dimUserSentScoreVectors); //lsh-cosine for  c's



//    //=============================== U-V CLUSTER's ==============================


    //ADD UsCluster && CsCluster IN NEW STRUCTURE THAT IMPLEMENTS getSuperSet() and keeps as attribute the euclidean distance

    auto *clust_U = new ClusteringProxSearching(configFileNameForCluster2,
                                                userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                dimUserSentScoreVectors, 0);
    auto *clust_C = new ClusteringProxSearching(configFileNameForCluster3,
                                                virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                dimUserSentScoreVectors, 0);

//    //=============================================================================
    /*NUMBER OF COINS TO RECOMMEND*/
    int numberOfCoins2recommend_U = 5;
    int numberOfCoins2recommend_C = 2;


////===================================== FUNCTOR INSTANTIATIONS =======================================
//
    /*FOR REAL-U USERS*/
    auto *RecommendFromRealUsers =  new RecommendCoins(P, numberOfCoins2recommend_U, CoinsList,
                                                       userTweetsSentimScore_umap,
                                                       userTweetsAverageSentimScore_umap,                      //U_userTweetsAverageSentimScore_umap,
                                                       userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,    //U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                       userTweetsAverageSentimScore_umap,                      //V_userTweetsAverageSentimScore_umap,
                                                       userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);   //V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

//    /*FOR VIRTUAL-C USERS*/
    auto *RecommendFromVirtualUsers = new RecommendCoins(P, numberOfCoins2recommend_C, CoinsList,
                                                         userTweetsSentimScore_umap,
                                                         userTweetsAverageSentimScore_umap,                            //U_userTweetsAverageSentimScore_umap,
                                                         userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,          //U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                         virtualUserTweetsAverageSentimScore_umap,                     //V_userTweetsAverageSentimScore_umap,
                                                         virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);  //V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);;


//==========================================================================================================

    DistanceMetrics *metricCos = new CosineMetric;
    DistanceMetrics *metricEucl = new EuclideanMetric;

    map<string,vector<string>> RecommendedCoins2UsersLSH;
    map<string,vector<string>> RecommendedCoins2UsersCLUSTER;
    map<string,vector<string>> RecommendedCoins2VirtualUsersLSH;
    map<string,vector<string>> RecommendedCoins2VirtualUsersCLUSTER;

    clock_t beginTime, stopTime;
    double executTime1A ;double executTime2A ;double executTime1B ;double executTime2B ; //= double(end - begin) / CLOCKS_PER_SEC;



//1A
    cout <<"[1A]:Processing...Stand by from real Users results LSH...\n";

    beginTime = clock();
    (*RecommendFromRealUsers)(RecommendedCoins2UsersLSH,metricCos , lsh_Users_ptr);
    stopTime = clock();

    executTime1A = double(stopTime - beginTime) / CLOCKS_PER_SEC;
//    printrecommendedCoins2Users(RecommendedCoins2UsersLSH);


//2A
    cout <<"\n[2A]:Processing...Stand by from virtual Users results LSH...\n";

    beginTime = clock();
    (*RecommendFromVirtualUsers)(RecommendedCoins2VirtualUsersLSH,metricCos, lsh_virtualUsers_ptr);
    stopTime = clock();

    executTime2A = double(stopTime - beginTime) / CLOCKS_PER_SEC;
//    printrecommendedCoins2Users(RecommendedCoins2VirtualUsersLSH);


    cout <<"\n[1B]:Processing...Stand by from real Users results CLUSTERING...\n";

//1B

    beginTime = clock();
    (*RecommendFromRealUsers)(RecommendedCoins2UsersCLUSTER,metricEucl , clust_U);
    stopTime = clock();


    executTime1B = double(stopTime - beginTime) / CLOCKS_PER_SEC;
//    printrecommendedCoins2Users(RecommendedCoins2UsersCLUSTER);


    cout <<"\n[2B]:Processing...Stand by from virtual Users results CLUSTERING...\n\n";

//2B

    beginTime = clock();
    (*RecommendFromVirtualUsers)(RecommendedCoins2VirtualUsersCLUSTER,metricEucl, clust_C);
    stopTime = clock();

    executTime2B = double(stopTime - beginTime) / CLOCKS_PER_SEC;
//    printrecommendedCoins2Users(RecommendedCoins2VirtualUsersCLUSTER);


    double mae1A;double mae2A;double mae1B;double mae2B;
    if (validateFlag ) {
        cout <<"Cross-Validating...real Users results from LSH...\n";

        mae1A = cross_validation_for_U("./configs/lsh1.conf", "LSH", userTweetsSentimScore_umap,
                                       P, dimUserSentScoreVectors, 10, 1);

        cout <<"Cross-Validating...real Users results from Clustering...\n";

        mae2A = cross_validation_for_U("./configs/cluster2.conf", "CLUSTER", userTweetsSentimScore_umap,
                                       P, dimUserSentScoreVectors, 10, 1);


        cout <<"Cross-Validating...virtual Users results from LSH...\n";

        mae1B = cross_validation_for_C(userTweetsSentimScore_umap,
                                       virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                       virtualUserTweetsAverageSentimScore_umap,
                                       lsh_virtualUsers_ptr,
                                       metricCos,
                                       P,
                                       10, 1); //iterates , crypto2hide


        cout <<"Cross-Validating...virtual Users results from Clustering...\n";

        mae2B = cross_validation_for_C(userTweetsSentimScore_umap,
                                       virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                       virtualUserTweetsAverageSentimScore_umap,
                                       clust_C,
                                       metricEucl,
                                       P,
                                       10, 1);//iterates , crypto2hide


    }

    Write_OutFileCoinRecommendation(OutFileName,
                                    mae1A, executTime1A,
                                    mae2A, executTime2A,
                                    mae1B, executTime1B,
                                    mae2B, executTime2B,
                                    RecommendedCoins2UsersLSH,
                                    RecommendedCoins2UsersCLUSTER,
                                    RecommendedCoins2VirtualUsersLSH,
                                    RecommendedCoins2VirtualUsersCLUSTER, validateFlag);


//    /*DELETION OF POINTERS*/
    delete lsh_Users_ptr;lsh_Users_ptr= nullptr;
    delete lsh_virtualUsers_ptr;lsh_virtualUsers_ptr= nullptr;
    delete clust_U;clust_U= nullptr;
    delete clust_C;clust_C= nullptr;
    delete RecommendFromRealUsers;RecommendFromRealUsers= nullptr;
    delete RecommendFromVirtualUsers;RecommendFromVirtualUsers= nullptr;
    delete metricCos;metricCos= nullptr;
    delete metricEucl;metricEucl= nullptr;
    cout <<"THE END"<<endl;
    return 0;
}











