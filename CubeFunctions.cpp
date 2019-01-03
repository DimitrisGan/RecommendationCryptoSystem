//
// Created by dimitrisgan on 23/10/2018.
//

#include <bitset>
#include "CubeFunctions.h"




vector <unsigned int > getAllNeigborsIndexes( unsigned int index , unsigned int k ){

    std::string str = std::bitset< 64 >( index ).to_string(); // string conversion from number/index
    unsigned long long  num=0;

    unsigned int i;
    for (i = 0; i < str.size(); ++i) {
        if (str[i] != '0'){
            break;
        }
    }
    str.erase(0,i);

    assert(str.size() <= k);

    if (str.size() < k){
        num = k - str.size() ;
    }

    for (unsigned int j = 0; j < num ; ++j) {
        str.insert(0,"0");
    }

    vector <string> bitstring_neighbors_list;
    bitstring_neighbors_list = HammingDist1(str);

    vector <unsigned int> neigbors_indexes_list;
    unsigned  int indexN;
    for (auto &neigbor_bitstr  : bitstring_neighbors_list ) {
        indexN = static_cast<unsigned int>(bitset<128>(neigbor_bitstr).to_ulong());
        neigbors_indexes_list.push_back(indexN);
    }

    return neigbors_indexes_list;

}

//=========================================================

vector <string> HammingDist1(const string &str ){

    string s= str;

    vector <string> temp;

    for (unsigned int i = 0; i < str.size(); ++i) {
        if (s[i] == '0'){
            s[i]='1';
        }
        else{
            s[i] = '0';
        }
        temp.push_back(s);
        s=str;

    }

    return temp;
}

//=========================================================

string f(long long int h_p , unordered_map< long long int, string > &f_umap_2_curr_h){ //tha pairnei enan arithmo kai to katallhlo unordered map

    if ( f_umap_2_curr_h.find(h_p) == f_umap_2_curr_h.end() ) {
        // not found
        int num = rand() % 2;
        assert(num==0 || num ==1);

        f_umap_2_curr_h.insert(std::make_pair(h_p,std::to_string(num)));

        return f_umap_2_curr_h[h_p];
    } else {
        // found
        return f_umap_2_curr_h[h_p];
    }
}

//=========================================================

void print_map(std::unordered_map < long long int, string >  input_map) {
    for (auto &mypair : input_map)
    {

        cout << "[MAP KEY] :" <<mypair.first << "\n"; //<< mypair.second <<endl;
        cout << "[MAP Value] :" <<mypair.second << "\n"; //<< mypair.second <<endl;


        std::cout << "\n";
    }
}


//=========================================================
std::vector< long long int> extract_keysF(std::unordered_map < long long int, string >  input_map) {
    std::vector<long long int> retval;
    retval.reserve(input_map.size());
    for (auto const& element : input_map) {
        cout << element.first << endl;
        retval.push_back(element.first);
    }
    return retval;
}

//=========================================================
