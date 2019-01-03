//
// Created by dimitrisgan on 23/10/2018.
//

#ifndef PROJECT_EM_HYPERCUBEE_H
#define PROJECT_EM_HYPERCUBEE_H


#include "MyVector.h"
#include "EuclideanSpaceCube.h"
#include "CosineSimilarityCube.h"
//#include "HashTablesStructures.h"
//class AbstractLshCube;
class  CubeTable;

#include "AbstractLSH_CUBE.h"

class HyperCube : public AbstractLshCube{
private:
    //maybe the K.L,W,..
    unsigned int probes ;
    unsigned int M;
    unsigned int k; //k_hf


    CubeTable *HT_ptr;//(L,TableSize,lsh_list);
    CubeAbstract * cubeAbstract_ptr;

public:
    CubeTable *getHT_ptr() const;

    CubeAbstract *getCubeAbstract_ptr() const;

public:
    ~HyperCube() override;

    set<string>  getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) override;

    vector<string> getVertexOfTheQuery(myVector &query);

    //eukleidio
    HyperCube(unsigned int TableSize ,unsigned int k,unsigned int d , unsigned int W, unordered_map<string, myVector >& in_umap ,  unsigned int &probes ,unsigned int &M );

    //cosine
    HyperCube(unsigned int TableSize ,unsigned int k,unsigned int d ,unordered_map<string, myVector >& in_umap,  unsigned int &probes ,unsigned int &M );




};




#endif //PROJECT_EM_LSH_H
