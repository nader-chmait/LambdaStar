#include "BiddingLocalSearchAgent.h"
#include "Agent.h"
#include "General.hpp"
#include "Observation.h"
#include <vector>
#include <algorithm>
BiddingLocalSearchAgent::BiddingLocalSearchAgent()
{
    //ctor

}

BiddingLocalSearchAgent::BiddingLocalSearchAgent(int initialPosition, std::string aName, int savedRewardSize):LocalSearchAgent(initialPosition, aName, savedRewardSize){
    target          = -99;//rand()%savedRewardSize +1;
    highestBid      = -1;
}

BiddingLocalSearchAgent::~BiddingLocalSearchAgent()
{
    //dtor
}

int BiddingLocalSearchAgent::performAction(int columns){
    int anAction        = approachPosition(target, getPosition(), columns);
    return anAction;
}

void BiddingLocalSearchAgent::updateMyBid(int columns, int environmentSize){
    double money    = findMaxValue(getObservation().getCellRewardDescription());

    if (money >= highestBid){
        highestBid      = money;
        int action      = LocalSearchAgent::performAction(columns);
        target          = getNewLocation(getPosition(), action, columns, environmentSize);
    }

}


