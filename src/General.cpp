#include "General.hpp"
#include <array>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdlib>      // std::rand, std::srand
#include <time.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>


// positive_modulo returns the remainder from the division i/n if i>=n, else it returns i
 int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}



/*
findNeighborhood returns the a vector holding the cell indecies (starting from 1) of the neighbor cell of "aPosition"
by the following order : {up-left, up, up-right, left, stay, right, down-left, down, downright}, so for example if
aPosition = 7, then findNeighborhood returns { 1, 2, 3, 6, 7, 8, 11, 12, 13}, and if aPosition = 25, findNeighborhood
returns { 19, 20, 16, 24, 25, 21, 4, 5, 1};

     1     2     3     4     5
     6     7     8     9    10
    11    12    13    14    15
    16    17    18    19    20
    21    22    23    24    25
*/
 std::vector<int> findNeighborhood(int aPosition, int observationRange, int environmentSize, int columns)
{
    int initial_cell                     = aPosition;
    int current_cell                     = 0;
    int neighbor_dim                     = observationRange*2;
    int center                           = observationRange;
    int neighbor_matrix[neighbor_dim + 1][neighbor_dim + 1];

    for(int j = 0; j <= neighbor_dim ; j++){
     for(int k = 0; k <= neighbor_dim ; k++){
			neighbor_matrix[j][k] = 1;
     }
	}

    neighbor_matrix[center][center]      = initial_cell  ;
    int right, left, up, down;

    //--------------------------------------------
    current_cell                = initial_cell;
    for (int range  = 1 ; range <= observationRange; range ++){
        if ((current_cell%columns) == 0)
            {right                                = current_cell+1-columns;}
        else
            {right                                = current_cell+1;}
        neighbor_matrix[center][center + range]   = right;
        current_cell                              = right;
    }
    //--------------------------------------------
    current_cell                                  = initial_cell;
    for (int range  = 1 ; range <= observationRange; range ++){
        if ((current_cell%columns) == 1)
            {left                                  = current_cell-1+columns;
            }
        else
            {
                left                                  = current_cell-1;
            }
        neighbor_matrix[center][center - range]   = left;
        current_cell                              = left;
    }
    //--------------------------------------------

    for (int i=0; i <= neighbor_dim; i++){
        current_cell                              = neighbor_matrix[center][i];
        for (int range  = 1 ; range <= observationRange; range ++){
            int up;
            int up1 = (current_cell -1);
            int up2 = up1 - columns;
            //up = (up2%(environmentSize) +1);
            up = positive_modulo(up2, environmentSize) + 1;
            neighbor_matrix[center-range][i]      = up;
            current_cell                          = up;
        }
    }
    //--------------------------------------------
    for (int i=0; i <= neighbor_dim; i++){
        current_cell                              = neighbor_matrix[center][i];
        for (int range  = 1 ; range <= observationRange; range ++){
            down                                  =  (((current_cell -1) + columns)%environmentSize) + 1;
            neighbor_matrix[center+range][i]      = down;
            current_cell                          = down;
        }
    }
    //--------------------------------------------
    std::vector<int> cellDescription;
    //cout << "-----"<< endl;
    for(int j = 0; j <= neighbor_dim ; j++){
     for(int k = 0; k <= neighbor_dim ; k++){
            //cout << "j : " << j << " and k : " << k << endl;
            //cout << neighbor_matrix[j][k] << endl;

            try{
			if (neighbor_matrix[j][k] > environmentSize || neighbor_matrix[j][k] < 1){
                throw 222;
			}
            }catch(int z){
            std::cout<<"Cannot breach environment boundary "<< neighbor_matrix[j][k]<<", ERROR NUMBER: "<< z<<std::endl;
            }
			cellDescription.push_back(neighbor_matrix[j][k]);
		 }
	}
	//printVector(cellDescription);
	return cellDescription;
}

