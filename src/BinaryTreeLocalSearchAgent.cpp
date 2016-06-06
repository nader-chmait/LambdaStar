#include "BinaryTreeLocalSearchAgent.h"
#include "General.hpp"

BinaryTreeLocalSearchAgent::BinaryTreeLocalSearchAgent(int initialPosition, std::string aName, int savedRewardSize, int agentIndexInTree, int nbrOfNodesInTree):LocalSearchAgent(initialPosition, aName, savedRewardSize)
{
    //ctor
    this->indexInTree = agentIndexInTree;
    int internalNodes = getNumberOfInternalNodes(nbrOfNodesInTree);
    if (agentIndexInTree <= internalNodes){
            isInternalNode = true;
            if ((agentIndexInTree == internalNodes) && (childrenNotComplete(nbrOfNodesInTree, agentIndexInTree))){
                this->children.push_back(agentIndexInTree);
                this->children.push_back(agentIndexInTree*2);
            }else{
                this->children.push_back(agentIndexInTree);
                this->children.push_back(agentIndexInTree*2);
                this->children.push_back((agentIndexInTree*2)+1);
            }
    }
    else{
            this->children.push_back(agentIndexInTree);
            isInternalNode = false;
    }
}

BinaryTreeLocalSearchAgent::~BinaryTreeLocalSearchAgent()
{
    //dtor
}

bool BinaryTreeLocalSearchAgent::getIsInternalNode(){
    return isInternalNode;
}

vector<int> BinaryTreeLocalSearchAgent::getChildren(){
    return children;
}

void BinaryTreeLocalSearchAgent::setTargets(int columns, double *binaryTreeRewards, int *binaryTreeTargets){

        Observation o                           = getObservation();
        std::vector<double> rewardDescription   = o.getCellRewardDescription();
        std::vector<int> maxIndecies            = findMaxIndecies(rewardDescription);
        int maxIndex                            = maxIndecies.at(0);
        //int maxIndex                    = maxIndecies.at(rand()%(maxIndecies.size()));
        //std::vector<int> lastObservationCellDesciption = o.getCellDescription();
        int treeIndex = getIndexInTree();
        binaryTreeTargets[treeIndex-1] = o.getCellDescription().at(maxIndex);
        binaryTreeRewards[treeIndex-1] = rewardDescription.at(maxIndex);
}

int BinaryTreeLocalSearchAgent::performAction(int columns, double *binaryTreeRewards, int *binaryTreeTargets){

    int anAction = -99;
    int index, maxIndex;
    maxIndex    = getChildren().at(0);
        for (int i = 1; i < getChildren().size(); i++){
            index = getChildren().at(i);
            if (binaryTreeRewards[index-1] > binaryTreeRewards[maxIndex-1]){
            maxIndex = index;
            }
        }

    anAction = approachPosition(binaryTreeTargets[maxIndex-1], getPosition(), columns);;
    return anAction;

}

int BinaryTreeLocalSearchAgent::updatePosition(int columns, double *binaryTreeRewards, int *binaryTreeTargets){

    int index, maxIndex;
    maxIndex    = getChildren().at(0);
        for (int i = 1; i < getChildren().size(); i++){
            index = getChildren().at(i);
            if (binaryTreeRewards[index-1] > binaryTreeRewards[maxIndex-1]){
            maxIndex = index;
            }
        }

     int aPosition = Agent::updatePosition(binaryTreeTargets[maxIndex-1]);
     return aPosition;
}

int BinaryTreeLocalSearchAgent::getIndexInTree(){
    return indexInTree;
}
