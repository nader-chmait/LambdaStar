#ifndef RANDOMAGENT_H
#define RANDOMAGENT_H

#include "Agent.h"


class RandomAgent : public Agent
{
    public:
        RandomAgent();
        RandomAgent(int);
        RandomAgent(int, std::string, int);
        virtual ~RandomAgent();
        int performAction();
    protected:
    private:
};

#endif // RANDOMAGENT_H
