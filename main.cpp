#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>        // std::time
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Agent.h"
#include "Environment.h"
#include "Test.h"
#include "RandomAgent.h"
#include "LocalSearchAgent.h"
#include "FrLocalSearch.h"
#include "BiddingLocalSearchAgent.h"
#include "BinaryTreeLocalSearchAgent.h"
#include "DictatorshipLocalSearchAgent.h"
#include "SubsetOfLocalSearchAgents.h"
#include "ImitativeLocalSearchAgent.h"
#include "Oracle.h"
#include "General.hpp"
#include "Qlearning.h"
#include "CoopQlearning.h"
#include "Sarsa.h"
#include "CoopSarsa.h"
#include "WocLocalSearch.h"
#include "UnitTest++\UnitTest++.h"
#include "UnitTest++\TestReporterStdout.h"


using namespace std;

//GLobal variables
int Agent::numOfAgents                              = 0;
int Environment::nbrOfEnvironments                  = 0;
int BiddingLocalSearchAgent::target                 = -99;
int DictatorshipLocalSearchAgent::onlyTarget        = -99;
double BiddingLocalSearchAgent::highestBid          = -1.0;

//main method
int main(int argc, char* argv[])
{
/* /// Unit Testing: use to test and verify new methods
//Uncomment for running some Unit testing (will not continue program execution after unit testing)
cout<<"Running all unit tests..."<<endl;
return UnitTest::RunAllTests(); //runs all unit tests

// To run a single test suite
cout<<"Running a UnitTest test suite..."<<endl;
UnitTest::TestReporterStdout reporter;
UnitTest::TestRunner runner( reporter );
return runner.RunTestsIf( UnitTest::Test::GetTestList() ,  "SuiteOne" , UnitTest::True(), 0 );
*/

std::srand ( unsigned ( std::time(0) ) ); // seed rand with time
///-----------------------------------------------------------------------
/// START of Test
///-----------------------------------------------------------------------
/// Environment initialization
cout << "----------- *** START OF TEST *** -----------" <<endl;


int rowInput;
int testEpisodesInput;
int nbrOfIterationsInput;
int nbrOfAgentsInput;
std::cout << "Select the number of test episodes for this experiment: "; cin  >> testEpisodesInput;
std::cout << "Select the number of iterations in each episode       : "; cin  >> nbrOfIterationsInput;
std::cout << "Select 'n' for a n-by-n environment size              : "; cin  >> rowInput;
std::cout << "Select the number of agents to be evaluated           : "; cin  >> nbrOfAgentsInput;


Environment e(rowInput, rowInput, 1);   // parameters = rows, columns, observation range (default is 1)
int environmentSize         = e.getEnvironmentSize();
int columns                 = e.getColumns();
int observationRange        = e.getObservationRange();

Test aTest(nbrOfIterationsInput, nbrOfAgentsInput, observationRange); //nbr of iteration, nbr of evaluated agents, obs range
int testIterations          = aTest.getIterations();
int numberOfEvaluatedAgents = aTest.getNumberOfEvaluatedAgents();
int numberOfTests           = testEpisodesInput;  // the number of test episodes
bool jumpingForbidden       = true; // To allow jumping beyond the observation range. Leave as default = true

std::string filename_good = "specialObjectsPatterns"        + NumberToString(numberOfEvaluatedAgents)  + "_" + NumberToString(environmentSize)  + "_" + NumberToString(numberOfTests) + "_" + NumberToString(testIterations) + ".txt";//
std::string filename_evil = "evilSpecialObjectsPatterns"    + NumberToString(numberOfEvaluatedAgents)  + "_" + NumberToString(environmentSize)  + "_" + NumberToString(numberOfTests) + "_" + NumberToString(testIterations) + ".txt";//
dynamicallyGenerateSpecialObjectPatterns(environmentSize, columns, (numberOfTests+10), (testIterations+10), filename_good, filename_evil);


std::vector<std::vector<int> > allGoodObjectPositions;
std::vector<std::vector<int> > allEvilObjectPositions;
std::vector<int>  goodObjPositions;
std::vector<int>  evilObjPositions;


double *averageRewards      = new double[environmentSize];
initializeArray(averageRewards, environmentSize, 0.0);
double *fakeReward          = new double[environmentSize];
initializeArray(fakeReward, environmentSize, 0.0);
double *binaryTreeRewards   = new double[numberOfEvaluatedAgents];
initializeArray(binaryTreeRewards, numberOfEvaluatedAgents, 0.0);
int *binaryTreeTargets      = new int[numberOfEvaluatedAgents];
initializeArray(binaryTreeTargets, numberOfEvaluatedAgents, 1);


// intialize RL agents
int trainingIterations      = 100;
const int nbrOfStates       = environmentSize*testIterations;
double** qlSharedQmatrix    = new double*[nbrOfStates];
double** sarsaSharedQmatrix = new double*[nbrOfStates];
for(int i = 0; i < nbrOfStates; i++){
    qlSharedQmatrix[i]      = new double[9];
    sarsaSharedQmatrix[i]   = new double[9];
}
initializeMatrix(qlSharedQmatrix    , 9, nbrOfStates, 2);
initializeMatrix(sarsaSharedQmatrix , 9, nbrOfStates, 2);
double learning_rate   = 0.3; // alpha
double discount_factor = 0.3; // gamma
double epsilon         = 0.9; // probaibility of QL random action
// end of intialization of RL agents

cout<< "Using "<<columns<<"-by-"<<columns<<" environment class"<<endl;
cout<< "Number of evaluated agents = "<<numberOfEvaluatedAgents<<", with and observation range of : "<<e.getObservationRange()<<endl;

/// create vectors to store agents
std::vector<Agent*>setOfRandomAgents;
std::vector<Agent*>setOfLocalSearchAgents;
std::vector<Agent*>setOfFrLocalSearchAgents;
std::vector<Agent*>setOfWOCLocalSearchAgents;
std::vector<Agent*>setOfBiddingLocalSearchAgents;
std::vector<Agent*>setOfDictatorshipLocalSearchAgents;
std::vector<Agent*>setOfBinaryTreeLocalSearchAgents;

Oracle oracleToFollow(rand()%environmentSize +1, "Oracle to imitate", testIterations);
std::vector<Agent*>setOfOracleAgents;
std::vector<Agent*>setOfQlearningAgents;
std::vector<Agent*>setOfSarsaAgents;
std::vector<Agent*>setOfCoopQlearningAgents;
std::vector<Agent*>setOfCoopSarsaAgents;
std::vector<Agent*>setOfImitativeLocalSearchAgents;

// vectors to hold group rewards across tests
std::vector<double> randomAgentGroupRewards         , localSearchGroupRewards                   ,
                    frLocalSearchGroupRewards       , binaryTreeLocalSearchGroupRewards         ,
                    biddingLocalSearchGroupRewards  , dictatorshipLocalSearchAgentGroupRewards  ,
                    qLearningGroupRewards           , sarsaGroupRewards                         ,
                    coopQlearningGroupRewards       , coopSarsaGroupRewards                     ,
                    imitativeLocalSearchGroupRewards, oracleGroupRewards                        ,
                    wocLocalSearchGroupRewards      ;

// generate a vector holding a random permutation of the possible agent positions
std::vector<int> randomPositions = generateRandomPermutation(environmentSize);

for (int i = 0; i<numberOfEvaluatedAgents; i++){
    int randPosition = randomPositions.at(i%environmentSize + 1);//rand()%environmentSize + 1;
    /// instantiate agents
    RandomAgent                     *aRandomAgent                   = new RandomAgent                   (randPosition, "Random agent"                           , testIterations);
    LocalSearchAgent                *aLocalSearchAgent              = new LocalSearchAgent              (randPosition, "Local search agent"                     , testIterations);
    FrLocalSearch                   *aFrLocalSearchAgent            = new FrLocalSearch                 (randPosition, "Local search agent using fake reward"   , testIterations);
    WocLocalSearch                  *aWOCLocalSearchAgent           = new WocLocalSearch                (randPosition, "Local search agent using WOC"           , testIterations);
    BiddingLocalSearchAgent         *aBiddingLocalSearchAgent       = new BiddingLocalSearchAgent       (randPosition, "Bidding local search agent"             , testIterations);
    DictatorshipLocalSearchAgent    *aDictatorLocalSearchAgent      = new DictatorshipLocalSearchAgent  (randPosition, "Dictatorship local search agent"        , testIterations);
    BinaryTreeLocalSearchAgent      *aBinaryTreeLocalSearchAgent    = new BinaryTreeLocalSearchAgent    (randPosition, "Binary tree local search agent"         , testIterations, (i+1), numberOfEvaluatedAgents);

    Oracle *anOracleAgent                                           = new Oracle                        (randPosition, "Oracle agent"                           , testIterations);
    Qlearning *aQlearningAgent                                      = new Qlearning                     (randPosition, "Qlearning agent"                        , testIterations, environmentSize, learning_rate, discount_factor, epsilon);
    Sarsa *aSarsaAgent                                              = new Sarsa                         (randPosition, "SARSA agent"                            , testIterations, environmentSize, learning_rate, discount_factor, epsilon);
    CoopQlearning *aCoopQlearningAgent                              = new CoopQlearning                 (randPosition, "Qlearning collective"                   , testIterations, environmentSize, learning_rate, discount_factor, epsilon, qlSharedQmatrix); //0.9, 0.8, 0.9
    CoopSarsa *aCoopSarsaAgent                                      = new CoopSarsa                     (randPosition, "SARSA collective"                       , testIterations, environmentSize, learning_rate, discount_factor, epsilon, sarsaSharedQmatrix);
    ImitativeLocalSearchAgent *anImitativeLocalSearchAgent          = new ImitativeLocalSearchAgent     (randPosition, "Local Search imitating an Oracle"       , testIterations);

    /// group agents of same type in a vector
    setOfRandomAgents.push_back(aRandomAgent);
    setOfLocalSearchAgents.push_back(aLocalSearchAgent);
    setOfFrLocalSearchAgents.push_back(aFrLocalSearchAgent);
    setOfWOCLocalSearchAgents.push_back(aWOCLocalSearchAgent);
    setOfBiddingLocalSearchAgents.push_back(aBiddingLocalSearchAgent);
    setOfDictatorshipLocalSearchAgents.push_back(aDictatorLocalSearchAgent);
    setOfBinaryTreeLocalSearchAgents.push_back(aBinaryTreeLocalSearchAgent);

    setOfOracleAgents.push_back(anOracleAgent);
    setOfQlearningAgents.push_back(aQlearningAgent);
    setOfSarsaAgents.push_back(aSarsaAgent);
    setOfCoopQlearningAgents.push_back(aCoopQlearningAgent);
    setOfCoopSarsaAgents.push_back(aCoopSarsaAgent);
    setOfImitativeLocalSearchAgents.push_back(anImitativeLocalSearchAgent);


}

/// Special Objects initialization
SpecialAgent good(1, "Good",testIterations);
SpecialAgent evil(1, "Evil", testIterations);

allGoodObjectPositions = readPatternsFromFile(filename_good);
allEvilObjectPositions = readPatternsFromFile(filename_evil);


///  -----------------------   Test starts here ------------------------------------
for (int currentTest=0; currentTest<numberOfTests; currentTest++){

cout << "Test number :   " << currentTest+1 << endl;

goodObjPositions    = getThisIterationPattern(currentTest, allGoodObjectPositions);
evilObjPositions    = getThisIterationPattern(currentTest, allEvilObjectPositions);
goodObjPositions.at(0);
good.updatePosition(goodObjPositions.at(0));
evil.updatePosition(evilObjPositions.at(0));
// Reward initialization based on the location of Good and Evil
e.updateCellRewards(good.getPosition(), evil.getPosition());


///-----------------------------------------------------------------------
/// TRAIN QLEARNING and SARSA
///-----------------------------------------------------------------------
/// reset epsilon for RL agents
for (int i=0; i < numberOfEvaluatedAgents; i++) {
        setOfQlearningAgents.at(i)->setEpsilon(epsilon);
        setOfSarsaAgents.at(i)->setEpsilon(epsilon);
        setOfCoopQlearningAgents.at(i)->setEpsilon(epsilon);
        setOfCoopSarsaAgents.at(i)->setEpsilon(epsilon);
}
// wisdom of the crowds experiment : trainingIterations changes to trainingIterations/5
for (int x =0; x < trainingIterations; x++) {
    for (int currentIteration =1; currentIteration <= testIterations; currentIteration++){
        int lastAction      = -99;
        for (int i=0; i < setOfSarsaAgents.size(); i++){ /// SARSA only
            /* wisdom of the crowds experiment*/

            setOfSarsaAgents.at(i)->setSecondLastState();
            lastAction          = setOfSarsaAgents.at(i)->performAction(currentIteration);
            setOfSarsaAgents.at(i)->setSecondLastAction(lastAction);
            setOfSarsaAgents.at(i)->setPosition(lastAction, columns, currentIteration);

            // Coop SARSA
            setOfCoopSarsaAgents.at(i)->setSecondLastState();
            lastAction          = setOfCoopSarsaAgents.at(i)->performAction(currentIteration);
            setOfCoopSarsaAgents.at(i)->setSecondLastAction(lastAction);
            setOfCoopSarsaAgents.at(i)->setPosition(lastAction, columns, currentIteration);
        }
        for (int i=0; i < setOfQlearningAgents.size(); i++){ /// QLearning only
            // wisdom of the crowds experiment

            lastAction          = setOfQlearningAgents.at(i)->performAction(currentIteration);
            setOfQlearningAgents.at(i)->setPosition(lastAction, columns, currentIteration);

            // Coop QL
            lastAction          = setOfCoopQlearningAgents.at(i)->performAction(currentIteration);
            setOfCoopQlearningAgents.at(i)->setPosition(lastAction, columns, currentIteration);
        }


        good.updatePosition(goodObjPositions.at(currentIteration));
        evil.updatePosition(evilObjPositions.at(currentIteration));
        e.updateCellRewards(good.getPosition(), evil.getPosition());


        e.sendVirtualReward(setOfSarsaAgents);
        e.sendVirtualReward(setOfQlearningAgents);
        e.sendVirtualReward(setOfCoopQlearningAgents);
        e.sendVirtualReward(setOfCoopSarsaAgents);

        for (int i=0; i < numberOfEvaluatedAgents; i++){ /// SARSA only
            // wisdom of the crowds experiment

            lastAction  = setOfSarsaAgents.at(i)->performAction(currentIteration);
            // a' = lastAction; s' = currentPosition; a = secondLastAction ; s = lastState
            setOfSarsaAgents.at(i)->updateQMatrix(currentIteration);

            // Coop SARSA
            lastAction  = setOfCoopSarsaAgents.at(i)->performAction(currentIteration);
            // a' = lastAction; s' = currentPosition; a = secondLastAction ; s = lastState
            setOfCoopSarsaAgents.at(i)->updateQMatrix(currentIteration);

        }
        for (int i=0; i < numberOfEvaluatedAgents; i++){ /// QLearning only
            // wisdom of the crowds experiment
            setOfQlearningAgents.at(i)->updateQMatrix();

            // Coop QL
            setOfCoopQlearningAgents.at(i)->updateQMatrix();
        }
    }
    /// reset agent positions and rewards
    for (int i=0; i < numberOfEvaluatedAgents; i++) { /// both Qlearning and SARSA
        // wisdom of the crowds experiment
        setOfQlearningAgents.at(i)->reset();
        setOfSarsaAgents.at(i)->reset();

        setOfCoopQlearningAgents.at(i)->reset();
        setOfCoopSarsaAgents.at(i)->reset();
    }

    good.reset(goodObjPositions);
    evil.reset(evilObjPositions);
    e.updateCellRewards(good.getPosition(), evil.getPosition());


}
/// reset epsilon for RL agents
for (int i=0; i < numberOfEvaluatedAgents; i++) {
        setOfQlearningAgents.at(i)->setEpsilon(0.0);
        setOfSarsaAgents.at(i)->setEpsilon(0.0);
        setOfCoopQlearningAgents.at(i)->setEpsilon(0.0);
        setOfCoopSarsaAgents.at(i)->setEpsilon(0.0);
}

///-----------------------------------------------------------------------
/// END QLEARNING and SARSA TRAINING
///-----------------------------------------------------------------------

///-----------------------------------------------------------------------
/// Observations
///-----------------------------------------------------------------------
for (int currentIteration =1; currentIteration <= testIterations; currentIteration++){

    e.sendObservations(setOfRandomAgents                    , observationRange);
    e.sendObservations(setOfLocalSearchAgents               , observationRange);
    e.sendObservations(setOfFrLocalSearchAgents             , observationRange);
    e.sendObservations(setOfWOCLocalSearchAgents            , observationRange);
    e.sendObservations(setOfBiddingLocalSearchAgents        , observationRange);
    e.sendObservations(setOfDictatorshipLocalSearchAgents   , observationRange);
    e.sendObservations(setOfBinaryTreeLocalSearchAgents     , observationRange);
    e.sendObservations(setOfOracleAgents                    , observationRange);
    e.sendObservations(setOfQlearningAgents                 , observationRange);
    e.sendObservations(setOfSarsaAgents                     , observationRange);
    e.sendObservations(setOfCoopQlearningAgents             , observationRange);
    e.sendObservations(setOfCoopSarsaAgents                 , observationRange);
    e.sendObservations(setOfImitativeLocalSearchAgents      , observationRange);

    // update bids for bidding local search agents
    for (int i=0; i < numberOfEvaluatedAgents; i++) {
        setOfBiddingLocalSearchAgents.at(i)->updateMyBid(columns, environmentSize);
        setOfFrLocalSearchAgents.at(i)->propagateFakeRewards(fakeReward);
        setOfWOCLocalSearchAgents.at(i)->propagateAverageRewards(averageRewards);
        setOfBinaryTreeLocalSearchAgents.at(i)->setTargets(columns, binaryTreeRewards, binaryTreeTargets);
    }

    setOfDictatorshipLocalSearchAgents.at(0)->updateSingleBid(columns, environmentSize);
///-----------------------------------------------------------------------
/// Actions
///-----------------------------------------------------------------------

    int anAction = -99;
    for (int i=0; i < numberOfEvaluatedAgents; i++) {
        /// Random agent
        anAction = setOfRandomAgents.at(i)->performAction();
        setOfRandomAgents.at(i)->setPosition(anAction, columns, environmentSize);
        /// Local search agent
        anAction = setOfLocalSearchAgents.at(i)->performAction(columns);
        setOfLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);

        /// Local search agent using fake reward
        anAction = setOfFrLocalSearchAgents.at(i)->performAction(fakeReward, columns, jumpingForbidden);
        setOfFrLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);

        /// Local search agent using WOC
        anAction = setOfWOCLocalSearchAgents.at(i)->performAction(averageRewards, columns, jumpingForbidden);
        setOfWOCLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);

        /// Local search agent using bidding
        anAction = setOfBiddingLocalSearchAgents.at(i)->performAction(columns);
        setOfBiddingLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);

        /// Local search agent following one dictator
        anAction = setOfDictatorshipLocalSearchAgents.at(i)->performAction(columns);
        setOfDictatorshipLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);


        /// Tree like Local search agent group
        anAction = setOfBinaryTreeLocalSearchAgents.at(i)->performAction(columns);
        setOfBinaryTreeLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);


        /// Oracle agent
        anAction = setOfOracleAgents.at(i)->performAction(goodObjPositions.at(currentIteration),columns,environmentSize); // Oracle agent
        setOfOracleAgents.at(i)->setPosition(anAction, columns, environmentSize);
        anAction = oracleToFollow.performAction(goodObjPositions.at(currentIteration),columns,environmentSize);
        oracleToFollow.setPosition(anAction, columns, environmentSize);
        /// Local search agent using imitation
        anAction = setOfImitativeLocalSearchAgents.at(i)->performAction(columns, oracleToFollow.getPosition(), environmentSize);
        setOfImitativeLocalSearchAgents.at(i)->setPosition(anAction, columns, environmentSize);

        /// Qlearning agent
        anAction = setOfQlearningAgents.at(i)->performAction(currentIteration);
        setOfQlearningAgents.at(i)->setPosition(anAction, columns, currentIteration);
        //Coop QL
        anAction = setOfCoopQlearningAgents.at(i)->performAction(currentIteration);
        setOfCoopQlearningAgents.at(i)->setPosition(anAction, columns, currentIteration);
        /// Sarsa agent
        anAction = setOfSarsaAgents.at(i)->performAction(currentIteration);
        setOfSarsaAgents.at(i)->setPosition(anAction, columns, currentIteration);
        //Coop Sarsa
        anAction = setOfCoopSarsaAgents.at(i)->performAction(currentIteration);
        setOfCoopSarsaAgents.at(i)->setPosition(anAction, columns, currentIteration);


    }


    good.updatePosition(goodObjPositions.at(currentIteration));
    evil.updatePosition(evilObjPositions.at(currentIteration));
    e.updateCellRewards(good.getPosition(), evil.getPosition());




