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


    string inCoinsFileName = "coins_queries.csv";
    string inVadarLexinconFile = "vader_lexicon.csv";
//    string inTweetsDatasetFile = "10_tweets_dataset_small.csv";
    string inTweetsDatasetFile = "tweets_dataset_small.csv";
//    string inTweetsDatasetFile = "tweets_dataset_big.csv";

    string inFileName = "twitter_dataset_small_v2.csv";
    string configFileName = "cluster.conf";


    vector <string> CoinsList;
    unordered_map<string ,int> coins_umap;
    unordered_map<string ,double> vaderLexicon_umap;


    ReadCoinsFile_saveIt(inCoinsFileName , CoinsList , coins_umap );

    unsigned  dimUserSentScoreVectors = static_cast<int>(CoinsList.size());

    ReadVaderLexicon_saveIt(inVadarLexinconFile , vaderLexicon_umap);


    unordered_map <string , Tweet > Tweets_umap;
    unordered_multimap <string ,string> userTweetsRelation_ummap;

    ReadTweetsInputDat_saveIt(inTweetsDatasetFile, Tweets_umap,userTweetsRelation_ummap);


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
//    int DistMetricFlag =1;

    unordered_map<string, myVector> in_Tf_Idf_Tweets_umap; //in_umap from project2

    ReadInFile_save2umap(inFileName, in_Tf_Idf_Tweets_umap, dimTfIdfVec );


    kClusters TwitterCluster;
    ClusterProcedure(TwitterCluster , in_Tf_Idf_Tweets_umap , configFileName , dimTfIdfVec);

    TwitterCluster.print_allClusters();


/*C VIRTUAL-USERS-VECTORS*/

    unordered_map <string , myVector > virtualUserTweetsSentimScore_umap;
