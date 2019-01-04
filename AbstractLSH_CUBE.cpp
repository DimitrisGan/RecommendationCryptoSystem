//
// Created by dimitrisgan on 3/1/2019.
//

#include "AbstractLSH_CUBE.h"

//
#include "LSH.h"
#include "HyperCube.h"


AbstractLshCube* constructLshDatastructure(const int &DistMetricFlag ,   Lsh *lsh_ptr , unsigned &k_hf ,
                                           unsigned &W , unsigned &d , long long &M_lsh ,unsigned &L , unordered_map<string, myVector> &in_umap ) {

    unsigned int TableSize;
    if (!DistMetricFlag) { // is euclideanSpace
        TableSize = static_cast<unsigned int>(in_umap.size() / 8);
        lsh_ptr = new Lsh(TableSize, k_hf, W, d, M_lsh, L, in_umap);

    } else { // is cosineSimilarity
        TableSize = static_cast<unsigned int>(pow(2, k_hf));
        lsh_ptr = new Lsh(TableSize, k_hf, d, L, in_umap);

    }

    assert(lsh_ptr != nullptr);




    return lsh_ptr;
}


AbstractLshCube* constructCubeDatastructure(const int &DistMetricFlag ,HyperCube *cube_ptr , unsigned &k_hf ,
                                            unsigned &W , unsigned &d ,unsigned &M_cube , unsigned int &probes, unordered_map<string, myVector> &in_umap ){

    unsigned int TableSize = static_cast<unsigned int>(pow(2, k_hf));

    if (!DistMetricFlag) {// is euclideanSpace
        cube_ptr = new HyperCube(TableSize, k_hf, d, W, in_umap, probes, M_cube);
//            cube_ptr->getHT_ptr()->print_HT();

    } else { // is cosineSimilarity
        cube_ptr = new HyperCube(TableSize, k_hf, d, in_umap, probes, M_cube);
//            cube_ptr->getHT_ptr()->print_HT();

    }

    assert(cube_ptr != nullptr);
    return cube_ptr;
}