///-----------------------------------------------------------------------
/// Rewards
///-----------------------------------------------------------------------
    e.sendReward(setOfRandomAgents                      , currentIteration);
    e.sendReward(setOfLocalSearchAgents                 , currentIteration);
    e.sendReward(setOfFrLocalSearchAgents               , currentIteration);
    e.sendReward(setOfWOCLocalSearchAgents              , currentIteration);
    e.sendReward(setOfBiddingLocalSearchAgents          , currentIteration);
    e.sendReward(setOfDictatorshipLocalSearchAgents     , currentIteration);
    e.sendReward(setOfBinaryTreeLocalSearchAgents       , currentIteration);
    e.sendReward(setOfOracleAgents                      , currentIteration);
    e.sendReward(setOfQlearningAgents                   , currentIteration);
    e.sendReward(setOfSarsaAgents                       , currentIteration);
    e.sendReward(setOfImitativeLocalSearchAgents        , currentIteration);
    e.sendReward(setOfCoopQlearningAgents               , currentIteration);
    e.sendReward(setOfCoopSarsaAgents                   , currentIteration);


}   // end of test iteration


///-----------------------------------------------------------------------
/// Scores
///-----------------------------------------------------------------------
double  randomAgentRewards                  = 0, localSearchRewards                         = 0,
        frLocalSearchRewards                = 0, localSearchAgentsSubgroup1Rewards          = 0,
        localSearchAgentsSubgroup2Rewards   = 0, localSearchAgentsSubgroup3Rewards          = 0,
        localSearchAgentsSubgroup4Rewards   = 0, binaryTreeLocalSearchAgentRewards          = 0,
        biddingLocalSearchAgentRewards      = 0, dictatorshipLocalSearchAgentRewards        = 0,
        oracleRewards                       = 0, qLearningRewards                           = 0,
        sarsaRewards                        = 0, coopQlearningRewards                       = 0,
        coopSarsaRewards                    = 0, imitativeLocalSearchAgentRewards           = 0,
        wocLocalSearchRewards               = 0;


