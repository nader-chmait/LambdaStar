#ifndef COOPSARSA_H
#define COOPSARSA_H

#include "Sarsa.h"


class CoopSarsa : public Sarsa
{
    public:
        CoopSarsa();
        CoopSarsa(int, std::string, int, int, double, double, double, double**);
        virtual ~CoopSarsa();
    protected:
    private:
};

#endif // COOPSARSA_H
