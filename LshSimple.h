//
// Created by dimitrisgan on 23/10/2018.
//

#ifndef PROJECT_EM_LSH_SIMPLE_H
#define PROJECT_EM_LSH_SIMPLE_H


#include <unordered_map>
#include "MyVector.h"
//#include "HashTablesStructures.h"



class LshSimple {
private:
    //maybe add K,L,W,...

public:

    virtual ~LshSimple() = default;

    virtual unsigned   int get_HT_index(myVector& p) const = 0 ;

    virtual string g(myVector& p) =0;

};



#endif //PROJECT_EM_LSH_H


