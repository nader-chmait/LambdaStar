#ifndef BIDDINGLOCALSEARCHAGENT_H
#define BIDDINGLOCALSEARCHAGENT_H

#include "LocalSearchAgent.h"

class BiddingLocalSearchAgent : public LocalSearchAgent
{
    public:
        BiddingLocalSearchAgent();
        BiddingLocalSearchAgent(int, std::string, int);
        virtual ~BiddingLocalSearchAgent();
        int performAction(int);
        void updateMyBid(int, int);
        static int target;
        //static int leaderPosition;
        static double highestBid;

        static double highestMoneySum;
    protected:
    private:



};

#endif // BIDDINGLOCALSEARCHAGENT_H
