#include "CoopSarsa.h"

CoopSarsa::CoopSarsa()
{
    //ctor
}
CoopSarsa::CoopSarsa(int initialPosition, std::string aName, int savedRewardSize, int environmentSize, double alphaValue, double gammaValue, double epsilonValue, double** referenceQmatrix):Sarsa(initialPosition, aName, savedRewardSize, environmentSize, alphaValue, gammaValue, epsilonValue){
    this->Qmatrix = referenceQmatrix;
}
CoopSarsa::~CoopSarsa()
{
    //dtor
}
