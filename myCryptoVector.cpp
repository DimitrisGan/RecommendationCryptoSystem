//
// Created by dimitrisgan on 31/12/2018.
//


#include <cmath>
#include "myCryptoVector.h"


class myVector;

double calculateSentimentScore(double totalScore){
    double Si;
    double denominator = sqrt(pow(totalScore,2) + ALPHA);
    Si  = totalScore / denominator;

    return Si;
}




// Function to check if the key is present or not
string check_key(const unordered_map<string ,double> &m, const string &key) // m = vaderLexicon_umap
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
set<int>    calculateTweetsScore(const string &tweetId, double &totalScore ,const unordered_map <string , Tweet > &tweets_umap,
                                 const unordered_map<string ,double> &vaderLexicon_umap  , const unordered_map<string ,int> &coins_umap ){

//    cout << "\n\n======================== NEW TWEET #"<<tweetId <<" ====================\n\n";

    set <int> coinsMentionedInTweet;

    Tweet tweetContext = tweets_umap.at(tweetId);

    for (const auto &wordInTweet : tweetContext.context ){
//        if (tweetId == "3591"){
////            cout <<"mpika\n";
//            cout << wordInTweet<<"\t";
//
//        }

        if (coins_umap.count(wordInTweet) > 0){ // if word exists in Coins Lexicon
            coinsMentionedInTweet.insert(coins_umap.at(wordInTweet)); //insert it in mentionCoinsInTweet
        }

        if (vaderLexicon_umap.count(wordInTweet) > 0){ //it means that the word exists in vader Lexicon
            totalScore+= vaderLexicon_umap.at(wordInTweet); //add it to the existing totalScore
        }

    }

//    if (tweetId == "3591"){
//        cout <<"\n\n NOW EXIT\n\n";
//        exit(1);
//
//    }
    /////////////////// diagnostic Prints Here
//    for ( auto &coinIndex : coinsMentionedInTweet) {
//        cout << "coinIndex = "<<coinIndex<<endl;
//    }



    return coinsMentionedInTweet;
}



/*calculating U vectors*/
void calculateUsersSentimentCryptoScoreMap(unordered_map<string, myVector> &userTweetsSentimScore_umap,
                                           const unordered_multimap<string, string> &userTweetsRelation_ummap,
                                           const unordered_map<string, Tweet> &tweets_umap,
                                           const unordered_map<string, double> &vaderLexicon_umap,
                                           const unordered_map<string, int> &coins_umap, int userVectorSize)
{

    //kanw extract ta keys se ena set
    //meta pairnw ena ena ta aknw query kai vriskw ta tweets ids

    set<string> multiMapKeys = extractMultiMapKeys (userTweetsRelation_ummap); //In this set now I have all the keys of the multiset


    for (const auto &userId : multiMapKeys ) { //gia kathe user

//        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ FOR USER #"<<userId <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";


        myVector u;
        u.initializeToInf(userVectorSize);
//        u.printCryptoVector();


        auto range =userTweetsRelation_ummap.equal_range(userId); //


        for (auto it=range.first;it!=range.second;++it){ //gia kathe Tweet you current User
//            cout << it->first<< " : "<<it->second<<endl;

            double totalScore=0;
            set<int> CoinsIndexes2addScoreInUser = calculateTweetsScore(it->second /*tweetId*/,totalScore , tweets_umap ,vaderLexicon_umap , coins_umap );


            double sentimentScore = calculateSentimentScore(totalScore);
            myVector current_u;
            current_u.initializeToInf(userVectorSize);
//            u.setMyCryptoVector(set <int> CoinsIndexes2addScoreInUser , float totalScore);

            //TODO EDW LOGIKA THA KALESW THN ADD2USERSVECTORU!!!!!!!
            current_u.setVectorToSpecificIndexes(CoinsIndexes2addScoreInUser , sentimentScore);


//            current_u.printCryptoVector();

//            cout << "BEFORE U = " <<endl;
//            u.printCryptoVector();
//            cout << "ADD WITH CURRENT U"<<endl;
//            current_u.printCryptoVector();

            u = u + current_u; //add to u UsersVector the tweetsVector
        }


//        cout << "AFTER U = " <<endl;
//        cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ USER'S U  #"<<userId <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
//
//        u.printCryptoVector();

        //TODO to prosthetw sto userTweetsSentimScore_umap setarwntas prwta to myVector

        //todo EDW THA TO KANW INSERT STO MAP userTweetsSentimScore_umap
        userTweetsSentimScore_umap.insert(make_pair(userId , u));

    }

}



