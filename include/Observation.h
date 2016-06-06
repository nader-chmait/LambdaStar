#ifndef OBSERVATION_H
#define OBSERVATION_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>

class Observation
{
public:
        Observation();
        virtual ~Observation(); // delete[] cellDescription

    protected:
    private:
            //static int     observationSize;
            std::vector<int>     cellDescription; // = new int[n]
            std::vector<double>  cellRewardDescription;

    public:
        void setCellDescription(std::vector<int>);
        void setCellRewardDescription(std::vector<double>);
        std::vector<int> getCellDescription();
        std::vector<double> getCellRewardDescription();
        void printCellDescription(std::vector<int>);
};

#endif // OBSERVATION_H
