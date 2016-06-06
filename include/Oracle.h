#ifndef ORACLE_H
#define ORACLE_H

#include "Agent.h"


class Oracle : public Agent
{
    public:
        Oracle();
        Oracle(int, std::string, int);
        virtual ~Oracle();
        int performAction(int, int, int);
        int getOppositeAction(int);
        //bool isPatternUnique();
        int predictLocation(int, int, int, int);
        void setSpecialObjectsPattern(std::vector<int>);


    protected:
    private:
        //std::vector<int> specialObjectsPattern;

};

#endif // ORACLE_H