/*
getNewLocation returns the cell indecies (starting from 1) reached from "currentLocation" after taking action "actionTaken"
Actions {1      , 2 , 3       , 4   , 5   , 6    , 7        , 8   ,         9}
map to  {up-left, up, up-right, left, stay, right, down-left, down, downright}
so for example if aPosition = 7, and actionTaken is 6 then getNewLocation returns 11
     1     2     3     4     5
     6     7     8     9    10
    11    12    13    14    15
    16    17    18    19    20
    21    22    23    24    25
*/
int getNewLocation(int currentLocation, int actionTaken, int columns, int environmentSize){
    std::vector<int> adjacentCells  = findNeighborhood(currentLocation,  1,  environmentSize,  columns);
    int newLocation                 = adjacentCells.at(actionTaken-1);
    try{
    if (newLocation < 0 || newLocation > environmentSize){
        throw 102;
    }
    }catch(int z){
    std::cout<<"Environment boundary breached, ERROR NUMBER: "<< z<<std::endl;
    }
    return newLocation;
}
void printVector (std::vector<int> v){
    std::cout << "Printing vector:" << std::endl;
    for (int i=0; i<v.size();i++){
    std::cout << v.at(i) << " ";
}
std::cout << "\n" ;
std::cout << "End of print" << std::endl;
}
void printVectorD (std::vector<double> v){
    std::cout << "Printing vector:" << std::endl;
    for (int i=0; i<v.size();i++){
    std::cout << v.at(i) << " ";
}
std::cout << "\n" ;
std::cout << "End of print" << std::endl;
}
void printArray (double* anArray, int arraySize){
    std::cout << "Printing array:" << std::endl;
    for (int i=0; i<arraySize ;i++){
    std::cout << anArray[i] << " ";
}
std::cout<< "\n" << std::endl;
std::cout << "End of print" << std::endl;
}

double findMaxValue(std::vector<double> rewards){
    double maxValue = rewards.at(0);
    try{
    for (int i=1; i<rewards.size();i++){
        if (rewards.at(i) > maxValue){
            maxValue = rewards.at(i);
        }
    }
    if (abs(maxValue) > 1){
        throw 103;
    }
    }catch(int z){
    std::cout<<"Max reward cannot be greater than 1, ERROR NUMBER: "<< z<<std::endl;
    }
    return maxValue;
    //int indexOfBiggest = std::distance(std::begin(lastObservationReward), biggest);
}

double findMinValue(std::vector<double> rewards){
    double minValue = rewards.at(0);
    try{
    for (int i=1; i<rewards.size();i++){
        if (rewards.at(i) < minValue){
            minValue = rewards.at(i);
        }
    }
    if (abs(minValue) > 1){
        throw 107;
    }
    }catch(int z){
    std::cout<<"Min reward cannot be less than 1, ERROR NUMBER: "<< z<<std::endl;
    }
    return minValue;
    //int indexOfBiggest = std::distance(std::begin(lastObservationReward), biggest);
}

// returns the indecies (starting from 0) where of the occurence of the maximum value  of a vector
std::vector<int> findMaxIndecies(std::vector<double> rewards){
    double maxValue = findMaxValue(rewards);
    std::vector<int> maxIndecies;
    //printVectorD(rewards);
    try{
    for (int i=0; i<rewards.size();i++){
        if (rewards.at(i) == maxValue){
            maxIndecies.push_back(i);
        }
    }
    if (maxIndecies.empty()){
            throw 111;
    }
    }catch(int z){
    std::cout<<"There must be at least one maximum in the vector, ERROR NUMBER: "<< z<<std::endl;
    }
    return maxIndecies;
}

// returns the indecies where of the occurence of the minimum value  of a vector
std::vector<int> findMinIndecies(std::vector<double> rewards){
    double minValue = findMinValue(rewards);
    std::vector<int> minIndecies;
    //printVectorD(rewards);
    try{
    for (int i=0; i<rewards.size();i++){
        if (rewards.at(i) == minValue){
            minIndecies.push_back(i);
        }
    }
    if (minIndecies.empty()){
            throw 111;
    }
    }catch(int z){
    std::cout<<"There must be at least one maximum in the vector, ERROR NUMBER: "<< z<<std::endl;
    }
    return minIndecies;
}

