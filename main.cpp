#include <iostream>
#include <unordered_map>
#include <fstream>

#include "AssistantFunctions.h"
#include "Tweet.h"
#include "myCryptoVector.h"
#include "ClusterAPI.h"
#include "SearchingAlgorithms.h"
#include "RecommendBestCoins.h"
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

    int dimUserVectors = CoinsList.size();

    ReadVaderLexicon_saveIt(inVadarLexinconFile , vaderLexicon_umap);


    unordered_map <string , Tweet > Tweets_umap;
    unordered_multimap <string ,string> userTweetsRelation_ummap;

    ReadTweetsInputDat_saveIt(inTweetsDatasetFile, Tweets_umap,userTweetsRelation_ummap);


    unordered_map <string , myVector > userTweetsSentimScore_umap;

    /*U USERS-VECTORS*/
    calculateUsersSentimentCryptoScoreMap(userTweetsSentimScore_umap, userTweetsRelation_ummap, Tweets_umap,
                                          vaderLexicon_umap,
                                          coins_umap, dimUserVectors);

    /*U USERS-VECTORS CHANGED THE INFS TO AVRG SENTIMENT*/
    unordered_map <string , myVector > userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
    unordered_map <string , double > userTweetsAverageSentimScore_umap;


    calculateAverageU_umap(userTweetsAverageSentimScore_umap, userTweetsSentimScore_umap);

    changeInfsToAverageSentimentsAndDiscardZeroVectors(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                       userTweetsSentimScore_umap, userTweetsAverageSentimScore_umap);
//    printUsersSentimentCryptoScoreMap(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


    //================== making the virtual clusters ================

    unsigned int dim_tfidfVec = 0;
//    int DistMetricFlag =1;

    unordered_map<string, myVector> in_Tf_Idf_Tweets_umap; //in_umap from project2

    ReadInFile_save2umap(inFileName, in_Tf_Idf_Tweets_umap, dim_tfidfVec );


    kClusters TwitterCluster;
    ClusterProcedure(TwitterCluster , in_Tf_Idf_Tweets_umap , configFileName , dim_tfidfVec);

    TwitterCluster.print_allClusters();



/*C VIRTUAL-USERS-VECTORS*/

    unordered_map <string , myVector > virtualUserTweetsSentimScore_umap;
    unordered_map <string , myVector > virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap_umap;
//
//
    calculateVirtualUsersFromTwitterCluster(virtualUserTweetsSentimScore_umap, TwitterCluster, Tweets_umap,
                                            vaderLexicon_umap,
                                            coins_umap, dimUserVectors);

    exit(1);
/*

    */
/*U USERS-VECTORS CHANGED THE INFS TO AVRG SENTIMENT*//*

    unordered_map <string , myVector > userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
    unordered_map <string , double > userTweetsAverageSentimScore_umap;


    calculateAverageU_umap(userTweetsAverageSentimScore_umap, userTweetsSentimScore_umap);

    changeInfsToAverageSentimentsAndDiscardZeroVectors(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                       userTweetsSentimScore_umap, userTweetsAverageSentimScore_umap);
//    printUsersSentimentCryptoScoreMap(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

*/

    cout << "\n\n\n\n============   VIRTUAL USERS   ============\n\n\n\n";
    printUsersSentimentCryptoScoreMap(virtualUserTweetsSentimScore_umap);


    exit(1);

//    //==========================================================================



    unsigned k_hf =  4;
    unsigned int W = 1;
    auto M_lsh = static_cast<long long int>(pow(2, 32) - 5);
    unsigned L = 2;
    unsigned  TableSize = static_cast<unsigned int>(pow(2, k_hf));

    unsigned int dim_sentScoreVectors = static_cast<unsigned int>(CoinsList.size());




//    AbstractLshCube* Lsh_ForNormalizedU = constructLshDatastructure(1/*Cosine*/,   lsh_ptr , k_hf ,
//                                               W , dim_sentScoreVectors , M_lsh ,L , userTweetsSentimScoreNormalized_umap ) ;


    /*SAVE THE NORMALIZED U's IN THE LSH*/
    Lsh *lsh_ptr = new Lsh ( TableSize, k_hf , dim_sentScoreVectors , L  , userTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for normalized u's


    //=============================== add function to this  todo findBestPForU===================================

    //     recommendCryptoForEveryU( ,Lsh *lshForNormalized_U_Vectors_ptr )

//    set<string> multiMapKeys = extractMultiMapKeys (userTweetsRelation_ummap); //In this set now I have all the keys of the multiset


    int P = 50;
    int numberOfCoins2recommend = 5;
    DistanceMetrics *metric = new CosineMetric;



    //todo na ftiaxtei suanrthsh
//    vector <int>  RecommendedCoinsIndexes =recommend5BestCoinsForUser(u ,bestP_u ,userTweetsSentimScore_umap  );
//    vector <double>  RecommendedCoinsIndexes =EvaluateAllCrypto(u ,bestP_u ,userTweetsSentimScoreNormalized_umap  );

    map<string,vector<string>> RecommendedCoins2Users;
    map<string,vector<string>> RecommendedCoins2VirtualUsers;

    RecommendationSystem(  RecommendedCoins2Users,
                           lsh_ptr,
                           metric,
                           P,
                           numberOfCoins2recommend,//number2recommend
                           CoinsList,
                           userTweetsAverageSentimScore_umap,
                           userTweetsSentimScore_umap ,
                           userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);




    printrecommendedCoins2Users(RecommendedCoins2Users);

    cout << "\n\n RecommendedCoins2Userssizeof = " << RecommendedCoins2Users.size()<<endl;

    cout << "\n\n userTweetsSentimScore_umap = " << userTweetsSentimScore_umap.size()<<endl;
    cout << "\n\n userTweetsSentimScoreWithoutInfsAndZeroVectors_umap = " << userTweetsSentimScoreWithoutInfsAndZeroVectors_umap.size()<<endl;
    cout << "\n\n vaderLexicon_umap = " << vaderLexicon_umap.size()<<endl;
    cout << "\n\n coins_umap = " << coins_umap.size()<<endl;


//

    cout <<"THE END"<<endl;
    return 0;
}











