//
// Created by dimitrisgan on 23/10/2018.
//

#ifndef PROJECT_EM_SEARCHINGALGORITHMS_H
#define PROJECT_EM_SEARCHINGALGORITHMS_H

#define C 1
#include "MyVector.h"
#include "Metrics.h"

#include <limits>
#include <unordered_map>


using namespace std;

vector<string> NN_searchForBestP(myVector &q, const string &qId, DistanceMetrics *metric, unordered_map<string, myVector> &in_umap,
                                 vector<string> &list2search, int number);

vector<string> NN_searchForBestP(myVector &q, const string &qId, DistanceMetrics *metric, unordered_map<string, myVector> &in_umap,
                                 set<string> &list2search, int number);

string NN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , vector <string>& list2search  );
string NN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , set <string>& list2search  );

vector <string > RangeN_search(myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , vector <string>& list2search , int& R);
vector <string > RangeN_search(myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap , set <string>& list2search , int& R);

string TrueNN_search( myVector& q , DistanceMetrics *metric , unordered_map <string, myVector >& in_umap  ); //Brute Force


#endif //PROJECT_EM_SEARCHINGALGORITHMS_H
