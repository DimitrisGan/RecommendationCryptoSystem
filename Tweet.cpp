//
// Created by dimitrisgan on 30/12/2018.
//

#include "Tweet.h"

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

