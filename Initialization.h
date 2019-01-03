//
// Created by dimitrisgan on 16/11/2018.
//

#ifndef PROJECT2_INITIALIZER_H
#define PROJECT2_INITIALIZER_H

#include <iostream>
#include <unordered_map>
#include <random>
#include <string>
#include <algorithm>

#include <set>
#include<bits/stdc++.h>


#include "MyVector.h"
#include "Metrics.h"

using  namespace std;


void printInitialCentroids(vector<int> centroids_ids );
void printInitialCentroids(vector<string> centroids_ids );

int randomIntNumberGen (int FromNum , int ToNum  );

double randomDoubleNumberGen (int FromNum , int ToNum  );

void Random_selection_of_k_points (const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors ); //todo na ginei functor

void k_meanspp(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , DistanceMetrics* dist , vector <myVector> &k_initial_vectors ); //todo

bool sortbysec(const pair<string,double> &a,
               const pair<string,double> &b);

//vector <double> listWithDistsFromCentroids(const set <string > &centroids_ids ,  pair <string, myVector> &vect ,  unordered_map<string, myVector> &in_umap , DistanceMetrics* dist   );
vector <double> listWithDistsFromCentroids(const vector <string > &centroids_ids ,  pair <  const string, myVector> &vect ,  unordered_map<string, myVector> &in_umap , DistanceMetrics* dist   );

double sumOfSquaresFromList (vector <double> &listDistFromCentroids );




class Initlializer{
public:
    virtual void operator()(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors) = 0;
    virtual ~Initlializer() = default;
};

class RandomInit: public Initlializer{
public:
    RandomInit() = default;

    ~RandomInit() override = default;

    void operator()(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors) override ;
};

class kMeanspp: public Initlializer{
private:
    DistanceMetrics  *dist;
public:
    explicit kMeanspp(DistanceMetrics *dist) : dist(dist) {};

    void operator()(const unsigned int &k ,  unordered_map<string, myVector> &in_umap , vector <myVector> &k_initial_vectors) override ;
};



#endif //PROJECT2_INITIALIZER_H

