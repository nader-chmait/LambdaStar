#include "WocLocalSearch.h"
#include <vector>
#include "General.hpp"

WocLocalSearch::WocLocalSearch()
{
    //ctor
}

WocLocalSearch::~WocLocalSearch()
{
    //dtor
}


WocLocalSearch::WocLocalSearch(int initialPosition, std::string aName, int savedRewardSize):FrLocalSearch(initialPosition, aName, savedRewardSize)
{
    //ctor
}



void WocLocalSearch::propagateAverageRewards(double* avgRewardArray){
    Observation o                       = getObservation();
    std::vector<double>realReward       = o.getCellRewardDescription();
    std::vector<int> propagationCells   = o.getCellDescription();

    for (int i = 0; i < realReward.size(); i++){
            if (realReward.at(i)!=0){
                avgRewardArray[propagationCells.at(i)-1] =  (double)(avgRewardArray[propagationCells.at(i)-1] + realReward.at(i))/2.0;
            }
    }

}

int WocLocalSearch::performAction(double* fakeRewardArray, int columns, bool jumpForbidden){
    int action = -99;
    int environmentSize = columns*columns;
    std::vector<int> maxIndecies        = findMaxIndecies(fakeRewardArray, environmentSize);
    int randomMaxIndex                  = maxIndecies.at(rand()%(maxIndecies.size()));

    if (jumpForbidden){
        action                          = approachPosition(randomMaxIndex+1, getPosition(),columns);
    }else{
        action                          = updatePosition(randomMaxIndex+1);

    }


    return action;
}
