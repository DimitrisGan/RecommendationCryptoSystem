//
// Created by dimitrisgan on 31/12/2018.
//

#include <unordered_map>
#include <set>
#include <assert.h>
#include "myCryptoVector.h"
#include "Tweet.h"


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
vector<pair<int , float>> calculateTweetsScore(const string &tweetId, const unordered_map <string , Tweet > &tweets_umap,
                                    const unordered_map<string ,float> &vaderLexicon_umap  , const unordered_map<string ,int> &coins_umap ){

    cout << "\n\n\n======================== NEW TWEET #"<<tweetId <<" ====================\n\n\n";

    set <int> coinsMentionedInTweet;
    float totalScore=0;

    Tweet tweetContext = tweets_umap.at(tweetId);

    for (const auto &wordInTweet : tweetContext.context ){
        cout << wordInTweet<<"\t";
        //todo tsekarw an yparxei sto vader kai prosthetw to score
        //todo tsekarw gia poia crypto anaferetai to tweet
        if (coins_umap.count(wordInTweet) > 0){
            coinsMentionedInTweet.insert(coins_umap.at(wordInTweet));
            cout <<"\ncoins added EDW : "+wordInTweet<<endl;
        }
        if (vaderLexicon_umap.count(wordInTweet) > 0){ //it means that the word exists in vader Lexicon
            totalScore+= vaderLexicon_umap.at(wordInTweet);
        }
    }

    cout <<endl;
    for ( auto &coinIndex : coinsMentionedInTweet) {
        cout << "coinIndex = "<<coinIndex<<endl;
    }

    cout << "totalScore = " << totalScore <<endl;


    vector<pair<int , float>> coinsIndexesAndScore;

    return coinsIndexesAndScore;
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


    for (const auto &userId : multiMapKeys ) {

        auto range =userTweetsRelation_ummap.equal_range(userId); //
        for (auto it=range.first;it!=range.second;++it){
            cout << it->first<< " : "<<it->second<<endl;

            vector<pair<int , float>> CoinsIndexes2addScoreInUser = calculateTweetsScore(it->second /*tweetId*/, tweets_umap ,vaderLexicon_umap , coins_umap );
//            vector<pair<int , float>> CoinsIndexes2addScoreInUser = calculateTweetsScore("4209"/*tweetId*/, tweets_umap ,vaderLexicon_umap , coins_umap );


        }
//        break;


        /* for (const auto &tweetPair : tweets_umap) {
             for (const auto &word : tweetPair.second.context) {
 //            if (vaderLexicon_umap.)

                 if (check_key(vaderLexicon_umap, word) == "Present") { //if word is present in the vader lexicon

                 }

             }
         }*/

    /*   for (auto tweet : user.second ){
           for (auto word : tweet ){

           }
       }*/
    }

}
