#ifndef TEST_H
#define TEST_H
#include <vector>
#include "Agent.h"
#include "SpecialAgent.h"

class Test
{
    private:
         //std::vector<agentType> setOfAgents;
         int iterations;
         int numberOfEvaluatedAgents;
         int observationRange;

    public:
        Test();
        Test(int, int);
        Test(int, int, int);
        virtual ~Test();
        int getIterations();
        int getNumberOfEvaluatedAgents();
        int getObservationRange();

    protected:



};

#endif // TEST_H
