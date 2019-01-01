#include <iostream>
#include <unordered_map>
#include <fstream>

#include "AssistantFunctions.h"
#include "Tweet.h"
#include "myCryptoVector.h"


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
    string inTweetsDatasetFile = "10_tweets_dataset_small.csv";
//    string inTweetsDatasetFile = "tweets_dataset_small.csv";

//    string inTweetsDatasetAfterTFIDFFile = "tweets_dataset_small.csv";
//    string configFileName = "cluster.conf";
//    string OutFileName;
//    ofstream outFile;

    vector <string> CoinsList;
    unordered_map<string ,int> coins_umap;



    ReadCoinsFile_saveIt(inCoinsFileName , CoinsList , coins_umap );

    for (const auto &coinPair : coins_umap){
        cout << coinPair.second << " :"<< coinPair.first <<endl;
    }

    unordered_map<string ,float> vaderLexicon_umap;

    ReadVaderLexicon_saveIt(inVadarLexinconFile , vaderLexicon_umap);


//    unordered_map <string , vector<string>> testMap;

    unordered_map <string , Tweet > tweets_umap;
    unordered_multimap <string ,string> userTweetsRelation_ummap;

    ReadTweetsInputDat_saveIt(inTweetsDatasetFile, tweets_umap,userTweetsRelation_ummap);


    unordered_map <string , myCryptoVector > userTweetsSentimScore_umap;

     calculateUsersSentimentCryptoScoreMap(userTweetsSentimScore_umap,userTweetsRelation_ummap,tweets_umap,vaderLexicon_umap ,coins_umap );




        return 0;
}













