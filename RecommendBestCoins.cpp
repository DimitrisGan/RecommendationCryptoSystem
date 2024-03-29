//
// Created by dimitrisgan on 5/1/2019.
//


#include "RecommendBestCoins.h"

/*from all the neighbors calculate in the current crypto the Sentiment Score*/
double RateCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id, DistanceMetrics *metric,
                  const unordered_map<string, double> &U_rating_umap,
                  const unordered_map<string, double> &V_rating_umap,
                  const unordered_map<string, myVector> &V_users_umap, int i)

{

    double avrgU_CryptoRating = U_rating_umap.at(u_Id);
    double sumSimilarities =0;
    double sumV_normalizedRatings=0 ;

//    assert(!bestP_u.empty());
    for (const auto &v_Id : bestP_u){
        myVector v = V_users_umap.at(v_Id);
        double dist = metric->distance(u,v);
        double similarity = metric->similarity(dist);

        sumSimilarities +=  abs(similarity);
        assert(abs(similarity) >= 0);

        double vCryptoRating = v.getCoords().at(i);
        double avrgV_CryptoRating = V_rating_umap.at(v_Id);

        double vNormalization = vCryptoRating - avrgV_CryptoRating;

        sumV_normalizedRatings += similarity * vNormalization;

    }

    assert(sumSimilarities > 0);
    double z = 1/sumSimilarities;

    double uCryptoRating= avrgU_CryptoRating + z*sumV_normalizedRatings;


    return uCryptoRating;
}




/*from all the neighbors calculate all the crypto's the Sentiment Score*/
vector<pair<int, double>>
EvaluateAllCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id, DistanceMetrics *metric,
                  const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                  const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                  const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
{

    vector <pair<int,double>> cryptoRatings;
//    double inf = std::numeric_limits<double>::infinity();

    for (int i = 0; i < u.getCoords().size(); ++i) {


        double RatingOfCurrentCrypto  = RateCrypto(u, bestP_u, u_Id, metric, U_userTweetsAverageSentimScore_umap,
                                                   V_userTweetsAverageSentimScore_umap,
                                                   V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, i);

        cryptoRatings.push_back(make_pair(i,RatingOfCurrentCrypto));
    }


    return cryptoRatings;

}




vector<string> recommendBestCoinsForUser(myVector &u, const vector<string> &bestP_u, const string &u_Id, int number2recommend,
                                         const vector<string> &CoinsList, DistanceMetrics *metric,
                                         const unordered_map<string, myVector> &userTweetsSentimScore_umap,
                                         const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                                         const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                                         const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
{

    double inf = std::numeric_limits<double>::infinity();

    vector <string> coins2Recommend;

    vector <pair<int,double>> cryptosRatings = EvaluateAllCrypto(u, bestP_u, u_Id,
                                                                 metric, U_userTweetsAverageSentimScore_umap,
                                                                 V_userTweetsAverageSentimScore_umap,
                                                                 V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


    std::sort(cryptosRatings.begin(),cryptosRatings.end(), [](pair<int,double> a, pair<int,double> b){ return a.second > b.second;} );


    int i=0;
    for (auto crypto2recommend : cryptosRatings){

        int indexOfcoin = crypto2recommend.first;

        if(userTweetsSentimScore_umap.at(u_Id).getCoords().at(indexOfcoin) != inf ){ //it is already referred from the user this crypto
            continue;
        }

        coins2Recommend.push_back(CoinsList.at(indexOfcoin));



        if (i== (number2recommend-1)){break;}
        i++;
    }


    return coins2Recommend;

}





//vector <string> recommendBestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const string &u_Id ,int number2recommend,
//                                          const vector <string> &CoinsList,
//                                          const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
//
//                                          const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
//                                          const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
//                                          const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap
//)
//{

void  RecommendationSystem(  map<string,vector<string>> &RecommendedCoins2Users,
//                            /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/ const vector<string> &bestP_u ,
        /*todo auto tha to vgalw de paizei///tha pairnaw pointer lsh-cluster*/
                             AbstractLshCluster *abstractLshClust_ptr,
                             DistanceMetrics *metric,
                             int P, //number of best Neighbors
                             int numberOfCoins2recommend, //number2recommend
                             const vector <string> &CoinsList,
                             const unordered_map <string , myVector > &userTweetsSentimScore_umap , //we need it to not a recommend an laready existing coin that user has spoken about

                             const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                             const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                             unordered_map<string, myVector> &U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                             unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap
)

{


    for (auto &u :  U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap){

        set <string> list2search = abstractLshClust_ptr->getSuperSet(u.second , V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

        if (list2search.empty()){ //case in  dataStructure with virtual Users
            vector <string> NoneVector {"NO SUGGESTION"};
            RecommendedCoins2Users[u.first] = NoneVector;
            continue;
        }
        if (list2search.size() == 1 && list2search.count(u.first)) {//case in  dataStructure with real Users and is the only one on the dataset
            // u is in the set, count is 1
            vector<string> NoneVector{"NO SUGGESTION"};
            RecommendedCoins2Users[u.first] = NoneVector;
            continue;
        }

        vector<string> bestP_u  = NN_searchForBestP(u.second,u.first, metric, V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, list2search, P);


        vector <string> recommendBestCoinsForCurrentUserU = recommendBestCoinsForUser(u.second, bestP_u, u.first,
                                                                                      numberOfCoins2recommend,
                                                                                      CoinsList, metric,
                                                                                      userTweetsSentimScore_umap,

                                                                                      U_userTweetsAverageSentimScore_umap,
                                                                                      V_userTweetsAverageSentimScore_umap,
                                                                                      V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

        RecommendedCoins2Users[u.first] = recommendBestCoinsForCurrentUserU;
    }


}


//======================================================

void printrecommendedCoins2Users(const map<string,vector<string>> &RecommendedCoins2Users){
    int i=0;
    for (auto recommendedCoins2Userr: RecommendedCoins2Users){
        cout<<i++<<": for User #"<<recommendedCoins2Userr.first<<" \t\t";
        cout << "[";
        for (const auto &coins2recommend: recommendedCoins2Userr.second){
            cout<<coins2recommend<<",";
        }
        cout << "]\n";

    }

}



RecommendCoins::RecommendCoins(int P, int numberOfCoins2recommend, const vector<string> &CoinsList,
                               const unordered_map<string, myVector> &userTweetsSentimScore_umap,
                               const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                               unordered_map<string, myVector> &U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                               const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                               unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
        : P(P), numberOfCoins2recommend(numberOfCoins2recommend), CoinsList(CoinsList),
          userTweetsSentimScore_umap(userTweetsSentimScore_umap),
          U_userTweetsAverageSentimScore_umap(U_userTweetsAverageSentimScore_umap),
          U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap(U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap),
          V_userTweetsAverageSentimScore_umap(V_userTweetsAverageSentimScore_umap),
          V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap(
                  V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap) {}

void
RecommendCoins::operator()(map<string, vector<string>> &RecommendedCoins2Users, DistanceMetrics *metric,
                           AbstractLshCluster *abstractLshClust_ptr) {


    RecommendationSystem(  RecommendedCoins2Users,
                           abstractLshClust_ptr,
                           metric,
                           P, //number of best Neighbors
                           numberOfCoins2recommend, //number2recommend
                           CoinsList,
                           userTweetsSentimScore_umap , //we need it to not a recommend an laready existing coin that user has spoken about

                           U_userTweetsAverageSentimScore_umap,
                           V_userTweetsAverageSentimScore_umap,
                           U_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                           V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap
    );
}