for (int i=0; i < numberOfEvaluatedAgents; i++) {
    setOfRandomAgents.at(i)->calculateAvgReward();
    randomAgentRewards                      += setOfRandomAgents.at(i)->getAvgReward();
    setOfFrLocalSearchAgents.at(i)->calculateAvgReward();
    frLocalSearchRewards                    += setOfFrLocalSearchAgents.at(i)->getAvgReward();

    setOfWOCLocalSearchAgents.at(i)->calculateAvgReward();
    wocLocalSearchRewards                   += setOfWOCLocalSearchAgents.at(i)->getAvgReward();

    setOfLocalSearchAgents.at(i)->calculateAvgReward();
    localSearchRewards                      += setOfLocalSearchAgents.at(i)->getAvgReward();

    setOfBiddingLocalSearchAgents.at(i)->calculateAvgReward();
    biddingLocalSearchAgentRewards          += setOfBiddingLocalSearchAgents.at(i)->getAvgReward();
    setOfDictatorshipLocalSearchAgents.at(i)->calculateAvgReward();
    dictatorshipLocalSearchAgentRewards     += setOfDictatorshipLocalSearchAgents.at(i)->getAvgReward();
    setOfBinaryTreeLocalSearchAgents.at(i)->calculateAvgReward();
    binaryTreeLocalSearchAgentRewards       += setOfBinaryTreeLocalSearchAgents.at(i)->getAvgReward();

    setOfOracleAgents.at(i)->calculateAvgReward();
    oracleRewards                           += setOfOracleAgents.at(i)->getAvgReward();
    setOfQlearningAgents.at(i)->calculateAvgReward();
    qLearningRewards                        += setOfQlearningAgents.at(i)->getAvgReward();
    setOfCoopQlearningAgents.at(i)->calculateAvgReward();
    coopQlearningRewards                    += setOfCoopQlearningAgents.at(i)->getAvgReward();
    setOfSarsaAgents.at(i)->calculateAvgReward();
    sarsaRewards                            += setOfSarsaAgents.at(i)->getAvgReward();
    setOfCoopSarsaAgents.at(i)->calculateAvgReward();
    coopSarsaRewards                        += setOfCoopSarsaAgents.at(i)->getAvgReward();
    setOfImitativeLocalSearchAgents.at(i)->calculateAvgReward();
    imitativeLocalSearchAgentRewards        += setOfImitativeLocalSearchAgents.at(i)->getAvgReward();
}


