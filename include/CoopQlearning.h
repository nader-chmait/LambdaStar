#ifndef COOPQLEARNING_H
#define COOPQLEARNING_H

#include "Qlearning.h"


class CoopQlearning : public Qlearning
{
    public:
        CoopQlearning();
        CoopQlearning(int, std::string, int, int, double, double, double, double**);
        virtual ~CoopQlearning();
    protected:
    private:
};

#endif // COOPQLEARNING_H
