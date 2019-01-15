//
// Created by dimitrisgan on 21/10/2018.
//

#include "CosineSimilarityLSH.h"


void H_Class_Cos_Lsh::normal_distribCos(unsigned int &dim){
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

string H_Class_Cos_Lsh::calculate_h_fun(myVector& p) const { //kanei to dot product kai epistrefei 0 h 1

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

void H_Class_Cos_Lsh::print_h() const{
    cout << "r values are :"<<endl;
    r.print_vector();
}

//====================================================================
//====================================================================

CosineSimilarityLSH::CosineSimilarityLSH( unsigned int& k , unsigned int& d) : k(k) ,d(d) {

    //cout << "CosineSimilarityLSH Constructor called " << endl;

    std::vector<H_Class_Cos_Lsh> h_classes(k, H_Class_Cos_Lsh(d));


    for (auto &h : h_classes) {
        h.normal_distribCos(d);
    }
    this->h_chain = h_classes;


}

//====================================================================

unsigned int CosineSimilarityLSH::get_HT_index (myVector& p ) const {
    string string_hash_value;
    unsigned int hash_value;
    for (auto &h : h_chain) {
        string_hash_value.append( h.calculate_h_fun(p) );
    }

    hash_value = static_cast<unsigned int>(bitset<128>(string_hash_value).to_ulong());

    return hash_value;
}

//====================================================================

string CosineSimilarityLSH::g(myVector& p){

    return "1";
}

//====================================================================


void CosineSimilarityLSH::print_CosineSimilarityLSH() const {
//    cout << "~~~~CosineSimilarityLSH has ~~~~ " << endl;

    for (auto &h : h_chain) {
        h.print_h();
    }
    cout << "================="<<endl;

}