std::vector<int> findMaxIndecies(double* rewards, int arraySize){
    double maxValue = rewards[firstMaxIndex(rewards, arraySize)];
    std::vector<int> maxIndecies;
    //printVectorD(rewards);
    try{
    for (int i=0; i<arraySize;i++){
        if (rewards[i] == maxValue){
            maxIndecies.push_back(i);
        }
    }
    if (maxIndecies.empty()){
            throw 1989;
    }
    }catch(int z){
    std::cout<<"There must be at least one maximum in the array, ERROR NUMBER: "<< z<<std::endl;
    }
    return maxIndecies;
}


// given aPosition findCoordinates returns its x, y cartesian coordinates
coordinates findCoordinates(int aPosition, int rows){
    coordinates xyCoord;
    double div;
    div = (double)aPosition/(double)rows;
    //int anX                  = ceil(aPosition/rows);
    xyCoord.xCoordinate      = (int) ceil(div);
    xyCoord.yCoordinate      = aPosition - (rows*(xyCoord.xCoordinate - 1));
    return xyCoord;
};

// findDistance returns the chebychev Distance or the minimum number of hopes between a source and target points (coordinates)
int findDistance(int sourcePosition, int tragetPosition, int rows){
    int distance;
    coordinates sourceCoord, targetCoord;
    sourceCoord = findCoordinates(sourcePosition, rows);
    targetCoord = findCoordinates(tragetPosition, rows);
    int arg1, arg2;
    arg1        = abs(targetCoord.xCoordinate-sourceCoord.xCoordinate);
    arg2        = abs(targetCoord.yCoordinate-sourceCoord.yCoordinate);
    distance    =  std::min(std::max(arg1,arg2),std::max(rows-arg1,rows-arg2));
    //distance2   = positive_modulo(distance,ceil(rows/2));
    if (distance > floor(rows/2)){
        distance = rows-distance;
    }
    return distance;
}
//int chebychevDistance(int pointA, int pointB){
//    distance = max(abs(x1-x2),abs(y2-y1));
//}

// starting at a sourcePosition, approachPosition returns the appropriate action which gets you closer to a targetPosition
int approachPosition(int targetPosition, int sourcePosition, int columns){

int action, row_action, col_action, midDistance, sourceXCood, sourceYCood, targetXCood, targetYCood, distanceToTargetRow, distanceToTargetColumn;
coordinates sourceCoordinates    	= findCoordinates(sourcePosition, columns);
coordinates targetCoordinates  		= findCoordinates(targetPosition, columns);
sourceXCood                         = sourceCoordinates.xCoordinate;
sourceYCood                         = sourceCoordinates.yCoordinate;
targetXCood                         = targetCoordinates.xCoordinate;
targetYCood                         = targetCoordinates.yCoordinate;
midDistance                         = floor(columns/2);
distanceToTargetRow                 = abs(sourceXCood-targetXCood) ;
distanceToTargetColumn              = abs(sourceYCood-targetYCood) ;


if      (sourceXCood < targetXCood){
    if  (distanceToTargetRow <= midDistance)
        {row_action = 8 ;} // move down}
    else                   //(distanceToTargetRow > midDistance)
        {row_action = 2 ;} // move up  }
    }
else if (sourceXCood > targetXCood) {
    if  (distanceToTargetRow <= midDistance)
        {row_action = 2  ;} // move up
    else                    //(distanceToTargetRow > midDistance)
        {row_action = 8  ;} // move down
    }
else if (sourceXCood == targetXCood)
        {row_action = 5  ;} // stay



if     (sourceYCood < targetYCood) {
    if (distanceToTargetColumn <= midDistance)
        {col_action = 6  ;} // move right
    else                    //(distanceToTargetColumn > midDistance)
        {col_action = 4  ;} // move left
    }
else if  (sourceYCood > targetYCood) {
    if (distanceToTargetColumn <= midDistance)
        {col_action = 4  ;} // move left
    else                    // (distanceToTargetColumn > midDistance)
        {col_action = 6  ;} // move right
    }
else if  (sourceYCood == targetYCood)
        {col_action = 5  ;} // stay



if    (row_action == 5  && col_action  == 5)
    {action = 5 ;} // stay
else if (  row_action == 2  && col_action  == 5)
    {action = 2 ;} // move up
else if (  row_action == 5  && col_action  == 6)
    {action = 6 ;} // move right
else if (  row_action == 8  && col_action  == 5)
    {action = 8 ;} // move down
else if (  row_action == 5  && col_action  == 4)
    {action = 4 ;} // move left
else if (  row_action == 2  && col_action  == 6)
    {action = 3 ;} // move up right
else if (  row_action == 2  && col_action  == 4)
    {action = 1 ;} // move up left
else if (  row_action == 8  && col_action  == 6)
    {action = 9 ;} // move down  right
else if (  row_action == 8  && col_action  == 4)
    {action = 7 ;} // move down left

return action;

}

