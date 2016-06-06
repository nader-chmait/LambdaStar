#include "Observation.h"

Observation::Observation()
{
    //ctor
    //this->cellDescription ={0};
    //this->cellRewardDescription ={0.0};
}

Observation::~Observation()
{
    //dtor
}

void Observation::setCellDescription(std::vector<int> aCellDescription){
        this->cellDescription =  aCellDescription;
}

void Observation::setCellRewardDescription(std::vector<double> aCellRewardDescription){
        this->cellRewardDescription = aCellRewardDescription;
}

std::vector<int> Observation::getCellDescription(){
    return cellDescription;
}
void Observation::printCellDescription(std::vector<int>  aCellDescription){
    std::cout << "cell desription:" << std::endl;
    int arraySize = aCellDescription.size();
    for (int i=0; i<arraySize;i++){
           std::cout << aCellDescription[i] << " ";
        }
}

std::vector<double> Observation::getCellRewardDescription(){
  return cellRewardDescription;
}
