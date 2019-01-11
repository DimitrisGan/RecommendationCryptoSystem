//
// Created by dimitrisgan on 10/1/2019.
//

#include <algorithm>
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

    //partial sort to take in the first index the minimum pair and thus the Centroid with the minimum distance
    std::partial_sort(distancesFromCentroidsAndTheirClusterIds.begin(), distancesFromCentroidsAndTheirClusterIds.begin() +1,
                      distancesFromCentroidsAndTheirClusterIds.end() , [](pair<double,unsigned> a, pair<double,unsigned> b){ return a.first < b.first;} );


    unsigned closestClusterId = distancesFromCentroidsAndTheirClusterIds[0].second;


    //todo apo to mindist pairnw to clusterId kai peristrefw gi auto to clustId to clust se set

    vector<string> ClustersDataset= this->allClusters.getDatapointsForGivenClusterId(closestClusterId);


    std::set<string> st( ClustersDataset.begin(), ClustersDataset.end() );

    return st;
}

 kClusters &ClusteringProxSearching::getAllClusters()    {
    return allClusters;
}