randomAgentGroupRewards.push_back(randomAgentRewards/(double)numberOfEvaluatedAgents);
localSearchGroupRewards.push_back(localSearchRewards/(double)numberOfEvaluatedAgents);
frLocalSearchGroupRewards.push_back(frLocalSearchRewards/(double)numberOfEvaluatedAgents);
wocLocalSearchGroupRewards.push_back(wocLocalSearchRewards/(double)numberOfEvaluatedAgents);
biddingLocalSearchGroupRewards.push_back(biddingLocalSearchAgentRewards/(double)numberOfEvaluatedAgents);
dictatorshipLocalSearchAgentGroupRewards.push_back(dictatorshipLocalSearchAgentRewards/(double)numberOfEvaluatedAgents);
binaryTreeLocalSearchGroupRewards.push_back(binaryTreeLocalSearchAgentRewards/(double)numberOfEvaluatedAgents);

oracleGroupRewards.push_back(oracleRewards/(double)numberOfEvaluatedAgents);
qLearningGroupRewards.push_back(qLearningRewards/(double)numberOfEvaluatedAgents);
sarsaGroupRewards.push_back(sarsaRewards/(double)numberOfEvaluatedAgents);
coopQlearningGroupRewards.push_back(coopQlearningRewards/(double)numberOfEvaluatedAgents);
coopSarsaGroupRewards.push_back(coopSarsaRewards/(double)numberOfEvaluatedAgents);
imitativeLocalSearchGroupRewards.push_back(imitativeLocalSearchAgentRewards/(double)numberOfEvaluatedAgents);


