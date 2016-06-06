#include "GeneralUnitTest.h"
#include "General.hpp"
#include "..\UnitTest++\UnitTest++.h"
#include <vector>
#include <iostream>

GeneralUnitTest::GeneralUnitTest()
{
    //ctor
}

namespace
{

TEST(moduloIsPositive)
{
    int Result = positive_modulo(30, 4);
    CHECK_EQUAL(2, Result);
}


TEST(moduloIsZero)
{
    int Result = positive_modulo(30, 30);
    CHECK_EQUAL(0, Result);
}

TEST(moduloIsAlwaysPositive)
{

    int Result = positive_modulo(3, 10);
    CHECK_EQUAL(3, Result);
}

TEST(areNieghbors)
{
  CHECK(isNeighborTo(10, 4, 25, 5));
  CHECK(isNeighborTo(10, 5, 25, 5));
  CHECK(isNeighborTo(10, 9, 25, 5));
  CHECK(isNeighborTo(10, 10, 25, 5));
  CHECK(isNeighborTo(10, 14, 25, 5));
  CHECK(isNeighborTo(10, 15, 25, 5));
  CHECK(isNeighborTo(10, 1, 25, 5));
  CHECK(isNeighborTo(10, 6, 25, 5));
  CHECK(isNeighborTo(10, 11, 25, 5));

  CHECK(isNeighborTo(25, 19, 25, 5));
  CHECK(isNeighborTo(25, 20, 25, 5));
  CHECK(isNeighborTo(25, 24, 25, 5));
  CHECK(isNeighborTo(25, 25, 25, 5));
  CHECK(isNeighborTo(25, 1, 25, 5));
  CHECK(isNeighborTo(25, 4, 25, 5));
  CHECK(isNeighborTo(25, 5, 25, 5));
  CHECK(isNeighborTo(25, 16, 25, 5));
  CHECK(isNeighborTo(25, 21, 25, 5));

}

TEST(areNotNieghbors)
{
  bool Result = isNeighborTo(10, 7, 25, 5);
  CHECK_EQUAL(false, Result);
  Result = isNeighborTo(25, 7, 25, 5);
  CHECK_EQUAL(false, Result);
}

TEST(numberOfLeavesInBinaryTree)
{
    CHECK_EQUAL(8, getNumberOfLeaves(15));
}

TEST(numberOfInternalNodesInBinaryTree)
{
    CHECK_EQUAL(7, getNumberOfInternalNodes(15));
}

TEST(nodeIsNotFullOrIsleafInBinaryTree)
{
  bool Result = childrenNotComplete(14, 7);
  CHECK_EQUAL(true, Result);
  Result = childrenNotComplete(14, 11);
  CHECK_EQUAL(true, Result);
}


TEST(maxValueInVector)
{
    std::vector<int> aVector = {10, 5, 99, 68, 10};
    CHECK_EQUAL(99, findMaxVal(aVector));

    aVector = {10, 5, 99, 99, 10};
    CHECK_EQUAL(99, findMaxVal(aVector));

    aVector = {10, 5, -99, 68, 10};
    CHECK_EQUAL(68, findMaxVal(aVector));

    aVector = {0, 0, 0, 0, 0};
    CHECK_EQUAL(0, findMaxVal(aVector));

    aVector = {0, -1, -6};
    CHECK_EQUAL(0, findMaxVal(aVector));
}

TEST(minValueInVector)
{
    std::vector<int> aVector = {10, 5, 99, 68, 10};
    CHECK_EQUAL(5, findMinVal(aVector));

    aVector = {10, 5, 5, 99, 10};
    CHECK_EQUAL(5, findMinVal(aVector));

    aVector = {10, 5, -99, 68, 10};
    CHECK_EQUAL(-99, findMinVal(aVector));

    aVector = {0, 0, 0, 0, 0};
    CHECK_EQUAL(0, findMinVal(aVector));

    aVector = {0, -1, -6};
    CHECK_EQUAL(-6, findMinVal(aVector));
}

TEST(neighborhood)
{
    std::vector<int> oned = { 1, 2, 3, 6, 7, 8, 11, 12, 13};
    std::vector<int> aNeighborhood =findNeighborhood(7, 1, 25, 5);
    CHECK_ARRAY_EQUAL(oned, aNeighborhood, 9); // succeeds

    oned = { 19, 20, 16, 24, 25, 21, 4, 5, 1};
    aNeighborhood =findNeighborhood(25, 1, 25, 5);
    CHECK_ARRAY_EQUAL(oned, aNeighborhood, 9); // succeeds

}

TEST(newLocation)
{
    int oldLocation = 7;


    int newLocation = getNewLocation(oldLocation, 1, 5, 25);
    CHECK_EQUAL(1, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 2, 5, 25);
    CHECK_EQUAL(2, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 3, 5, 25);
    CHECK_EQUAL(3, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 4, 5, 25);
    CHECK_EQUAL(6, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 5, 5, 25);
    CHECK_EQUAL(7, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 6, 5, 25);
    CHECK_EQUAL(8, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 7, 5, 25);
    CHECK_EQUAL(11, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 8, 5, 25);
    CHECK_EQUAL(12, newLocation); // succeeds

    newLocation = getNewLocation(oldLocation, 9, 5, 25);
    CHECK_EQUAL(13, newLocation); // succeeds

}

TEST(maxIndecies)
{
    std::vector<int> maxIndecies = findMaxIndecies({0.1, 0.99, 0.3, 0.80, 0.45});
    std::vector<int> oned = {1};
    CHECK_ARRAY_EQUAL(oned, maxIndecies, maxIndecies.size()); // succeeds

    maxIndecies = findMaxIndecies({0.1, 0.99, 0.3, 0.99, 0.45});
    oned = {1, 3};
    CHECK_ARRAY_EQUAL(oned, maxIndecies, maxIndecies.size()); // succeeds
}

TEST(minIndecies)
{
    std::vector<int> minIndecies = findMinIndecies({0.1, 0.99, 0.3, 0.80, 0.45});
    std::vector<int> oned = {0};
    CHECK_ARRAY_EQUAL(oned, minIndecies, minIndecies.size()); // succeeds

    minIndecies = findMinIndecies({0.1, 0.99, 0.3, 0.99, 0.1});
    oned = {0, 4};
    CHECK_ARRAY_EQUAL(oned, minIndecies, minIndecies.size()); // succeeds
}

TEST(xyCoordinates)
{
    /*---------------------------------
    1     2     3     4     5
    6     7     8     9    10
    11    12    13    14    15
    16    17    18    19    20
    21    22    23    24    25
    */
    coordinates Result = findCoordinates(7, 5);
    CHECK_EQUAL(2, Result.xCoordinate);
    CHECK_EQUAL(2, Result.yCoordinate);

    Result = findCoordinates(8, 5);
    CHECK_EQUAL(2, Result.xCoordinate);
    CHECK_EQUAL(3, Result.yCoordinate);

    /*---------------------------------
     1     2     3     4     5     6
     7     8     9    10    11    12
    13    14    15    16    17    18
    19    20    21    22    23    24
    25    26    27    28    29    30
    31    32    33    34    35    36
    */
    Result = findCoordinates(7, 6);
    CHECK_EQUAL(2, Result.xCoordinate);
    CHECK_EQUAL(1, Result.yCoordinate);

}

TEST(distanceBetween2Points)
{
    int Result = findDistance(2,2,5);
    CHECK_EQUAL(0, Result);

    Result = findDistance(2,3,5);
    CHECK_EQUAL(1, Result);

    Result = findDistance(2,8,5);
    CHECK_EQUAL(1, Result);

    Result = findDistance(2,13,5);
    CHECK_EQUAL(2, Result);

    Result = findDistance(2,22,5);
    CHECK_EQUAL(1, Result);

    Result = findDistance(25,1,5);
    CHECK_EQUAL(1, Result);

    Result = findDistance(2,16,5);
    CHECK_EQUAL(2, Result);
}

TEST(actionToApproachPosition)
{
    int Result = approachPosition(2, 2, 5);
    CHECK_EQUAL(5, Result);

    Result = approachPosition(22, 2, 5);
    CHECK_EQUAL(2, Result);

    Result = approachPosition(8, 2, 5);
    CHECK_EQUAL(9, Result);

    Result = approachPosition(7, 2, 5);
    CHECK_EQUAL(8, Result);

    Result = approachPosition(6, 2, 5);
    CHECK_EQUAL(7, Result);

    Result = approachPosition(23, 2, 5);
    CHECK_EQUAL(3, Result);

    Result = approachPosition(21, 2, 5);
    CHECK_EQUAL(1, Result);

    Result = approachPosition(13, 2, 5);
    CHECK_EQUAL(9, Result);

    Result = approachPosition(20, 6, 5);
    CHECK_EQUAL(7, Result);
}

TEST(elementsAreUnique)
{
    bool Result = isUnique({1, 2, 3, 4, 5});
    CHECK_EQUAL(false, Result);

    Result = isUnique({1, 1, 1, 1, -1});
    CHECK_EQUAL(false, Result);

    Result = isUnique({1, 1, 1, 1, 1});
    CHECK_EQUAL(true, Result);

}

/* // example of a test suite using test fixtures
SUITE(SuiteOne)
{

struct MyFixture
{
    std::string testData;

    MyFixture() :
        testData("my test data")
    {
        std::cout << "my setup" << std::endl;
    }

    ~MyFixture()
    {
        std::cout << "my teardown" << std::endl;
    }
};

TEST_FIXTURE(MyFixture, MyTestCase)
{
    std::cout << testData << std::endl;
}

}
*/

TEST(kolmogorovComplexity)
{
    bool normalized = true;
    double complexity = kolmogorov("111111111", normalized);
    CHECK_CLOSE(0.7044, complexity, 0.001);
    complexity = kolmogorov("111111111", !normalized);
    CHECK_EQUAL(2, complexity);

    complexity = kolmogorov("111121111", normalized);
    CHECK_CLOSE(1.0566, complexity, 0.001);
    complexity = kolmogorov("111121111", !normalized);
    CHECK_EQUAL(3, complexity);

    complexity = kolmogorov("123456789", normalized);
    CHECK_CLOSE(3.1699, complexity, 0.001);
    complexity = kolmogorov("123456789", !normalized);
    CHECK_EQUAL(9, complexity);

    complexity = kolmogorov("1212121212", normalized);
    CHECK_CLOSE(0.9966, complexity, 0.001);
    complexity = kolmogorov("1212121212", !normalized);
    CHECK_EQUAL(3, complexity);

    complexity = kolmogorov("123123123123", normalized);
    CHECK_CLOSE(1.1950, complexity, 0.001);
    complexity = kolmogorov("123123123123", !normalized);
    CHECK_EQUAL(4, complexity);

    complexity = kolmogorov("12312312312312", normalized);
    CHECK_CLOSE(1.0878, complexity, 0.001);
    complexity = kolmogorov("12312312312312", !normalized);
    CHECK_EQUAL(4, complexity);

    complexity = kolmogorov("123589431898354158313", normalized);
    CHECK_CLOSE(2.7191, complexity, 0.001);
    complexity = kolmogorov("123589431898354158313", !normalized);
    CHECK_EQUAL(13, complexity);
}

TEST(kolmogorov2Complexity)
{
    bool normalized = true;
    std::vector<std::string> input = {"1","1","1","1","1","1","1","1","1"};
    double complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(0.7044, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(2, complexity);

    input = {"1","1","1","1","2","1","1","1","1"};
    complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(1.0566, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(3, complexity);

    input = {"1","2","3","4","5","6","7","8","9"};
    complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(3.1699, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(9, complexity);

    input = {"1","2","1","2","1","2","1","2","1","2"};
    complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(0.9966, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(3, complexity);

    input = {"1","2","3","1","2","3","1","2","3","1","2","3"};
    complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(1.1950, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(4, complexity);

    input = {"1","2","3","1","2","3","1","2","3","1","2","3","1","2"};
    complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(1.0878, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(4, complexity);

    input = {"1","2","3","5","8","9","4","3","1","8","9","8","3","5","4","1","5","8","3","1","3"};
    complexity = kolmogorov2(input, normalized);
    CHECK_CLOSE(2.7191, complexity, 0.001);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(13, complexity);

    input = {"123","2335","75","88","9","12","23","123","66","0"};
    //complexity = kolmogorov2(input, normalized);
    //CHECK_CLOSE(3.1699, complexity, 0.01);
    complexity = kolmogorov2(input, !normalized);
    CHECK_EQUAL(9, complexity);
}


} // end of unit testing
