//
// Created by dimitrisgan on 10/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_ABSTRACTLSH_CLUSTER_H
#define RECOMMENDATIONCRYPTOSYSTEM_ABSTRACTLSH_CLUSTER_H


#include <set>
#include <string>
#include <unordered_map>
#include "MyVector.h"
#include "LSH.h"
#include "Cluster.h"

using namespace std;

class AbstractLshCluster {

public:

    virtual ~AbstractLshCluster() = default;


    virtual set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) = 0;

};


//    Lsh *lsh_virtualUsers_ptr = new Lsh ( TableSize, k_hf , dimUserSentScoreVectors , L  , virtualUserTweetsSentimScoreWithoutInfsAndZeroVectors_umap); //lsh-cosine for normalized c's



#endif //RECOMMENDATIONCRYPTOSYSTEM_ABSTRACTLSH_CLUSTER_H
