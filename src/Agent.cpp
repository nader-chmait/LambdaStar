#include "Agent.h"
#include <vector>
#include "Observation.h"
#include <string.h>
#include <sstream>
#include "General.hpp"
#include <numeric>

Agent::Agent()
{
    //ctor
 numOfAgents++;
 std::stringstream  ss;
 ss << numOfAgents;
 this->Id = ss.str();
 this->avgReward = 0;
 this->rewardSum = 0;

 //std::cout<< "New agent created with  Id = " << Id << endl;
}
Agent::Agent(int initialPosition):Agent(){
        this->position = initialPosition;
        //std::cout<< "New agent created at position = " << initialPosition << endl;
        //std::cout<< "Agent Id = " << Id << endl;
}

Agent::Agent(int initialPosition, std::string aName):Agent(initialPosition){
        this->name = aName;
        //std::cout<< "New agent created at position = " << initialPosition << endl;
        //std::cout<< "Agent Id = " << Id << " Name = " << aName << endl;
}
Agent::Agent(int initialPosition, std::string aName, int savedRewardSize):Agent(initialPosition,aName){
        this->rewards         = new double [savedRewardSize];
        this->testSteps       = savedRewardSize;
        this->startupPosition = initialPosition;
        this->lastPosition    = initialPosition;
        reset();
        //std::cout<< "New agent created at position = " << initialPosition << endl;
        //std::cout<< "Agent Id = " << Id << " Name = " << aName << endl;
}

Agent::~Agent()
{
    //dtor
}

std::string Agent::getName(){
        return name;
}
int Agent::getPosition(){
    return position;
}

int Agent::setPosition(int action, int columns, int environmentSize){
    this->lastPosition  = position;
    this->position      = getNewLocation(position, action, columns, environmentSize);
    return position;
}

std::string Agent::getId(){
    return Id;
}


Observation Agent::getObservation(){
        return lastObservation;
}

void Agent::setObservation(Observation anObservation){
    this->lastObservation = anObservation;
}

void Agent::pushReward(double aReward, int currentIteration){
    this->rewards[currentIteration-1] += aReward;
    this->lastReward = aReward;
}

double Agent::getAvgReward(){
    return avgReward;
    }

void Agent::calculateAvgReward(){
    try {
    double sum = 0;
    for (int i=0; i <testSteps; i++){
        sum += rewards[i];
    }
    this->rewardSum =  sum;
    this->avgReward =  sum/(double)testSteps;
    if (abs(rewardSum) > testSteps){
        throw 101;
    }
    }catch(int z){
    cout<<"Cannot exceed maximum reward of 1.0, ERROR NUMBER: "<< z<<endl;
    }
}

void Agent::reset(){
    for(int j = 0; j < testSteps; j++)
    {
        this->rewards[j] = 0.0;
    }
    this->rewardSum     = 0;
    this->avgReward     = 0;
    this->lastReward    = 0;
    this->position      = startupPosition;
    this->lastPosition  = startupPosition;
}

void Agent::resetAll(int aStartupPosition){
    for(int j = 0; j < testSteps; j++)
    {
        this->rewards[j] = 0.0;
    }
    this->rewardSum         = 0;
    this->avgReward         = 0;
    this->lastReward        = 0;
    this->position          = aStartupPosition;
    this->lastPosition      = aStartupPosition;
    this->startupPosition   = aStartupPosition;
}

double Agent::getReward(int anIteration){
    return rewards[anIteration -1];
}
double Agent::getLastReward(){
    return lastReward;
}
int Agent::getStartupPosition(){
    return startupPosition;
}

void Agent::setLastReward(double aReward){
    this->lastReward = aReward;
}

void Agent::resetPosition(int aPosition){
    this->lastPosition = aPosition;
}
int Agent::getLastPosition(){
    return lastPosition;
}
int Agent::updatePosition(int newPosition){
    this->lastPosition  = position;
    this->position      = newPosition;
    return position;
}
