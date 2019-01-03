//
// Created by dimitrisgan on 16/11/2018.
//

#ifndef PROJECT2_UPDATE_H
#define PROJECT2_UPDATE_H


#include <unordered_map>
#include "MyVector.h"
#include "Cluster.h"
#include "Metrics.h"
#include "Initialization.h"


class Updater{
public:
    virtual void operator()(unordered_map<string, myVector> &in_umap ,kClusters &allClusters) = 0;
    virtual ~Updater() = default;
};

class kMeans: public Updater{
private:
    unsigned int dim;
public:
    explicit kMeans(unsigned int dim) : dim(dim) {};

    ~kMeans() override = default;

    void operator()(unordered_map<string, myVector> &in_umap ,kClusters &allClusters) override ;
};

class PAM: public Updater{
private:
    DistanceMetrics  *dist;
public:
    explicit PAM(DistanceMetrics *dist) : dist(dist) {};

    void operator()(unordered_map<string, myVector> &in_umap ,kClusters &allClusters) override ;
};



void k_means(unordered_map<string, myVector> &in_umap ,kClusters &allClusters , unsigned int dim );

void pam(unordered_map<string, myVector> &in_umap, kClusters &allClusters, DistanceMetrics *dist);

#endif //PROJECT2_UPDATE_H
