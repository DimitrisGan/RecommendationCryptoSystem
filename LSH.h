//
// Created by dimitrisgan on 29/11/2018.
//

#ifndef LSH_LSH_H
#define LSH_LSH_H


#include <set>
#include "LshSimple.h"
class AbstractLSH_CUBE;

#include "HashTablesStructures.h"
#include "EuclideanSpaceLSH.h"
#include "CosineSimilarityLSH.h"

class multi_hash_table;

using namespace std;

class Lsh  : public AbstractLshCube {
private:

    multi_hash_table *MHT_ptr;

public:
    ~Lsh() override;

    set<string> getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) override;

    Lsh(unsigned int TableSize, unsigned int k, unsigned int W, unsigned int d, long long int M, unsigned int &L ,unordered_map<string, myVector >& in_umap );

    Lsh (unsigned  int TableSize, unsigned int& k ,unsigned int& d , unsigned int& L  , unordered_map<string, myVector >& in_umap  );

};


#endif //LSH_LSH_H
