//
// Created by dimitrisgan on 10/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_CLUSTERINGPROXSEARCHING_H
#define RECOMMENDATIONCRYPTOSYSTEM_CLUSTERINGPROXSEARCHING_H


#include <unordered_map>
#include "Metrics.h"
#include "Cluster.h"
#include "AbstractLSH_CLUSTER.h"

class ClusteringProxSearching : public AbstractLshCluster {
private:
    DistanceMetrics *euclidean;
    kClusters allClusters;

public:
    explicit ClusteringProxSearching(const kClusters &allClusters);

    ~ClusteringProxSearching() override;

    set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) override;

     kClusters &getAllClusters() ;
};





#endif //RECOMMENDATIONCRYPTOSYSTEM_CLUSTERINGPROXSEARCHING_H