//
//
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


    cout << "\n\n\n\n============   VIRTUAL USERS   ============\n\n\n\n";
    printUsersSentimentCryptoScoreMap(virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


    cout << "\n\n virtualUserTweetsSentimScore_umap = " << virtualUserTweetsSentimScore_umap.size()<<endl;
    cout << "\n\n virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap = " << virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap.size()<<endl;



//    //==========================================================================





    unsigned k_hf =  4;
    unsigned int W = 1;
    auto M_lsh = static_cast<long long int>(pow(2, 32) - 5);
    unsigned L = 2;
    auto TableSize = static_cast<unsigned int>(pow(2, k_hf));


//    ============================ U-V LSH's =================================


    /*SAVE THE nonInf&zero U's IN THE LSH*/

    Lsh *lsh_Users_ptr = new Lsh ( TableSize, k_hf , dimUserSentScoreVectors , L  , userTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for normalized u's

    /*SAVE THE nonInf&zero C's IN THE LSH*/
    Lsh *lsh_virtualUsers_ptr = new Lsh ( TableSize, k_hf , dimUserSentScoreVectors , L  , virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for normalized c's



    //=============================== U-V CLUSTER's ==============================

    string configFileName2 = configFileName; //TODO FTIAXNW NWO CONFIG FILE H STO IDIO DIABAZW APO KEI POU MEINA

    kClusters UCluster;
    ClusterProcedure(UCluster , userTweetsSentimScoreWithoutInfsAndZeroVectors_umap ,
            configFileName2 , dimUserSentScoreVectors);

    UCluster.print_allClusters();

    //TODO TO XWNW STH NEA DOMH MOU PROXSEARXHINGCLUSTERING


    ClusteringProxSearching  *clV = new ClusteringProxSearching(UCluster);

    clV->getAllClusters().print_allClusters();

    AbstractLshCluster* AbstractObjForUcluster =  clV ;



exit(1);
    //=============================== add function to this  todo findBestPForU===================================


    //     recommendCryptoForEveryU( ,Lsh *lshForNormalized_U_Vectors_ptr )

//    set<string> multiMapKeys = extractMultiMapKeys (userTweetsRelation_ummap); //In this set now I have all the keys of the multiset


    int P = 20; //range: [20-50]
    int numberOfCoins2recommend_U = 5;
    int numberOfCoins2recommend_C = 2;
    DistanceMetrics *metric = new CosineMetric;



    //todo na ftiaxtei suanrthsh
//    vector <int>  RecommendedCoinsIndexes =recommend5BestCoinsForUser(u ,bestP_u ,userTweetsSentimScore_umap  );
//    vector <double>  RecommendedCoinsIndexes =EvaluateAllCrypto(u ,bestP_u ,userTweetsSentimScoreNormalized_umap  );

    map<string,vector<string>> RecommendedCoins2Users;
    map<string,vector<string>> RecommendedCoins2VirtualUsers;




//    RecommendationSystem(  RecommendedCoins2Users,
//                           lsh_virtualUsers_ptr,
//                           metric,
//                           P,
//                           numberOfCoins2recommend,//number2recommend
//                           CoinsList,
//                           userTweetsSentimScore_umap,
//
//                           userTweetsAverageSentimScore_umap,
//                           virtualUserTweetsAverageSentimScore_umap,
//                           userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
//                           virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
//
//
//// /*FOR C-VIRTUAL USERS*/
////cout << "\n\n\n\n\n\n\n\n\n";
//
//    RecommendationSystem(  RecommendedCoins2Users,
//                           lsh_Users_ptr,
//                           metric,
//                           P,
//                           numberOfCoins2recommend,//number2recommend
//                           CoinsList,
//                           userTweetsSentimScore_umap ,
//
//                           userTweetsAverageSentimScore_umap,
//                           userTweetsAverageSentimScore_umap,
//                           userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
//                           userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
//



//=====================================     /*INSTANTIATIONS*/      =======================================

    /*FOR REAL-U USERS*/
    auto *RecommendForsUsers = new RecommendCoins(P, numberOfCoins2recommend_U, CoinsList,
                                            userTweetsSentimScore_umap,
                                            userTweetsAverageSentimScore_umap,//    U_userTweetsAverageSentimScore_umap,
                                            userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,//    U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                            userTweetsAverageSentimScore_umap,//    V_userTweetsAverageSentimScore_umap,
                                            userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);//    V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

    /*FOR VIRTUAL-C USERS*/
    auto *RecommendForsVirtulUsers = new RecommendCoins(P, numberOfCoins2recommend_C, CoinsList,
                                                                  userTweetsSentimScore_umap,
                                                                  userTweetsAverageSentimScore_umap,//    U_userTweetsAverageSentimScore_umap,
                                                                  userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,//    U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                                  virtualUserTweetsAverageSentimScore_umap,//    V_userTweetsAverageSentimScore_umap,
                                                                  virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);//    V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);;

//==========================================================================================================


/*

    (*RecommendForsUsers)(RecommendedCoins2Users,metric , lsh_Users_ptr);
    (*RecommendForsVirtulUsers)(RecommendedCoins2VirtualUsers,metric, lsh_virtualUsers_ptr);
*/


    printrecommendedCoins2Users(RecommendedCoins2Users);
    printrecommendedCoins2Users(RecommendedCoins2VirtualUsers);

    cout << "\n\n RecommendedCoins2Userssizeof = " << RecommendedCoins2Users.size()<<endl;
    cout << "\n\n RecommendedCoins2VirtualUsers = " << RecommendedCoins2VirtualUsers.size()<<endl;

    cout << "\n\n userTweetsSentimScore_umap = " << userTweetsSentimScore_umap.size()<<endl;
    cout << "\n\n userTweetsSentimScoreWithoutInfsAndZeroVectors_umap = " << userTweetsSentimScoreWithoutInfsAndZeroVectors_umap.size()<<endl;
    cout << "\n\n vaderLexicon_umap = " << vaderLexicon_umap.size()<<endl;
    cout << "\n\n coins_umap = " << coins_umap.size()<<endl;


//

    cout <<"THE END"<<endl;
    return 0;
}











