#ifndef GENERAL_H
#define GENERAL_H

#include <vector>
#include <string>
#include <Agent.h>

int positive_modulo(int, int);
int getNewLocation(int, int, int, int);
void printVector(std::vector<int>);
void printVectorD(std::vector<double>);
void printArray(double*, int);
std::vector<int> findNeighborhood(int, int, int, int);
std::vector<int> findMaxIndecies(std::vector<double>);
std::vector<int> findMinIndecies(std::vector<double>);
double findMaxValue(std::vector<double>);
double findMinValue(std::vector<double>);
int findMaxVal(std::vector<int>);
int findMinVal(std::vector<int>);

double kolmogorov(std::string, bool);
double kolmogorov2(std::vector<std::string>, bool);
bool isUnique(std::vector<int>);
struct coordinates {
  int xCoordinate;
  int yCoordinate;
} ;
coordinates findCoordinates(int, int);

int getNumberOfInternalNodes(int);
int getNumberOfLeaves(int);
bool childrenNotComplete(int, int);
double generateRandomNumber();
//float randomFloat(float min, float max);
//float randomFloat2(float min, float max);
int findDistance(int, int, int);
int approachPosition(int, int, int);
bool isNeighborTo(int, int, int, int);
int firstMaxIndex(std::vector<double>);
int firstMaxIndex(double *, int);
std::vector<int> generateRandomPermutation(int);
const std::string currentDateTime();
void initializeMatrix(double**, int, int, int);
void initializeArray(double*, int, double);
void initializeArray(int*, int, int);
void printMatrix(double**, int, int);
double CalculateMean(std::vector<double>);
double CalculateSum(std::vector<double>);
double CalculateVariance(std::vector<double>);
std::vector<std::vector<int> > readPatternsFromFile(std::string);
std::vector<int> getThisIterationPattern(int, std::vector<std::vector<int> >);
void print2DVector(std::vector<std::vector<int> >);
std::vector<int> getAlternativePattern(std::vector<int>);
void saveCoordinatesToFile(std::vector<Agent*>*, int);
void saveArrayToFile(double*, int, int);
std::vector<int> findMaxIndecies(double*, int);
void appendArrayToFile(double*, int, int);
int getRandomNeighborCell(int, int, int);
void generateSpecialObjectPatterns(int, int, int, int);
void dynamicallyGenerateSpecialObjectPatterns(int, int, int, int, std::string,std::string);
string NumberToString(int);
#endif // SPECIALAGENT_H