//void    calculateUsersSentimentCryptoScoreMap(unordered_map <string , myVector > &userTweetsSentimScore_umap,
//                                              const unordered_multimap <string ,string> &userTweetsRelation_ummap,
//                                              const unordered_map <string , Tweet > &tweets_umap,
//                                              const unordered_map<string ,double> &vaderLexicon_umap ,
//                                              const unordered_map<string ,int> &coins_umap )


void calculateVirtualUsersFromTwitterCluster(unordered_map<string, myVector> &virtualUserTweetsSentimScore_umap,
                                             kClusters &TwitterCluster, const unordered_map<string, Tweet> &tweets_umap,
                                             const unordered_map<string, double> &vaderLexicon_umap,
                                             const unordered_map<string, int> &coins_umap, int userVectorSize)
{



    for (auto cluster : TwitterCluster.getClusters() ) { //gia kathe user

//        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ FOR USER #"<<userId <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";


        myVector c;
        c.initializeToInf(userVectorSize);
//        u.printCryptoVector();




        for (const auto tweetId : cluster->getDatapoints()){ //gia kathe Tweet you current User
//            cout << it->first<< " : "<<it->second<<endl;

            double totalScore=0;
            set<int> CoinsIndexes2addScoreInUser = calculateTweetsScore(tweetId,totalScore , tweets_umap ,vaderLexicon_umap , coins_umap );


            double sentimentScore = calculateSentimentScore(totalScore);
            myVector current_c;
            current_c.initializeToInf(userVectorSize);
//            u.setMyCryptoVector(set <int> CoinsIndexes2addScoreInUser , float totalScore);

            //TODO EDW LOGIKA THA KALESW THN ADD2USERSVECTORU!!!!!!!
            current_c.setVectorToSpecificIndexes(CoinsIndexes2addScoreInUser , sentimentScore);


//            current_u.printCryptoVector();

//            cout << "BEFORE U = " <<endl;
//            u.printCryptoVector();
//            cout << "ADD WITH CURRENT U"<<endl;
//            current_u.printCryptoVector();

            c = c + current_c; //add to u UsersVector the tweetsVector
        }


//        cout << "AFTER U = " <<endl;
//        cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~ USER'S U  #"<<userId <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
//
//        u.printCryptoVector();

        //TODO to prosthetw sto userTweetsSentimScore_umap setarwntas prwta to myVector

        //todo EDW THA TO KANW INSERT STO MAP userTweetsSentimScore_umap

        string clusterId = to_string(cluster->getId());
//        cout << clusterId <<endl;
        virtualUserTweetsSentimScore_umap.insert(make_pair(clusterId , c));

    }


}



void calculateAverageU_umap(unordered_map<string, double> &userTweetsAverageSentimScore_umap,
                            const unordered_map<string, myVector> &userTweetsSentimScore_umap){

    for (const auto &u : userTweetsSentimScore_umap) {
        double averageScore = calculateAverageU(u.second);
        userTweetsAverageSentimScore_umap.insert(make_pair(u.first,averageScore));

    }


}


//todo Όχι. Αυτοί μετά την κανονικοποίηση είναι [-1, 1, 0, ..., 0] επομένως δεν είναι μηδενικά διανύσματα.

double calculateAverageU(const myVector &u ){
    double avrg=0;
    double sum=0;
    double counter=0;
    double inf = std::numeric_limits<double>::infinity();

    for (auto coord : u.getCoords()){
        if (coord != inf){
            counter++;
            sum+=coord;
        }
        else{
            continue; // is inf
        }
    }

    if (counter == 0  ) {
        return 0;
    }
    avrg = sum / counter;


    return avrg;
}


