#include "EuclideanSpaceCube.h"//
// Created by dimitrisgan on 19/10/2018.
//


int glob=0;


long long int uniform_int_distrib(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(-100, 100);

    return dis(gen);
}

//=========================================================
//=========================================================

H_Class_Cube::H_Class_Cube(unsigned int& W,unsigned int& d)  : W(W) , d(d) {
    cout << " H_Class_Cube Constructor was called " <<endl;
}


//=========================================================

void H_Class_Cube::assign_v_t(){
    cout << "CALLED #"<< glob++<<endl;
    uniform_distrib(); //uniform_real_distribution()
    normal_distrib(this->d);
}

//=========================================================

long long int  H_Class_Cube::calculate_h_fun(myVector& p) const{
    double h_value;
    long long int val;
    double dot,numerator;
    dot = p.dot_product(this->v);
    numerator = dot + (double)this->t;
    h_value = numerator / ((double) this->W );
    val = static_cast<long long int>(floor(h_value));
    return val;
}

//=========================================================

//float uniform_distrib();
void H_Class_Cube::uniform_distrib(){
    std::random_device rd; //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0, W);

    this->t = float(dis(gen));

}

//=========================================================

void H_Class_Cube::normal_distrib(unsigned int& dim){
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{0,1};
    double v_coord;
    unsigned int n;
    std::vector<double> v_temp;

    for(n=0; n<dim; ++n) {
        v_coord = d(gen);
        v_temp.push_back(v_coord);
    }
    this-> v.setCoords(v_temp);

}

//=========================================================

void H_Class_Cube::print_h() const{
    std::cout << "t = " << t << " \t & v = "<< endl;
    v.print_vector();
}

//=========================================================
//=========================================================


EuclideanSpaceCube::EuclideanSpaceCube(  unsigned int k , unsigned int W,unsigned int d ) :   k(k) , W(W) , d(d)  {

//    cout << "EuclideanSpaceCube Constructor called " << endl;

    std::vector<H_Class_Cube> h_classes(k, H_Class_Cube(W,d));
    vector<unordered_map< long long int, string > > temp_f_umaps(k);

    for (auto &h : h_classes) {
        h.assign_v_t();
    }

    this->h_chain = h_classes;
    this->f_umaps = temp_f_umaps;

}

//=========================================================


unsigned  int EuclideanSpaceCube::get_HT_index(myVector& p ) {
    long long int temp_val_h_p;

    std::vector<long long int> h_p_chain;
    for (auto &h : this->h_chain) {
        temp_val_h_p = h.calculate_h_fun(p);
        h_p_chain.push_back(temp_val_h_p);
    }

    assert( this->f_umaps.size() == h_p_chain.size());

    string string_hash_value;
    string temp;
    int i=0;
    unsigned long beforeSize;

    for ( auto &f_umap : f_umaps ) {
        beforeSize = f_umap.size();

        temp = f (h_p_chain[i] , f_umap);


        assert( (f_umap.size() == beforeSize) || (f_umap.size() == beforeSize +1) );
        string_hash_value.append(temp);
        i++;
    }


    unsigned  int hash_value = static_cast<unsigned int>(bitset<128>(string_hash_value).to_ulong());

    return hash_value;


}

//=========================================================

const vector<H_Class_Cube> &EuclideanSpaceCube::getH_chain() const {
    return h_chain;
}

//=========================================================

void EuclideanSpaceCube::print_EuclideanSpaceCube() const {
    cout << "~~~~EuclideanSpaceCube has ~~~~ " << endl;
    for (auto &h : h_chain) {
        h.print_h();
    }
    cout << "================="<<endl;
    cout << "with r values in f "<<endl;
//    F_HF.print_F_r_values();

    cout << "~~~~EuclideanSpaceCube ends here ~~~~ " << endl;
}


void EuclideanSpaceCube::print_dictionaries(){


    std::vector< long long int> keysInF;
    unsigned int i=0;
    for (auto &dict : this->f_umaps) {
        cout << "DictF #"<< i++<<endl;

        keysInF = extract_keysF(dict);

        for ( auto &key :keysInF ) {
            cout << "key = "<< key <<endl;

        }
        print_map(dict);
    }
}


