//
// Created by dimitrisgan on 30/12/2018.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_TWEET_H
#define RECOMMENDATIONCRYPTOSYSTEM_TWEET_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>




using namespace std;



void calculateTweetsScoreMap( const unordered_map<string ,double> &vaderLexicon_umap ,unordered_map <string , double > &tweetsScore_umap);


class Tweet {
public:

//    int tweetId;
    vector<string> context;


    friend ostream & operator << (ostream &out, const Tweet &tweet);

    void printTweet();
};


void printTweetsCryptoReferencesNames(unordered_map <string , Tweet > tweets_umap , vector <string> CoinsList , unordered_map<string ,int> coins_umap);


#endif //RECOMMENDATIONCRYPTOSYSTEM_TWEET_H

