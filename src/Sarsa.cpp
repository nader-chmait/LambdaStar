#include "Sarsa.h"


Sarsa::Sarsa()
{
    //ctor
}
Sarsa::Sarsa(int initialPosition, std::string aName, int savedRewardSize, int environmentSize, double alphaValue, double gammaValue, double epsilonValue):Qlearning(initialPosition, aName, savedRewardSize, environmentSize, alphaValue, gammaValue, epsilonValue){
    this->secondPreviousState   = initialPosition;
    this->secondLastAction      = -99;
}

Sarsa::~Sarsa()
{
    //dtor
}
void Sarsa::updateQMatrix(int currentIteration){
    int currentState = getPosition() + (environmentStates*(currentIteration-1));
    this->Qmatrix[previousState-1][secondLastAction-1] +=  alpha*(getLastReward() + gamma*(this->Qmatrix[currentState-1][lastAction-1]) - this->Qmatrix[previousState-1][secondLastAction-1]);
    previousState       = currentState;
    secondLastAction    = lastAction;
}

void Sarsa::setSecondLastState(){
    this->secondPreviousState = getPosition();
}
void Sarsa::setSecondLastAction(int anAction){
    this->secondLastAction= anAction;
}

void Sarsa::resetAll(int aStartupPOsition){
    Qlearning::resetAll(aStartupPOsition);
    this->currentAction         = -99;
    this->secondLastAction      = -99;
    this->secondPreviousState   = aStartupPOsition;
}
