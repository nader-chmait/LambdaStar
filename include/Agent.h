#ifndef AGENT_H
#define AGENT_H
#include <vector>
#include "Observation.h"
#include <iostream>
#include <string>


using namespace std;

class Agent
{
private:
        int position;
        int testSteps;
        std::string Id;
        std::string name;
        double* rewards;
        double avgReward;
        double rewardSum;
        double lastReward;
        int lastPosition;
        Observation lastObservation;
        static int numOfAgents;
    protected:
        int startupPosition;
    public:
        Agent();
        Agent(int);
        Agent(int, std::string);
        Agent(int, std::string, int);
        virtual ~Agent();

        int getPosition();
        int getLastPosition();
        int getStartupPosition();
        int updatePosition(int);
        void resetPosition(int);
        void pushReward(double, int);
        void calculateAvgReward();
        double getAvgReward();
        double getReward(int);
        double getLastReward();
        std::string getName();
        std::string getId();
        Observation getObservation();
        void setObservation(Observation);
        void setLastReward(double);
        virtual int setPosition(int, int, int);
        virtual int performAction(){return 99;}
        virtual int performAction(double*, int){return 99;}
        virtual int performAction(int){return 99;}
        virtual int performAction(int, int, int){return 99;}
        virtual int performAction(double*, int, bool){return 99;}
        virtual int performAction(int, int, int, int){return 99;}
        virtual int performAction(int, int, int, int, bool){return 99;}
        virtual void propagateFakeRewards(double*){}
        virtual void updateMyBid(int, int){}
        virtual void propagate(){}
        virtual void updateQMatrix(){}
        virtual void updateQMatrix(int){}
        virtual void setSecondLastAction(int){};
        virtual void setSecondLastState(){};
        virtual void reset();
        virtual void resetAll(int);
        virtual void setTargets(int, double *, int *){};
        virtual void updateSingleBid(int, int){};
        virtual int updatePosition(int, double *, int *){};
        virtual int performJumpAction(int, int, int){};
        virtual void propagateAverageRewards(double* ){};
        virtual void setEpsilon(double){};
        static int getNumberOfAgents(){
            return numOfAgents;
        }
};

#endif // AGENT_H
