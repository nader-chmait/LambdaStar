#include "LocalSearchAgentUnitTest.h"
#include "LocalSearchAgent.h"
#include "Environment.h"
#include <vector>
#include "C:\UnitTesting\unittest-cpp-master\UnitTest++\UnitTest++.h"

LocalSearchAgentUnitTest::LocalSearchAgentUnitTest()
{
    //ctor
}

namespace
{
    TEST(setPosition)
{
    LocalSearchAgent* ls;
    ls = new LocalSearchAgent(7, "UnitTestLSAgent", 20);

    Environment* e = new Environment(5, 5, 1);
    e->nullifyCellRewards();
    e->updateCellRewards(7, 19);
    std::vector<Agent*> agentSet;
    agentSet.push_back(ls);
    e->sendObservations(agentSet, 1);

    int anAction = ls->performAction(5);
    CHECK_EQUAL(5, anAction);

    ls->updatePosition(3);
    anAction = ls->performAction(5);
    CHECK_EQUAL(7, anAction);

    ls->updatePosition(23);
    anAction = ls->performAction(5);
    CHECK_EQUAL(7, anAction);


    delete e;
    delete ls;
    agentSet.clear();
}

}
