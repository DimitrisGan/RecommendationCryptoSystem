//
// Created by dimitrisgan on 16/11/2018.
//

#include "Update.h"



void pam(unordered_map<string, myVector> &in_umap, kClusters &allClusters, DistanceMetrics *dist){

    for (auto &cluster  : allClusters.getClusters() ) {
        if (cluster->getDatapoints().empty()){
            continue;
        }
        double minDist = cluster->getTotal_distance();
        myVector bMedoid (cluster->getCentroid() );
        for (auto &Point1 : cluster->getDatapoints() ){

            if (in_umap[Point1].getCoords() == bMedoid.getCoords()){continue;}

            double sumDist=0;

            for (auto &Point2 : cluster->getDatapoints()  ){

                sumDist += dist->distance( in_umap[Point1] , in_umap[Point2] );
            }


            if (sumDist < minDist){
                minDist = sumDist;
                bMedoid = in_umap[Point1];
            }
        }

        cluster->setCentroid(bMedoid.getCoordsByValue());

        cluster->setTotal_distance(minDist);

        cluster->getDatapoints().clear();

    }

}



void k_means(unordered_map<string, myVector> &in_umap ,kClusters &allClusters ,unsigned int dim  ){

    for (auto &cluster  : allClusters.getClusters() ) {
        if (cluster->getDatapoints() .empty()){
            continue; //periptwsh apo lsh/cube kuriws pou to cluster tou einai adeio alla de thelw na allaksei to centroid tou
        }
        vector <double> sumV_Coords (dim , 0);
        myVector meanV (sumV_Coords);

        unsigned long numOfElementsInClusterDataset = cluster->getDatapoints().size();

        for (auto &dataPoint : cluster->getDatapoints() ){

            meanV =   in_umap[dataPoint] + meanV ;       //dianusma
        }

        meanV.divideVectorWithNumber(numOfElementsInClusterDataset); //de me noiazei na ypologistei sto 2o update kai to Centroid gt einia ousiastika o mo opote den exei kamia diafora sto teliko apotelesma

        cluster->setCentroid(meanV.getCoordsByValue()); // meanV is set as the new Centroid

        cluster->getDatapoints().clear();
        //todo na upologisw objective function

    }

}





void PAM::operator()(unordered_map<string, myVector> &in_umap, kClusters &allClusters) {
    pam(in_umap, allClusters, this->dist);

}

void kMeans::operator()(unordered_map<string, myVector> &in_umap, kClusters &allClusters) {
    k_means(in_umap ,allClusters , this->dim ); //todo 24/12

}
