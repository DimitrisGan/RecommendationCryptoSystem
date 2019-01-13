//
// Created by dimitrisgan on 29/11/2018.
//

#ifndef LSH_LSH_H
#define LSH_LSH_H



#include "HashTablesStructures.h"
#include "EuclideanSpaceLSH.h"
#include "CosineSimilarityLSH.h"



#include <string>
#include <set>
#include <unordered_map>
#include "MyVector.h"
#include "AbstractLSH_CLUSTER.h"
#include "AbstractLSH_CUBE.h"




class multi_hash_table;

using namespace std;

class Lsh  : public AbstractLshCluster,public AbstractLshCube
{
private:

    multi_hash_table *MHT_ptr;

public:
    ~Lsh() override;

    set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) override;

    //LSH FOR EUCLIDEAN
    Lsh(unsigned int TableSize, unsigned int k, unsigned int W, unsigned int d, long long int M, unsigned int &L ,unordered_map<string, myVector >& in_umap );
    //LSH FOR COSINE
    Lsh (unsigned  int TableSize, unsigned int& k ,unsigned int& d , unsigned int& L  , unordered_map<string, myVector >& in_umap  );


};


#endif //LSH_LSH_H
