#ifndef FRLOCALSEARCH_H
#define FRLOCALSEARCH_H

#include "LocalSearchAgent.h"


class FrLocalSearch : public LocalSearchAgent
{
    public:
        FrLocalSearch();
        FrLocalSearch(int, std::string,int);
        virtual ~FrLocalSearch();
        int performAction(double*, int, bool);
        void propagateFakeRewards(double*);
    protected:
    private:
        bool isInformed;
};

#endif // FRLOCALSEARCH_H
