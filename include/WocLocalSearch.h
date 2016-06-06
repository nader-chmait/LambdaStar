#ifndef WOCLOCALSEARCH_H
#define WOCLOCALSEARCH_H

#include "FrLocalSearch.h"


class WocLocalSearch : public FrLocalSearch
{
    public:
        WocLocalSearch();
        WocLocalSearch(int, std::string,int);
        virtual ~WocLocalSearch();
        void propagateAverageRewards(double* );
        int performAction(double*, int, bool);

    protected:
    private:
};

#endif // WOCLOCALSEARCH_H
