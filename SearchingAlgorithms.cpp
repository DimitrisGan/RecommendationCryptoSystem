////
//// Created by dimitrisgan on 23/10/2018.
////
//
//#include "SearchingAlgorithms.h"
//
//
//string NN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , vector <string>& list2search  ){
//
//    string b ;
//    myVector p;
//    double smallest_dist = numeric_limits<double>::infinity();
//    double curr_dist;
//
//    for (auto &p_id : list2search) {
//        p = in_umap[p_id];
//        curr_dist = metric->distance(q, p);
//
//        if (curr_dist < smallest_dist){
//            b = p_id;
//            smallest_dist = curr_dist;
//        }
//    }
//    return b;
//
//
//}
//
////=================================================================================================
//
//
//vector <string > RangeN_search(myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , vector <string>& list2search  , int& R){
//
//    vector <string> nn_list;
//    myVector p;
//    double curr_dist;
//
//
//    for (auto &p_id : list2search) {
//        p = in_umap[p_id];
//        curr_dist = metric->distance(q, p);
//        if (curr_dist < C * R){
//
//            nn_list.push_back(p_id);
//        }
//
//    }
//
//
//
//    return nn_list;
//}
//
////=================================================================================================
//
//
//string TrueNN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap  ){ //Brute Force
//    string TrueNN;
//    myVector p;
//    double curr_dist;
//    double smallest_dist = numeric_limits<double>::infinity();
//
//    std::vector<std::string> keys_p;
//    keys_p = extract_keys(in_umap);
//
//    for (auto &p_id : keys_p) {
//        p = in_umap[p_id];
//        curr_dist = metric->distance(q, p);
//
//        if (curr_dist < smallest_dist){
//            TrueNN = p_id;
//            smallest_dist = curr_dist;
//        }
//
//    }
//
//
//    return TrueNN;
//}
//
//
//
