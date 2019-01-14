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
    std::cout << "Hello, World!" << std::endl;


/*int Radius=0;*//*

    unsigned  int L ; //default:L=5
    unsigned int k ; //for k clusters todo
    unsigned int k_hf; // for k h  //default:k_hf=4

    unsigned int d = 0;
    int DistMetricFlag = 0; // 0 --> for euclidean  and 1 --> cosine
    int completeFlag = 0; // 0 --> for euclidean  and 1 --> cosine

    unsigned int M_cube;
    unsigned int probes;
    int I_option,A_option,U_option;
    int flagInputLsh;
    string algOptions;

    unsigned int i;

    unsigned int TableSize;
    unsigned int W = 1;
    auto M_lsh = static_cast<long long int>(pow(2, 32) - 5);

    unordered_map<string, myVector> in_umap;

    ReadHandleArgms(argc, argv , inFileName  , configFileName  , OutFileName , DistMetricFlag ,completeFlag );

    cout << "inFileName = "<<inFileName<<endl;
    cout << "configFileName = "<<configFileName<<endl;
    cout << "OutFileName = "<<OutFileName<<endl;
    cout << "DistMetricFlag = "<<DistMetricFlag<<endl;

    ReadInFile_save2umap(inFileName, in_umap, d );

    ReadConfigFile(configFileName , k , k_hf , L ,M_cube ,probes , I_option , A_option ,U_option , flagInputLsh ,algOptions);

    cout << "k = "<<k<<endl;
    cout << "k_hf = "<<k_hf<<endl;
    cout << "L = "<<L<<endl;
    cout << "M_cube = "<<M_cube<<endl;
    cout << "probes = "<<probes<<endl;
    cout << "I_option = "<<I_option<<endl;
    cout << "A_option = "<<A_option<<endl;
    cout << "U_option = "<<U_option<<endl;
    cout << "dimensions = "<<d<<endl;

//    ========================================================================================
*/


    //todo ftiaxnw ta input


//    InputParser
//    InputReader


    string inCoinsFileName = "./inputs/coins_queries.csv";
    string inVadarLexinconFile = "./inputs/vader_lexicon.csv";
    string inTweetsDatasetFile = "./inputs/tweets_dataset_small.csv";
//    string inTweetsDatasetFile = "./inputs/MINE_tweets_dataset_small.csv";
//    string inTweetsDatasetFile = "tweets_dataset_big.csv";

    string inFileName = "./inputs/twitter_dataset_small_v2.csv";

    string configFileName1 = "./configs/cluster1.conf";
    string configFileName2 = "./configs/cluster2.conf";
    string configFileName3 = "./configs/cluster3.conf";


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

    cout << "userTweetsRelation_ummap.size0f : "<<userTweetsRelation_ummap.size()<<endl;
    cout << "Tweets_umap.size0f : "<<Tweets_umap.size()<<endl;

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

//    unsigned int dimTfIdfVec = 0;
////    int DistMetricFlag =1;
//
//    unordered_map<string, myVector> in_Tf_Idf_Tweets_umap; //in_umap from project2
//
//    ReadInFile_save2umap(inFileName, in_Tf_Idf_Tweets_umap, dimTfIdfVec );
//
//
//    kClusters TwitterCluster;
//    ClusterProcedure(TwitterCluster , in_Tf_Idf_Tweets_umap , configFileName1 , dimTfIdfVec);
//
//    TwitterCluster.print_allClusters();
//
//
//
///*C VIRTUAL-USERS-VECTORS*/
//
//    unordered_map <string , myVector > virtualUserTweetsSentimScore_umap;
////
////
//    calculateVirtualUsersFromTwitterCluster(virtualUserTweetsSentimScore_umap, TwitterCluster, Tweets_umap,
//                                            vaderLexicon_umap,
//                                            coins_umap, dimUserSentScoreVectors);
//
//
///*C USERS-VECTORS CHANGED THE INFS TO AVRG SENTIMENT*/
//
//    unordered_map <string , myVector > virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
//    unordered_map <string , double > virtualUserTweetsAverageSentimScore_umap;
//
//
//    calculateAverageU_umap(virtualUserTweetsAverageSentimScore_umap, virtualUserTweetsSentimScore_umap);
//
//    changeInfsToAverageSentimentsAndDiscardZeroVectors(virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
//                                                       virtualUserTweetsSentimScore_umap, virtualUserTweetsAverageSentimScore_umap);
////    printUsersSentimentCryptoScoreMap(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
//
//
//    cout << "\n\n\n\n============   VIRTUAL USERS   ============\n\n\n\n";
//    printUsersSentimentCryptoScoreMap(virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
//
//
//    cout << "\n\n virtualUserTweetsSentimScore_umap = " << virtualUserTweetsSentimScore_umap.size()<<endl;
//    cout << "\n\n virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap = " << virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap.size()<<endl;
//


//    //==========================================================================

//
//
//
//
    unsigned k_hf =  4;
    unsigned L = 2;
    auto TableSize = static_cast<unsigned int>(pow(2, k_hf));


//    ============================ U-V LSH's ====================================

