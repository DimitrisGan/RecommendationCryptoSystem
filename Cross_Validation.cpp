//
// Created by dimitrisgan on 13/1/2019.
//

#include "Cross_Validation.h"
#include "SearchingAlgorithms.h"
#include "RecommendBestCoins.h"



double
cross_validation_for_C(
                       const unordered_map<string, myVector> &userTweetsSentimScore_umapStartState,
                       unordered_map <string , myVector > virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                       const unordered_map <string , double > &virtualUserTweetsAverageSentimScore_umap,
                       AbstractLshCluster *abstractLshClust_ptr ,
                       DistanceMetrics *metric,
                       int P,
                       int foldingTimes, int crypto2hide) {

    double avrgMAE;
    vector <double> MAE_list;


    unordered_map<string, myVector> userTweetsSentimScore_umap2change= userTweetsSentimScore_umapStartState;
    vector <string> keysU = extract_keys(userTweetsSentimScore_umapStartState);
    int foldIn_f_piecesNumber = static_cast<int>(keysU.size() / foldingTimes);



    for (int i = 0; i < foldingTimes ; ++i) {
//        cout << "~~~~~~~~~~~~~~~~~~~~~~ITERATIONS #" << i << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        vector<string> keysU2Change = keys2change(keysU, i, foldIn_f_piecesNumber); //EDW PAIRNW TO 1/10 KATHE FORA


        unordered_map<string, myVector> userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
        unordered_map<string, double> userTweetsAverageSentimScore_umap;


        vector<pair<string, int>> UserIndexesPairsChanged = changeDataset(userTweetsSentimScore_umap2change,
                                                                          keysU2Change, crypto2hide);


        calculateAverageU_umap(userTweetsAverageSentimScore_umap, userTweetsSentimScore_umap2change);


        changeInfsToAverageSentimentsAndDiscardZeroVectors(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                           userTweetsSentimScore_umap2change,
                                                           userTweetsAverageSentimScore_umap);



        vector <pair<double,double>> predictedAndRealScorePair;

        for (auto &UserScorePairChanged :  UserIndexesPairsChanged) {

            string uId = UserScorePairChanged.first;
            int index2change = UserScorePairChanged.second;
            myVector u = userTweetsSentimScoreWithoutInfsAndZeroVectors_umap[uId];

            assert(!u.getCoords().empty());

            set<string> list2search = abstractLshClust_ptr->getSuperSet(u, virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


            if (list2search.empty()){continue;} //no reason because we cant predict


            vector<string> bestP_u  = NN_searchForBestP(u,uId, metric, virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap, list2search, P);


            double realRating = userTweetsSentimScore_umapStartState.at(uId).getCoords().at(index2change);
            double  predictedRating = RateCrypto(u, bestP_u, uId, metric,
                                                 userTweetsAverageSentimScore_umap,
                                                 virtualUserTweetsAverageSentimScore_umap,
                                                 virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap, index2change);



            predictedAndRealScorePair.emplace_back(predictedRating,realRating);


        }

        double MeanAbsoluteError = MAE(predictedAndRealScorePair);
        MAE_list.push_back(MeanAbsoluteError);

//        cout <<"MAE = "<< MeanAbsoluteError<<endl;

        userTweetsSentimScore_umap2change.clear();
        userTweetsSentimScore_umap2change= userTweetsSentimScore_umapStartState; //return 2 initial umap dataset (userTweetsSentimScore)

        predictedAndRealScorePair.clear();

    }

    avrgMAE = accumulate( MAE_list.begin(), MAE_list.end(), 0.0)/MAE_list.size(); ;

//    cout << "AVERAGE MAE: "<<avrgMAE<<endl;

    return avrgMAE;
}



double
cross_validation_for_U(string configFileName, string type,
                       const unordered_map<string, myVector> &userTweetsSentimScore_umapStartState,
                       int P,
                       unsigned dimUserSentScoreVectors, int foldingTimes, int crypto2hide) {

    double avrgMAE;
    vector <double> MAE_list;


    DistanceMetrics *metric;
    if (type == "LSH" || type =="lsh"){
        metric = new CosineMetric();
    }
    else{
        metric = new EuclideanMetric();
    }

    unordered_map<string, myVector> userTweetsSentimScore_umap2change= userTweetsSentimScore_umapStartState;
    vector <string> keysU = extract_keys(userTweetsSentimScore_umapStartState);
    int foldIn_f_piecesNumber = static_cast<int>(keysU.size() / foldingTimes);



    for (int i = 0; i < foldingTimes ; ++i) {
//        cout << "~~~~~~~~~~~~~~~~~~~~~~ITERATIONS #" << i << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        vector<string> keysU2Change = keys2change(keysU, i, foldIn_f_piecesNumber); //EDW PAIRNW TO 1/10 KATHE FORA


        unordered_map<string, myVector> userTweetsSentimScoreWithoutInfsAndZeroVectors_umap;
        unordered_map<string, double> userTweetsAverageSentimScore_umap;


        vector<pair<string, int>> UserIndexesPairsChanged = changeDataset(userTweetsSentimScore_umap2change,
                                                                          keysU2Change, crypto2hide);


        calculateAverageU_umap(userTweetsAverageSentimScore_umap, userTweetsSentimScore_umap2change);


        changeInfsToAverageSentimentsAndDiscardZeroVectors(userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                           userTweetsSentimScore_umap2change,
                                                           userTweetsAverageSentimScore_umap);

        AbstractLshCluster *abstractLshClust_ptr;
        if (type == "LSH" || type == "lsh") {
            abstractLshClust_ptr = new Lsh(configFileName,userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, dimUserSentScoreVectors);
        } else { //type == "cluster"
            abstractLshClust_ptr = new ClusteringProxSearching(configFileName,
                                                               userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                                               dimUserSentScoreVectors, 1);
        }


        vector <pair<double,double>> predictedAndRealScorePair;

        for (auto &UserScorePairChanged :  UserIndexesPairsChanged) {

            string uId = UserScorePairChanged.first;
            int index2change = UserScorePairChanged.second;
            myVector u = userTweetsSentimScoreWithoutInfsAndZeroVectors_umap[uId];

            assert(!u.getCoords().empty());

            set<string> list2search = abstractLshClust_ptr->getSuperSet(u, userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

            assert(!list2search.empty());

            if (list2search.size() == 1){continue;} //no reason because we cant predict


            int index_u2remove=0;
            for (const auto &currId : list2search){
                if (currId == uId){
                    list2search.erase(currId);
                    break;
                }
                index_u2remove++;
            }


            vector<string> bestP_u  = NN_searchForBestP(u,uId, metric, userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, list2search, P);


            double realRating = userTweetsSentimScore_umapStartState.at(uId).getCoords().at(index2change);
            double  predictedRating = RateCrypto(u, bestP_u, uId, metric,
                                                 userTweetsAverageSentimScore_umap,
                                                 userTweetsAverageSentimScore_umap,
                                                 userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, index2change);

            predictedAndRealScorePair.emplace_back(predictedRating,realRating);

        }

        double MeanAbsoluteError = MAE(predictedAndRealScorePair);
        MAE_list.push_back(MeanAbsoluteError);

//        cout <<"MAE = "<< MeanAbsoluteError<<endl;

        userTweetsSentimScore_umap2change.clear();
        userTweetsSentimScore_umap2change= userTweetsSentimScore_umapStartState; //return 2 initial umap dataset (userTweetsSentimScore)

        delete abstractLshClust_ptr;abstractLshClust_ptr= nullptr;
        predictedAndRealScorePair.clear();


    }


    delete metric;metric= nullptr;

    avrgMAE = accumulate( MAE_list.begin(), MAE_list.end(), 0.0)/MAE_list.size(); ;

//    cout << "AVERAGE MAE: "<<avrgMAE<<endl;

    return avrgMAE;
}


//CKECKED
//Rj=actual rating, Pj =predicted rating
double MAE(vector <pair<double,double>> predictedAndRealScorePair) {//Mean Absolute Error

    double mae=0;
    int j= static_cast<int>(predictedAndRealScorePair.size());

    assert(!predictedAndRealScorePair.empty());
    for (auto& myPair : predictedAndRealScorePair ){
        mae += abs(myPair.second - myPair.first);
        assert(mae >=0);
    }

    assert(j>0);
    return mae/j;
}



//CKECKED
int isNotValid2changeVector(const myVector &u, int crypto2hide){
    double inf = std::numeric_limits<double>::infinity();
    int counter=0;
    int counterZeros=0;

    for (auto coord : u.getCoords()){
        if (coord != inf ){
            counter++;
            if (coord ==0){
                counterZeros++;
            }
        }
    }
    int counterNonZeros = counter - counterZeros;
    if (counterNonZeros > crypto2hide && counterNonZeros > 0  ){ // be sure these vectors will not be evicted from the withouInfs&Zeros umap [thus there should be at least 2 vectors
        return 0; //is Valid 2 change It
    }

    return  1; //is NOT Valid 2 change It
}



//CHECKED
vector<int> changeSomeCryptoScores2unknown(myVector &u,int crypto2hide){

    vector <int> indexesChangedReturned;
    double inf = std::numeric_limits<double>::infinity();
    vector<pair<int,double>> coinsList;


    int index=0;
    for (auto &crypto : u.getCoords()){
        if (crypto!= inf){
            coinsList.emplace_back(index,crypto);
        }
        index++;
    }

    int coinRandomlyChosen ;
    int indexCoin2change;

    for (int i = 0; i < crypto2hide; ++i) {
        coinRandomlyChosen = static_cast<int>(std::rand() % coinsList.size());

        assert(coinsList[coinRandomlyChosen].second != inf);

        indexCoin2change = coinsList[coinRandomlyChosen].first ;

        coinsList.erase(coinsList.begin() + coinRandomlyChosen);



        u.changeValueToSpecificIndex(indexCoin2change , inf);
        indexesChangedReturned.push_back(indexCoin2change);

        assert(u.getCoords().at(indexCoin2change) == inf);

    }

    //todo edw PROSOXH

    return indexesChangedReturned;
}


//CKECKED
vector<pair<string,int>> changeDataset(unordered_map<string, myVector>  &userTweetsSentimScore_umap, const vector <string> &keysU2Change,int crypto2hide){
    vector<pair<string,int>> valuesChanged;
    for (auto& u_key : keysU2Change){
        myVector u2change = userTweetsSentimScore_umap[u_key];
        if (isNotValid2changeVector(u2change,crypto2hide) ){ //if not valid to change continue
            continue;
        }
        vector<int> indexesInCurrentU2change = changeSomeCryptoScores2unknown(u2change,crypto2hide);
        assert (indexesInCurrentU2change.size() == crypto2hide);

        for (auto curr_index : indexesInCurrentU2change){
            valuesChanged.emplace_back(u_key,curr_index);
        }
        userTweetsSentimScore_umap[u_key] = u2change; //new value (overrides) in the umap with the u vector been changed to inf some known cryptos

    }

    return valuesChanged;
}

//CKECKED
vector<string> keys2change(const vector<string> &keysU,int i,int foldIn10piecesNumber){
    vector <string> keys2Return;

    int initialId2Read = i*foldIn10piecesNumber;

    keys2Return.reserve(static_cast<unsigned long>(foldIn10piecesNumber));

    for (int j = 0; j < foldIn10piecesNumber; ++j) {

        keys2Return.push_back(keysU[initialId2Read+j]);
    }


    return keys2Return;
}








