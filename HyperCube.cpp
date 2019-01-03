//
// Created by dimitrisgan on 30/11/2018.
//
class CubeTable;
#include "HyperCube.h"

#include "HashTablesStructures.h"

set<string> HyperCube::getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap){

    unsigned M_counter = 0;
    unsigned int Vertices_counter = 1;
    unsigned int number2eraseFromList;

    vector<string> list2search;


    unsigned int Index2HT = this->HT_ptr->get_index2HT(query);
    vector <string> MyVertex = getVertexOfTheQuery(query);

    vector<unsigned int> nearby_verticesIndex_list; //nearby vertices with Hamming distance 1;
    nearby_verticesIndex_list = getAllNeigborsIndexes(Index2HT, this->k);


    for (auto &v_id : MyVertex) {
        if (M_counter >= M) {
            break;
        }
        M_counter++;
        list2search.push_back(v_id);
    }
//mexri edw exw parei olous tous epitrepomenous geitones sth 1h korufh = myVertex

    if (probes > 1 && M_counter < M) {

        if (nearby_verticesIndex_list.size() > (probes - 1)) {
            number2eraseFromList = static_cast<unsigned int>(nearby_verticesIndex_list.size() - (probes - 1));
            nearby_verticesIndex_list.erase(nearby_verticesIndex_list.begin(),
                                            nearby_verticesIndex_list.begin() + number2eraseFromList);
        }

        for (auto &vertexIndex : nearby_verticesIndex_list) {
            if (M_counter >= M) {
                break;
            }
            Vertices_counter++;
            const vector<string> &temp = this->HT_ptr->getBucket_chain_index(vertexIndex); //MHT.getBucketChain(vertexIndex, 0);

            for (auto &v_id  : temp) {

                if (M_counter >= M) {
                    break;
                }
                M_counter++;
                list2search.push_back(v_id);

            }
        }
    }

    std::set<string> st( list2search.begin(), list2search.end() );

    return st;
}


vector<string> HyperCube::getVertexOfTheQuery(myVector &query) {

    return this->HT_ptr->getVertex(query);
}


HyperCube::HyperCube(unsigned int TableSize ,unsigned int k,unsigned int d , unsigned int W, unordered_map<string, myVector >& in_umap ,  unsigned int &probes ,unsigned int &M ) {

    cout << "~~~~~ CONSTRUCTOR CUBE - EUCLIDEAN CALLED ~~~~~\n";

    this->M = M;  //dianusmata pou thelei na stamathsw

    this->probes = probes;
    if (this->probes  >  k) {
        this->probes = k;
    }
    this->k = k;

    this->cubeAbstract_ptr = new EuclideanSpaceCube(  k ,  W,  d );

    this->HT_ptr = new CubeTable(TableSize , this->cubeAbstract_ptr ); //hash_tableCube(unsigned int& HT_SIZE , HyperCube *cube);

    this->HT_ptr->SaveSataset2CubeTable(in_umap);
}


HyperCube::HyperCube(unsigned int TableSize ,unsigned int k,unsigned int d ,unordered_map<string, myVector >& in_umap ,  unsigned int &probes ,unsigned int &M ){

    cout << "~~~~~ CONSTRUCTOR CUBE - COSINE CALLED ~~~~~\n";

    this->M = M;  //dianusmata pou thelei na stamathsw
    this->probes = probes;
    if (this->probes  >  k) {
        this->probes = k;
    }
    this->k = k;

    this->cubeAbstract_ptr = new CosineSimilarityCube( k , d);

    this->HT_ptr = new CubeTable(TableSize , this->cubeAbstract_ptr); //hash_tableCube(unsigned int& HT_SIZE , HyperCube *cube);

    this->HT_ptr->SaveSataset2CubeTable(in_umap);



}

CubeTable *HyperCube::getHT_ptr() const {
    return HT_ptr;
}

CubeAbstract *HyperCube::getCubeAbstract_ptr() const {
    return cubeAbstract_ptr;
}

HyperCube::~HyperCube() {
    cout << "the destructor of CubeHT has been called\n";
    delete HT_ptr;//(L,TableSize,lsh_list);

}

