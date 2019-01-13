//
// Created by dimitrisgan on 13/1/2019.
//

#include "Cross_Validation.h"



double cross_validation(string configFileName, string type, unordered_map<string, myVector> userTweetsSentimScore_umap,
                        int P , int dimUserSentScoreVectors , int foldingTimes) {


    cout <<"HI MAIN \n";

    unordered_map<string, myVector> userTweetsSentimScore_umapStartState = userTweetsSentimScore_umap;
    vector <string> keysU = extract_keys(userTweetsSentimScore_umap);
    int foldIn_f_piecesNumber = keysU.size()/foldingTimes;



    for (int i = 0; i < 10 ; ++i) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~ITERATIONS #"<<i<<"~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        vector <string> keysU2Change = keys2change(keysU,i,foldIn_f_piecesNumber); //EDW PAIRNW TO 1/10 KATHE FORA
        //TODO APO AUTA TA 1/10 KLEIDIA ALLAZW MIA GNWSTH TIMH *PROSOX* MHN EINIA MONO MIA H GNWSTH


        print_keys(keysU2Change);
    }


    //todo pairnw to 1/10 kathe fora



    AbstractLshCluster * myStructure_ptr;
//    if (type == "LSH"){
//        unsigned k_hf =  4;
//        unsigned int W = 1;
//        auto M_lsh = static_cast<long long int>(pow(2, 32) - 5);
//        unsigned L = 2;
//        auto TableSize = static_cast<unsigned int>(pow(2, k_hf));
//
//        myStructure_ptr = new Lsh ( TableSize, k_hf , dimUserSentScoreVectors , L  , userTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for  u's
//    }
//    if (type == "CLUSTER"){
//        myStructure_ptr = new ClusteringProxSearching (configFileName ,userTweetsSentimScoreWithoutInfsAndZeroVectors_umap ,  dimUserSentScoreVectors);
//    }


    return 0;
}




vector<string> keys2change(const vector<string> &keysU,int i,int foldIn10piecesNumber){
    vector <string> keys2Return;

    int initialId2Read = i*foldIn10piecesNumber;

    keys2Return.reserve(static_cast<unsigned long>(foldIn10piecesNumber));

    for (int j = 0; j < foldIn10piecesNumber; ++j) {

        keys2Return.push_back(keysU[initialId2Read+j]);
    }


    return keys2Return;
}








