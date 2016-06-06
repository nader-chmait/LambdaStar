#include "CoopQlearning.h"

CoopQlearning::CoopQlearning()
{
    //ctor
}

CoopQlearning::CoopQlearning(int initialPosition, std::string aName, int savedRewardSize, int environmentSize, double alphaValue, double gammaValue, double epsilonValue, double** referenceQmatrix):Qlearning(initialPosition, aName, savedRewardSize, environmentSize, alphaValue, gammaValue, epsilonValue){
        this->Qmatrix = referenceQmatrix;
}

CoopQlearning::~CoopQlearning()
{
    //dtor
}
