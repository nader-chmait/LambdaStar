#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Observation.h"
#include <vector>
#include "Agent.h"

//template <typename T>
class Environment
{   private:
         int rows;
         int columns;
         int observationRange;
         int environmentSize = rows*columns;
         static int nbrOfEnvironments;
         double *rewardDistribution;
         //double *landscapeFitness;
         std::vector<int> neighborhoodOfGood;
         std::vector<int> neighborhoodOfEvil;

    public:
        Environment();
        Environment(int, int);
        Environment(int, int, int);
        virtual ~Environment();
        int getColumns();
        int getEnvironmentSize();
        int getNbrOfColumns();
        int getObservationRange();
        void initializeEnvironment(int, int, int);
        Observation generateObservation(int, int);
        void sendObservations(std::vector<Agent*>, int);
        void sendReward(std::vector<Agent*>, int);
        void sendVirtualReward(std::vector<Agent*>);
        void updateCellRewards(int, int);
        void printRewardDistribution();
        double* getRewardDistribution();
        void resetRewardDistribution();
        void randomizeCellRewards(int);
        void nullifyCellRewards();
    protected:

};

#endif // ENVIRONMENT_H
