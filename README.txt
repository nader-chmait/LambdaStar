
I. File list
******************************************************************************
Agent.cpp                                                 Implementation of "abstract" class Agent
Agent.h                                                   header file
AgentUnitTest.cpp                                         Unit tests for class Agent 
AgentUnitTest.h                                           Unit test header file
Bid.cpp                                                   Implementation of an "English Auction" Bidding class
Bid.h                                                     header file
BiddingLocalSearchAgent.cpp                               Implementation of interactive Local Search agent using bidding
BiddingLocalSearchAgent.h                                 header file
BinaryTreeLocalSearchAgent.cpp                            Implementation of tree-like team organisation structure
BinaryTreeLocalSearchAgent.h                              header file
CoopQlearning.cpp                                         Implementation of a Q-learning cooperative agent
CoopQlearning.h                                           header file
CoopSarsa.cpp                                             Implementation of a SARSA cooperative agent
CoopSarsa.h                                               header file
DictatorshipLocalSearchAgent.cpp                          Implementation of an autocracy structure
DictatorshipLocalSearchAgent.h                            header file
Environment.cpp                                           Implementation of the Lambda Star environment
Environment.h                                             header file
EnvironmentUnitTest.cpp                                   Unit tests for the Environment class
EnvironmentUnitTest.h                                     header file
FrLocalSearch.cpp                                         Implementation of a local search using stigmergy
FrLocalSearch.h                                           header file
General.cpp                                               Implements  a large set of general useful functionalities
General.hpp                                               header file
GeneralUnitTest.cpp                                       Unit tests for the functionalities in implemented in General.cpp
GeneralUnitTest.h                                         header file
imitativeLocalSearchAgent.cpp                             Implementation of a local search agent imitating an Oracle agent
imitativeLocalSearchAgent.h                               header file
LocalSearchAgent.cpp                                      Implementation of a local search agent
LocalSearchAgent.h                                        header file
LocalSearchAgentUnitTest.cpp                              Unit tests for localSearchAgent class
LocalSearchAgentUnitTest.h                                header file
main.cpp                                                  The main function which runs the intelligence test, defines the agents, the environemnt, observations and rewards
Observation.cpp                                           Implementation of an Observation
Observation.h                                             header file
Oracle.cpp                                                Implementation of an Oracle (expert) agent
Oracle.h                                                  header file
Qlearning.cpp                                             Implementation of a Q-learning algorithm
Qlearning.h                                               header file
RandomAgent.cpp                                           Implementation of a random agent
RandomAgent.h                                             header file
Sarsa.cpp                                                 Implementation of a SARSA algorithm
Sarsa.h                                                   header file
SpecialAgent.cpp                                          Implementation of speacial objects (\oplus and \ominus)
SpecialAgent.h                                            header file
Test.cpp                                                  Implementation of an intelligence Test (episode)
Test.h                                                    header file
WocLocalSearch.cpp                                        Implementation of local search agent using the Wisdom of the crowd
WocLocalSearch.h                                          header file

II. Evaluation framework : Agent-Environment Framework
******************************************************************************

An environment is defined as the world where an agent, or a group of agents, can interact using a set of observations, actions and rewards. The environment  generates observations from the set of observations 'O', and rewards from the set of real numbers, and sends them to the agent. The agent performs actions from a limited set of actions 'A' in response.  An iteration or step 'i' stands for one sequence of observation-action-reward. An observation at iteration 'i' is denoted by 'o_i', while the corresponding action and reward for the same iteration are denoted by 'a_i' and 'r_i' respectively. The string 'o_1a_1r_1o_2a_2r_2' is an example sequence of interactions over two iterations between one agent and its environment.

III. Project description
******************************************************************************
The Lambda Star $\Lambda^*$  environment class used in [Chmait et al. 2016] is an extension of the Lambda environment showing in [Sec. 6.3, Hernandez-Orallo2010] and [Insa-cabrera_theanynt] that focuses on a restricted - but important - set of tasks in AI. 
 The general idea is to evaluate an agent that can perform a set of actions, by placing it in a grid of cells with two special objects, Good ($\oplus$) and  Evil ($\ominus$) travelling in the space using movement patterns of measurable complexities. The rewards are defined as a function of the position of the evaluated agent with respect to the positions of $\oplus$ and $\ominus$. 
 
 An environment space is an m-by-n grid-world populated with a finite set of objects. Each object/agent can have actions from a finite set of actions {up-left, up, up-right, left,  stay, right, down-left, down, down-right}.   All objects can share the same cell at the same time except for $\oplus$ and $\ominus$ where in this case, one of them is randomly chosen to move to the intended cell while the other one keeps its old position. In the context of the agent-environment framework, a test episode consisting of a series of interactions such that: 

1. the environment space is first initialised to an m-by-n toroidal grid-world, and populated with a subset of evaluated agents, and the two special objects $\oplus$ and $\ominus$,
2. the environment sends to each agent a description of its range of 1 Moore neighbour cells [Gray03, Weisstein] and their contents (the rewards in these cells) as an observation,
3. the agents (communicate/interact and) respond to the observations by performing an action, and the special objects perform the next action in their movement pattern,
4. the environment then returns a reward to each evaluated agent based on its position (distance) with respect to the locations of the special objects,
5. this process is repeated again from point #2 until a test episode is completed.

The Lambda Star environment consists of a toroidal grid space in the sense that moving off one border makes an agent appear on the opposite one. Consequently, the distance between two agents is calculated using the surpassing rule (toroidal distance) such that, in a 5-by-5 in grid space for example, the distance between cell (1, 3) and (5, 3) is equal to 1 cell. 

IV. Sample agent beahviors
******************************************************************************
An abstract class 'Agent' is defined with many declared functionalities that will come out to be essential for implementing and evaluating new agent behaviors over the Lambda Star environment. 

New isolated (non-interactive) agent behaviors can be introduced as (one of the) subclasses of 'Agent', providing implementations for its abstract methods as necessary. Interactive agent behaviors, on the other hand, are polymorphic classes redefining and extending the behavior of their isolated agent's superclass. 

Homogeneous collectives of interactive agents are aggregations of two or more interactive agents of the same behavior (class).
Likewise, heterogeneous collectives of agents can be defined as aggregations of two or more interactive agents of different behaviors  (classes). 


III. MIT License
******************************************************************************

Copyright (c) 2016 Nader Chmait

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************