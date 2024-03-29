//
// Created by dimitrisgan on 23/10/2018.
//

#include "SearchingAlgorithms.h"
#include "AssistantFunctions.h"



vector<string> NN_searchForBestP(myVector &q, const string &qId, DistanceMetrics *metric, unordered_map<string, myVector> &in_umap,
                                 vector<string> &list2search, int number) {

    vector<string> bestP ;
    myVector p;
    string b ;


    for (int i = 0; i < number; ++i) {

        if(list2search.size() < number && i== list2search.size())
            break;


        double smallest_dist = numeric_limits<double>::infinity();
        double curr_dist;

        for (auto &p_id : list2search) {

            if (p_id == qId)
                continue;

            if (std::find(bestP.begin(), bestP.end(),p_id)!=bestP.end()){ //if is already in the bestP vector then continue
                continue;
            }

            p = in_umap[p_id];
            curr_dist = metric->distance(q, p);

            if (curr_dist < smallest_dist) {
                b = p_id;
                smallest_dist = curr_dist;
            }
        }
        bestP.push_back(b);

    }

    assert(bestP.size() <= number);

    return bestP;

}



vector<string> NN_searchForBestP(myVector &q, const string &q_id, DistanceMetrics *metric, unordered_map<string, myVector> &in_umap,
                                 set<string> &list2search, int number){

    vector<string> bestP ;
    myVector p;
    double distance;


    vector <pair<string,double>> neighborVectorsDistance;
    for (auto &p_id : list2search) {
        if (p_id == q_id){continue;}

        p = in_umap[p_id];
        distance = metric->distance(q, p);
        neighborVectorsDistance.emplace_back(p_id,distance);
    }


    if (number > list2search.size()){
        std::vector<string> listReturned(list2search.begin(), list2search.end());
        return listReturned;
    }

    std::sort(neighborVectorsDistance.begin(),neighborVectorsDistance.end(), [](pair<string,double> a, pair<string,double> b){ return a.second > b.second;} );


    bestP.reserve(number);
    for (int i = 0; i < number; ++i) {

        if((list2search.size()-1) < number && i== (list2search.size()-1)) {
            break;
        }
        bestP.push_back(neighborVectorsDistance.at(i).first);
    }

    assert(bestP.size() <= number);
    return bestP;

}


//=================================================================================================
string NN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , vector <string>& list2search  ){

    string b ;
    myVector p;
    double smallest_dist = numeric_limits<double>::infinity();
    double curr_dist;

    for (auto &p_id : list2search) {
        p = in_umap[p_id];
        curr_dist = metric->distance(q, p);

        if (curr_dist < smallest_dist){
            b = p_id;
            smallest_dist = curr_dist;
        }
    }
    return b;


}

string NN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , set <string>& list2search  ){

    string b ;
    myVector p;
    double smallest_dist = numeric_limits<double>::infinity();
    double curr_dist;

    for (auto &p_id : list2search) {
        p = in_umap[p_id];
        curr_dist = metric->distance(q, p);

        if (curr_dist < smallest_dist){
            b = p_id;
            smallest_dist = curr_dist;
        }
    }
    return b;


}

//=================================================================================================


vector <string > RangeN_search(myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , vector <string>& list2search  , int& R){

    vector <string> nn_list;
    myVector p;
    double curr_dist;


    for (auto &p_id : list2search) {
        p = in_umap[p_id];
        curr_dist = metric->distance(q, p);
        if (curr_dist < C * R){

            nn_list.push_back(p_id);
        }

    }



    return nn_list;
}
vector <string > RangeN_search(myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , set <string>& list2search  , int& R){

    vector <string> nn_list;
    myVector p;
    double curr_dist;


    for (auto &p_id : list2search) {
        p = in_umap[p_id];
        curr_dist = metric->distance(q, p);
        if (curr_dist < C * R){

            nn_list.push_back(p_id);
        }

    }



    return nn_list;
}

//=================================================================================================


string TrueNN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap  ){ //Brute Force
    string TrueNN;
    myVector p;
    double curr_dist;
    double smallest_dist = numeric_limits<double>::infinity();

    std::vector<std::string> keys_p;
    keys_p = extract_keys(in_umap);

    for (auto &p_id : keys_p) {
        p = in_umap[p_id];
        curr_dist = metric->distance(q, p);

        if (curr_dist < smallest_dist){
            TrueNN = p_id;
            smallest_dist = curr_dist;
        }

    }


    return TrueNN;
}



