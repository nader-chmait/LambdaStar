#ifndef SARSA_H
#define SARSA_H

#include "Qlearning.h"


class Sarsa : public Qlearning
{
    public:
        Sarsa();
        Sarsa(int, std::string, int, int, double, double, double);
        virtual ~Sarsa();
        void updateQMatrix(int);
        void setSecondLastState();
        void setSecondLastAction(int);
        void resetAll(int);
    protected:
    private:
        int currentAction;
        int secondPreviousState;
        int secondLastAction;
};

#endif // SARSA_H
