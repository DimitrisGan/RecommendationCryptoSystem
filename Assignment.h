//
// Created by dimitrisgan on 16/11/2018.
//

#ifndef PROJECT2_ASSIGN_H
#define PROJECT2_ASSIGN_H

#include <unordered_map>
#include <algorithm>
#include "Cluster.h"
#include "Metrics.h"
#include "AbstractLSH_CUBE.h"
#include "AssistantFunctions.h"





class Assigner{
public:
    virtual void operator()(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist) = 0;
    virtual ~Assigner() = default;
};



class ReverseAssignment : public Assigner{
private:
    AbstractLshCube * myStructure_ptr;

public:
    explicit ReverseAssignment(AbstractLshCube *myStructure_ptr);

    ~ReverseAssignment() override ;

    void RevAssign(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist);

    void operator()(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist) override ;

};


class LloydAssignment : public Assigner{

public:

    LloydAssignment() = default;

    ~LloydAssignment() override = default;

    void LloydAssign(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist );

    void operator()(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist) override ;

};



#endif //PROJECT2_ASSIGN_H
