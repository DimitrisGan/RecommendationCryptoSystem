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
//     ClusteringProxSearching(kClusters allClusters);

     ClusteringProxSearching(const string &configFileName,
                                  unordered_map<string, myVector> &userTweetsSentimScoreWithoutInfsAndZeroVectors_umap,
                                  unsigned dimUserSentScoreVectors, int validationFlag);

    ~ClusteringProxSearching() override;

    set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) override;

};



#endif //RECOMMENDATIONCRYPTOSYSTEM_CLUSTERINGPROXSEARCHING_H
