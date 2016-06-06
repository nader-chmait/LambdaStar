#ifndef LOCALSEARCHAGENT_H
#define LOCALSEARCHAGENT_H

#include "Agent.h"


class LocalSearchAgent : public Agent
{
    public:
        LocalSearchAgent();
        LocalSearchAgent(int, std::string,int);
        virtual ~LocalSearchAgent();
        virtual int performAction(int);

    protected:
    private:
};

#endif // LOCALSEARCHAGENT_H
