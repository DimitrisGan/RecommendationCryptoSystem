//
// Created by dimitrisgan on 16/11/2018.
//

#include "Initialization.h"


void RandomInit::operator()(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors) {
    Random_selection_of_k_points (k ,  in_umap , k_initial_vectors );
}

void kMeanspp::operator()(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors) {

    k_meanspp(k ,  in_umap , this->dist , k_initial_vectors );

}

int randomIntNumberGen (int FromNum , int ToNum  ){
    int NumChosen;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(FromNum, ToNum);

    NumChosen = dis(gen);

    return NumChosen;
}

double randomDoubleNumberGen (int FromNum , int ToNum  ){
    double NumChosen;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(FromNum, ToNum);

    NumChosen = dis(gen);

    return NumChosen;
}


void Random_selection_of_k_points (const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors ) { //todo na ginei functor

    int item_id ;
    string str_item_id ;
    k_initial_vectors.resize(k);
    vector <int> centroids_ids;

    for ( auto &init_vector : k_initial_vectors) {
        while(true) {
            bool alreadyExistFlag = 0;
            bool isUnique=0;

            item_id = randomIntNumberGen(1, static_cast<int>(in_umap.size()));

            str_item_id = std::to_string(item_id);

            for (auto &Centr :  centroids_ids ){
                string Centr_str = to_string(Centr);
                if (in_umap[Centr_str].getCoords() == in_umap[str_item_id].getCoords() ){

                    isUnique = 1;
                }
            }
            if (isUnique == 0){
                break;
            }
        }

        init_vector = in_umap[str_item_id];
        centroids_ids.push_back(item_id);
//        init_vector.print_vector();

    }

    printInitialCentroids(centroids_ids);

}


// Driver function to sort the vector elements
// by second element of pairs
bool sortbysec(const pair<string,double> &a,
               const pair<string,double> &b)
{
    return (a.second < b.second);
}


/*
 *(1) Choose a centroid uniformly at random; t ← 1.
 *
 *(2) ∀ non-centroid point i = 1, . . . , n − t, let D (i ) ← min distance to some
 *centroid, among t chosen centroids.
 *
 *(3) Choose new centroid: r chosen with probability proportional to D (r )^2 / athroisma D (r )^2  :
 *
*/

void k_meanspp(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , DistanceMetrics* dist , vector <myVector> &k_initial_vectors ){

    vector <string > centroids_ids ;

    int firstRandomK = randomIntNumberGen (1 , static_cast<int>(in_umap.size()));
    string firstRandomK_str = to_string(firstRandomK);

    centroids_ids.push_back(firstRandomK_str);
    cout << endl;

    int i=0;

    while (i < k-1){ // gia k centroids pou thelw

        i++;

        vector <pair<string,double > > listAllMinDists;
        double squareSumOfAllMinDistsFromCentroids=0;
        for ( auto& vect : in_umap   ) { //gia kathe vector mesa sto map (ektos twn hdh centroids)

            if ( std::find(centroids_ids.begin(), centroids_ids.end(), vect.first) != centroids_ids.end() ) continue;  // it means the item_id is a centroid --> continue

            vector <double> listDistFromCentroids = listWithDistsFromCentroids(centroids_ids ,  vect ,  in_umap , dist   );
            assert(!listDistFromCentroids.empty());


            auto minDist = *min_element(listDistFromCentroids.begin(), listDistFromCentroids.end());

            squareSumOfAllMinDistsFromCentroids += pow(minDist , 2);

            listAllMinDists.emplace_back(vect.first,minDist);

        }

        vector <pair <string , double>> listProb;
        listProb.reserve(listAllMinDists.size());

        for ( auto &minDistPair : listAllMinDists ) {
            listProb.emplace_back(minDistPair.first , pow(minDistPair.second , 2) / squareSumOfAllMinDistsFromCentroids);
        }


        sort(listProb.begin(), listProb.end(), sortbysec);
        //============================================

        double val = randomDoubleNumberGen(0 , 1);
        double sumToReachVal=0;

        for ( auto probPair : listProb ) {
            sumToReachVal += probPair.second;

            if ( val < sumToReachVal ) {
                string vec_id = (string) probPair.first;
                centroids_ids.push_back(vec_id);
                break;
            }
        }

    } //telos while


    for (  auto &centroidId : centroids_ids ) {
        k_initial_vectors.push_back(in_umap[centroidId]);
    }

    printInitialCentroids(centroids_ids);

}


/////// logic : https://stackoverflow.com/questions/8529665/changing-probability-of-getting-a-random-number
double sumOfSquaresFromList (vector <double> &listDistFromCentroids ){
    double sumSquareDists=0;
    for ( auto &dist  : listDistFromCentroids ) {
        sumSquareDists += pow(dist , 2);
    }
    return sumSquareDists;
}


vector <double> listWithDistsFromCentroids(const vector <string > &centroids_ids ,  pair <  const string, myVector> &vect ,  unordered_map<string, myVector> &in_umap , DistanceMetrics* dist   ){
    vector <double> temp_listDist ;
    double distValue;
    for ( auto &centroid_id : centroids_ids ) {
        assert(centroid_id != vect.first);
        distValue = dist->distance(in_umap[centroid_id] , vect.second );
        temp_listDist.push_back(distValue);
    }

    return  temp_listDist;
};


void printInitialCentroids(vector<int> centroids_ids ){
    cout << "\nINITIAL CENTROIDS \n [";
    int i=0;
    for (auto &centroidId  : centroids_ids  ) {
        cout << centroidId;
        if (centroids_ids.size()-1 != i)
            cout<<",";
        i++;

    }
    cout<<"]"<<endl;


}

void printInitialCentroids(vector<string> centroids_ids ){
    cout << "INITIAL CENTROIDS !! [";
    int i=0;
    for (auto &centroidId  : centroids_ids  ) {
        cout << centroidId;
        if (centroids_ids.size()-1 != i)
            cout<<",";
        i++;

    }
    cout<<"]"<<endl;


}