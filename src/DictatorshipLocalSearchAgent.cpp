#include "DictatorshipLocalSearchAgent.h"
#include "General.hpp"

DictatorshipLocalSearchAgent::DictatorshipLocalSearchAgent(int initialPosition, std::string aName, int savedRewardSize):BiddingLocalSearchAgent(initialPosition, aName, savedRewardSize)
{
    //ctor
    onlyTarget = -99;
}

DictatorshipLocalSearchAgent::~DictatorshipLocalSearchAgent()
{
    //dtor
}

void DictatorshipLocalSearchAgent::updateSingleBid(int columns, int environmentSize){
    double money    = findMaxValue(getObservation().getCellRewardDescription());

    int action      = LocalSearchAgent::performAction(columns);
    onlyTarget      = getNewLocation(getPosition(), action, columns, environmentSize);

}

int DictatorshipLocalSearchAgent::performAction(int columns){


     int anAction        = approachPosition(onlyTarget, getPosition(), columns);
     return anAction;

}
