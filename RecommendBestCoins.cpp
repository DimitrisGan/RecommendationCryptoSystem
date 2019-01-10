//
// Created by dimitrisgan on 5/1/2019.
//


#include "RecommendBestCoins.h"

/*from all the neighbors calculate in the current crypto the Sentiment Score*/
double RateCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
                  const unordered_map<string, double> &U_rating_umap,
                  const unordered_map<string,double> &V_rating_umap,
                  const unordered_map<string, myVector> &V_users_umap, int i)

{

    double avrgU_CryptoRating = U_rating_umap.at(u_Id);
    double sumSimilarities =0;
    double sumV_normalizedRatings=0 ;

//    assert(!bestP_u.empty());
    for (const auto &v_Id : bestP_u){
        myVector v = V_users_umap.at(v_Id);

        double enumerator = u.dot_product(v);
        double denominator = u.euclidean_norm()/v.euclidean_norm();

        double similarity = enumerator/denominator;
        sumSimilarities +=  abs(similarity);

        double vCryptoRating = v.getCoords().at(i);
        double avrgV_CryptoRating = V_rating_umap.at(v_Id);

        double vNormalization = vCryptoRating - avrgV_CryptoRating;

        sumV_normalizedRatings += similarity * vNormalization;

    }

    double z = 1/sumSimilarities;

    double uCryptoRating= avrgU_CryptoRating + z*sumV_normalizedRatings;


    return uCryptoRating;
}




//todo prepei na kanw recommend coins pou den exei hdh

/*from all the neighbors calculate all the crypto's the Sentiment Score*/
vector<pair<int, double>> EvaluateAllCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
                                            const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                                            const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                                            const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
{

    vector <pair<int,double>> cryptoRatings;
//    double inf = std::numeric_limits<double>::infinity();

    for (int i = 0; i < u.getCoords().size(); ++i) {

//        double coord = userTweetsSentimScore_umap.at(u_Id).getCoords().at(i);
//        if (coord == inf){ continue;}

        double RatingOfCurrentCrypto  = RateCrypto(u, bestP_u, u_Id, U_userTweetsAverageSentimScore_umap,
                                                   V_userTweetsAverageSentimScore_umap,
                                                   V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, i);

        cryptoRatings.emplace_back(i,RatingOfCurrentCrypto);
    }



    return cryptoRatings;

}



//EvaluateAllCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
//const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
//const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
//const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
//{


//todo prepei na kane iterate epanalipsi gia kathe u sto map na callarw evaluate kai meta na vriskw to katallhlo pou thelw
vector <string> recommendBestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const string &u_Id ,int number2recommend,
                                          const vector <string> &CoinsList,
                                          const unordered_map <string , myVector > &userTweetsSentimScore_umap ,

                                          const unordered_map<string, double> &U_userTweetsAverageSentimScore_umap,
                                          const unordered_map<string, double> &V_userTweetsAverageSentimScore_umap,
                                          const unordered_map<string, myVector> &V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap
)
{

    double inf = std::numeric_limits<double>::infinity();

    vector <string> coins2Recommend;

    vector <pair<int,double>> cryptosRatings = EvaluateAllCrypto(u ,bestP_u ,u_Id,U_userTweetsAverageSentimScore_umap,
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
                             Lsh *lsh_ptr,
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

        set <string> list2search = lsh_ptr->getSuperSet(u.second , V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);
        if (list2search.empty()){ //case in  dataStructure with virtual Users
            vector <string> NoneVector {"NONE"};
            RecommendedCoins2Users[u.first] = NoneVector;
            continue;
        }
        if (list2search.size() == 1 && list2search.count(u.first)) {//case in  dataStructure with real Users and is the only one on the dataset
            // u is in the set, count is 1
            vector<string> NoneVector{"NONE"};
            RecommendedCoins2Users[u.first] = NoneVector;
            continue;
        }

        vector<string> bestP_u  = NN_searchForBestP(u.second,u.first, metric, V_userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, list2search, P);


//todo        if (bestP_u.empty()){
//            continue; //to lsh de gurise geitones
//        }

        vector <string> recommendBestCoinsForCurrentUserU = recommendBestCoinsForUser(u.second ,bestP_u ,u.first , numberOfCoins2recommend, CoinsList,
                                                                                      userTweetsSentimScore_umap ,

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


void RecommendCoins::operator()(DistanceMetrics *metric, Lsh *lsh_ptr) {

    RecommendationSystem(metric,lsh_ptr);

}
