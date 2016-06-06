#include "AgentUnitTest.h"
#include "Agent.h"
#include "C:\UnitTesting\unittest-cpp-master\UnitTest++\UnitTest++.h"
#include <vector>

AgentUnitTest::AgentUnitTest()
{
    //ctor
}



namespace
{

TEST(setPosition)
{
    Agent testAgent;
    testAgent = Agent(7, "UnitTestAgent", 20);
    int Result = testAgent.setPosition(1,5,25);
    CHECK_EQUAL(1, Result);

    Result = testAgent.setPosition(8,5,25);
    CHECK_EQUAL(6, Result);

}


}
