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
    //todo pairnw ta Centroids kai gia kathe Centroid kanw dist() me u ta sortarw kai pairnw auto me th mikroterh apostash === mono min timh thelw

//    allClusters.

    vector <pair<myVector,unsigned >>  CentroidsAndClusterIds =this->allClusters.getCentroidsAndTheirClusterIds();

    vector <pair<double,unsigned>> distancesFromCentroidsAndTheirClusterIds;

    for (auto &myPair : CentroidsAndClusterIds){
        //tha petaksw
        double dist = this->euclidean->distance(query ,myPair.first );
        distancesFromCentroidsAndTheirClusterIds.emplace_back(dist,myPair.second);
    }

//    std::get<1>(*std::min_element(begin(distancesFromCentroidsAndTheirClusterIds), end(distancesFromCentroidsAndTheirClusterIds),
//            [](auto lhs, auto rhs){return std::get<1>(lhs)<std::get<1>(rhs);}));

    double minDist ;
    unsigned clustId;

    //todo apo to mindist pairnw to clusterId kai peristrefw gi auto to clustId to clust se set

    return set<string>();
}

 kClusters &ClusteringProxSearching::getAllClusters()    {
    return allClusters;
}
