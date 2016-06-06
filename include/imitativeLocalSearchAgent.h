#ifndef IMITATIVELOCALSEARCHAGENT_H
#define IMITATIVELOCALSEARCHAGENT_H

#include "LocalSearchAgent.h"


class ImitativeLocalSearchAgent : public LocalSearchAgent
{
    public:
        ImitativeLocalSearchAgent();
        ImitativeLocalSearchAgent(int, std::string, int);
        virtual ~ImitativeLocalSearchAgent();
        int performAction(int, int, int);
        int performJumpAction(int, int, int);
    protected:
    private:
        //bool isNeighborToGood;
};

#endif // IMITATIVELOCALSEARCHAGENT_H
