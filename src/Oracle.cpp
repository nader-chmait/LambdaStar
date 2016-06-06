#include "Oracle.h"
#include "General.hpp"

Oracle::Oracle()
{
    //ctor
}

Oracle::~Oracle()
{
    //dtor
}
Oracle::Oracle(int initialPosition, std::string aName, int savedRewardSize):Agent(initialPosition, aName, savedRewardSize){

}

int Oracle::predictLocation(int targetPosition, int action, int columns, int environmentSize){
    return getNewLocation(targetPosition, action, columns, environmentSize);
}

int Oracle::performAction(int targetPosition, int columns, int environmentSize){
    return approachPosition(targetPosition, getPosition(), columns);
}

int Oracle::getOppositeAction(int anAction){
    return (10 - anAction);
}
