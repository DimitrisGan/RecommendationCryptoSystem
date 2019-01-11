//
// Created by dimitrisgan on 16/11/2018.
//

#ifndef PROJECT2_ASSISTANTFUNCTIONS_H
#define PROJECT2_ASSISTANTFUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>



#include "MyVector.h"
#include "Tweet.h"

//#include "HyperCube.h"
//#include "LSH.h"

class Lsh;
class HyperCube;

/*
#include "AbstractLSH_CUBE.h"
#include "Cluster.h"
*/


using namespace std;

/*
class Lsh;
class HyperCube;
*/




void ReadTweetsInputDat_saveIt(const string &inTweetsDatasetFileName, unordered_map<string, Tweet> &tweets_umap,
                               unordered_multimap<string, string> &userTweetsRelation_ummap, int &P);
void printTweetsIdsForGivenUserId(const string &userId , const unordered_multimap<string, string> &userTweetsRelation_ummap);
void printMultiUMap(const unordered_multimap<string, string> &userTweetsRelation_ummap);
void printTweetsUmap(const unordered_map<string, Tweet> &tweets_umap);

void ReadVaderLexicon_saveIt(const string &inVaderFileName , unordered_map<string ,double> &VaderUmap);
void print_map (const unordered_map<string ,double> &VaderUmap);

void ReadCoinsFile_saveIt(const string &inCoinsFileName , vector<string> &CoinsList , unordered_map<string ,int> &CoinsUmap ); //todo thelei 5h sthlh kai opou den yparxei prwth
void print_map(const unordered_map<string, int> &CoinsUmap) ;


/*

void Write2_OutFile(std::ofstream& outFile ,string &OutFileName , string &algOptions , int &DistMetricFlag ,
                    vector<double> listClustersSilhouette , kClusters &allClusters , unordered_map<string , myVector> &in_umap, double &elapsed_secs_for_Clustering ,int &completeFlag);



AbstractLshCube* constructLshDatastructure(const int &DistMetricFlag ,   Lsh *lsh_ptr , unsigned &k_hf ,
                                           unsigned &W , unsigned &d , long long int &M_lsh ,unsigned &L , unordered_map<string, myVector> &in_umap ) ;

AbstractLshCube* constructCubeDatastructure(const int &DistMetricFlag , HyperCube *cube_ptr , unsigned &k_hf ,
                                            unsigned &W , unsigned &d ,unsigned &M_cube , unsigned int &probes, unordered_map<string, myVector> &in_umap );

*/

void printPairValues (std::pair<unsigned , double > pairValues );

void print_map(unordered_map <string , std::pair<unsigned , double >> myMap); //todo change name

bool checkIfEqual( vector <myVector> &previousStateCentroids , vector <myVector> &newStateCentroids);




void ReadHandleArgms( int& argc,  char**& argv , string &inFileName  , string &configFileName  , string &OutFileName , int &metric_flag ,int &completeFlag);

void ReadInFile_save2umap(const string &inFileName,unordered_map<string, myVector > &umap ,unsigned  int &d );
void ReadCommaTypeFile_save2umap(const string &inFileName,unordered_map<string, myVector > &umap ,unsigned  int &d );
void ReadTabTypeFile_save2umap(const string &inFileName,unordered_map<string, myVector > &umap ,unsigned  int &d );


void ReadConfigFile(const string &configFileName , unsigned  int &k , unsigned  int &k_hf , unsigned  int &L , unsigned int &M_cube , unsigned int &probes ,
                    int &I_option ,int &A_option ,int &U_option ,int& flagInputLsh , string &algOptions);

//=====================================================================

std::vector<std::string> extract_keys(std::unordered_map <std::string, myVector > const& input_map);
void print_keys(std::vector<std::string> keys);
void print_map(unordered_map<string, myVector > umap); //todo change name



//=====================================================================

class InputParser{  // a class for parsing command line arguements and their options
private:
    vector <string> tokens;
public:
    InputParser (int &argc, char **argv){
        for (int i=1; i < argc; ++i)
            this->tokens.emplace_back(argv[i]); // this->tokens.push_back(string(argv[i]));

    }

    const string& getCmdOption(const string &option) const{  //option = flag
        vector<string>::const_iterator itr;
        itr = find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()){ // insure that gives file_path/option after the flag
            return *itr;
        }
        static const string empty_string; //("");
        return empty_string;
    }

    bool cmdOptionExists(const string &option) const{
        return find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }

};




#endif //PROJECT2_ASSISTANTFUNCTIONS_H
