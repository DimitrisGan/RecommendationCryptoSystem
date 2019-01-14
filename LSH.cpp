//
// Created by dimitrisgan on 29/11/2018.
//
#include "LSH.h"





set<string> Lsh::getSuperSet(myVector &query, unordered_map<string, myVector> &in_umap) {
    //todo gia kathe hashtable pare ta buckets
    vector <string> list =  this->MHT_ptr->getFiltered_buckets_from_All_HTs(query , in_umap );
    std::set<string> st ( list.begin(), list.end() );

    return  st;
}


Lsh::Lsh(unsigned  int TableSize, unsigned int k , unsigned int W,unsigned int d ,long long int  M ,unsigned int& L  ,unordered_map<string, myVector >& in_umap ) {
    cout << "~~~~~ CONSTRUCTOR LSH - EUCLIDEAN CALLED ~~~~~\n";

//            cout << "~~~~~~~~~~SELECTED EUCLIDEAN LshSimple~~~~~~~~~~ "<<endl;

    vector <LshSimple* > list_lsh;
    list_lsh.resize(L);
    for ( int i = 0; i < L; ++i) {
        list_lsh[i] = new EuclideanSpaceLSH (TableSize , k, W, d , M);
    }

    this->MHT_ptr = new multi_hash_table(L,TableSize, list_lsh);
    MHT_ptr->SaveDataset2_All_HastTables(in_umap);

}



//lsh_ptr = new Lsh(TableSize, k_hf, d, L, in_umap);

Lsh::Lsh (unsigned  int TableSize, unsigned int& k ,unsigned int& d , unsigned int& L  , unordered_map<string, myVector >& in_umap  ){
    cout << "~~~~~ CONSTRUCTOR LSH - COSINE CALLED ~~~~~\n";
    vector <LshSimple* > list_lsh;
    list_lsh.resize(L);
    for (int i = 0; i < L; ++i) {

        list_lsh[i] = new CosineSimilarityLSH(k , d);
    }

    this->MHT_ptr = new multi_hash_table(L,TableSize,list_lsh);

    MHT_ptr->SaveDataset2_All_HastTables(in_umap);

    MHT_ptr->print_MHT();

}

Lsh::~Lsh() {
    cout <<"the destructor lsh class has been called\n";
    delete MHT_ptr;
}

Lsh::Lsh(const string &confilFileName, unordered_map<string, myVector> &in_umap, unsigned int &d) {
    cout << "~~~~~ CONSTRUCTOR LSH - COSINE CALLED ~~~~~\n";


    unsigned k ;
    unsigned L ;

    ReadConfigFileLsh(confilFileName,k,L);


    auto TableSize = static_cast<unsigned int>(pow(2, k));


    vector <LshSimple* > list_lsh;
    list_lsh.resize(L);
    for (int i = 0; i < L; ++i) {

        list_lsh[i] = new CosineSimilarityLSH(k , d);
    }

    this->MHT_ptr = new multi_hash_table(L,TableSize,list_lsh);

    MHT_ptr->SaveDataset2_All_HastTables(in_umap);

    MHT_ptr->print_MHT();
}

