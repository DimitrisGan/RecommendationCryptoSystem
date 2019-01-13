//
// Created by dimitrisgan on 10/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_ABSTRACTLSH_CLUSTER_H
#define RECOMMENDATIONCRYPTOSYSTEM_ABSTRACTLSH_CLUSTER_H


#include <set>
#include <string>
#include <unordered_map>
#include "MyVector.h"


using namespace std;

class AbstractLshCluster {

public:



    virtual ~AbstractLshCluster() = default;

    virtual set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) = 0;
};





#endif //RECOMMENDATIONCRYPTOSYSTEM_ABSTRACTLSH_CLUSTER_H
