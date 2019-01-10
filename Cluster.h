//
// Created by dimitrisgan on 16/11/2018.
//

#ifndef PROJECT2_CLUSTER_H
#define PROJECT2_CLUSTER_H

#include <string>
#include <vector>
#include <iostream>
#include "MyVector.h"

using namespace std;


class Cluster {
private:
    unsigned int id;
    myVector  Centroid;
    double total_distance{std::numeric_limits<double>::infinity()};
    vector <string> datapoints;

public:

    explicit Cluster(myVector& Centroid , unsigned id);

    myVector &getCentroid() ;
    myVector getCentroidByValue();

    unsigned int getId() const;

    vector<string> &getDatapoints() ;

    double getTotal_distance() const;

    void setTotal_distance(double total_distance);

    void setCentroid(vector<double> Centroid);

    void addPointId2cluster(string pointId);

    void printClust();

};

class kClusters{
private:
    vector <Cluster *> clusters;
public:
    kClusters(unsigned int k , vector <myVector> listCentroids );

    vector<Cluster *> &getClusters() ;

    void addPoint2clusterId(unsigned int clustId , string point);

    myVector  getCentroidForClusterId(unsigned &clustId) ;

    virtual ~kClusters();

    vector <myVector> listOfCentroids();

    void print_allClusters();
    void print_ClustersDatasetSize();


    void initializeClusters(unsigned int k , vector <myVector> listCentroids );
    kClusters()= default;


    /*new function*/

    vector <pair<myVector,unsigned >>  getCentroidsAndTheirClusterIds();



};






#endif //PROJECT2_CLUSTER_H


