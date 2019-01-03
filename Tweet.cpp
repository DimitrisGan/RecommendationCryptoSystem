//
// Created by dimitrisgan on 30/12/2018.
//

#include "Tweet.h"

using namespace std;



/*void calculateTweetsScore( unordered_map <string , double > &tweetsScore_umap , const unordered_map<string ,float> &vaderLexicon_umap){

}*/



void Tweet::printTweet(){

    cout << "Tweet : [";
    for (const auto &tw : this->context ){
        cout << tw << ",";
    }
    cout <<"]"<<endl;

}

ostream &operator<<(ostream &out, const Tweet &tweet)
{
    out << "Context:\t[";
    for (const auto &tw : tweet.context){
        out << tw <<",";
    }
    out <<"]"<<endl;
    return out;
}



void printTweetsCryptoReferencesNames(unordered_map <string , Tweet > tweets_umap , vector <string> CoinsList , unordered_map<string ,int> coins_umap){


    for (auto tweet : tweets_umap){
        cout << "\nPRINTING TWEET #"<<tweet.first<<endl;
//        tweet.second.printTweet();
        cout <<"[";
        for (auto word : tweet.second.context){
            if (coins_umap.count(word) > 0){
                int index = coins_umap.at(word);
                cout << CoinsList.at(index)<<",";
            }
        }
        cout <<"]\n";
    }
}