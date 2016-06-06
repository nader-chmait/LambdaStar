#include "Qlearning.h"
#include <iostream>
#include <string.h>
#include <vector>

Qlearning::Qlearning()
{
    //ctor
}

Qlearning::Qlearning(int initialPosition, std::string aName, int savedRewardSize, int environmentSize, double alphaValue, double gammaValue, double epsilonValue):Agent(initialPosition, aName, savedRewardSize){
    this->numberOfStates    = environmentSize*savedRewardSize;
    this->environmentStates = environmentSize;
    this->alpha             = alphaValue;
    this->gamma             = gammaValue;
    this->epsilon           = epsilonValue;
    this->startupPosition   = initialPosition;
    this->Qmatrix = new double*[numberOfStates];
    for(int i = 0; i < numberOfStates; ++i){
         this->Qmatrix[i] = new double[9]; // numberOfStates = environmentSize
    }
     initializeQmatrix();
     //printQmatrix();
}


Qlearning::~Qlearning()
{
    //dtor
}


double Qlearning::getMaxRowValue(int rowIndex){
    double maxValue = Qmatrix[rowIndex-1][0];
    try{
    for(int i = 1; i < 9; ++i){
        if (Qmatrix[rowIndex-1][i] > maxValue) {
            maxValue = Qmatrix[rowIndex-1][i];
        }
    }
    if (maxValue < -999 || maxValue > 999){
        throw 106;
    }
    }catch(int z){
    std::cout<<"Max state/action value can take values in [-999,999], ERROR NUMBER: "<< z<<std::endl;
    }
    return maxValue;
}

void Qlearning::updateQMatrix(){
    this->Qmatrix[previousState-1][lastAction-1] +=  alpha*((getLastReward() + gamma*getMaxRowValue(getPosition())) - (this->Qmatrix[previousState-1][lastAction-1]));
}
int Qlearning::performAction(int currentIteration){
    int currentState        = getPosition() + (environmentStates*(currentIteration-1));
    double stateActionMax   = getMaxRowValue(currentState);
    std::vector<int> maxIndecies;
    int action;
    // choose either explore or exploit
    if (epsilon < rand()%1 + 1){ // exploit
        maxIndecies   = findMaxRewardingActions(stateActionMax, currentState);      // maxValue = max(state_action);
        action        = maxIndecies.at(rand()%(maxIndecies.size())) + 1;
    }
    else {                      // explore
        action        = (rand()%9 + 1);                                     // choose 1 action randomly
    }
    try{
    if (action > 9 || action < 1){
        throw 120;
    }
    }catch(int z){
    std::cout<<"Action can only be in [1,2,3,4,5,6,7,8,9], ERROR NUMBER: "<< z<<std::endl;
    }
    this->lastAction    = action;
    //this->previousState = currentState;
    return action;
}

std::vector<int> Qlearning::findMaxRewardingActions(double maxValue, int currentState){
    std::vector<int> maxIndecies;
    for (int i=0; i<9;i++){
        if (Qmatrix[currentState-1][i] == maxValue){
            maxIndecies.push_back(i);
        }
    }
    try{
    if (maxIndecies.empty()){
        throw 105;
    }
    }catch(int z){
    std::cout<<"There must be at least one maximum, ERROR NUMBER: "<< z<<std::endl;
    }
    return maxIndecies;
}

void Qlearning::setAlpha(double alphaValue){
    this->alpha = alphaValue;
}
void Qlearning::setGamma(double gammaValue){
    this->gamma = gammaValue;
}
double Qlearning::getAlpha(){
    return alpha;
}
double Qlearning::getGamma(){
    return gamma;
}
void Qlearning::setEpsilon(double epsilonValue){
    this->epsilon = epsilonValue;
}
double Qlearning::getEpsilon(){
    return epsilon;
}
void Qlearning::printQmatrix()
{
  for (int R = 0; R < numberOfStates; R++){
    for (int C = 0; C < 9; C++){
       std::cout << Qmatrix[R][C];
    }
    std::cout<<"\n";
  }
}
void Qlearning::initializeQmatrix(){
  for (int R = 0; R < numberOfStates; R++){
    for (int C = 0; C < 9; C++){
       this->Qmatrix[R][C] = 2;
    }
  }
}

void Qlearning::reset(){
    this->previousState = getStartupPosition();
    this->lastAction    = -99;
    //printQmatrix();
    Agent::reset();
}
void Qlearning::resetAll(int aStartupPosition){
    Agent::resetAll(aStartupPosition);
    this->previousState = aStartupPosition;
    this->lastAction    = -99;
    initializeQmatrix();
}
int Qlearning::setPosition(int action, int columns, int currentIteration){
    //this->lastPosition  = getPosition();
    this->previousState = getPosition() + (environmentStates*(currentIteration-1));
    return Agent::setPosition(action, columns, environmentStates);
}
