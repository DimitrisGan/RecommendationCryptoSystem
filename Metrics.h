//
// Created by dimitrisgan on 22/10/2018.
//



#ifndef PROJECT_EM_METRICS_H
#define PROJECT_EM_METRICS_H

#include <iostream>
#include <iomanip>

#include "MyVector.h"


class DistanceMetrics {
private:

public:
    DistanceMetrics() = default;

    virtual ~DistanceMetrics() = default;

    virtual  double distance(myVector& p,myVector& q) = 0;

    virtual double similairty(double dist)=0;

};

//=========================================================

class EuclideanMetric final : public DistanceMetrics {
private:
public:
    EuclideanMetric() = default;

    ~EuclideanMetric() override = default;


    double distance(myVector& p,myVector& q) override;

    double similairty(double dist) override;

};

//=========================================================

class CosineMetric final : public DistanceMetrics{
private:
public:
    CosineMetric() = default;

    ~CosineMetric() override = default;

    double distance(myVector& p,myVector& q) override;

    double similairty(double dist) override;
};



#endif //PROJECT_EM_METRICS_H