myVector  normalizeU(const myVector &u , const double& avrg){
    myVector uNormilized;
    vector<double> normalizedCoords;

    double inf = std::numeric_limits<double>::infinity();


    for (auto coord : u.getCoords()){
        if (coord == inf){ //all infs convert them to Zeros
            normalizedCoords.push_back(0);
        }
        else{
            normalizedCoords.push_back(coord - avrg);
        }
    }


    uNormilized.setCoords(normalizedCoords);

    return uNormilized;
}


int isZeroVector(const vector <double> &coords){
    for (auto coord : coords){
        if (coord != 0)
            return 0;
    }
    return  1;
}



//void calculateNormalizeUsersSentimentCryptoScoreMap(unordered_map <string , myVector > &userTweetsSentimScoreNormalized_umap,
//                                                    const unordered_map <string , myVector > &userTweetsSentimScore_umap )
//
//{
//    for (const auto &u : userTweetsSentimScore_umap){
//
//        double averageU = calculateAverageU(u.second );
//        myVector uNormilized;
//
//
//        if (averageU != 0){  //means that the user has only 1 tweet or that refers to only one crypto
//
//            //    convertInfs2Zeros(unordered_map <string , myVector > &userTweetsSentimScoreNormalized_umap,
//            uNormilized = normalizeU( u.second , averageU);
//
//            if(! isZeroVector(uNormilized.getCoords())){
//
//                userTweetsSentimScoreNormalized_umap.insert(make_pair(u.first,uNormilized));
//            }
//
//            else{
//                continue;
//            }
//
//
//        }
//
//    }
//
//}







void printUsersSentimentCryptoScoreMap(const unordered_map <string , myVector > &userTweetsSentimScore_umap){
    int i=0;
    for (auto user : userTweetsSentimScore_umap){

        cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<i++<<": USER'S U  #"<<user.first <<" ~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        user.second.print_vector();

    }
}



void changeInfsToAverageSentimentsAndDiscardZeroVectors(
        unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
        const unordered_map<string, myVector> &userTweetsSentimScore_umap,
        const unordered_map<string, double> &userTweetsAverageSentimScore_umap) {

    double inf = std::numeric_limits<double>::infinity();

    for (const auto &u : userTweetsSentimScore_umap){
        vector <double> newCoords;
        for (auto coord : u.second.getCoords()){
            if (coord == inf){
                newCoords.push_back(userTweetsAverageSentimScore_umap.at(u.first));
            }
            else{
                newCoords.push_back(coord);
            }
        }

        int zeroVectorFlag =  isZeroVector(newCoords);
        if (zeroVectorFlag){
            continue;
        }


        myVector newU (newCoords);
        userTweetsSentimScoreWithoutInfsAndZeroVectors_umap.insert(make_pair(u.first,newU));
    }


}

// ================================================================================================================
// ================================================================================================================



//myVector::myVector() {
//
//    double inf = std::numeric_limits<double>::infinity();
//
//    vector <double> CryptoSc(100,inf);
//
//    this->CryptoScore = CryptoSc;
//
//}
//
//
//
//void myVector::printCryptoVector(){
//    cout<<"[";
//    int i=0;
//    for (auto coinScore : this->CryptoScore){
////        cout<<""<<i++<<" :"<<coinScore<<",";
//        cout<<coinScore<<",";
//    }
//    cout<<"]\n";
//}
////myCryptoVector()  : CryptoScore( 100, value ) {}
//
//
//void myVector::setMyCryptoVector(set<int> coinsIndexes2addScoreInUser , double Si){
//
//    for (auto coinIndex : coinsIndexes2addScoreInUser){
//        this->CryptoScore[coinIndex] = Si;
//    }
//}
//
//void myVector::setCryptoScore(const vector<double> &CryptoScore) {
//    myVector::CryptoScore = CryptoScore;
//}


