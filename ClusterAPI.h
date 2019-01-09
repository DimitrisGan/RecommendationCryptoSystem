//
// Created by dimitrisgan on 3/1/2019.
//

#ifndef RECOMMENDATIONCRYPTOSYSTEM_CLUSTERAPI_H
#define RECOMMENDATIONCRYPTOSYSTEM_CLUSTERAPI_H

/*
#include <iostream>
#include <string>
#include <vector>


#include <unordered_map>
#include "MyVector.h"
#include "Cluster.h"


//#include "AssistantFunctions.h"
#include "AssistantFunctions.h"
#include "Metrics.h"
#include "Initialization.h"
#include "Assignment.h"
#include "Update.h"
#include "AbstractLSH_CUBE.h"
#include "HyperCube.h"
#include "LSH.h"

*/
#include <iostream>
#include <unordered_map>

#include "SearchingAlgorithms.h"
#include "AssistantFunctions.h"
#include "Initialization.h"
#include "Cluster.h"
#include "Assignment.h"
#include "Update.h"
#include "EvaluationMetric.h"
//#include "AbstractLSH_CUBE.h"
//#include "LSH.h"
//#include "HyperCube.h"




#define ITERATIONS 10 //TODO VALTO 20

using namespace std;


void ClusterProcedure(kClusters &allClusters , unordered_map<string, myVector> &in_umap , const string &configFileName , unsigned int d);





#endif //RECOMMENDATIONCRYPTOSYSTEM_CLUSTERAPI_H