//cout << "---------------- *** END OF TEST *** ----------------" <<endl;
// generate new random positions permutation for the new test
randomPositions = generateRandomPermutation(environmentSize);
for (int i=0; i < numberOfEvaluatedAgents; i++) {
    setOfRandomAgents.at(i)->resetAll(randomPositions.at(i));
    setOfLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    setOfFrLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    setOfWOCLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    setOfBinaryTreeLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    setOfBiddingLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    setOfDictatorshipLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    setOfOracleAgents.at(i)->resetAll(randomPositions.at(i));
    setOfQlearningAgents.at(i)->resetAll(randomPositions.at(i));
    setOfSarsaAgents.at(i)->resetAll(randomPositions.at(i));
    setOfCoopQlearningAgents.at(i)->resetAll(randomPositions.at(i));
    setOfCoopSarsaAgents.at(i)->resetAll(randomPositions.at(i));
    setOfImitativeLocalSearchAgents.at(i)->resetAll(randomPositions.at(i));
    oracleToFollow.resetAll(randomPositions.at(i));
}


initializeArray(fakeReward          , environmentSize        , 0.0);
initializeArray(averageRewards      , environmentSize        , 0.0);
initializeArray(binaryTreeRewards   , numberOfEvaluatedAgents, 0.0);
initializeArray(binaryTreeTargets   , numberOfEvaluatedAgents, 0);

