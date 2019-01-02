//
// Created by dimitrisgan on 31/12/2018.
//


#include <cmath>
#include "myCryptoVector.h"





double calculateSentimentScore(float totalScore){
    double Si;
    double denominator = sqrt(pow(totalScore,2) + ALPHA);
    Si  = totalScore / denominator;

    return Si;
}




// Function to check if the key is present or not
string check_key(const unordered_map<string ,float> &m, const string &key) // m = vaderLexicon_umap
{
    // Key is not present
    if (m.find(key) == m.end())
        return "Not Present";

    return "Present";
}



set<string> extractMultiMapKeys (const unordered_multimap <string ,string> &userTweetsRelation_ummap){
    set<string> multiMapKeysSet;
    for (const auto &user :  userTweetsRelation_ummap){
        multiMapKeysSet.insert(user.first);
    }

    return  multiMapKeysSet;
}


/*returns a vector of coins indexes to add and totalscore */
set<int>    calculateTweetsScore(const string &tweetId, float &totalScore ,const unordered_map <string , Tweet > &tweets_umap,
                                    const unordered_map<string ,float> &vaderLexicon_umap  , const unordered_map<string ,int> &coins_umap ){

    cout << "\n\n======================== NEW TWEET #"<<tweetId <<" ====================\n\n";

    set <int> coinsMentionedInTweet;

    Tweet tweetContext = tweets_umap.at(tweetId);

    for (const auto &wordInTweet : tweetContext.context ){
        cout << wordInTweet<<"\t";

        if (coins_umap.count(wordInTweet) > 0){ // if word exists in Coins Lexicon
            coinsMentionedInTweet.insert(coins_umap.at(wordInTweet)); //insert it in mentionCoinsInTweet
        }

        if (vaderLexicon_umap.count(wordInTweet) > 0){ //it means that the word exists in vader Lexicon
            totalScore+= vaderLexicon_umap.at(wordInTweet); //add it to the existing totalScore
        }
    }
    cout <<endl;

    /////////////////// diagnostic Prints Here
//    for ( auto &coinIndex : coinsMentionedInTweet) {
//        cout << "coinIndex = "<<coinIndex<<endl;
//    }



    return coinsMentionedInTweet;
}



/*calculating U vectors*/
void calculateUsersSentimentCryptoScoreMap(unordered_map <string , myCryptoVector > &userTweetsSentimScore_umap,
                                           const unordered_multimap <string ,string> &userTweetsRelation_ummap,
                                           const unordered_map <string , Tweet > &tweets_umap,
                                           const unordered_map<string ,float> &vaderLexicon_umap ,
                                           const unordered_map<string ,int> &coins_umap )
{

    //kanw extract ta keys se ena set
    //meta pairnw ena ena ta aknw query kai vriskw ta tweets ids

     set<string> multiMapKeys = extractMultiMapKeys (userTweetsRelation_ummap); //In this set now I have all the keys of the multiset


    for (const auto &userId : multiMapKeys ) { //gia kathe user

        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ FOR USER #"<<userId <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";


        myCryptoVector u;
        u.printCryptoVector();


        auto range =userTweetsRelation_ummap.equal_range(userId); //
        //TODO  edw logika tha ftiaksw to u!!!!!!


        for (auto it=range.first;it!=range.second;++it){ //gia kathe Tweet you current User
//            cout << it->first<< " : "<<it->second<<endl;

            float totalScore=0;
            set<int> CoinsIndexes2addScoreInUser = calculateTweetsScore(it->second /*tweetId*/,totalScore , tweets_umap ,vaderLexicon_umap , coins_umap );


            double sentimentScore = calculateSentimentScore(totalScore);
            myCryptoVector current_u;
//            u.setMyCryptoVector(set <int> CoinsIndexes2addScoreInUser , float totalScore);

            //TODO EDW LOGIKA THA KALESW THN ADD2USERSVECTORU!!!!!!!
            current_u.setMyCryptoVector(CoinsIndexes2addScoreInUser , sentimentScore);


//            current_u.printCryptoVector();

//            cout << "BEFORE U = " <<endl;
//            u.printCryptoVector();
            cout << "ADD WITH CURRENT U"<<endl;
            current_u.printCryptoVector();

            u = u + current_u; //add to u UsersVector the tweetsVector
        }


//        cout << "AFTER U = " <<endl;
        cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ USER'S U  #"<<userId <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        u.printCryptoVector();

        //TODO to prosthetw sto userTweetsSentimScore_umap setarwntas prwta to myCryptoVector

        //todo EDW THA TO KANW INSERT STO MAP userTweetsSentimScore_umap
        userTweetsSentimScore_umap.insert(make_pair(userId , u));

    }

}



// ================================================================================================================
// ================================================================================================================



myCryptoVector::myCryptoVector() {

    double inf = std::numeric_limits<double>::infinity();

    vector <double> CryptoSc(100,inf);

    this->CryptoScore = CryptoSc;

}



void myCryptoVector::printCryptoVector(){
    cout<<"[";
    for (auto coinScore : this->CryptoScore){
        cout<<coinScore<<",";
    }
    cout<<"]\n";
}
//myCryptoVector()  : CryptoScore( 100, value ) {}


void myCryptoVector::setMyCryptoVector(set<int> coinsIndexes2addScoreInUser , double Si){

    for (auto coinIndex : coinsIndexes2addScoreInUser){
        this->CryptoScore[coinIndex] = Si;
    }
}

void myCryptoVector::setCryptoScore(const vector<double> &CryptoScore) {
    myCryptoVector::CryptoScore = CryptoScore;
}



void printUsersSentimentCryptoScoreMap(const unordered_map <string , myCryptoVector > &userTweetsSentimScore_umap){
    for (auto user : userTweetsSentimScore_umap){
        cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ USER'S U  #"<<user.first <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        user.second.printCryptoVector();

    }
}
