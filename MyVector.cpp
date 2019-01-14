//
// Created by dimitrisgan on 19/10/2018.
//

#include "MyVector.h"



//bool myVector::isEqual(myVector other){
//
//    bool result = std::equal(this->coords.begin(), this->coords.end(), other.begin());
//}


void myVector::divideVectorWithNumber (unsigned long num){
    for ( auto &coord  : this->coords  ) {
        coord = coord / num;
    }
}


void myVector::setCoords(vector<double> &coords) {
    myVector::coords = coords;
}
//=================================================================================================
const vector<double> &myVector::getCoords() const {
    return coords;
}

vector<double> myVector::getCoordsByValue(){
    return coords;

}
//=================================================================================================

const double myVector::dot_product(const myVector& myV2  ){
    double  dot_product = 0;

    vector<double >::const_iterator  ItA, ItB;
    assert(this->coords.size() == myV2.coords.size( ));

    ItA = this->coords.begin();
    ItB = myV2.coords.begin();
    while(true)
    {

        //do stuff with ItA and ItB
        dot_product += (*ItA) * (*ItB);

        if(ItA != this->coords.end())
        {
            ++ItA;
        }
        if(ItB != myV2.coords.end())
        {
            ++ItB;
        }
        if(ItA == this->coords.end() && ItB == myV2.coords.end())
        {
            break;
        }
    }

    return dot_product;

}

//=================================================================================================

double myVector::euclidean_norm(){
    double norm =0;
    double sum_of_square_coords =0;
    for (auto &coord : this->getCoords()) {
        sum_of_square_coords += pow(coord,2);
    }
    norm = sqrt(sum_of_square_coords);
    return  norm;
}

//=================================================================================================

void myVector::print_vector() const{
//    cout.precision(dbl::max_digits10 + 1);
//    cout.precision(8);


//    std::ostringstream strs;


//    std::cout << "[VECTOR COORDS] :\t";

//    std::cout  << std::setw(2)   << getCoords().at(0) <<"\t\t";

       for (auto &coords : getCoords()) {
   //        strs << coords;
   //        std::string str = strs.str();
           std::cout  /*<< std::setw(2)*/   << coords <<"\t";
       }
       printf("\n" );
}


bool myVector::operator==(const myVector & q){
    return this->getCoords() == q.getCoords();

}


void myVector::initializeToInf(int size) {
    double inf = std::numeric_limits<double>::infinity();


    vector <double> CryptoSc(size,inf);

    this->coords = CryptoSc;

    assert(size == 100);

}

void myVector::setVectorToSpecificIndexes(set<int> coinsIndexes2addScoreInUser, double Si) {

    for (auto coinIndex : coinsIndexes2addScoreInUser){
        this->coords[coinIndex] = Si;
    }
}

void myVector::changeValueToSpecificIndex(int index, double value) {
    this->coords[index] = value;
}



