//
// Created by dimitrisgan on 19/10/2018.
//

#ifndef PROJECT_EM_H_CLASS_FUNCTIONS_CUBE_H
#define PROJECT_EM_H_CLASS_FUNCTIONS_CUBE_H


#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cstdlib>

#include "MyVector.h"
#include "CubeFunctions.h"
#include "CubeAbstract.h"


#include <sstream>


using namespace std;


//=========================================================

long long int uniform_int_distrib();

//=========================================================

class H_Class_Cube {
private:
    myVector v;
    float t{};
    unsigned int W{};
    unsigned int d{};
public:
    H_Class_Cube(unsigned int& W,unsigned int& d);
    H_Class_Cube() = default;
    virtual ~H_Class_Cube() = default;

    void assign_v_t();
    long long int calculate_h_fun(myVector& p) const;

    void uniform_distrib();
    void normal_distrib(unsigned int& d);

    void print_h() const;

};


//=========================================================


class EuclideanSpaceCube : public CubeAbstract {
private:

    vector<H_Class_Cube > h_chain;
    vector<unordered_map< long long int, string > > f_umaps;

    unsigned  int k;

    unsigned int W;

    unsigned  int d;

public:


    EuclideanSpaceCube(  unsigned int k , unsigned int W,unsigned int d );

    unsigned  int get_HT_index(myVector& p) override; //aka φ


    const vector<H_Class_Cube> &getH_chain() const;

    void print_EuclideanSpaceCube() const;

    void print_dictionaries() override;

};


//=========================================================


#endif //PROJECT_EM_H_CLASS_FUNCTIONS_H
