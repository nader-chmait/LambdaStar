#include "ImitativeLocalSearchAgent.h"
#include "General.hpp"

ImitativeLocalSearchAgent::ImitativeLocalSearchAgent()
{
    //ctor
}
ImitativeLocalSearchAgent::ImitativeLocalSearchAgent(int initialPosition, std::string aName, int savedRewardSize):LocalSearchAgent(initialPosition, aName, savedRewardSize){

}
ImitativeLocalSearchAgent::~ImitativeLocalSearchAgent()
{
    //dtor
}
int ImitativeLocalSearchAgent::performAction(int columns, int positionOfOracle, int environmentSize){
    int action;
    if (isNeighborTo(positionOfOracle, getPosition(), environmentSize,columns)){
        action  = approachPosition(positionOfOracle, getPosition(), columns);
    }else{
        action  = LocalSearchAgent::performAction(columns);
    }
    return action;
}


int ImitativeLocalSearchAgent::performJumpAction(int columns, int positionOfOracle, int environmentSize){
    int action;
    if (isNeighborTo(positionOfOracle, getPosition(), environmentSize,columns)){
        action  = updatePosition(positionOfOracle);
    }else{
        action  = LocalSearchAgent::performAction(columns);
    }
    return action;
}
