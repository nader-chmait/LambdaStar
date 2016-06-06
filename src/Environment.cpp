#include "Environment.h"
#include "Agent.h"
#include "Observation.h"
#include <vector>
#include <iostream>
#include "SpecialAgent.h"
#include "Test.h"
#include "General.hpp"


Environment::Environment()
{
    //ctor
    nbrOfEnvironments++;
}

Environment::~Environment()
{
    //dtor
    nbrOfEnvironments--;
}
Environment::Environment(int e_rows, int e_columns):Environment()
{
    //ctor
    this->rows                  = e_rows;
    this->columns               = e_columns;
    this->environmentSize       = e_rows*e_columns;
    this->rewardDistribution    = new double[e_rows*e_columns];
}

Environment::Environment(int e_rows, int e_columns,int anObservationRange):Environment(e_rows, e_columns){
this->observationRange  = anObservationRange;
}

void Environment::initializeEnvironment(int e_rows, int e_columns, int anObservationRange){
    this->rows                  = e_rows;
    this->columns               = e_columns;
    this->environmentSize       = e_rows*e_columns;
    this->rewardDistribution    = new double[e_rows*e_columns];
    this->observationRange      = anObservationRange;
}

int Environment::getEnvironmentSize(){
    return environmentSize;
}
int Environment::getNbrOfColumns(){
    return columns;
}
int Environment::getObservationRange(){
    return observationRange;
}

Observation Environment::generateObservation(int aPosition, int observationRange)
{   Observation o;
    vector<int> cellDescription = findNeighborhood(aPosition, observationRange,  environmentSize,  columns);
    vector<double> cellRewardDescription;
    for (int i=0; i<cellDescription.size();i++){
        cellRewardDescription.push_back(rewardDistribution[cellDescription.at(i)-1]);
    }
    o.setCellDescription(cellDescription);
    o.setCellRewardDescription(cellRewardDescription);
    return o;
}

void Environment::sendObservations(std::vector<Agent*> evaluatedAgents, int observationRange){
    for (int i=0; i<evaluatedAgents.size(); i++){
            Observation anObservation   = generateObservation(evaluatedAgents.at(i)->getPosition(), observationRange);
            evaluatedAgents.at(i)->setObservation(anObservation);
    }
}

int Environment::getColumns(){
    return columns;
}



void Environment::sendReward(std::vector<Agent*> setOfAgents, int currentIteration){
    int aPosition;
    for (int i=0; i < setOfAgents.size(); i++){
        aPosition = setOfAgents.at(i)->getPosition();
        setOfAgents.at(i)->pushReward(rewardDistribution[aPosition-1], currentIteration);
    }
}

void Environment::sendVirtualReward(std::vector<Agent*> setOfAgents){
    int aPosition;
    for (int i=0; i < setOfAgents.size(); i++){
        aPosition = setOfAgents.at(i)->getPosition();
        setOfAgents.at(i)->setLastReward(rewardDistribution[aPosition-1]*10);
    }
}
//*
 void Environment::updateCellRewards(int locationOfGood, int locationOfEvil){

    nullifyCellRewards();
    this->neighborhoodOfGood = findNeighborhood(locationOfGood, getObservationRange(), getEnvironmentSize(), getColumns());
    this->neighborhoodOfEvil = findNeighborhood(locationOfEvil, getObservationRange(), getEnvironmentSize(), getColumns());
    this->rewardDistribution[locationOfGood-1] =   0.5;
    this->rewardDistribution[locationOfEvil-1] =  -0.5;

    for (int i=0; i < neighborhoodOfGood.size(); i++){
        this->rewardDistribution[neighborhoodOfGood.at(i)-1] = this->rewardDistribution[neighborhoodOfGood.at(i)-1] + 0.5;
        this->rewardDistribution[neighborhoodOfEvil.at(i)-1] = this->rewardDistribution[neighborhoodOfEvil.at(i)-1] - 0.5;
    }
    //printRewardDistribution();
}

void Environment::printRewardDistribution(){
     std::cout<< "Printing reward distribution"<<std::endl;
 printArray(rewardDistribution, environmentSize);
 }
double* Environment::getRewardDistribution(){
    return rewardDistribution;
}

void Environment::resetRewardDistribution(){
    //std::fill(rewardDistribution.begin(), rewardDistribution.end(), 0);
    for(int j = 0; j < environmentSize; j++)
    {
        this->rewardDistribution[j] = 0;
    }
}

void Environment::randomizeCellRewards(int numberOfRewardCells){
    int tempRand ;
    for(int j = 0; j < environmentSize; j++)
    {   //this->rewardDistribution[j] = generateRandomNumber();
        this->rewardDistribution[j] = 0.0;
    }
    for(int x = 0; x < numberOfRewardCells-1; x++){
        tempRand = rand()%environmentSize;
        if (this->rewardDistribution[tempRand] != 0){
             x--;}
        else{
            this->rewardDistribution[tempRand] = generateRandomNumber();
        }
    }

    do{ //set a reward value of 1.0 in the environment
        tempRand = rand()%environmentSize;
    }while(this->rewardDistribution[tempRand] != 0);
    this->rewardDistribution[tempRand] = 1.0;

     do{ //set a reward value of -1.0 in the environment
        tempRand = rand()%environmentSize;
    }while(this->rewardDistribution[tempRand] != 0);

    this->rewardDistribution[tempRand] = -1.0;
}

void Environment::nullifyCellRewards(){
    for(int j = 0; j < environmentSize; j++)
    {
        this->rewardDistribution[j] = 0.0;
    }
}
