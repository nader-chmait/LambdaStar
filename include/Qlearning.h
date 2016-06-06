#ifndef QLEARNING_H
#define QLEARNING_H

#include "Agent.h"


class Qlearning : public Agent
{
    public:
        Qlearning();
        Qlearning(int, std::string, int, int, double, double, double);

        virtual ~Qlearning();
        double getMaxRowValue(int);
        virtual void updateQMatrix();
        void setAlpha(double);
        void setGamma(double);
        double getAlpha();
        double getGamma();
        void setEpsilon(double);
        double getEpsilon();
        virtual int performAction(int);
        int setPosition(int, int, int);
        std::vector<int> findMaxRewardingActions(double, int);
        void printQmatrix();
        void initializeQmatrix();
        void train(int,int);
        void reset();
        void resetAll(int);
        double getQmatrix(int,int);
    protected:
        double** Qmatrix;
        int numberOfStates;
        int environmentStates;
        double alpha;
        double gamma;
        double epsilon;
        int previousState;
        int lastAction;
    private:



};

#endif // QLEARNING_H
