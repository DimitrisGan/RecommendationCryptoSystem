//
// Created by dimitrisgan on 21/10/2018.
//

#ifndef PROJECT_EM_COSINESIMILARITY_LSH_H
#define PROJECT_EM_COSINESIMILARITY_LSH_H

#include <vector>

#include <iostream>
#include <random>
#include "MyVector.h"
#include <bits/stdc++.h>

#include "LshSimple.h"


using namespace std;

//====================================================================

class H_Class_Cos_Lsh{
private:
    myVector r;

public:

    explicit H_Class_Cos_Lsh(unsigned int& dim){
//        cout << " H_Class_Cos_Lsh Constructor was called " <<endl;

        normal_distribCos(dim);
    }

    void normal_distribCos(unsigned int &dim);

    string calculate_h_fun(myVector& p) const;  //calls dot product and returns 0 or 1

    void print_h() const;
};

//====================================================================

class CosineSimilarityLSH : public  LshSimple {
private:
    vector<H_Class_Cos_Lsh > h_chain;
    unsigned  int k;
    unsigned int d;
public:
    CosineSimilarityLSH(unsigned int& k ,unsigned int& d);

    unsigned  int get_HT_index(myVector& p) const override;

    string  g(myVector& p) override;

    void print_CosineSimilarityLSH() const;

};



#endif //PROJECT_EM_COSINESIMILARITYLSH_H
