#include "LocalSearchAgent.h"
#include "Agent.h"
#include "General.hpp"
#include <algorithm>


LocalSearchAgent::LocalSearchAgent()
{
    //ctor
}

LocalSearchAgent::~LocalSearchAgent()
{
    //dtor
}
LocalSearchAgent::LocalSearchAgent(int initialPosition, std::string aName, int savedRewardSize):Agent(initialPosition, aName, savedRewardSize){

}

int LocalSearchAgent::performAction(int columns){
    Observation o                   = getObservation();
    std::vector<int> maxIndecies    = findMaxIndecies(o.getCellRewardDescription());
    int randomMaxIndex              = maxIndecies.at(rand()%(maxIndecies.size())); // maxIndecies.at(b);
    std::vector<int> lastObservationCellDesciption = o.getCellDescription();
    int action  = approachPosition(lastObservationCellDesciption.at(randomMaxIndex), getPosition(),columns);
    return action;

}
