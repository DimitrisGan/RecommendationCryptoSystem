//
// Created by dimitrisgan on 20/10/2018.
//

#ifndef PROJECT_EM_HASHTABLESSTRUCTURES_H
#define PROJECT_EM_HASHTABLESSTRUCTURES_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>

#include "AssistantFunctions.h"

#include "LshSimple.h"
#include "CubeAbstract.h"



using namespace std;




struct bucket_chain  //hash table's bucket
{
    vector<string> vector_id_bucket_chain;  // basically a bucket is a vector that contains pointers to already saved vector_item_id's

    void add_vector_id_to_bucket_chain(string vector_id);
    void print_bucket_chain();

    const vector<string> &getVector_id_bucket_chain() const;
};

//=========================================================

struct hash_table
{
    unsigned int HT_SIZE;
    LshSimple * lsh;
    vector<bucket_chain *> bucket_chain_index; //basically a hash table is a vector that contains pointers to its buckets


    hash_table(unsigned int& HT_SIZE , LshSimple *lsh);

    virtual ~hash_table();

    const vector<string> &getBucket_chain_index(unsigned int& index) const;

    const unsigned int  get_index2HT(myVector& q ) const;

    void insert_vector_id_to_HT(string vector_id, unsigned int HT_index);

    const vector<string> getFiltered_by_g_collision_chain_bucket(myVector& query ,unordered_map<string, myVector >& in_umap  ) const ;

    void print_HT();

};

//=========================================================
/*
HASH TABLE FOR CUBE
*/
//=========================================================

struct CubeTable
{
    unsigned int HT_SIZE;
    vector<bucket_chain *> bucket_chain_index; //basically a hash table is a vector that contains pointers to its buckets
    CubeAbstract * cube;


    CubeTable(unsigned int& HT_SIZE , CubeAbstract *cube);

    virtual ~CubeTable();


    vector<string> getVertex(myVector &query) ;


    const vector<string> &getBucket_chain_index(unsigned int& index) const;

    const unsigned int  get_index2HT(myVector& q ) const;


    void insert_vector_id_to_HT(string vector_id, unsigned int HT_index);


    void print_HT();

    void SaveSataset2CubeTable(unordered_map<string, myVector >& in_umap);

};

//=========================================================
//=========================================================

struct multi_hash_table
{
    unsigned int L;
    vector <hash_table *> HT_id ; // basically a multi hash table is a vector that contains pointers to its hash tables


    multi_hash_table(unsigned int& L, unsigned int& HT_SIZE, vector <LshSimple *> lsh_list);

    virtual ~multi_hash_table();

    void SaveDataset2_All_HastTables(unordered_map<string, myVector >& in_umap );

    const vector<string> getFiltered_buckets_from_All_HTs(myVector &query, unordered_map<string, myVector> &in_umap) const;

    const vector<hash_table *> &getHT_id() const;

    void print_MHT();

};






#endif //PROJECT_EM_HASHTABLESSTRUCTURES_H
