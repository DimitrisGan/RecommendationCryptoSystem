//
// Created by dimitrisgan on 21/10/2018.
//

#include "CosineSimilarityCube.h"


void H_Class_Cos::normal_distrib(unsigned int&  dim){
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{0,1};
    float v_coord;
    unsigned int n;
    std::vector<double> v_temp;

    for(n=0; n<dim; ++n) {
        v_coord = static_cast<float>(d(gen));

        v_temp.push_back(v_coord);
    }
    this-> r = v_temp;

}

//====================================================================

string H_Class_Cos::calculate_h_fun(myVector& p) const {
    double dot;

    dot = p.dot_product(this->r);
//    r.print_vector();

    if (dot >= 0){
        return "1";
    }
    else{
        return "0";
    }
}

//====================================================================

void H_Class_Cos::print_h() const{
    cout << "r values are :"<<endl;
    r.print_vector();
}

//====================================================================
//====================================================================

CosineSimilarityCube::CosineSimilarityCube( unsigned int& k , unsigned int& d) : k(k) ,d(d) {

//    cout << "CosineSimilarityLSH Constructor called " << endl;

    std::vector<H_Class_Cos> h_classes(k, H_Class_Cos(d));


    for (auto &h : h_classes) {
        h.normal_distrib(d);
    }
    this->h_chain = h_classes;


}

//====================================================================

unsigned int CosineSimilarityCube::get_HT_index (myVector& p )  {
    string string_hash_value;
    unsigned int hash_value;
    for (auto &h : h_chain) {
        string_hash_value.append( h.calculate_h_fun(p) );
    }

    hash_value = static_cast<unsigned int>(bitset<128>(string_hash_value).to_ulong());
    return hash_value;


}


//====================================================================


void CosineSimilarityCube::print_CosineSimilarityLSH() const {
    cout << "~~~~CosineSimilarityLSH has ~~~~ " << endl;

    for (auto &h : h_chain) {
        h.print_h();
    }
    cout << "================="<<endl;

}

