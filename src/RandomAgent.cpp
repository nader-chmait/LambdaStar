#include "RandomAgent.h"
#include "Agent.h"
#include <iostream>

RandomAgent::RandomAgent():Agent()
{
    //ctor
}
RandomAgent::RandomAgent(int initialPosition):Agent(initialPosition){

}
RandomAgent::RandomAgent(int initialPosition, std::string aName, int testIterations):Agent(initialPosition, aName, testIterations){

}
RandomAgent::~RandomAgent()
{
    //dtor
}

int RandomAgent::performAction(){
    return ((rand()%9) + 1);
}
