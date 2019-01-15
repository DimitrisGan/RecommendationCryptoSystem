
//
// Created by dimitrisgan on 20/10/2018.
//

#include "HashTablesStructures.h"



void bucket_chain::add_vector_id_to_bucket_chain(string vector_id){

    vector_id_bucket_chain.push_back(vector_id);
}

//=========================================================


void bucket_chain::print_bucket_chain(){
    cout<<"[";
    for(unsigned int i=0 ; i < vector_id_bucket_chain.size() ; i++)
    {
        cout<<vector_id_bucket_chain[i];
        if (vector_id_bucket_chain.size()-1 != i)
            cout<<",";
    }
    cout<<"]"<<endl;
}

//=========================================================

const vector<string> &bucket_chain::getVector_id_bucket_chain() const {
    return vector_id_bucket_chain;
}

//=========================================================
//=========================================================

hash_table::hash_table(unsigned int& HT_SIZE , LshSimple * lsh)
{
    this->lsh = lsh;
    this->HT_SIZE = HT_SIZE;

    for (unsigned int i=0; i < HT_SIZE ; i++) //dynamically create all HT_SIZE buckets and store their pointers to a vector
    {
        auto * bucket_chain_ptr = new bucket_chain;

        bucket_chain_index.push_back(bucket_chain_ptr);
    }
}

//=========================================================

hash_table::~hash_table()
{   //taking care of memory leaks
    //cout << "the destructor of hash_table has been called\n";

    for (unsigned int i=0; i < HT_SIZE ; i++)
    {
        delete bucket_chain_index[i];
    }

    delete lsh; //todo tha xw thema sto cube !!
}

//=========================================================

const vector<string > &hash_table::getBucket_chain_index(unsigned int& index) const {
    return bucket_chain_index.at(index)->vector_id_bucket_chain;
}


//=========================================================
const unsigned int  hash_table::get_index2HT(myVector& q ) const{
    unsigned int index = this->lsh->get_HT_index(q);
    return index;
}

//=========================================================

void hash_table::insert_vector_id_to_HT(string vector_id, unsigned int HT_index){

    bucket_chain_index[HT_index]-> add_vector_id_to_bucket_chain(std::move(vector_id));
}

//=========================================================

const vector<string> hash_table::getFiltered_by_g_collision_chain_bucket(myVector& query ,unordered_map<string, myVector >& in_umap  ) const {

    unsigned  int index = this->get_index2HT(query);
    vector <string> temp = getBucket_chain_index(index);

    vector <string> filtered_vector_ids ;
    myVector v;

    for (auto &id_v : temp) {

        v = in_umap[id_v];

        if (lsh->g(v) == lsh->g(query)){ //both return string
            filtered_vector_ids.push_back(id_v);
        }
    }
    return filtered_vector_ids;
}

//=========================================================

void hash_table::print_HT(){

    for(unsigned int i=0 ; i < HT_SIZE ; i++)
    {
        cout<<"->Printing bucket #"<<i<<endl;
        bucket_chain_index[i]->print_bucket_chain();
    }
    cout<<"------------------------------------"<<endl;
}

//=========================================================
//=========================================================

multi_hash_table::multi_hash_table(unsigned int& L, unsigned int& HT_SIZE, vector <LshSimple * > lsh_list) : L(L) {

    for (unsigned int i = 0; i < L ; ++i) {
        auto * HT_ptr = new  hash_table(HT_SIZE , lsh_list.at(i));
        this->HT_id.push_back(HT_ptr);
    }
}

//=========================================================

multi_hash_table::~multi_hash_table() {
    //cout << "the destructor of multi_hash_table has been called\n";
    for (unsigned int i = 0; i < L ; ++i) {
        delete HT_id[i];
    }
}

//=========================================================

void multi_hash_table::SaveDataset2_All_HastTables(unordered_map<string, myVector >& in_umap ) {
    unsigned int Index2HT;
    std::vector<std::string> keys;
    keys = extract_keys(in_umap);


    for (auto &HT :HT_id) {
        for (auto &vector_id :keys) {
            Index2HT = HT->lsh->get_HT_index(in_umap[vector_id]);
            HT->insert_vector_id_to_HT(vector_id, Index2HT);
        }
    }
}

//=========================================================

const vector<string> multi_hash_table::getFiltered_buckets_from_All_HTs(myVector &query,
                                                                        unordered_map<string, myVector> &in_umap) const {
    vector <string> filt_g_from_all_HTs ;
    for (auto &HT : this->HT_id) {
        vector <string> temp = HT->getFiltered_by_g_collision_chain_bucket(query , in_umap);
        filt_g_from_all_HTs.insert(end(filt_g_from_all_HTs) , begin(temp) , end(temp));
    }

    return filt_g_from_all_HTs;
}

//=========================================================

const vector<hash_table *> &multi_hash_table::getHT_id() const {
    return HT_id;
}

//=========================================================

void multi_hash_table::print_MHT(){
    int i=0;
    for (auto &HT :HT_id) {
        cout << "~~~~ PRINTING HASHTABLE #"<<i++ <<" ~~~~"<<endl;
        HT->print_HT();
    }
}


//=========================================================
//=========================================================
//=========================================================
//=========================================================
//=========================================================
//=========================================================

CubeTable::CubeTable(unsigned int& HT_SIZE , CubeAbstract * cube)
{
    this->cube = cube;
    this->HT_SIZE = HT_SIZE;

    for (unsigned int i=0; i < HT_SIZE ; i++) //dynamically create all HT_SIZE buckets and store their pointers to a vector
    {
        auto * bucket_chain_ptr = new bucket_chain;

        bucket_chain_index.push_back(bucket_chain_ptr);
    }
}


//=========================================================

CubeTable::~CubeTable()
{   //taking care of memory leaks
    for (unsigned int i=0; i < HT_SIZE ; i++)
    {
        delete bucket_chain_index[i];
    }
    delete cube; //todo tha xw thema sto cube !!


}

//=========================================================

vector<string> CubeTable::getVertex(myVector &query) {
    unsigned  int index = get_index2HT(query );
    vector <string> Vertex = getBucket_chain_index(index);

    return Vertex;
}


//=========================================================

const vector<string > &CubeTable::getBucket_chain_index(unsigned int& index) const {
    return bucket_chain_index.at(index)->vector_id_bucket_chain;
}



//=========================================================
const unsigned int  CubeTable::get_index2HT(myVector& q ) const{
    unsigned int index = this->cube->get_HT_index(q);
    return index;
}

//=========================================================

void CubeTable::insert_vector_id_to_HT(string vector_id, unsigned int HT_index){

    bucket_chain_index[HT_index]-> add_vector_id_to_bucket_chain(std::move(vector_id));
}


//=========================================================

void CubeTable::print_HT(){

    for(unsigned int i=0 ; i < HT_SIZE ; i++)
    {
        cout<<"->Printing bucket #"<<i<<endl;
        bucket_chain_index[i]->print_bucket_chain();
    }
    cout<<"------------------------------------"<<endl;
}




void CubeTable::SaveSataset2CubeTable(unordered_map<string, myVector >& in_umap){
    unsigned int Index2HT;

    for (auto &vec :in_umap) {
        Index2HT = this->cube->get_HT_index(vec.second);
        this->insert_vector_id_to_HT(vec.first, Index2HT);
    }
}