//
//    /*SAVE THE nonInf&zero U's IN THE LSH*/
//
    Lsh *lsh_Users_ptr = new Lsh ( TableSize, k_hf , dimUserSentScoreVectors , L  , userTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for  u's
//
//    /*SAVE THE nonInf&zero C's IN THE LSH*/
//    Lsh *lsh_virtualUsers_ptr = new Lsh ( TableSize, k_hf , dimUserSentScoreVectors , L  , virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for  c's
//
//
////
//    //=============================== U-V CLUSTER's ==============================
//
////    kClusters UsCluster;
////    ClusterProcedure(UsCluster , userTweetsSentimScoreWithoutInfsAndZeroVectors_umap ,
////            configFileName2 , dimUserSentScoreVectors);
////
////    UsCluster.print_allClusters();
////
////
////
////    kClusters CsCluster;
////    ClusterProcedure(CsCluster , virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap ,
////                     configFileName3 , dimUserSentScoreVectors);
////
////    CsCluster.print_allClusters();
//
//    //=============================================================================
//
//
//    //ADD UsCluster && CsCluster IN NEW STRUCTURE THAT IMPLEMENTS getSuperSet() and keeps as attribute the euclidean distance
//
//    auto *clust_U = new ClusteringProxSearching (configFileName2 ,userTweetsSentimScoreWithoutInfsAndZeroVectors_umap ,  dimUserSentScoreVectors);
//    auto *clust_C = new ClusteringProxSearching (configFileName3 ,virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap ,  dimUserSentScoreVectors);
//
//    //=============================================================================
//    /*NUMBER OF COINS TO RECOMMEND*/
//    int numberOfCoins2recommend_U = 5;
//    int numberOfCoins2recommend_C = 2;
//
//
////===================================== FUNCTOR INSTANTIATIONS =======================================
//
    /*FOR REAL-U USERS*/
//    auto *RecommendForsUsers =  new RecommendCoins(P, numberOfCoins2recommend_U, CoinsList,
//                                            userTweetsSentimScore_umap,
//                                            userTweetsAverageSentimScore_umap,                      //U_userTweetsAverageSentimScore_umap,
//                                            userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,    //U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
//                                            userTweetsAverageSentimScore_umap,                      //V_userTweetsAverageSentimScore_umap,
//                                            userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);   //V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
//
//    /*FOR VIRTUAL-C USERS*/
//    auto *RecommendForsVirtualUsers = new RecommendCoins(P, numberOfCoins2recommend_C, CoinsList,
//                                                                  userTweetsSentimScore_umap,
//                                                                  userTweetsAverageSentimScore_umap,                            //U_userTweetsAverageSentimScore_umap,
//                                                                  userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,          //U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
//                                                                  virtualUserTweetsAverageSentimScore_umap,                     //V_userTweetsAverageSentimScore_umap,
//                                                                  virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);  //V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);;
//

//==========================================================================================================

    DistanceMetrics *metricCos = new CosineMetric;
    DistanceMetrics *metricEucl = new EuclideanMetric;

    map<string,vector<string>> RecommendedCoins2UsersLSH;
    map<string,vector<string>> RecommendedCoins2UsersCLUSTER;
    map<string,vector<string>> RecommendedCoins2VirtualUsersLSH;
    map<string,vector<string>> RecommendedCoins2VirtualUsersCLUSTER;



//    cout <<"Processing...Stand by from real Users results LSH...\n";
////1A
//
//    (*RecommendForsUsers)(RecommendedCoins2UsersLSH,metricCos , lsh_Users_ptr);
//    printrecommendedCoins2Users(RecommendedCoins2UsersLSH);
//
//    cout <<"\nProcessing...Stand by from virtual Users results LSH...\n";
////1B
//
//    (*RecommendForsVirtualUsers)(RecommendedCoins2VirtualUsersLSH,metricCos, lsh_virtualUsers_ptr);
//    printrecommendedCoins2Users(RecommendedCoins2VirtualUsersLSH);
//
//
//    cout <<"\nProcessing...Stand by from real Users results CLUSTERING...\n";
//
////2A
//
//    (*RecommendForsUsers)(RecommendedCoins2UsersCLUSTER,metricEucl , clust_U);
//    printrecommendedCoins2Users(RecommendedCoins2UsersCLUSTER);
//
//
//    cout <<"\nProcessing...Stand by from virtual Users results CLUSTERING...\n";
//
////2B
//
//    (*RecommendForsVirtualUsers)(RecommendedCoins2VirtualUsersCLUSTER,metricEucl, clust_C);
//
//    printrecommendedCoins2Users(RecommendedCoins2VirtualUsersCLUSTER);
//




//    cout << "\n\n RecommendedCoins2UsersLSHssizeof = " << RecommendedCoins2UsersLSH.size()<<endl;
//    cout << "\n\n RecommendedCoins2UsersCLUSTERsizeof = " << RecommendedCoins2UsersCLUSTER.size()<<endl;
//    cout << "\n\n RecommendedCoins2VirtualUsers = " << RecommendedCoins2VirtualUsersLSH.size()<<endl;
//
//    cout << "\n\n userTweetsSentimScore_umap = " << userTweetsSentimScore_umap.size()<<endl;
//    cout << "\n\n userTweetsSentimScoreWithoutInfsAndZeroVectors_umap = " << userTweetsSentimScoreWithoutInfsAndZeroVectors_umap.size()<<endl;
//    cout << "\n\n vaderLexicon_umap = " << vaderLexicon_umap.size()<<endl;
//    cout << "\n\n coins_umap = " << coins_umap.size()<<endl;


    cross_validation("./configs/cluster2.conf", "LSH", userTweetsSentimScore_umap,
                     P, dimUserSentScoreVectors, 10, 1);


    /*DELETION OF POINTERS*/
/*
    delete lsh_Users_ptr;lsh_Users_ptr= nullptr;
    delete lsh_virtualUsers_ptr;lsh_virtualUsers_ptr= nullptr;
    delete clust_U;clust_U= nullptr;
    delete clust_C;clust_C= nullptr;
    delete RecommendForsUsers;RecommendForsUsers= nullptr;
    delete RecommendForsVirtualUsers;RecommendForsVirtualUsers= nullptr;
    delete metricCos;metricCos= nullptr;
    delete metricEucl;metricEucl= nullptr;
    */
    cout <<"THE END"<<endl;
    return 0;
}











