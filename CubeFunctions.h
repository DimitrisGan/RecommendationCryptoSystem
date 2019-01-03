//
// Created by dimitrisgan on 23/10/2018.
//

#ifndef PROJECT_EM_CUBEFUNCTIONS_H
#define PROJECT_EM_CUBEFUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <typeinfo>
#include <random>
#include <assert.h>     /* assert */
#include "MyVector.h"

#include <fstream>


using namespace std;

vector <unsigned int > getAllNeigborsIndexes( unsigned int index , unsigned int k );

vector <string> HammingDist1(const string &str );


std::vector< long long int> extract_keysF(std::unordered_map < long long int, string >  input_map);

void print_map(std::unordered_map < long long int, string >  input_map);


string f(long long int h_p , unordered_map< long long int, string > &f_umap_2_curr_h);



#endif //PROJECT_EM_CUBEFUNCTIONS_H
