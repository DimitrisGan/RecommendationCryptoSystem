#include <utility>

//
// Created by dimitrisgan on 19/10/2018.
//

#ifndef PROJECT_EM_MYVECTOR_CLASS_FUNCTIONS_H
#define PROJECT_EM_MYVECTOR_CLASS_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <random>
#include <assert.h>     /* assert */
#include <iomanip>
#include <limits>
#include <sstream>
#include <set>


using namespace std;
typedef std::numeric_limits< double > dbl;


class myVector {
private:
    vector<double > coords;
public:
    myVector() = default;

    myVector(vector<double> coords) : coords(std::move(coords)) {}
    ~myVector() = default;


    void initializeToInf(int size);
    void setVectorToSpecificIndexes(set<int> coinsIndexes2addScoreInUser , double Si);


    const vector<double> &getCoords() const ;
    vector<double> getCoordsByValue();
    void setCoords(vector<double> &coords);

    const double dot_product(const myVector& myV2  );

    double euclidean_norm();

    void print_vector() const;

//    bool isEqual(myVector other);

    myVector operator+(const myVector& q) {

        vector <double> NewCoords (this->coords.size() , 0);
//        NewCoords.resize(q.coords.size());
//        for ( auto &coor  : NewCoords ) {
//            cout << coor << "\t";
//        }
        myVector result(NewCoords);

        assert(this->coords.size() == q.coords.size());

        vector<double >::const_iterator  ItA, ItB;
        double inf = std::numeric_limits<double>::infinity();


        ItA = this->getCoords().begin();
        ItB = q.getCoords().begin();

        unsigned int index=0;
        while(true)
        {


            if (*ItA == inf && *ItB == inf){
                result.coords[index] = inf;

            }
            if (*ItA == inf && *ItB != inf){// to current
                result.coords[index] = *ItB;

            }
            if (*ItA != inf && *ItB == inf){// to current
                result.coords[index] = *ItA;

            }
            if (*ItA != inf && *ItB != inf){// to current
                result.coords[index] = *ItA + *ItB;

            }

            index++;



            if(ItA != this->getCoords().end())
            {
                ++ItA;
            }
            if(ItB != q.getCoords().end())
            {
                ++ItB;
            }
            if(ItA == this->getCoords().end() && ItB == q.getCoords().end())
            {
                break;
            }

        }

        return result;
    }



    bool operator==(const myVector & q);


    void divideVectorWithNumber (unsigned long num);



};





#endif //PROJECT_EM_MYVECTOR_CLASS_FUNCTIONS_H
