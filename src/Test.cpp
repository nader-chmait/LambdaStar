#include "Test.h"
#include <vector>
#include "Agent.h"
#include "RandomAgent.h"
#include "Environment.h"



Test::Test(){

}

Test::Test(int numberOfIterations, int numOfEvaluatedAgents){
this ->iterations = numberOfIterations;
this->numberOfEvaluatedAgents = numOfEvaluatedAgents;
cout << "Test created with " << numOfEvaluatedAgents << " agents" << endl;
}
Test::Test(int numberOfIterations, int numOfEvaluatedAgents, int anObservationRange) : Test(numberOfIterations, numOfEvaluatedAgents)
{
this->observationRange = anObservationRange;
}

Test::~Test()
{
    //dtor
}

int Test::getIterations(){
    return iterations;
}
int Test::getNumberOfEvaluatedAgents(){
    return numberOfEvaluatedAgents;
}
int Test::getObservationRange(){
    return observationRange;
}
