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



vector<string> NN_searchForBestP(myVector &q, const string &qId, DistanceMetrics *metric, unordered_map<string, myVector> &in_umap,
                                 set<string> &list2search, int number){

    vector<string> bestP ;
    myVector p;
    string b ;

    if (list2search.size() == 1){return bestP;} //it means that lsh returned only the query vector

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



