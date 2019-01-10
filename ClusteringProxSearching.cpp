//
// Created by dimitrisgan on 10/1/2019.
//

#include "ClusteringProxSearching.h"



ClusteringProxSearching::ClusteringProxSearching(const kClusters &allClusters) : allClusters(allClusters) {

   euclidean = new EuclideanMetric();

}

ClusteringProxSearching::~ClusteringProxSearching() {
    delete euclidean; euclidean=nullptr;
}


set<string> ClusteringProxSearching::getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) {
    //todo
    //todo pairnw ta Centroids kai gia kathe Centroid kanw dist() me u ta sortarw kai pairnw auto me th mikroterh apostash

//    allClusters.


    return set<string>();
}