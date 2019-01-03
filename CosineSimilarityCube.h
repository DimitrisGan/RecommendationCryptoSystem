//
// Created by dimitrisgan on 21/10/2018.
//

#ifndef PROJECT_EM_COSINESIMILARITY_CUBE_H
#define PROJECT_EM_COSINESIMILARITY_CUBE_H

#include <vector>

#include <iostream>
#include <random>
#include "MyVector.h"
#include <bits/stdc++.h>

#include "CubeAbstract.h"




using namespace std;

//====================================================================

class H_Class_Cos{
private:
    myVector r;

public:

    explicit H_Class_Cos(unsigned int& dim){
//        cout << " H_Class_Cos Constructor was called " <<endl;

        normal_distrib(dim);
    }

    void normal_distrib(unsigned int& dim);

    string calculate_h_fun(myVector& p) const;

    void print_h() const;
};

//====================================================================

class CosineSimilarityCube : public  CubeAbstract {
private:
    vector<H_Class_Cos > h_chain;
    unsigned  int k;
    unsigned int d;
public:
    CosineSimilarityCube(unsigned int& k ,unsigned int& d);

    unsigned  int get_HT_index(myVector& p) override;

//    string  g(myVector& p) override;

    void print_CosineSimilarityLSH() const;


};



#endif //PROJECT_EM_COSINESIMILARITYLSH_H
