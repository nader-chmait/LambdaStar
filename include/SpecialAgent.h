#ifndef SPECIALAGENT_H
#define SPECIALAGENT_H

#include "Agent.h"
#include <vector>
#include <string>

class SpecialAgent : public Agent
{
    public:
        SpecialAgent();
        SpecialAgent(int); // : Agent()
        SpecialAgent(int, std::string, int);//:Agent(initialPosition)
        void generatePattern(int);
        int getNextAction(std::vector<int>, int);
        int performAction(std::vector<int>, int);
        void extendPattern(std::vector<int>, int);
        void setExtendedPattern(std::vector<int>);
        virtual ~SpecialAgent();
        std::vector<int> getPattern();
        std::vector<int> getExtendedPattern();
        void reset(std::vector<int>);
    protected:
    private:
        std::vector<int> pattern;
        std::vector<int> extendedPattern;
};

#endif // SPECIALAGENT_H