initializeMatrix(qlSharedQmatrix    , 9, nbrOfStates, 2);
initializeMatrix(sarsaSharedQmatrix , 9, nbrOfStates, 2);

BiddingLocalSearchAgent::target             = -99;
DictatorshipLocalSearchAgent::onlyTarget    = -99;
BiddingLocalSearchAgent::highestBid         = -1.0;

}/// end for loop of new test
// average rewards across tests
double  finalRandomAgentGroupRewards                = 0, finalLocalSearchGroupRewards           = 0,
        finalBiddingLocalSearchGroupRewards         = 0, finalFrLocalSearchGroupRewards         = 0,
        finalDictatorshipLocalSearchGroupRewards    = 0, finalBinaryTreeLocalSearchGroupRewards = 0,
        finalUnionSubsetOfLocalSearchGroupsRewards  = 0, finalOracleGroupRewards                = 0,
        finalQlearningGroupRewards                  = 0, finalSarsaGroupRewards                 = 0,
        finalCoopQlearningGroupRewards              = 0, finalCoopSarsaGroupRewards             = 0,
        finalImitativeLocalSearchGroupRewards       = 0, finalWocLocalSearchGroupRewards        = 0;


for (int i=0; i < numberOfTests; i++) {
    finalRandomAgentGroupRewards            = CalculateMean(randomAgentGroupRewards);
    finalLocalSearchGroupRewards            = CalculateMean(localSearchGroupRewards);
    finalFrLocalSearchGroupRewards          = CalculateMean(frLocalSearchGroupRewards);
    finalWocLocalSearchGroupRewards         = CalculateMean(wocLocalSearchGroupRewards);

    finalBinaryTreeLocalSearchGroupRewards  = CalculateMean(binaryTreeLocalSearchGroupRewards);
    finalBiddingLocalSearchGroupRewards     = CalculateMean(biddingLocalSearchGroupRewards);
    finalDictatorshipLocalSearchGroupRewards= CalculateMean(dictatorshipLocalSearchAgentGroupRewards);

    finalOracleGroupRewards                 = CalculateMean(oracleGroupRewards);
    finalQlearningGroupRewards              = CalculateMean(qLearningGroupRewards);
    finalSarsaGroupRewards                  = CalculateMean(sarsaGroupRewards);
    finalCoopQlearningGroupRewards          = CalculateMean(coopQlearningGroupRewards);
    finalCoopSarsaGroupRewards              = CalculateMean(coopSarsaGroupRewards);
    finalImitativeLocalSearchGroupRewards   = CalculateMean(imitativeLocalSearchGroupRewards);

}
cout << "Agent scores:" <<endl;
cout << "Average reward for Random agents                   = " << finalRandomAgentGroupRewards                 << endl;
cout << "Average reward for Local Search agents             = " << finalLocalSearchGroupRewards                 << endl;
cout << "Average reward for FR Local Search Collective      = " << finalFrLocalSearchGroupRewards               << endl;
cout << "Average reward for WOC Local Search Collective     = " << finalWocLocalSearchGroupRewards              << endl;

