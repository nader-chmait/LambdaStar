#include "EnvironmentUnitTest.h"
#include "Environment.h"
#include "Observation.h"
#include "C:\UnitTesting\unittest-cpp-master\UnitTest++\UnitTest++.h"
#include <vector>

EnvironmentUnitTest::EnvironmentUnitTest()
{
    //ctor
}
//EnvironmentUnitTest eut;



namespace
{
    TEST(rewardUpdate)
    {
        Environment* e = new Environment(5, 5, 1);
        //e.initializeEnvironment(5, 5, 1);
        e->nullifyCellRewards();

        e->updateCellRewards(7, 19);
        Observation testObservationGood = e->generateObservation(7, 1);
        Observation testObservationEvil = e->generateObservation(19, 1);
        Observation testObservationNone = e->generateObservation(9, 1);


        vector<double> oned1  = {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.0};
        vector<double> oned2  = {0.0,-0.5,-0.5,-0.5,-1.0,-0.5,-0.5,-0.5,-0.5};
        vector<double> oned3  = {0.5, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0,-0.5,-0.5};

        CHECK_ARRAY_EQUAL(oned1, testObservationGood.getCellRewardDescription(), 9);
        CHECK_ARRAY_EQUAL(oned2, testObservationEvil.getCellRewardDescription(), 9);
        CHECK_ARRAY_EQUAL(oned3, testObservationNone.getCellRewardDescription(), 9);

        e->nullifyCellRewards();

        e->updateCellRewards(7, 8);
        testObservationGood = e->generateObservation(7, 1);
        testObservationEvil = e->generateObservation(8, 1);
        testObservationNone = e->generateObservation(19, 1);


        oned1  = { 0.5, 0.0, 0.0, 0.5, 0.5,-0.5, 0.5, 0.0, 0.0};
        oned2  = { 0.0, 0.0,-0.5, 0.5,-0.5,-0.5, 0.0, 0.0,-0.5};
        oned3  = { 0.0,-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


        CHECK_ARRAY_EQUAL(oned1, testObservationGood.getCellRewardDescription(), 9);
        CHECK_ARRAY_EQUAL(oned2, testObservationEvil.getCellRewardDescription(), 9);
        CHECK_ARRAY_EQUAL(oned3, testObservationNone.getCellRewardDescription(), 9);

        oned1  = {  1, 2, 3, 6, 7, 8, 11, 12, 13};
        oned2  = {  2, 3, 4, 7, 8, 9, 12, 13, 14};
        oned3  = { 13,14,15,18,19,20, 23, 24, 25};

        CHECK_ARRAY_EQUAL(oned1, testObservationGood.getCellDescription(), 9);
        CHECK_ARRAY_EQUAL(oned2, testObservationEvil.getCellDescription(), 9);
        CHECK_ARRAY_EQUAL(oned3, testObservationNone.getCellDescription(), 9);

        delete e;
    }

}
