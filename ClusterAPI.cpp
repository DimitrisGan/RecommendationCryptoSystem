//
// Created by dimitrisgan on 3/1/2019.
//

#include "ClusterAPI.h"

using namespace std;

kClusters ClusterProcedure(unordered_map<string, myVector> &in_umap , const string &configFileName , unsigned int d){

//    configFileName = "cluster.conf";

    /*int Radius=0;*/
    unsigned  int L ; //default:L=5
    unsigned int k ; //for k clusters todo
    unsigned int k_hf; // for k h  //default:k_hf=4

//    unsigned int d = static_cast<unsigned int>(in_umap.at(0).getCoords().size());
    int DistMetricFlag = 0; // 0 --> for euclidean  and 1 --> cosine
    int completeFlag = 0; // 0 --> for euclidean  and 1 --> cosine

    unsigned int M_cube;
    unsigned int probes;
    int I_option,A_option,U_option;
    int flagInputLsh;
    string algOptions;

    unsigned int i;

    unsigned int TableSize;
    unsigned int W = 1;
    auto M_lsh = static_cast<long long int>(pow(2, 32) - 5);


//    ReadHandleArgms(argc, argv , inFileName  , configFileName  , OutFileName , DistMetricFlag ,completeFlag );


    ReadConfigFile(configFileName , k , k_hf , L ,M_cube ,probes , I_option , A_option ,U_option , flagInputLsh ,algOptions);

    cout << "k = "<<k<<endl;
    cout << "k_hf = "<<k_hf<<endl;
    cout << "L = "<<L<<endl;
    cout << "M_cube = "<<M_cube<<endl;
    cout << "probes = "<<probes<<endl;
    cout << "I_option = "<<I_option<<endl;
    cout << "A_option = "<<A_option<<endl;
    cout << "U_option = "<<U_option<<endl;
    cout << "dimensions = "<<d<<endl;

//    ========================================================================================
/*INSTANTIATIONS*/

    // Distance Metric
    DistanceMetrics *distMetric;

    if(DistMetricFlag == 0)
        distMetric = new EuclideanMetric();
    else
        distMetric=new  CosineMetric();

    // Initlialization Algorithm - functor

    Initlializer* init_ptr;
    if (I_option == 1)
        init_ptr = new RandomInit();
    else
        init_ptr = new kMeanspp(distMetric);


    // Assignment Algorithm - functor

    Assigner* assign_ptr ;

    Lsh *lsh_ptr;
    lsh_ptr = nullptr;
    HyperCube *cube_ptr= nullptr;
    AbstractLshCube *myPtr= nullptr;

    if (A_option == 1){
        assign_ptr = new LloydAssignment();
    }
    else{   //constructAppropriateDatastructure () //lsh or hyperCube
        if(flagInputLsh ) {// we have to construct lsh Datastructure here
            myPtr = constructLshDatastructure(DistMetricFlag , lsh_ptr ,k_hf ,W ,d ,M_lsh ,L ,in_umap );

        } else { // we have to construct hypercube Datastructure here
            myPtr = constructCubeDatastructure( DistMetricFlag, cube_ptr , k_hf ,
                                                W , d ,M_cube , probes, in_umap );
        }
        assert(myPtr != nullptr);
        assign_ptr = new ReverseAssignment(myPtr);
    }

    // Update Algorithm - functor

    Updater* update_ptr ;
    if(U_option ==1)
        update_ptr= new kMeans(d);
    else
        update_ptr = new PAM(distMetric);


//========================================================================================
    /*INITIALIZE THE K CLUSTERS*/

    vector <myVector> k_initial_vectors ; //list for the initial clusters

    (*init_ptr)(k , in_umap , k_initial_vectors ); //initialization returns the k initial Centroids

    kClusters allClusters(k  , k_initial_vectors); //initialize k clusters entities with the initial Centroids


//========================================================================================

    vector <myVector> previousStateCentroids;
    vector <myVector> newStateCentroids;

    int emptyClusters;

    clock_t beginTime, stopTime;
    double elapsed_secs_for_Clustering ; //= double(end - begin) / CLOCKS_PER_SEC;
    Assigner* lastAssignWithLloyd_ptr = new LloydAssignment();

    beginTime = clock();
    for (i = 0; i < ITERATIONS ; ++i) {

        bool flagCentroidsEqual;
        previousStateCentroids = allClusters.listOfCentroids();


        (*assign_ptr)(allClusters, in_umap, distMetric ); //ASSIGN


        (*update_ptr)(in_umap, allClusters);            //UPDATE

        newStateCentroids = allClusters.listOfCentroids();
        flagCentroidsEqual = checkIfEqual(previousStateCentroids , newStateCentroids);


        if (flagCentroidsEqual){
            cout << "previous and current Centroids are equal\n";
            cout << "ITERATIONS ACHIEVED = #"<<i<<endl;
            break;
        }

        previousStateCentroids.clear();
        newStateCentroids.clear();

    }
    stopTime = clock();
    elapsed_secs_for_Clustering = double(stopTime - beginTime) / CLOCKS_PER_SEC;


    /* TRICK : Last Assignment will be with Lloyd to be sure that all the points from lsh/hyperCube will be added in the Clusters    */
    (*lastAssignWithLloyd_ptr)(allClusters, in_umap, distMetric ); //ASSIGN

    // allClusters.print_ClustersDatasetSize();

//    allClusters.print_ClustersDatasetSize();

//    vector<double> listClustersSilhouette = Silhouette (in_umap , allClusters , distMetric ,emptyClusters);
//    cout << "Number of empty clusters = "<<emptyClusters<<endl;
//    cout << "ITERATIONS #"<<i<<endl;

//    allClusters.print_allClusters();

//    Write2_OutFile(outFile ,OutFileName , algOptions , DistMetricFlag ,
//                   listClustersSilhouette , allClusters , in_umap ,elapsed_secs_for_Clustering ,completeFlag);

//here free the memory before exit
    delete init_ptr;init_ptr = nullptr;
    delete assign_ptr;assign_ptr = nullptr;
    delete update_ptr;assign_ptr = nullptr;

    return allClusters;

}