cout << "Average reward for Bidding LS Collective           = " << finalBiddingLocalSearchGroupRewards          << endl;
cout << "Average reward for Dictator LS Collective          = " << finalDictatorshipLocalSearchGroupRewards     << endl;
cout << "Average reward for LS agents binary tree           = " << finalBinaryTreeLocalSearchGroupRewards       << endl;

cout << "Average reward for Oracle agents                   = " << finalOracleGroupRewards                      << endl;
cout << "Average reward for QLearning agents                = " << finalQlearningGroupRewards                   << endl;
cout << "Average reward for Sarsa agents                    = " << finalSarsaGroupRewards                       << endl;
cout << "Average reward for Cooperative QL Collective       = " << finalCoopQlearningGroupRewards               << endl;
cout << "Average reward for Cooperative Sarsa Collective    = " << finalCoopSarsaGroupRewards                   << endl;
cout << "Average reward for Imitative LS Collective         = " << finalImitativeLocalSearchGroupRewards        << endl;
//cout << "Average reward for Imitative LS Collective         = " << finalImitativeLocalSearchGroupRewards<< endl;

//write data to file
ofstream myfile;
myfile.open ("results.txt", ios::app);
myfile << "\n";
myfile << "Writing to results.\n";
myfile << "Experiment run on                                    : " << currentDateTime()                        <<"\n";
myfile << "Number of evaluated agents                           : " << numberOfEvaluatedAgents                  <<"\n";
myfile << "Number of tests                                      : " << numberOfTests                            <<"\n";
myfile << "Number of test iterations                            : " << testIterations                           <<"\n";
myfile << "Environment dimensions                               : " << columns <<"-by-"<< columns               <<"\n";
myfile << "Agent scores                                         : " << "\n";
myfile << "Average reward for Random agents                     = " << finalRandomAgentGroupRewards             <<"\n";
myfile << "Average reward for Local Search agents               = " << finalLocalSearchGroupRewards             <<"\n";
myfile << "Average reward for FR Local Search Collective        = " << finalFrLocalSearchGroupRewards           <<"\n";
myfile << "Average reward for WOC Local Search Collective       = " << finalWocLocalSearchGroupRewards          <<"\n";
myfile << "Average reward for Bidding LS Collective             = " << finalBiddingLocalSearchGroupRewards      <<"\n";
myfile << "Average reward for Dictator LS Collective            = " << finalDictatorshipLocalSearchGroupRewards <<"\n";
myfile << "Average reward for LS agents binary tree             = " << finalBinaryTreeLocalSearchGroupRewards   <<"\n";
myfile << "Average reward for Oracle agents                     = " << finalOracleGroupRewards                  <<"\n";
myfile << "Average reward for QLearning agents                  = " << finalQlearningGroupRewards               <<"\n";
myfile << "Average reward for Cooperative QL Collective         = " << finalCoopQlearningGroupRewards           <<"\n";
myfile << "Average reward for Sarsa agents                      = " << finalSarsaGroupRewards                   <<"\n";
myfile << "Average reward for Cooperative Sarsa Collective      = " << finalCoopSarsaGroupRewards               <<"\n";
myfile << "Average reward for Imitative LS Collective           = " << finalImitativeLocalSearchGroupRewards    <<"\n";

