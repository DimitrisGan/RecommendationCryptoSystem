//
// Created by dimitrisgan on 26/11/2018.
//

#include "EvaluationMetric.h"



//=======================================================================================================

// Driver function to sort the vector elements
// by first element of pairs
bool sortbyfirst(const pair<double,myVector> &a,
                 const pair<double,myVector> &b)
{
    return (a.first < b.first);
}

myVector DistFrom2ndBestCentroid ( myVector Point , vector <myVector> listOtherCendroids , DistanceMetrics* dist ) {
    vector<pair<double,myVector> > listPair_CentroidAndDistFromPoint;

    listPair_CentroidAndDistFromPoint.reserve(listOtherCendroids.size() -1);

    for (auto &centr : listOtherCendroids) {
        assert(!isnan(dist->distance(Point, centr)));
        listPair_CentroidAndDistFromPoint.emplace_back( dist->distance(Point, centr),centr);

    }


    std::partial_sort(listPair_CentroidAndDistFromPoint.begin(), listPair_CentroidAndDistFromPoint.begin() +1,
                      listPair_CentroidAndDistFromPoint.end() , sortbyfirst);


    return listPair_CentroidAndDistFromPoint[0].second;

}


double computeMeansFromVector(vector <double> list){
    if (list.empty()) return 0;

    return accumulate(list.begin(), list.end(), 0.0) / list.size();
}



double AverageDistanceBetweenPointCluster(myVector Point , vector <string> DatapointsOfCluster , unordered_map<string, myVector> &in_umap , DistanceMetrics* dist){
    double averageDist;

    double sumDist=0;

    if (DatapointsOfCluster.empty()){return 0;} // todo gia na mhn exw -NaN

    for( auto &dataPoint : DatapointsOfCluster){
        sumDist += dist->distance(Point , in_umap[dataPoint]);
    }

    averageDist = sumDist / DatapointsOfCluster.size();

    return averageDist;
}


double calculateS(double &a , double &b){

    assert(!isnan(a));
    assert(!isnan(b));
    if (a == 0 && b==0){
        return 0;
    }
//    assert(a >= 0 && b >=0 );

    return (b-a)/std::max(a,b);
}




vector<double> Silhouette (unordered_map<string, myVector> &in_umap , kClusters &allClusters , DistanceMetrics* dist ,int &clustersWithoutDataset ) {
    clustersWithoutDataset=0;

    vector<double> listAllClustersSilhouette;

    vector<myVector> listCendroids = allClusters.listOfCentroids();
    vector<double> listSilhouetteOfAllClusters;
    for (auto &clust  : allClusters.getClusters()) {
        if (clust->getDatapoints().size() == 1 || clust->getDatapoints().empty() ){ //means that there is only the centroid in this clusters Dataset
//            for (auto& listC : listCendroids){
//                if (listC.getCoords() ==)
//            }
            clustersWithoutDataset++;

            continue;
        }

//        distFromCentroids.reserve(allClusters.getClusters().size() );

        vector<double> listClustEvaluation;
        listClustEvaluation.clear();


        for (auto &point : clust->getDatapoints()) {
//            if (in_umap[point].getCoords() == clust->getCentroid().getCoords()) {continue;}
            myVector toErase = clust->getCentroid();

            //I make new vector for deletion of the Centroid that was assigned
            vector<myVector> listCentroidsWithoutItsOwn;//(allClusters.getClusters().size())  ;
//            copy(listCendroids.begin(), listCendroids.end(),
//                 back_inserter(listCentroidsWithoutItsOwn));//listCentroidsWithoutItsOwn = listCendroids;
            listCentroidsWithoutItsOwn.assign(listCendroids.begin(), listCendroids.end());
            //I find & delete the centroid that was assigned to this point
            for (int i = 0; i < listCentroidsWithoutItsOwn.size(); ++i) {
                if (listCentroidsWithoutItsOwn[i].getCoords() == toErase.getCoords()) {
                    listCentroidsWithoutItsOwn.erase(listCentroidsWithoutItsOwn.begin() + i);
                    break;
                }
            }
//            assert(listCentroidsWithoutItsOwn.size() == listCendroids.size() - 1);


            myVector Best2ndCentroid = DistFrom2ndBestCentroid(in_umap[point], listCentroidsWithoutItsOwn, dist); /*in the first position of the list is the 2nd closest Centroid
                                                                                            *and as a result 2nd closest Cluster */

            double a;
            double b;
            vector<string> DatapointsOf2ndBest;
            for (auto &clust2 : allClusters.getClusters()) {
                if (clust2->getCentroid().getCoords() == Best2ndCentroid.getCoords()) {

                    DatapointsOf2ndBest = clust2->getDatapoints();
                    break;
                }
            }


            a = AverageDistanceBetweenPointCluster(in_umap[point], clust->getDatapoints(), in_umap, dist);
            b = AverageDistanceBetweenPointCluster(in_umap[point], DatapointsOf2ndBest, in_umap, dist);

            double S_point = calculateS(a, b);
            assert(!isnan(S_point));


            listClustEvaluation.push_back(S_point);

        }
        //teleiwsa me th Silhouete tou dataset sto cluster

        double meansClusterSil = computeMeansFromVector(listClustEvaluation) ;


        assert(!isnan(meansClusterSil));

        listSilhouetteOfAllClusters.push_back(meansClusterSil);
    }


    double meanSilhOfAllClusters = computeMeansFromVector( listSilhouetteOfAllClusters);
    assert(!isnan(meanSilhOfAllClusters));

    cout << "Mean Silhouette of all clusters = " << meanSilhOfAllClusters <<endl;


    return listSilhouetteOfAllClusters;
}









