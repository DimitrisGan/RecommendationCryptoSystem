//
// Created by dimitrisgan on 16/11/2018.
//

#include "Assignment.h"



void ReverseAssignment::operator()(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist) {

    RevAssign(allClusters, in_umap, dist );
}


ReverseAssignment::ReverseAssignment(AbstractLshCube *myStructure_ptr) : myStructure_ptr(myStructure_ptr) {}
//======================================================================

void LloydAssignment::operator()(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist) {
    LloydAssign(allClusters ,in_umap ,dist);
}

//======================================================================



// Function to check if the key is present or not
bool checkIfkeyExists(const string &key , const unordered_map <string , std::pair<unsigned , double >> &myMap ){

    return !(myMap.find(key) == myMap.end());

}



void ReverseAssignment::RevAssign(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist){


    unordered_map <string , std::pair<unsigned int , double >> myTripletMap; // <item_id ,cluster_id ,distance>

    for ( auto &clust : allClusters.getClusters() ) {
        set<string> SetReturned = this->myStructure_ptr->getSuperSet(clust->getCentroid() ,in_umap); //gia to sugkekrimeno centroid gurna to set pou eixe collision


        for ( auto& vecId : SetReturned) { //gia kathe vectorId pou epistrafike apo to set
            bool flagExists = checkIfkeyExists(vecId,myTripletMap);
//            cout << "flagExists = " << flagExists;

            if (flagExists){ //ean uparxei hdh to vecId sto tripletMap
                auto& vecIdPair = myTripletMap[vecId];

                if ( vecIdPair.second < 0){ //edw exei ginei anathesh alla den exei upologistei dist
                    myVector existingCentroidInTripletMap = allClusters.getCentroidForClusterId(vecIdPair.first);

                    double dist1 = dist->distance(existingCentroidInTripletMap , in_umap[vecId]);
                    double dist2 = dist->distance(clust->getCentroid() , in_umap[vecId]);


                    if (dist2 < dist1){ //ean to current centroid einia mikrotero apo to uparxwn centroid sto TripletMap vale to uparxwn sth thesi tou

                        vecIdPair.first = clust->getId();
                        vecIdPair.second = dist2;

                    } //dist2 >=dist1
                    else{ //alliws vale thn apostash tou yparxwn centroid sto TripletMap pou molis upologisame

                        assert(vecIdPair.second == -1);
                        vecIdPair.second = dist1;

                    }
                }
                else { //edw exei ginei anathesi kai exei upologistei to distance sto uparxwn table

                    double dist2 = dist->distance(clust->getCentroid() , in_umap[vecId]);
                    if (dist2 < vecIdPair.second){ //edw to distance tou current Centroid einai mikrotero tou uparxwn ara tha prepei na to allaksw
                        vecIdPair.first = clust->getId();
                        vecIdPair.second = dist2;
                    }
                    else{ //edw to distance tou current Centroid einai megalutero h iso tou uparxwn ara de kanw tpt
                        //pass
                    }

                }

            }
            else { //edw den yparxei to dianusma opote to kanw insert

                myTripletMap.insert({vecId,std::make_pair(clust->getId(),-1)});
            }

        }
        //print_map(myTripletMap);


    }

    //here I have all my vectorIds with their appropriate clusters
    //put them in the clusters

    for (  auto &triplet : myTripletMap ) {
        allClusters.addPoint2clusterId(triplet.second.first , triplet.first);
    }




}

ReverseAssignment::~ReverseAssignment() {
    free (this->myStructure_ptr);
}




//======================================================================
//======================================================================

void LloydAssignment::LloydAssign(kClusters &allClusters , unordered_map<string , myVector> &in_umap , DistanceMetrics *dist ){
    cout.precision(20);



    for ( auto &vect  : in_umap ) {

        vector <pair<double , unsigned int >> listDistFromCentroids ;

        int CentroidIndex =0;

        for (  auto &centroid : allClusters.getClusters() ) {


            double dist2Centroid = dist->distance(vect.second , centroid->getCentroid());

            listDistFromCentroids.emplace_back(dist2Centroid , CentroidIndex);

            CentroidIndex++;
        }

        //By default the sort function sorts the vector elements on basis of first element of pairs.
        // Using simple sort() function to sort
        sort(listDistFromCentroids.begin(), listDistFromCentroids.end()); //edw sortarei to vector of pairs os pros to distance se ascending order

        pair <double,unsigned int> Centroid2addCurrPoint = listDistFromCentroids.at(0);


        unsigned int indexCentroid2add = Centroid2addCurrPoint.second;

        allClusters.getClusters().at(indexCentroid2add)->addPointId2cluster(vect.first); //here we push the datapoint to the cluster that belongs

    }

}




