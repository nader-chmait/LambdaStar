#include "Bid.h"

Bid::Bid()
{
    //ctor
}

Bid::~Bid()
{
    //dtor
}

void Bid::setTraget(int aTarget){
    this->target = aTarget;
}
int  Bid::getTraget(){
    return target;
}
void Bid::setBiddingMoney(double value){
    this->biddingMoney = value;
}
double Bid::getBiddingMoney(){
    return biddingMoney;
}
