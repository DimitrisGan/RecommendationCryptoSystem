//
// Created by dimitrisgan on 5/1/2019.
//

#include "RecommendBestCoins.h"




//R(u,i) = z * (Σsim(u,υ)*R(υ,i))


void recommend5BestCoinsForUser(){

    //
}



double RateCrypto(myVector &u , const vector<string> &bestP_u ,    const unordered_map <string , myVector > &userTweetsSentimScore_umap , int i){
    double uCryptoRating=0;

    for (const auto &v_Id : bestP_u){
        myVector v = userTweetsSentimScore_umap.at(v_Id);

        double enumerator = u.dot_product(v);
        double denominator = u.euclidean_norm()/v.euclidean_norm();

        double similarity = enumerator/denominator;

        double vCryptoRating = v.getCoords().at(i);

        uCryptoRating += similarity * vCryptoRating;

    }

    return uCryptoRating;
}


//todo prepei na kanw recommend coins pou den exei hdh
vector <double> EvaluateAllCrypto(myVector &u ,const vector<string> &bestP_u ,const  unordered_map <string , myVector > &userTweetsSentimScore_umap  ){

    vector <double> EvaluateAllCryptoFor_u;


    vector <double> cryptoRatings;
    for (int i = 0; i < u.getCoords().size(); ++i) {


        double RatingOfCurrentCrypto  = RateCrypto(u ,bestP_u,userTweetsSentimScore_umap , i);

        cryptoRatings.push_back(RatingOfCurrentCrypto);
    }



    return EvaluateAllCryptoFor_u;

}


//todo prepei na kane iterate epanalipsi gia kathe u sto map na callarw evaluate kai meta na vriskw to katallhlo pou thelw
vector <int> recommend5BestCoinsForUser(myVector &u ,const vector<string> &bestP_u ,const  unordered_map <string , myVector > &userTweetsSentimScore_umap  ){

    vector <int> coinsIndexes2Recommend;


    vector <double> cryptoRatings;
    for (int i = 0; i < u.getCoords().size(); ++i) {


        double RatingOfCurrentCrypto  = RateCrypto(u ,bestP_u,userTweetsSentimScore_umap , i);

        cryptoRatings.push_back(RatingOfCurrentCrypto);
    }



    return coinsIndexes2Recommend;

}
