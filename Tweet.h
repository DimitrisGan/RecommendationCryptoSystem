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



void calculateTweetsScoreMap( const unordered_map<string ,float> &vaderLexicon_umap ,unordered_map <string , double > &tweetsScore_umap);


class Tweet {
public:

//    int tweetId;
    vector<string> context;


    friend ostream & operator << (ostream &out, const Tweet &tweet);

    void printTweet();
};



#endif //RECOMMENDATIONCRYPTOSYSTEM_TWEET_H

