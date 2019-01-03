//
// Created by dimitrisgan on 30/11/2018.
//

#ifndef PROJECT2_CUBEABSTRACT_H
#define PROJECT2_CUBEABSTRACT_H

#include "MyVector.h"

class CubeAbstract{
private:
public:

    virtual ~CubeAbstract() = default;

    virtual unsigned  int get_HT_index(myVector& p)  = 0 ;


//    virtual string g(myVector& p) =0;
    virtual void  print_dictionaries() {};
};






#endif //PROJECT2_CUBEABSTRACT_H
