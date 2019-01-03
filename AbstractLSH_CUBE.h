//
// Created by dimitrisgan on 30/11/2018.
//

#ifndef PROJECT2_ABSTRACTLSH_CUBE_H
#define PROJECT2_ABSTRACTLSH_CUBE_H

#include <string>
#include <set>
#include "MyVector.h"
#include <unordered_map>

class Lsh;
class HyperCube;



using namespace std;

class AbstractLshCube {

public:

    virtual ~AbstractLshCube() = default;


    virtual set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) = 0;

};




AbstractLshCube* constructLshDatastructure(const int &DistMetricFlag ,   Lsh *lsh_ptr , unsigned &k_hf ,
                                           unsigned &W , unsigned &d , long long int &M_lsh ,unsigned &L , unordered_map<string, myVector> &in_umap ) ;

AbstractLshCube* constructCubeDatastructure(const int &DistMetricFlag , HyperCube *cube_ptr , unsigned &k_hf ,
                                            unsigned &W , unsigned &d ,unsigned &M_cube , unsigned int &probes, unordered_map<string, myVector> &in_umap );



#endif //PROJECT2_ABSTRACTLSH_CUBE_H
