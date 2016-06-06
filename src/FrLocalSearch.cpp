#include "FrLocalSearch.h"
#include "General.hpp"
#include <vector>

FrLocalSearch::FrLocalSearch()
{
    //ctor
}
FrLocalSearch::FrLocalSearch(int initialPosition, std::string aName, int savedRewardSize):LocalSearchAgent(initialPosition, aName, savedRewardSize){

}
FrLocalSearch::~FrLocalSearch()
{
    //dtor
}
void FrLocalSearch::propagateFakeRewards(double* fakeRewardArray){
    Observation o                       = getObservation();
    std::vector<double>realReward       = o.getCellRewardDescription();
    std::vector<int> propagationCells   = o.getCellDescription();
    double maxReward                    = findMaxValue(realReward);
    double minReward                    = findMinValue(realReward);
    //double newReward                    = 0;

    this->isInformed  = true;
    double fakeReward = (maxReward+minReward)*0.4;
    //double pushedReward = 0;
    if (fakeReward != 0){
        for (int i = 0; i < realReward.size(); i++){
                fakeRewardArray[propagationCells.at(i)-1] =  (double)(fakeRewardArray[propagationCells.at(i)-1] + realReward.at(i)+ fakeReward)/3.0;

        }
    }
}

int FrLocalSearch::performAction(double* fakeRewardArray, int columns, bool jumpForbidden){
    int action = -99;
    int environmentSize = columns*columns;
    if (jumpForbidden){
        //Observation o                       = getObservation();
        //std::vector<int> propagationCells   = o.getCellDescription();
        std::vector<double>fakeRewardObservation;
        std::vector<int> neighborhood = findNeighborhood(getPosition(), 1, environmentSize, columns);
        for (int i = 0; i < neighborhood.size(); i++){
            fakeRewardObservation.push_back(fakeRewardArray[neighborhood.at(i)-1]);
        }

        std::vector<int> maxIndecies        = findMaxIndecies(fakeRewardObservation);
        int randomMaxIndex                  = maxIndecies.at(rand()%(maxIndecies.size()));
        action                              = approachPosition(neighborhood.at(randomMaxIndex), getPosition(),columns);
    }else{
        std::vector<int> maxIndecies        = findMaxIndecies(fakeRewardArray, environmentSize);
        int randomMaxIndex                  = maxIndecies.at(rand()%(maxIndecies.size()));
        //int maxIndex                        = firstMaxIndex(fakeRewardArray,environmentSize);
        action = updatePosition(randomMaxIndex+1);

    }


    return action;
}
