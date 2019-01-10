#include <utility>

//
// Created by dimitrisgan on 16/11/2018.
//

#include "Cluster.h"

Cluster::Cluster(myVector& Centroid , unsigned id){
    this->Centroid = Centroid;
    this->id =id;
}

void Cluster::setCentroid(vector<double> Centroid) {
    this->Centroid = std::move(Centroid);
}

myVector &Cluster::getCentroid()  {
    return Centroid;
}
myVector Cluster::getCentroidByValue()  {
    return Centroid;
}


kClusters::kClusters(unsigned int k , vector <myVector> listCentroids ){
    std::vector<Cluster> listClusters;
    listClusters.reserve(k);
    unsigned id=0;
    for ( auto& centroid :  listCentroids) {
        this->clusters.push_back(new Cluster(centroid ,id));
        id++;
    }

}

void kClusters::initializeClusters(unsigned int k , vector <myVector> listCentroids ){
    std::vector<Cluster> listClusters;
    listClusters.reserve(k);
    unsigned id=0;
    for ( auto& centroid :  listCentroids) {
        this->clusters.push_back(new Cluster(centroid ,id));
        id++;
    }

}

vector<Cluster *> &kClusters::getClusters()  {
    return clusters;
}

myVector  kClusters::getCentroidForClusterId(unsigned &clustId) {
    for (auto &clust  : this->clusters ) {
        if (clust->getId() == clustId){
            return clust->getCentroid();
        }
    }
    cout <<"NEVER NEVER SHOULD COME HERE\n";
    assert(1);
}


void Cluster::addPointId2cluster(string pointId){

    this->datapoints.push_back(pointId);
}

void kClusters::addPoint2clusterId(unsigned int clustId , string point){
    for (auto &clust  : this->clusters  ) {
        if (clust->getId() == clustId){
            clust->addPointId2cluster(point);
            break;
        }
    }
    assert(1);
}



void kClusters::print_allClusters(){
    int i=0;
    int sumDataset = 0;
    for (  auto &clust  : this->clusters ) {
        cout << "~~~~ PRINTING CLUSTER #"<<i++ <<" ~~~~"<<endl;

//        cout << "[CLUSTER CENTROID] = \t";
//        clust->getCentroid().print_vector();

        clust->printClust();
        cout << "Dataset size = " << clust->getDatapoints().size() <<endl;
        sumDataset +=clust->getDatapoints().size();
//
        cout << "Objective Fun = "<<clust->getTotal_distance() <<endl;
    }
//
    cout << "---------------------\n";

    cout << "sumDataset = " << sumDataset <<endl;
}


void kClusters::print_ClustersDatasetSize(){
    int sumDataset = 0;
    for (  auto &clust  : this->clusters ) {

        sumDataset +=clust->getDatapoints().size();
    }

    cout << "sumDataset = " << sumDataset <<endl;
}


vector <myVector> kClusters::listOfCentroids(){

    vector <myVector> list;
    for (  auto C : this->clusters ) {
        list.push_back(C->getCentroidByValue());
//        if (C->getDatapoints().empty() || C->getDatapoints().size() ==1){
//            continue;
//        }
    }

    return list;
}

kClusters::~kClusters() {
    for (auto &clust  : this->clusters) {
        delete clust;
    }
    clusters.clear();
}


vector<pair<myVector, unsigned >> kClusters::getCentroidsAndTheirClusterIds() {

    vector<pair<myVector, unsigned >> returnedVector;

    for (auto clust : this->getClusters()){
        returnedVector.emplace_back(clust->getCentroid(),clust->getId());
    }

    return returnedVector;
}


void Cluster::printClust(){

    cout<<"[";
    int i=0;
    for ( auto &pointId  : this->datapoints ) {
        cout << pointId ;

        if (datapoints.size()-1 != i)
            cout<<",";

        i++;

    }
    cout<<"]"<<endl;


}

vector<string> &Cluster::getDatapoints()  {
    return datapoints;
}



double Cluster::getTotal_distance() const {
    return total_distance;
}

void Cluster::setTotal_distance(double total_distance) {
    Cluster::total_distance = total_distance;
}

unsigned int Cluster::getId() const {
    return id;
}






















