//
// Created by dimitrisgan on 19/10/2018.
//

#ifndef PROJECT_EM_H_CLASS_FUNCTIONS_LSH_H
#define PROJECT_EM_H_CLASS_FUNCTIONS_LSH_H


#include <iostream>
#include <vector>
#include "MyVector.h"
#include "LshSimple.h"

//#include "LshSimple.h"

#include <sstream>

class LshSimple;


using namespace std;


//=========================================================

long long int uniform_int_distrib_Lsh();

//=========================================================

class F_HF_Obj {
private:

    vector<long long int > r_values;
    unsigned int k{}; //todo na to ftiaksw na mhn xreiazetai

public:
    explicit F_HF_Obj(  unsigned int k );

    F_HF_Obj() = default;

    virtual ~F_HF_Obj() = default;

    void assign_r_values();

    const vector<long long int> &getR_values() const;

    void print_F_r_values() const;

};

//=========================================================

class H_Class_Lsh {
private:

    myVector v;
    float t{};
    unsigned int W{};
    unsigned int d{};
public:
    H_Class_Lsh(unsigned int& W,unsigned int& d);
    H_Class_Lsh() = default;
    virtual ~H_Class_Lsh() = default;

    void assign_v_t();
    long long int calculate_h_fun(myVector& p) const;

    void uniform_distrib();
    void normal_distrib(unsigned int& d);

    void print_h() const;

};


//=========================================================

class EuclideanSpaceLSH : public LshSimple {
private:
    unsigned  long long TableSize;

    vector<H_Class_Lsh > h_chain;
    F_HF_Obj   F_HF;

    unsigned  int k;

    unsigned int W;

    unsigned  int d;

    long long int M;

public:


    EuclideanSpaceLSH(unsigned  int TableSize, unsigned int k , unsigned int W,unsigned int d ,long long int  M);

    unsigned  int get_HT_index(myVector& p) const  override; //aka φ

    string g(myVector& p) override;

    const vector<H_Class_Lsh> &getH_chain() const;
    const F_HF_Obj &getF_HF() const;

    void print_EuclideanSpaceLSH() const;

};


//=========================================================


#endif //PROJECT_EM_H_CLASS_FUNCTIONS_H
