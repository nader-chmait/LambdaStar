#ifndef BINARYTREELOCALSEARCHAGENT_H
#define BINARYTREELOCALSEARCHAGENT_H

#include <LocalSearchAgent.h>


class BinaryTreeLocalSearchAgent : public LocalSearchAgent
{
    public:
        BinaryTreeLocalSearchAgent();
        BinaryTreeLocalSearchAgent(int, std::string, int, int, int);
        virtual ~BinaryTreeLocalSearchAgent();
        int performAction(int, double*, int*);
        int getIndexInTree();
        vector<int> getChildren();
        bool getIsInternalNode();
        void setTargets(int, double *, int *);
        int updatePosition(int, double *, int *);
    protected:
    private:
        int indexInTree;
        bool isInternalNode;
        vector<int> children;
};

#endif // BINARYTREELOCALSEARCHAGENT_H
