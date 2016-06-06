#include "SpecialAgent.h"
#include "General.hpp"
//
SpecialAgent::SpecialAgent():Agent(){

}
SpecialAgent::SpecialAgent(int initialPosition):Agent(initialPosition){

}
SpecialAgent::SpecialAgent(int initialPosition, std::string aName, int testIterations):Agent(initialPosition, aName, testIterations){

}
SpecialAgent::~SpecialAgent()
{
    //dtor

}

void SpecialAgent::generatePattern(int patternSize){
    for (int i = 0; i < patternSize; i++ ){
          this->pattern.push_back((rand()%9) + 1);
          //cout << "Pattern(" << i <<") = "<< pattern.at(i) << endl;
    }
}

int SpecialAgent::getNextAction(std::vector<int> aPattern, int iteration){
    int patternSize     = aPattern.size();
    int patternIndex    = positive_modulo(iteration, patternSize);
    int action;
    if (patternIndex == 0){
        patternIndex    = aPattern.size();
    }
    action              = aPattern.at(patternIndex -1);
    return action;
}

int SpecialAgent::performAction(std::vector<int> anExtendedPattern, int iteration){
    return anExtendedPattern.at(iteration-1);
}

void SpecialAgent::extendPattern(std::vector<int> aPattern, int limit){
    this->extendedPattern = aPattern;
    if (aPattern.size() < limit) {
        int iteration = 1;
        int patternSize = extendedPattern.size();
        while (patternSize < limit){
            int nextAction = getNextAction(extendedPattern, iteration);
            extendedPattern.push_back(nextAction);
        patternSize++;
        iteration++;
        }
    }
}
void SpecialAgent::reset(std::vector<int> aPattern){
    Agent::reset();
    this->extendedPattern  = aPattern;
}


std::vector<int> SpecialAgent::getExtendedPattern(){
    return extendedPattern;
}

std::vector<int> SpecialAgent::getPattern(){
    return pattern;
}

void SpecialAgent::setExtendedPattern(std::vector<int> aPattern){
    this->extendedPattern = aPattern;
}
