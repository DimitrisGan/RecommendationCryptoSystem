//
// Created by dimitrisgan on 22/10/2018.
//

#include "Metrics.h"




double EuclideanMetric::distance(myVector& p,myVector& q){
//    cout << "Euclidean Distance Metric is called"<<endl;
    double sum_dist =0;
    double x;
    double dist =0;
    //==============

    vector<double >::const_iterator  ItA, ItB;
    assert(p.getCoords().size() == q.getCoords().size());

    ItA = p.getCoords().begin();
    ItB = q.getCoords().begin();

    while(true)
    {
        x = *ItA - *ItB;

        sum_dist += pow(x,2);

        if(ItA != p.getCoords().end())
        {
            ++ItA;
        }
        if(ItB != q.getCoords().end())
        {
            ++ItB;
        }
        if(ItA == p.getCoords().end() && ItB == q.getCoords().end())
        {
            break;
        }

    }
    //==============
//    dist = sqrt(sum_dist);
    dist = sum_dist;
    if (dist < 0){
        dist =0; //ta dianusmata einai idia kai de theloume sfalma strogguleushs
    }
    assert(dist >= 0);
    return dist;
}

double EuclideanMetric::similarity(double dist) {

    return 1/(1+dist);
}

//=========================================================

double CosineMetric::distance(myVector& p,myVector& q){
//    cout << "Cosine Distance Metric is called"<<endl;
//    cout.precision(4);

    double enumerator = p.dot_product(q);
//    cout << "enumerator = "<<p.dot_product(q)<<endl;
    double denominator = p.euclidean_norm() * q.euclidean_norm();
//    cout << "denominator = "<< denominator<<endl;
    double cos  = enumerator/denominator;
//    cout << "cos = "<< cos <<endl;
    double dist = (1.0 - cos);
//    cout << "dist = "<< dist <<endl;
    if (dist < 0){
        assert(1);
        dist =0; //ta dianusmata einai idia kai de theloume sfalma strogguleushs
    }
    return dist;
}

double CosineMetric::similarity(double dist) {
    return (1-dist);
}

