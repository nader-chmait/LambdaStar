#ifndef DICTATORSHIPLOCALSEARCHAGENT_H
#define DICTATORSHIPLOCALSEARCHAGENT_H

#include <BiddingLocalSearchAgent.h>
#include "LocalSearchAgent.h"

class DictatorshipLocalSearchAgent : public BiddingLocalSearchAgent
{
    public:
        DictatorshipLocalSearchAgent();
        DictatorshipLocalSearchAgent(int, std::string, int);
        virtual ~DictatorshipLocalSearchAgent();
        static int onlyTarget;
        void updateSingleBid(int, int);
        int performAction(int);
    protected:
    private:

};

#endif // DICTATORSHIPLOCALSEARCHAGENT_H