// isNeighborTo returns true if the locations of positionA and positionB are contained in the same
// range of 1 Moore neighborhood given an environment of size environmentSize with a number of "columns"
bool isNeighborTo(int positionA, int positionB, int environmentSize, int columns){
    std::vector<int> positionANeighborCells  = findNeighborhood(positionA,  1,  environmentSize,  columns);
    bool isPresent = (std::find(positionANeighborCells.begin(), positionANeighborCells.end(), positionB) != positionANeighborCells.end());
    return isPresent;
}
int firstMaxIndex(std::vector<double> rewards){
    double maxValue = rewards.at(0);
    int index = 0;
    for (int i=0; i<rewards.size();i++){
    if (rewards.at(i) > maxValue){
        maxValue = rewards.at(i);
        index = i;
    }
    }
return index;
}

int firstMaxIndex(double *anArray, int arraySize){
    double maxValue = -1.0;
    int index;
    for (int i=0; i<arraySize;i++){
        try{ if(anArray[i] > 1.0) throw 6565;} catch(int er){std::cout<<" Fake reward cannot be greater than 1 "<<std::endl;}
        if (anArray[i] > maxValue){
            maxValue = anArray[i];
            index = i;
        }
    }
return index;
}

// randomly permutes/re-arranges a vector of integers from 1, 2, 3, ..., vectorSize
std::vector<int> generateRandomPermutation(int arraySize){
    std::vector<int> myvector;
    // set some values:
    for (int i=1; i<=arraySize; ++i) {
        myvector.push_back(i);
    }
    // using built-in random generator:
    std::random_shuffle (myvector.begin(), myvector.end());
    return myvector;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

// to initaialize the elements of a 2D array ta a "value"
void initializeMatrix(double** aMatrix, int xDim, int yDim, int value){
    for (int R = 0; R < yDim; R++){
        for (int C = 0; C < xDim; C++){
           aMatrix[R][C] = value;
        }
    }
}


void initializeArray(double *anArray, int dim, double value){
    for (int R = 0; R < dim; R++){
        anArray[R] = value;
    }
}

void initializeArray(int *anArray, int dim, int value){
    for (int R = 0; R < dim; R++){
        anArray[R] = value;
    }
}
// to output on the console the elements of a 2D array
void printMatrix(double** aMatrix, int xDim, int yDim){
  for (int R = 0; R < yDim; R++){
    for (int C = 0; C < xDim; C++){
       std::cout<< aMatrix[R][C];
    }
    std::cout<<" "<<std::endl;
  }
}

// returns the mean of the values of all elements in a vector
double CalculateMean(std::vector<double> aVector)
{
    double sum  = 0;
    int vSize   = aVector.size();
    for(int i = 0; i < vSize; i++)
        sum += aVector.at(i);
    return (sum / (double)vSize);
}

// returns the sum of the values of all elements in a vector
double CalculateSum(std::vector<double> aVector)
{
    double sum  = 0;
    int vSize   = aVector.size();
    for(int i = 0; i < vSize; i++)
        sum += aVector.at(i);
    return sum;
}

// returns the variance of the values of all elements in a vector
double CalculateVariance(std::vector<double> aVector)
{
    double mean = CalculateMean(aVector);
    int vSize   = aVector.size();
    double temp = 0;
    for(int i = 0; i < vSize; i++)
    {
         temp += (aVector.at(i) - mean) * (aVector.at(i) - mean) ;
    }
    return temp / (double)(vSize-1);
}

// FUNCTION: kolmogorov.m
// DATE: 9th Feb 2005
// AUTHOR: Stephen Faul (stephenf@rennes.ucc.ie)
//
// Function for estimating the Kolmogorov Complexity as per:
// "Easily Calculable Measure for the Complexity of Spatiotemporal Patterns"
// by F Kaspar and HG Schuster, Physical Review A, vol 36, num 2 pg 842
//
// Input is a digital string, so conversion from signal to a digital stream
// must be carried out a priori a la Lempel and Ziv (IEEE trans inf theory it-22, 75 (1976),
// h(n)=c(n)/b(n) where c(n) is the kolmogorov complexity
// and h(n) is a normalised measure of complexity.

// returns an approximation of the kolmogorov complexity of a string pattern using the Lempel-Ziv complexity model
double kolmogorov(std::string pattern, bool normalized){
                                                     /*
int n       =pattern.length();
int c       =1;
int l       =1;
int i       =0;
int k       =0;
int k_max   =0;
int stop    =0;
*/

int n       =pattern.length();
int c       =1;
int l       =1;
int i       =0;
int k       =1;
int k_max   =1;
int stop    =0;


while (stop==0){
	if (pattern.at(i+k-1)!=pattern.at(l+k-1)){
        if (k>k_max){
            k_max=k;
        }
        i=i+1;

        if (i==l){
            c=c+1;
            l=l+k_max;
            if (l+1>n){ //
                stop=1;
				}
            else{
                i=0;
                k=1;
                k_max=1;
            }
        }
        else{
            k=1;
        }
	}
	else{
        k=k+1;

        if (l+k>n){
            c=c+1;
            stop=1;
        }
	}
}

double b           = (double) n/std::log2(n); /// h(n)=c(n)/b(n) where c(n) is the kolmogorov complexity
double complexity  = (double) c/b;            /// and h(n) is a normalised measure of complexity.
if (normalized){
	return complexity;
	}
else{
	return c;
    }
}

double kolmogorov2(std::vector<std::string> pattern, bool normalized){

int n       =pattern.size();
int c       =1;
int l       =1;
int i       =0;
int k       =1;
int k_max   =1;
int stop    =0;


while (stop==0){
	if (pattern.at(i+k-1)!=pattern.at(l+k-1)){
        if (k>k_max){
            k_max=k;
        }
        i=i+1;

        if (i==l){
            c=c+1;
            l=l+k_max;
            if (l+1>n){ //
                stop=1;
				}
            else{
                i=0;
                k=1;
                k_max=1;
            }
        }
        else{
            k=1;
        }
	}
	else{
        k=k+1;

        if (l+k>n){
            c=c+1;
            stop=1;
        }
	}
}

double b           = (double) n/std::log2(n); /// h(n)=c(n)/b(n) where c(n) is the kolmogorov complexity
double complexity  = (double) c/b;            /// and h(n) is a normalised measure of complexity.
if (normalized){
	return complexity;
	}
else{
	return c;
    }
}



// isUnique returns TRUE if all the elements in a vector have the same value and FALSE otherwise
// For example isUnique({3,3,3,3}) returns true while isUnique({3,1,3,3} returns false
bool isUnique(std::vector<int> str){
    bool uniqueStr = true;
    for(int i=0; i<str.size()-1; i++)
    {
      if(str.at(i) != str.at(i+1)){
           uniqueStr = false;
           break;
      }
    }
return uniqueStr;
}

// readPatternsFromFile opens a txt file and reads the data in it, and then saves this data in a vector and returns it
std::vector<std::vector<int> > readPatternsFromFile(std::string filename){
    std::vector<std::vector<int> > data;
    std::ifstream file;//(filename);// file path
    file.open(filename);
    std::string line;
    while (getline(file, line))
    {
        data.push_back(std::vector<int>());
        std::istringstream ss(line);
        int value;
        while (ss >> value)
        {
            data.back().push_back(value);
        }
    }
    return data;
    file.close();
}


// given a 2D vector, getThisIterationPattern returns the data stored in vector[some index][DATA]
std::vector<int> getThisIterationPattern(int iteration, std::vector<std::vector<int>> listOfPatterns){

    std::vector<int>currentPattern;
    int pattern_length = listOfPatterns[1].size();
        for (int x = 0; x < pattern_length; x++)
        {
           currentPattern.push_back(listOfPatterns[iteration][x]);
        }
    return currentPattern;
}

// given a 2D vector, getThisIterationPattern returns the data stored in vector[some index][DATA]
std::vector<int> getThisIterationPosition(int iteration, std::vector<std::vector<int>> listOfPatterns){

    std::vector<int>currentPattern;
    int pattern_length = listOfPatterns[1].size();
        for (int x = 0; x < pattern_length; x++)
        {
           currentPattern.push_back(listOfPatterns[iteration][x]);
        }
    return currentPattern;
}

void print2DVector(std::vector<std::vector<int> >  aVector){
    for (int y = 0; y < aVector.size(); y++)
    {
        for (int x = 0; x < aVector[y].size(); x++)
        {
            std::cout<<aVector[y][x]<< " ";
        }
        std::cout << std::endl;
    }
}

// modifies a given pattern and returns the modified version
std::vector<int> getAlternativePattern(std::vector<int> aPattern){
    std::vector<int>alternativePattern;
    int add = rand()%8 +1;
    for (int x = 0; x < aPattern.size(); x++)
        {
           alternativePattern.push_back((aPattern.at(x)+add)%9+1);
        }
    return  alternativePattern;
}

// Given a binary tree with a number of nodes = nbrOfNodesInTree, getNumberOfLeaves returns
// the number of leaves in this tree
int getNumberOfLeaves(int nbrOfNodesInTree){
    double leafNodes  = (nbrOfNodesInTree+1)/2;
    if ( leafNodes - (int)leafNodes > 0.0 ){
        leafNodes++;
    }
    return leafNodes;
}

// Given a binary tree with a number of nodes = nbrOfNodesInTree, getNumberOfInternalNodes returns
// the number of internal nodes (non-leaf nodes) in this tree
int getNumberOfInternalNodes(int nbrOfNodesInTree){
    int leafNodes       = getNumberOfLeaves(nbrOfNodesInTree);
    int internalNodes   = nbrOfNodesInTree - leafNodes;
    return internalNodes;
}

// Given a binary tree with a number of nodes = nbrOfNodesInTree, childrenNotComplete returns
// True if anIndex (OF A NODE) is not has no children (leaf node) or if it has only one child (node not full)
// check the link "http://courses.cs.vt.edu/~cs3114/Fall09/wmcquain/Notes/T03a.BinaryTreeTheorems.pdf" for more details
bool childrenNotComplete(int nbrOfNodesInTree, int anIndex){
    bool incompleteTree = false;
    int  internalNodes  = getNumberOfInternalNodes(nbrOfNodesInTree);
    double leafNodes    = ((double)nbrOfNodesInTree+1.0)/2.0;
    if (anIndex > internalNodes){ //This index is a leaf so I consider it as incomplete
        incompleteTree = true;
    }
    else if ((anIndex == internalNodes)&&(leafNodes - (int)(leafNodes) > 0.0)){
        incompleteTree = true;
    }
    return incompleteTree;
}


int findMaxVal(std::vector<int> rewards){
    int maxValue = rewards.at(0);

    for (int i=1; i<rewards.size();i++){
        if (rewards.at(i) > maxValue){
            maxValue = rewards.at(i);
        }
    }
    return maxValue;
    //int indexOfBiggest = std::distance(std::begin(lastObservationReward), biggest);
}

int findMinVal(std::vector<int> rewards){
    int minValue = rewards.at(0);

    for (int i=1; i<rewards.size();i++){
        if (rewards.at(i) < minValue){
            minValue = rewards.at(i);
        }
    }
    return minValue;
}

double generateRandomNumber(){
    double fMin = -1.0;
    double fMax =  1.0;

    double randomNumber = (double)rand() / RAND_MAX;
    return fMin + randomNumber * (fMax - fMin);

    return randomNumber;
}

void saveCoordinatesToFile(std::vector<Agent*>* setOfAgents, int columns){

        ofstream myPlottingDatafile;
        myPlottingDatafile.open("plot.txt", ios::app);

        int tempPosition;
        coordinates xyCoord;
        for (int agentIndex = 0; agentIndex < setOfAgents->size(); agentIndex++)
        {
            tempPosition    = setOfAgents->at(agentIndex)->getPosition();
            xyCoord         = findCoordinates(tempPosition, columns);
            myPlottingDatafile << xyCoord.xCoordinate <<  std::setw(3)  << xyCoord.yCoordinate << endl;
        }

        myPlottingDatafile.close();
}

void saveArrayToFile(double* rewardArray, int rowCount, int colCount)
{
    ofstream outputfile;
    outputfile.open("rewardArray.txt");
    int totalCount = 0;
    for (int counter = 0; counter < rowCount; counter ++)
        {
            for (int index= 0; index < colCount; index++){
                outputfile << rewardArray[totalCount]<<" ";   //Space between each character
                totalCount++;
            }
            outputfile<<endl;                           //New line for each row
        }

        outputfile.close();
}

void appendArrayToFile(double* rewardArray, int rowCount, int colCount)
{
    ofstream outputfile;
    //if (outputfile.is_open()){
        //outputfile.close();
    outputfile.open("rewardArray.txt", ios::app);
    //outputfile << " ------------------------ "<<endl;;
    int totalCount = 0;
    for (int counter = 0; counter < rowCount; counter ++)
        {
            for (int index= 0; index < colCount; index++){
                outputfile << rewardArray[totalCount]<<" ";   //Space between each character
                totalCount++;
            }
            outputfile<<endl;                           //New line for each row
        }

        outputfile.close();
}


void generateSpecialObjectPatterns(int environmentSize, int columns, int numberOfPatterns, int limit)
{
    ofstream outputfile, outputfile2;
    outputfile.open("specialObjectsPatterns.txt");
    outputfile2.open("evilSpecialObjectsPatterns.txt");

    std::vector<std::string> locations, evilLocations;
    int locationOfGood, patternLength, limitCounter;
    std::string tempLocation, tempLocation2;

    for (int index = 0; index < numberOfPatterns; index ++){
        locationOfGood  = rand()%environmentSize +1;
        patternLength   = rand()%columns +columns;
        limitCounter    = patternLength;
        double patternComplexity, patternNormalizedComplexity;

        for (int counter = 0; counter < patternLength; counter ++)
            {
                tempLocation = getRandomNeighborCell(locationOfGood, environmentSize, columns);
                locations.push_back(tempLocation);
                outputfile  << tempLocation<<" ";
                outputfile2 << positive_modulo(atoi(tempLocation.c_str())+(environmentSize/3), environmentSize) +1 <<" ";

            }
            patternComplexity           = kolmogorov2(locations, false);
            patternNormalizedComplexity = kolmogorov2(locations, true);
        while(limitCounter< limit)
            {
                std::reverse(locations.begin(),locations.end());
                for (int innerCounter = 0; innerCounter < patternLength; innerCounter ++)
                    {
                        tempLocation = locations.at(innerCounter);
                        outputfile  << tempLocation <<" ";
                        outputfile2 << positive_modulo(atoi(tempLocation.c_str())+(environmentSize/3), environmentSize) +1 <<" ";
                        limitCounter++;
                        if (limitCounter == limit){
                            break;
                        }
                    }
            }
        outputfile <<"     " << patternComplexity <<" " << patternNormalizedComplexity;
        outputfile<<endl; //New line for each pattern
        outputfile2 <<"     " << patternComplexity <<" " << patternNormalizedComplexity;
        outputfile2<<endl; //New line for each pattern

        locations.clear();
    }
        outputfile.close();
        outputfile2.close();
}


void dynamicallyGenerateSpecialObjectPatterns(int environmentSize, int columns, int numberOfPatterns, int limit, std::string filename_good, std::string filename_evil)
{

    ofstream outputfile, outputfile2;
    outputfile.open(filename_good);
    outputfile2.open(filename_evil);

    std::vector<std::string> locations, evilLocations;
    int locationOfGood, patternLength, limitCounter;
    std::string tempLocation, tempLocation2;

    for (int index = 0; index < numberOfPatterns; index ++){
        locationOfGood  = rand()%environmentSize +1;
        patternLength   = rand()%columns +columns;
        limitCounter    = patternLength;
        double patternComplexity, patternNormalizedComplexity;

        for (int counter = 0; counter < patternLength; counter ++)
            {
                locationOfGood  = getRandomNeighborCell(locationOfGood, environmentSize, columns);
                tempLocation    = NumberToString(locationOfGood);
                locations.push_back(tempLocation);
                outputfile  << tempLocation<<" ";
                outputfile2 << positive_modulo(atoi(tempLocation.c_str())+(environmentSize/3), environmentSize) +1 <<" ";

            }
            patternComplexity           = kolmogorov2(locations, false);
            patternNormalizedComplexity = kolmogorov2(locations, true);
        while(limitCounter< limit)
            {
                std::reverse(locations.begin(),locations.end());
                for (int innerCounter = 0; innerCounter < patternLength; innerCounter ++)
                    {
                        tempLocation = locations.at(innerCounter);
                        outputfile  << tempLocation <<" ";
                        outputfile2 << positive_modulo(atoi(tempLocation.c_str())+(environmentSize/3), environmentSize) +1 <<" ";
                        limitCounter++;
                        if (limitCounter == limit){
                            break;
                        }
                    }
            }
        outputfile <<"     " << patternComplexity <<" " << patternNormalizedComplexity;
        outputfile<<endl; //New line for each pattern
        outputfile2 <<"     " << patternComplexity <<" " << patternNormalizedComplexity;
        outputfile2<<endl; //New line for each pattern

        locations.clear();
    }
        outputfile.close();
        outputfile2.close();
}


int getRandomNeighborCell(int aPosition, int environmentSize, int columns){
        std::vector<int> neighborhood = findNeighborhood(aPosition, 1, environmentSize, columns);
        return neighborhood.at(rand()%9);
        //std::ostringstream stm ;
        //stm << neighborhood.at(rand()%9) ;
        //return stm.str() ;
}


std::string NumberToString (int number)
{
 std::ostringstream ss;
 ss << number;
 return ss.str();
}

/*
float randomFloat(float min, float max)
{
// this  function assumes max > min, you may want
// more robust error checking for a non-debug build
std::srand ( unsigned ( time(0) ) );
assert(max > min);
float random = ((float) rand()) / (float) RAND_MAX;

// generate (in your case) a float between 0 and (4.5-.78)
// then add .78, giving you a float between .78 and 4.5
float range = max - min;
return (random*range) + min;
}

float randomFloat2(float min, float max) {
return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}
*/
