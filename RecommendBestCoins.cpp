//
// Created by dimitrisgan on 5/1/2019.
//


#include "RecommendBestCoins.h"




//R(u,i) = z * (Σsim(u,υ)*R(υ,i))

//R(u,i)= R(u)+ z*Σsim(u,υ)*(R(υ,i)-R(υ))


double RateCrypto(myVector &u, const vector<string> &bestP_u, const string &u_Id,
                  const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                  const unordered_map<string, myVector> &userTweetsSentimScore_umap,
                  const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, int i) {

    double avrgU_CryptoRating = userTweetsAverageSentimScore_umap.at(u_Id);
    double sumSimilarities =0;
    double sumV_normalizedRatings=0 ;

    for (const auto &v_Id : bestP_u){
        myVector v = userTweetsSentimScoreWithoutInfsAndZeroVectors_umap.at(v_Id);

        double enumerator = u.dot_product(v);
        double denominator = u.euclidean_norm()/v.euclidean_norm();

        double similarity = enumerator/denominator;
        sumSimilarities +=  abs(similarity);

        double vCryptoRating = v.getCoords().at(i);
        double avrgV_CryptoRating = userTweetsAverageSentimScore_umap.at(v_Id);

        double vNormalization = vCryptoRating - avrgV_CryptoRating;

        sumV_normalizedRatings += similarity * vNormalization;

    }

    double z = 1/sumSimilarities;

    double uCryptoRating= avrgU_CryptoRating + z*sumV_normalizedRatings;


    return uCryptoRating;
}




//todo prepei na kanw recommend coins pou den exei hdh
vector <pair<double,int>> EvaluateAllCrypto(myVector &u ,const vector<string> &bestP_u ,const string &u_Id,
                                            const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                                            const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
                                            const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
{

    vector <pair<double,int>> cryptoRatings;
    double inf = std::numeric_limits<double>::infinity();

    for (int i = 0; i < u.getCoords().size(); ++i) {

        double coord = userTweetsSentimScore_umap.at(u_Id).getCoords().at(i);
        if (coord == inf){ continue;}

        double RatingOfCurrentCrypto  =  RateCrypto(u, bestP_u, u_Id, userTweetsAverageSentimScore_umap, userTweetsSentimScore_umap,
                                                    userTweetsSentimScoreWithoutInfsAndZeroVectors_umap, i);

        cryptoRatings.emplace_back(RatingOfCurrentCrypto,i);
    }



    return cryptoRatings;

}


//todo prepei na kane iterate epanalipsi gia kathe u sto map na callarw evaluate kai meta na vriskw to katallhlo pou thelw
vector <string> recommendBestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const string &u_Id ,int number2recommend,
                                          const vector <string> &CoinsList,
                                          const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                                          const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
                                          const unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap)
{

    vector <string> coins2Recommend;

    vector <pair<double,int>> cryptosRatings = EvaluateAllCrypto(u ,bestP_u ,u_Id,userTweetsAverageSentimScore_umap,
                                                                 userTweetsSentimScore_umap ,userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);


    std::sort(cryptosRatings.begin(),cryptosRatings.end(), [](pair<double,int> a, pair<double,int> b){ return a.second > b.second;} );


    int i=0;
    for (auto crypto2recommend : cryptosRatings){
        if (i== number2recommend){break;}

        int indexOfcoin = crypto2recommend.second;
        coins2Recommend.push_back(CoinsList.at(indexOfcoin));

        i++;
    }


    return coins2Recommend;

}



void  RecommendationSystem(  map<string,vector<string>> &RecommendedCoins2Users,
                             const vector<string> &bestP_u ,int number2recommend,
                             const vector <string> &CoinsList,
                             const unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                             const unordered_map <string , myVector > &userTweetsSentimScore_umap ,
                             unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap) {


    for (auto &u :  userTweetsSentimScoreWithoutInfsAndZeroVectors_umap){

        vector <string> recommendBestCoinsForCurrentUserU = recommendBestCoinsForUser(u.second ,bestP_u ,u.first ,number2recommend, CoinsList,
                                                                                      userTweetsAverageSentimScore_umap,
                                                                                      userTweetsSentimScore_umap ,
                                                                                      userTweetsSentimScoreWithoutInfsAndZeroVectors_umap);

        RecommendedCoins2Users[u.first] = recommendBestCoinsForCurrentUserU;
    }


}
