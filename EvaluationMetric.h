//
// Created by dimitrisgan on 26/11/2018.
//

#ifndef PROJECT2_EVALUATIONMETRIC_H
#define PROJECT2_EVALUATIONMETRIC_H

#include <algorithm>

#include "SearchingAlgorithms.h"
#include "Cluster.h"





vector<double> Silhouette (unordered_map<string, myVector> &in_umap , kClusters &allClusters , DistanceMetrics* dist ,int &clustersWithoutDataset);

#endif //PROJECT2_EVALUATIONMETRIC_H