myfile << "-----------------------*** End of results ***-----------------------"   <<"\n";
myfile.close();

ofstream myCSVfile;
myCSVfile.open ("csvResults.csv", ios::app);
if (myCSVfile.is_open()){
myCSVfile   <<numberOfEvaluatedAgents                   <<","
            <<numberOfTests                             <<","
            <<testIterations                            <<","
            <<columns<<","<<columns                     <<","
            <<trainingIterations                        <<","
            <<finalRandomAgentGroupRewards              <<","
            <<finalLocalSearchGroupRewards              <<","
            <<finalFrLocalSearchGroupRewards            <<","
            <<finalWocLocalSearchGroupRewards           <<","
            <<finalBiddingLocalSearchGroupRewards       <<","
            <<finalDictatorshipLocalSearchGroupRewards  <<","
            <<finalBinaryTreeLocalSearchGroupRewards    <<","
            <<finalImitativeLocalSearchGroupRewards     <<","
            <<finalQlearningGroupRewards                <<","
            <<finalCoopQlearningGroupRewards            <<","
            <<finalSarsaGroupRewards                    <<","
            <<finalCoopSarsaGroupRewards                <<","
            <<finalOracleGroupRewards                   <<","
            <<learning_rate                             <<","
            <<discount_factor                           <<","
            <<epsilon                                   <<endl;

            myCSVfile.close();
}
else{
        cout << " -- Warning -- " << endl;
        cout << "Unable to open and save results to file" <<endl;
}

//-----------------------------------

///-----------------------------------------------------------------------
/// END of Test
///-----------------------------------------------------------------------

for (std::vector<Agent*>::iterator it = setOfRandomAgents.begin() ; it != setOfRandomAgents.end(); ++it){
    delete (*it);
}
setOfRandomAgents.clear();
for (std::vector<Agent*>::iterator it = setOfLocalSearchAgents.begin() ; it != setOfLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfLocalSearchAgents.clear();

for (std::vector<Agent*>::iterator it = setOfFrLocalSearchAgents.begin() ; it != setOfFrLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfFrLocalSearchAgents.clear();

for (std::vector<Agent*>::iterator it = setOfWOCLocalSearchAgents.begin() ; it != setOfWOCLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfWOCLocalSearchAgents.clear();

for (std::vector<Agent*>::iterator it = setOfBiddingLocalSearchAgents.begin() ; it != setOfBiddingLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfBiddingLocalSearchAgents.clear();


for (std::vector<Agent*>::iterator it = setOfDictatorshipLocalSearchAgents.begin() ; it != setOfDictatorshipLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfDictatorshipLocalSearchAgents.clear();

for (std::vector<Agent*>::iterator it = setOfBinaryTreeLocalSearchAgents.begin() ; it != setOfBinaryTreeLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfBinaryTreeLocalSearchAgents.clear();


for (std::vector<Agent*>::iterator it = setOfOracleAgents.begin() ; it != setOfOracleAgents.end(); ++it){
    delete (*it);
}
setOfOracleAgents.clear();

for (std::vector<Agent*>::iterator it = setOfQlearningAgents.begin() ; it != setOfQlearningAgents.end(); ++it){
    delete (*it);
}
setOfQlearningAgents.clear();

for (std::vector<Agent*>::iterator it = setOfSarsaAgents.begin() ; it != setOfSarsaAgents.end(); ++it){
    delete (*it);
}
setOfSarsaAgents.clear();

for (std::vector<Agent*>::iterator it = setOfCoopSarsaAgents.begin() ; it != setOfCoopSarsaAgents.end(); ++it){
    delete (*it);
}
setOfCoopSarsaAgents.clear();

for (std::vector<Agent*>::iterator it = setOfCoopQlearningAgents.begin() ; it != setOfCoopQlearningAgents.end(); ++it){
    delete (*it);
}
setOfCoopQlearningAgents.clear();

for (std::vector<Agent*>::iterator it = setOfImitativeLocalSearchAgents.begin() ; it != setOfImitativeLocalSearchAgents.end(); ++it){
    delete (*it);
}
setOfImitativeLocalSearchAgents.clear();

return 0;
}
///-----------------------------------------------------------------------
///-----------------------------------------------------------------------
///-----------------------------------------------------------------------
///-----------------------------------------------------------------------
