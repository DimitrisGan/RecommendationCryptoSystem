//
// Created by dimitrisgan on 13/1/2019.
//

#include "Cross_Validation.h"
#include "SearchingAlgorithms.h"
#include "RecommendBestCoins.h"


double
cross_validation(string configFileName, string type,
                 const unordered_map<string, myVector> &userTweetsSentimScore_umapStartState,
                 int P,
                 unsigned dimUserSentScoreVectors, int foldingTimes, int crypto2hide) {

    double avrgMAE;
    vector <double> MAE_list;

    cout <<"HI MAIN \n";

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
        cout << "~~~~~~~~~~~~~~~~~~~~~~ITERATIONS #" << i << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        vector<string> keysU2Change = keys2change(keysU, i, foldIn_f_piecesNumber); //EDW PAIRNW TO 1/10 KATHE FORA
        print_keys(keysU2Change);

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



        //todo gia tis times pou allaksa kanw rate ta crypto "predicted score"
        //todo tha parw mono ta u pou allaksa kai tha ta elenksw

        vector <pair<double,double>> predictedAndRealScorePair;

        for (auto &UserScorePairChanged :  UserIndexesPairsChanged) {
            cout << UserScorePairChanged.first << ":" << UserScorePairChanged.second << endl;

            string uId = UserScorePairChanged.first;
            int index2change = UserScorePairChanged.second;
            myVector u = userTweetsSentimScoreWithoutInfsAndZeroVectors_umap[uId];



            set<string> list2search = abstractLshClust_ptr->getSuperSet(u, userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

            assert(!list2search.empty());

            if (list2search.size() == 1){continue;} //no reason because we cant predict

            vector<string> bestP_u  = NN_searchForBestP(u,uId, metric, userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, list2search, P);




            double realRating = userTweetsSentimScore_umapStartState.at(uId).getCoords().at(index2change);
            double  predictedRating = RateCrypto(u, bestP_u, uId, metric,
                                                 userTweetsAverageSentimScore_umap,
                                                 userTweetsAverageSentimScore_umap,
                                                 userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, index2change);


            predictedAndRealScorePair.emplace_back(predictedRating,realRating);
            cout << "realRating:" << realRating<<endl;
            cout << "predictedRating:" << predictedRating<<endl;

        }

        double MeanAbsoluteError = MAE(predictedAndRealScorePair);
        MAE_list.push_back(MeanAbsoluteError);

        cout <<"\n\n";
        cout <<"MAE = "<< MeanAbsoluteError<<endl;

        userTweetsSentimScore_umap2change= userTweetsSentimScore_umapStartState; //return 2 initial umap dataset (userTweetsSentimScore)

        delete abstractLshClust_ptr;abstractLshClust_ptr= nullptr;

    }

    delete metric;metric= nullptr;

    avrgMAE = accumulate( MAE_list.begin(), MAE_list.end(), 0.0)/MAE_list.size(); ;

    cout << "AVERAGE MAE: "<<avrgMAE<<endl;

    return 0;
}



//Rj=actual rating, Pj =predicted rating
double MAE(vector <pair<double,double>> predictedAndRealScorePair) {//Mean Absolute Error

    double mae=0;
    int j=0;
    for (auto& myPair : predictedAndRealScorePair ){
        mae += abs(myPair.second - myPair.first);
        assert(mae >=0);
        j++;
    }

    assert(j>0);
    return mae/j;
}














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

        if (counter > crypto2hide && counter != counterZeros){ // be sure these vectors will not be evicted from the withouInfs&Zeros umap
            return 0; //is Valid 2 change It
        }
    }

    return  1; //is NOT Valid 2 change It
}



//int getNewCoinIndex2change(vector<int> coinRandomlyChosenFixed){
//    int position;
//
//    while (1){
//        position = static_cast<int>(std::rand() % coinRandomlyChosenFixed.size());
//
//        for (auto posFixed : coinRandomlyChosenFixed){
//            if (position != posFixed )
//        }
//    }
//
//    return
//}


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


vector<pair<string,int>> changeDataset(unordered_map<string, myVector>  &userTweetsSentimScore_umap, const vector <string> &keysU2Change,int crypto2hide){
    vector<pair<string,int>> valuesChanged;
    for (auto& u_key : keysU2Change){
        myVector u2change = userTweetsSentimScore_umap[u_key];
        if (isNotValid2changeVector(u2change,crypto2hide) ){ //if not valid to change continue
            continue;
        }
        vector<int> indexesInCurrentU2change = changeSomeCryptoScores2unknown(u2change,crypto2hide);
        for (auto curr_index : indexesInCurrentU2change){
            valuesChanged.emplace_back(u_key,curr_index);
        }

    }

    return valuesChanged;
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








