//
// Created by dimitrisgan on 16/11/2018.
//

#include <fstream>
#include <sstream>
#include <cstdlib>

#include "AssistantFunctions.h"


using namespace std;


void ReadCoinsFile_saveIt(const string &inCoinsFileName , vector<string> &CoinsList , unordered_map<string ,int> &CoinsUmap ){


    ifstream inFile;
    inFile.open(inCoinsFileName);
    if (!inFile) {
        cout << "Unable to open inCoinsFile\n";
        exit(1); // terminate with error
    }

    string line;

    int index = 0; //line number
    while (getline(inFile, line, '\n')) {
        int column=0;

        // skip empty lines:
        if (line.empty()) continue;

        if (line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        istringstream iss(line);

        string CoinNameFirstColumn;
        string CoinNameFifthColumn;
        string CoinName;


        iss>>CoinNameFirstColumn;

//        CoinsList.push_back(CoinName); //add the first Column of CoinsFile in the vector

        CoinsUmap[CoinNameFirstColumn] = index;

//        while (iss >> CoinName) {
        while (getline(iss, CoinName, '\t')) {
            if (CoinName.empty() || CoinName == "\t")continue;
            column++;
            if (column == 4){
                CoinNameFifthColumn = CoinName;
            }
            CoinsUmap[CoinName] = index;
        }

        if (column < 5){
            CoinsList.push_back(CoinNameFirstColumn);
        }
        else{
            CoinsList.push_back(CoinNameFifthColumn);

        }


        index++;
    }
    inFile.close();

}



void ReadTweetsInputDat_saveIt(const string &inTweetsDatasetFileName, unordered_map<string, Tweet> &tweets_umap,
                               unordered_multimap<string, string> &userTweetsRelation_ummap, int &P) {
    ifstream inFile;
    inFile.open(inTweetsDatasetFileName);
    if (!inFile) {
        cout << "Unable to open inTweetsDatasetFile\n";
        exit(1); // terminate with error
    }
    P =20; //default value

    string line;
    int flagFirstLine=0;

    while (getline(inFile, line, '\n')) {


        if (line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        // skip empty lines:
        if (line.empty()) continue;



        istringstream iss(line);
        string userId;
        string tweetId;

        iss >> userId;


        if (flagFirstLine==0) {
            if (userId == "P:") {
                flagFirstLine = 1;

                iss >> P;


                continue;

            }
        }
        flagFirstLine=1;

        iss >> tweetId;
//        cout << "userId :"<<userId<<endl;
//        cout << "tweetId :"<<tweetId<<endl;


        userTweetsRelation_ummap.insert(make_pair(userId,tweetId)); //insert in the userTweetsRelation_ummap

        //todo take the remain line which is the tweet and put it in the vector --> ttweet

        string tweetWord;
        Tweet currTweet;

//        while (iss >> tweetWord ){
//        cout <<"TWEET :\n";

//cout <<"Printing TweetId #"<<tweetId<<endl;
        while (getline(iss, tweetWord, '\t') ){
            if (tweetWord.empty() || tweetWord == "\t")continue;
            currTweet.context.push_back(tweetWord);
//            cout <<"tweetWord:" << tweetWord <<endl;
        }

        tweets_umap.insert(make_pair(tweetId,currTweet));
//        tweets_umap[tweetId] = currTweet;


    }
//    printMultiUMap(userTweetsRelation_ummap);
//    printTweetsUmap(tweets_umap);

    inFile.close();



}


void printTweetsUmap(const unordered_map<string, Tweet> &tweets_umap){
    for (auto myPair : tweets_umap){
        cout << "TweetId #"<<myPair.first << " with ";
        cout <<myPair.second;
//        cout <<endl;
    }

}

void printTweetsIdsForGivenUserId(const string &userId , const unordered_multimap<string, string> &userTweetsRelation_ummap){

    auto range =userTweetsRelation_ummap.equal_range(userId);

    for (auto it=range.first;it!=range.second;++it){
        cout << it->first<< " : "<<it->second<<endl;
    }

}

void printMultiUMap(const unordered_multimap<string, string> &userTweetsRelation_ummap){

    vector <string> fixedUsers;
    for (const auto &myPair : userTweetsRelation_ummap){
        bool isPresent = (std::find(fixedUsers.begin(), fixedUsers.end(), myPair.first ) != fixedUsers.end());
        if (isPresent){
            continue;
        }
        cout << "User #"<<myPair.first << "--> Tweets:\t [";
        for (const auto &myPair2 : userTweetsRelation_ummap){
            if (myPair.first == myPair2.first){
                cout << myPair2.second;
                cout << ",";
            }
        }
        cout << "]"<<endl;
        fixedUsers.push_back(myPair.first);
    }

}



void ReadVaderLexicon_saveIt(const string &inVaderFileName , unordered_map<string ,double> &VaderUmap) {

    ifstream inFile;
    inFile.open(inVaderFileName);
    if (!inFile) {
        cout << "Unable to open inVaderFile\n";
        exit(1); // terminate with error
    }

    string line;

    //=-------------------------------------
    while (getline(inFile, line, '\n')) {

        // skip empty lines:
        if (line.empty()) continue;


        istringstream iss(line);
        string VaderWord;
        double score;


        getline(iss, VaderWord, '\t');  // read up-to the first tab (discard tab).
        iss >> score;




        VaderUmap[VaderWord] = score;

    }

    inFile.close();
}





//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
void Write2_OutFile(std::ofstream& outFile ,string &OutFileName , string &algOptions , int &DistMetricFlag ,
                    vector<double> listClustersSilhouette , kClusters &allClusters , unordered_map<string , myVector> &in_umap ,double &elapsed_secs_for_Clustering ,int &completeFlag){

    outFile.open(OutFileName);//erase the content of the output file if already exists

    if(outFile.is_open()) {

        outFile << "\nAlgorithm: "<< algOptions << endl;

        string metricToWrite;
        if (DistMetricFlag == 0){
            metricToWrite = "Euclidean";
        }
        else{
            metricToWrite = "Cosine";
        }

        outFile << "\nMetric: "+metricToWrite <<endl;

        for (auto &clust : allClusters.getClusters()){
            outFile <<"\nCLUSTER-"<<clust->getId() ;
            outFile << "{size: "<<clust->getDatapoints().size()-1 ;
            outFile << " , centroid: ";
            if (algOptions[5] == '1'){ //KMEANS UPDATE
                for (auto &it : clust->getCentroid().getCoords()){
                    outFile << it <<","; //print the item id of the Centroid
                }

            }
            else{ //PAM UPDATE

                for (auto &it : in_umap){
                    if (it.second == clust->getCentroid() ){
                        outFile << it.first; //print the item id of the Centroid
                        break;
                    }
                }
            }
            outFile << "}\n";


        }
        outFile << "\nclustering_time: "<< elapsed_secs_for_Clustering ;
        outFile << "\nSilhouette: ";
        outFile << "[";
        for (auto &s : listClustersSilhouette){
            outFile << s ;
            outFile << "," ;
        }

        double S_total = accumulate( listClustersSilhouette.begin(), listClustersSilhouette.end(), 0.0)/listClustersSilhouette.size();
        outFile << S_total ;
        outFile << "] \n\n";

        if (completeFlag == 1){
            outFile << "--------------------------------------------\n\n";
            for (auto &clust : allClusters.getClusters()){
                outFile <<"\nCLUSTER-"<<clust->getId() ;
                outFile << " {";
                int j=0;
                for (auto& pointId : clust->getDatapoints()){
                    outFile << pointId;
                    j++;
                    if (clust->getDatapoints().size() != j ){
                        outFile<<",";

                    }
                }
                outFile << "} \n";

            }
        }

    }
    else {
        cout << "Could not open Output file: " << OutFileName << endl;
    }
    outFile.close();


}




void print_map(unordered_map <string , std::pair<unsigned , double >> myMap){

    cout << "Printing Triple Map\n";

    for ( auto& id : myMap ) {
        cout<<"[";
        cout << "vecId = "<<id.first <<",";
        cout << "Cluster id = "<< id.second.first <<",";
        cout << "dist = "<< id.second.second <<",";
        cout<<"]\n";
    }
}

void printPairValues (std::pair<unsigned , double > pairValues ){
    cout<<"[";
    cout << "Cluster id = "<< pairValues.first <<",";
    cout << "dist = "<< pairValues.second <<",";
    cout<<"]\n";
}




bool checkIfEqual(vector <myVector> &previousStateCentroids , vector <myVector> &newStateCentroids) {

    assert(previousStateCentroids.size() == newStateCentroids.size());
    for (int i =0 ; i< previousStateCentroids.size() ;i++){
        if (previousStateCentroids.at(i).getCoords() != newStateCentroids.at(i).getCoords()){
            return false;
        }
    }


    return true; //means that they are the same
}


//unsigned k_hf =  4;
//unsigned L = 2;
//auto TableSize = static_cast<unsigned int>(pow(2, k_hf));



void ReadConfigFileLsh(const string &configFileName, unsigned int &k_hf, unsigned int &L) {

    ifstream configFile;
    configFile.open(configFileName);

    if (!configFile) {
        cout << "Unable to open config file for lsh";
        exit(1); // terminate with error
    }
    string line;

    //DEFAULT VALUES
    k_hf = 4;
    L = 5;

    while (getline(configFile, line, '\n')) {

        // skip empty lines:
        if (line.empty()) continue;
        if (line[0] == '#' ){ //comments
            continue;
        }
        std::stringstream   linestream(line);
        istringstream iss(line);
        string type;
        unsigned int number;

        getline(iss , type , ':');

        if (type == "L" ) {
            iss >> L;
        }
        if (type == "k_hf" ) {
            iss >> k_hf;
        }



    }

    configFile.close();


}



void ReadConfigFile(const string &configFileName, unsigned int &k, unsigned int &k_hf, unsigned int &L, unsigned int &M_cube,
                    unsigned int &probes, int &I_option, int &A_option, int &U_option, int &flagInputLsh, string &algOptions,
                    int &metricOption, int &SilhouetteOption, string &outputFileName, int &completeOption,
                    int &MAX_ITERATIONS_VAR) {

    ifstream configFile;
    configFile.open(configFileName);

    if (!configFile) {
        cout << "Unable to open config file";
        exit(1); // terminate with error
    }
    string line;
    int flagValidConfigFile=0;
    int flagAlgorOtionsGiven=0;
    int flagRevAssignOtionsGiven=0;

    int flagDistanceMetricGiven =0;
    int flagSilhouetteOptionGiven =0;

    int flagOutputOptionGiven =0;
    int flagOutputFileNameOptionGiven =0;
    int flagCompleteOptionGiven =0;




    //Default Initialiazation
    MAX_ITERATIONS_VAR = 20;
    completeOption=0;
    metricOption=0;
    SilhouetteOption=0;
    k_hf = 4;
    L = 5;
    M_cube = std::numeric_limits<unsigned  int>::max();
    probes=2;
    I_option = 1; //algorithm options
    A_option = 1;
    U_option = 1;
    flagInputLsh =1; //default lsh

    string distMetricString ;
    string SilhouetteOptionString ;
    string completeOptionString ;

    string flagOutputOptionString ;

    algOptions = "I1A1U1" ;
    string reverseAssignmentOption ;
    while (getline(configFile, line, '\n')) {

        // skip empty lines:
        if (line.empty()) continue;
        std::stringstream   linestream(line);
        istringstream iss(line);
        string type;
        unsigned int number;

        getline(iss , type , ':');

        if (type == "MAX_ITERATIONS" ) {
            iss >> MAX_ITERATIONS_VAR;
        }
        if (type == "complete" ) {
            iss >> completeOptionString;
            flagCompleteOptionGiven = 1;
        }
        if (type == "Output_file_name" ){
            iss>>outputFileName;
            flagOutputFileNameOptionGiven =1;

        }
        if (type == "Output" ){
            iss>>flagOutputOptionString;
            flagOutputOptionGiven =1;

        }
        if (type == "Silhouette" ){
            iss>>SilhouetteOptionString;
            flagSilhouetteOptionGiven =1;

        }
        if (type == "distance_metric" ){
            iss>>distMetricString;
            flagDistanceMetricGiven =1;

        }
        if (type == "number_of_clusters" ){
            iss>>number;

            flagValidConfigFile=1;
            k = number;
        }
        if (type == "number_of_hash_functions" ){
            iss>>number;

            k_hf = number;
        }
        if (type == "number_of_hash_tables" ){
            iss>>number;

            L = number;
        }
        if (type == "number_of_total_points_to_check_in_hyperCube" ){
            iss>>number;

            M_cube = number;
        }
        if (type == "number_of_probes" ){
            iss>>number;

            probes = number;
        }
        if (type == "Algorithm" ){
            iss>>algOptions;
            flagAlgorOtionsGiven =1;
        }
        if (type == "Reverse_Assignment_type" ){
            iss>>reverseAssignmentOption;
            flagRevAssignOtionsGiven=1;
        }

        if (type[0] == '#' ){ //comments
            continue;
        }

    }



    if (flagValidConfigFile == 0 ){
        cout << "ERROR : NOT VALID CONFIG FILE -> NOT GIVEN NUMBER OF CLUSTERS";
        exit(1);
    }

    if (flagCompleteOptionGiven){
        if (completeOptionString == "yes"){
            completeOption=1;
        }

    }

    if (flagOutputOptionString=="yes" ){
        if(flagOutputFileNameOptionGiven ==0  || (flagSilhouetteOptionGiven ==0 || SilhouetteOptionString == "no") ) { //if one of these 2 is zero
            cout << "ERROR : NOT VALID CONFIG FILE -> NOT GIVEN OUTPUT FILE NAME OR SILHOUETTE OPTION \"YES\" ";
            exit(1);
        }
    }




    if (flagSilhouetteOptionGiven ){
        if (SilhouetteOptionString == "yes"){
            SilhouetteOption = 1;
        }
    }
    if (flagDistanceMetricGiven){
        if (distMetricString == "cosine"){
            metricOption = 1;
        }
    }

    if (flagAlgorOtionsGiven){
        cout << "algOptions = "<<algOptions<<endl;

        I_option = (int)algOptions.at(1) - '0';
        A_option = (int)algOptions.at(3) - '0';
        U_option = (int)algOptions.at(5) - '0';
//        cout << "I_option = " <<I_option << endl;
//        cout << "A_option = " <<A_option << endl;
//        cout << "U_option = " <<U_option << endl;


        if (A_option==3 && flagRevAssignOtionsGiven==1){
            if(reverseAssignmentOption == "HYPERCUBE" || reverseAssignmentOption == "hypercube" || reverseAssignmentOption == "cube"){
                flagInputLsh =0; //cube option has been chosen for assign
            }
        }


        if (I_option <1 || I_option > 2){
            cout << "ERROR : NOT VALID INITIALIZATION ALGORITHM OPTION";
            exit(1);
        }
        if (A_option <1 || A_option > 3){
            cout << "ERROR : NOT VALID ASSIGN ALGORITHM OPTION";
            exit(1);
        }
        if (U_option <1 || U_option > 2){
            cout << "ERROR : NOT VALID UPDATE ALGORITHM OPTION";
            exit(1);
        }



    }


    configFile.close();

}




void ReadInFile_save2umap(const string &inFileName,unordered_map<string, myVector > &umap ,unsigned  int &d ){

    ifstream inFile;
    inFile.open(inFileName);
    if (!inFile) {
        cout << "Unable to open Dataset from project2\n";
        exit(1); // terminate with error
    }

    string line;
    bool flagInputCommaType = false;

    getline(inFile, line, '\n');

//    cout <<"line = " << line<<endl;


    for ( auto &str  : line ) {
        if (str == ','){
            flagInputCommaType= true;
            break;
        }
    }

    inFile.close();

    if (flagInputCommaType){ // the input is separated by comma
        ReadCommaTypeFile_save2umap(inFileName, umap, d );
    }
    else{
        ReadTabTypeFile_save2umap(inFileName, umap, d );
    }
    inFile.close();

}


//=========================================================



void ReadCommaTypeFile_save2umap(const string &inFileName,unordered_map<string, myVector > &umap ,unsigned  int &d ){


    ifstream inFile;
    inFile.open(inFileName);
    if (!inFile) {
        cout << "Unable open Dataset from project1\n";
        exit(1); // terminate with error
    }
    string line;

    myVector values;
    std::vector<double> temp;
    while (getline(inFile, line, '\n')) {

        // skip empty lines:
        if (line.empty()) continue;

        std::stringstream   linestream(line);


        istringstream iss(line);
        string item_id;

        getline(iss , item_id , ',');

        double coord;
        string str_coord;
        temp.clear();
        while (getline(iss , str_coord , ',')) {
            coord = stod(str_coord);
            temp.push_back(coord);
        }
        values.setCoords(temp);

        umap[item_id]=values;

    }
    inFile.close();
    d = static_cast<unsigned int>(values.getCoords().size());
}



void ReadTabTypeFile_save2umap(const string &inFileName,unordered_map<string, myVector > &umap ,unsigned  int &d ){


    ifstream inFile;
    inFile.open(inFileName);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string line;

    myVector values;
    std::vector<double> temp;
    unsigned  int n =0;
    while (getline(inFile, line, '\n')) {

        // skip empty lines:
        if (line.empty()) continue;

        istringstream iss(line);
        string item_id;

        iss>>item_id;

        double coord;
        temp.clear();
        values.setCoords(temp);
        while (iss >> coord) {
            temp.push_back(coord);
        }
        values.setCoords(temp);

        umap[item_id]=values;

        n++;
    }
    inFile.close();
    d = static_cast<unsigned int>(values.getCoords().size());
}



void ReadHandleArgms( int& argc,  char**& argv , string &inFileName  , string &configFileName  , string &OutFileName , int &metric_flag ,int &completeFlag){

    InputParser input(argc, argv);

    if(input.cmdOptionExists("-i"))
    {
        const string &arg_str = input.getCmdOption("-i");
        inFileName = arg_str;
    }
    else
    {
        cout<<"->Please enter input file name:"<<endl;
        cin >> inFileName;
    }


    if(input.cmdOptionExists("-c"))
    {
        const string &arg_str = input.getCmdOption("-c");
        configFileName = arg_str;
    }
    else
    {
        cout<<"->Please enter configuration file name:"<<endl;
        cin >> configFileName;
    }


    if(input.cmdOptionExists("-o"))
    {
        const string &arg_str = input.getCmdOption("-o");
        OutFileName = arg_str;
    }
    else
    {
        cout<<"->Please enter output file name:"<<endl;
        cin >> OutFileName;
    }

//    Euclidean ή Cosine

    if(input.cmdOptionExists("-d"))
    {
        const string &arg_str = input.getCmdOption("-d");
        const string &metricName = arg_str;
        if (metricName == "Euclidean" || metricName == "euclidean" || metricName == "eucl")
        {
//               metric_flag =0;
        }
        else if (metricName == "Cosine" || metricName == "cosine" || metricName == "cos"){
            metric_flag = 1;
        }

    }
    else {
        cout << "->You forgot to choose distance metric. Euclidean was set by default." << endl;

    }

    if(input.cmdOptionExists("-completeOption"))
    {
        completeFlag =1;
    }


}

//=========================================================


std::vector<std::string> extract_keys(std::unordered_map <std::string, myVector > const& input_map) {
    std::vector<std::string> retval;
    retval.reserve(input_map.size());
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}

//=========================================================

void print_map(unordered_map<string, myVector > umap) {


    for (auto &mypair : umap)
    {

//        cout << "[MAP KEY] : " <<mypair.first << "\n"; //<< mypair.second <<endl;
        cout << "[ " <<mypair.first << " ] : \t"  ;
        mypair.second.print_vector();

    }
}

//=========================================================

void print_keys(std::vector<std::string> keys){
    cout << " keys:";
    for (auto &key : keys )
    {
        cout << "\t" << key;
    }
    cout << endl;

}

//=========================================================


void print_map(const unordered_map<string, int> &CoinsUmap) {

    for (const auto &key : CoinsUmap){
        cout << key.first << " & index =" << key.second <<endl;
    }

}

void print_map (const unordered_map<string ,float> &VaderUmap){

    for (auto key : VaderUmap){
        cout << key.first << " = " << key.second <<endl;
    }

}