/*	This file contains declarations of the standard classes 
	(most of them abstract classes) for the use in RL systems.
	File:		interface_classes.h
	Author:		Bohdana Ratitch
	Last modified:	May, 2002
*/

#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//typedef short bool; //you may have uncomment this typedef, depending on the compiler version

#define DIR_SEP "/"
//#define DIR_SEP "\\" //use this statement if compiling for DOS or Windows 

#define true 1
#define false 0

float gasdev(long *idum); //routive for sampling from Gaussians
float ran1(long *idum);//routine for uniform sampling in [0,1] 

// STATE AND ACTION REPRESENTATION

struct State{ //implementation in sarepr.cpp

  static int dimensionality;// number of variables
  double* x;//array of variables describing a state

  State();
  State(int n);
  /* Construcs a "super"-state that combines n states with current dimensionality.
     Used by random MDP generator mainly.
  */

  State(State& s);
  void operator = (const State& s);
  ~State();
};

std::ostream& operator << (std::ostream& file, const State& s);
/* Overloaded operator for state output to a file or cout.
*/

////////////////////////////////////////////////////////////////////////////////////

struct Subset{//implementation in sarepr.cpp
  /* Hypercube in the state space.
   */
  double* left;//left bounds on state variables
  double* right;//right bounds on state variables
	
  Subset();
  Subset(int N);
  /* Size of the allocated arrays is (State::dimensionality * N)
   */
  ~Subset();
};
///////////////////////////////////////////////////////////////////////

struct Action{//implementation in sarepr.cpp
  /* For descrete actions
   */
		
  int id; /* by default is assigned the ordinal number 
	     as the actions are added to some action set.
	     In other words its value coincides with the action's array 
	     index in the action set to which it belongs 
	     (see ActionSet declaration below).
	  */

  char* description;//may be given a "name"
  double value;	//numerical value of the action
  static int count; //total number of Action objects created

  Action();
  /* Default constructor.
   */

  Action(const char* d);
  /* General constructor.
     Parameters: 
     d : description of an action
  */

  Action(const char* d, double v);
  /* General constructor.
     Parameters:
     d : description of an action
     v : numerical value of an action
  */
  
  void operator = (const Action& b);

  Action(Action& a);

  ~Action();
};

std::ostream& operator << (std::ostream& file, const Action& a);
/* Overloaded operator for action output to a file or cout.
*/

///////////////////////////////////////////////////////////////////////

struct ActionSet{//implementation in sarepr.cpp
  /* Groups together all actions for an RL system.
   */

  int size;//number of actions in the set
  Action* action;//array of actions that belong to this set	
  int added;//indicates how many actions have already been added to the set

  ActionSet();

  ActionSet(int n);
  /* General constructor.
     n : size of the action set
  */

  void create(int n);//as a constructor, can be called after object is created with default constructor

  void addAction(Action& a);
  /* Add action to the action set.
     a : action to be added.
  */

  void operator = (const ActionSet& a);

  ~ActionSet();
};

////////////////////////////////////////////////////////////////////////////////

struct TransitionSamples{//implemented in environment.cpp
  /* This structurte is used by the function ComputeAttributes() implemented in the base class Environment. 
   */

  int Transitions;//number of transitions made from currentState with action a 
  State currentState;	
  Action a;
  State* nextState;//array of collected samples of next states
  double* reward;//array of collected samples of rewards
  int* binIndexNS;//used to calculate an index of a state in a discretized space
  int B;//number of bins in which the state space is discretized
  double* prob;//estimates of the transition probabilites (for each bin)

  TransitionSamples();
  void setTransitionNumber(int T);
  void computeTransitionProbabilities(int b);
  ~TransitionSamples();
};

//////////////////////////////////////////////////////////////////

class Approximator{
  /* Abstract class - base for all FA methods.
   */

 protected:
  //these data members may be used to trace changes during learning
  double MaxParameterChange;
  int NumberParametersChanged;

 public:
  
  virtual int getSize()=0;
  /* Return the number of parameters in this architecture
   */

  virtual void predict(const State& s, double& output) =0;
  /* Predicts an output value for a given input.
     s : reference to the input (state)
     output : returned value of the predicted output
  */

  virtual void learn(const State& s, const double target)=0;
  /* Learns an input-output pair.
     s : input (state)
     target: target output value
  */

  virtual void computeGradient(const State& s, double* GradientVector)=0;
  /* Compute the gradient w.r.t. architecture parameters at the current parameters' values and input s
   */

  virtual void updateParameters(double* delta)=0;
  /* Update parameters by amounts in delta array, 
     possible multiplied by appropriate learning steps.
  */

  virtual void replaceTraces(const State& s, double replace)=0;
  /* Replace traces of parameters, activated by input state s to value replace.
   */

  virtual void decayTraces(double factor)=0;
  /* Decay (multiply) traces by factor.
   */

  virtual void accumulateTraces(const State& s, double amount)=0;
  /* Increment traces by amount for parameters activated by input s.
   */

  virtual void setArchitectureParameters(int argc, char *argv[])=0;
  /* Loads parameters of the architecture from a text file.
     argc : number of supplied arguments
     argv : array of arguments
  */

  virtual void saveArchitectureParameters(int argc, char *argv[])=0;
  /* Saves parameters of the architecture into a text file.
     argc : number of supplied arguments
     argv : array of arguments
  */

  virtual void setLearningParameters(int argc, char *argv[])=0;
  /* Sets learning parameters (e.g. learning step).
     argc : number of supplied arguments
     argv : array of arguments
  */
  
  double getMaxParameterChange(){
    double c=MaxParameterChange;
    MaxParameterChange=0;
    return c;
  }

  int getNumberParametersChanged(){
    return NumberParametersChanged;
  }

 virtual ~Approximator(){}

};

////////////////////////////////////////////////////////////////

class StateActionFA {//implemented in safa.cpp
  /* Contains separate approximator for each action.
   */
	
  int A;//Number of actions (architectures)
  Approximator** fa;/* Array of pointers to approximators.	
		       Each element is a base pointer to a derived approximator object.
		    */
 public:

  StateActionFA();
  ~StateActionFA();

  StateActionFA(int n, Approximator** f);
  /* General constructor.
     n : number of actions (architectures)
     f : pointer to the array of pointers to approximator objects
  */

  int getSize();
  /* Return number of parameters in one of the component architectures 
     (assuming that all of them have the same number of parameters). 
  */

  void getMaxParameterChange(double* changes);
  /* Returns an array of MaxParameterChanges for all component architectures */

  void getNumberParametersChanged(int* changes);
  /* Returns an array of the number of changed parameters for each component architecture
   */

  void predict(const Action& a, const State& s,  double& output);
  /* Predicts an output value with an approximator corresponding a given action.
     a : reference to an action
     s : reference to the input (state)
     output : returned value of the predicted output
  */
	
  void learn(const Action& a, const State& s, double target);	
  /* Learns an input-output pair with an approximator corresponding a given action.
     a : reference to an action
     s : reference to the input (state)
     target : target output value
  */

  void computeGradient(const Action& a, const State& s, double* GradientVector);
  /* Compute the gradient w.r.t. architecture parameters at the current parameters' values and input s.
   */

  void updateParameters(const Action& a, double* delta);
  /* Update parameters by amounts in delta array (possibly multiplied with appropriate learning step).
   */

  void clearTraces(const Action& a, const State& s, double replace);
  /* Clears traces for those actions that were not taken in state s.
     a : action for traces should NOT be replaced
     s : input (state)
     replace : value to which traces should be replaced (usually zero)
  */

  void replaceTraces(const Action& a, const State& s, double trace);
  /* Replaces traces of the architecture for action a for parameters activated by input s
   */

  void decayTraces(double factor);
  /* Decay (multiply) traces of all architectures by factor.
   */
	
  void accumulateTraces(const Action& a, const State& s, double amount);
  /* Increment traces by amount for the architecture of action a for parameters activated by s.
   */

  void setArchitectureParameters(const Action& a, int argc, char *argv[]);
  /* Loads parameters of the architecture corresponding to a given action.
     a : action
     argc : number of supplied arguments
     argv : array of arguments
     What parameters exactly you send in argv depends on the implementation 
     of the class inherited from Approximator class: you send parameters 
     exactly as to the setArchitectureParameters() function of that class.
  */
	
  void saveArchitectureParameters(const Action& a, int argc, char *argv[]);
  /* Saves parameters of the architecture corresponding to a given action.
     a : action
     argc : number of supplied arguments
     argv : array of arguments
     What parameters exactly you send in argv depends on the implementation 
     of the class inherited from Approximator class: you send parameters 
     exactly as to the saveArchitectureParameters() function of that class.
  */

  void saveAllArchitectureParameters(char** fileNames);
	
  void setLearningParameters(const Action& a, int argc, char *argv[]);
  /* Sets learning parameters of the architecture corresponding to a given action.
     a : action
     argc : number of supplied arguments
     argv : array of arguments
  */

  void setAllLearningParameters(int argc, char* argv[]);
  /* Sets (the same) learning parameters of architectures corresponding to each action.
     argc : number of supplied arguments
     argv : array of arguments
     What parameters exactly you send in argv depends on the implementation 
     of the class inherited from Approximator class: you send parameters 
     exactly as to the setLearningParameters() function of that class. 
  */

};

//////////////////////////////////////////////////////////////////////////////

struct Attributes{//implementation in environment.cpp 
  double* Entropy; //array where i-th item is the i-step Entropy
  int n; //up to which step entropy is computed
  double Controllability;
  double RiskFactor;
  double RFconst;
  double RewardVariance;
  double TransitionDistance;
  double TransitionVariability;

  Attributes();

  Attributes(int N, double c);
  /* N : up to which step the State Transition Entropy should be computed.
     c : (multiplicative) threshold for the risk factor (in [0,1)).
  */

  void setParameters(int N, double c);
  /* Sets parameters for the attributes' calculation:
     N : up to which step the State Transition Entropy should be computed.
     c : (multiplicative) threshold for the risk factor (in [0,1)).
  */

  ~Attributes();
};

//////////////////////////////////////////////////////////////////////////////
class Environment {//implementation of some non-virtual functions in environment.cpp

 protected:
  State CurrentState;//current state
  Action CurrentAction;//last action performed by the agent
  double reward;//reward after transition to state s under action a
  static long idum; //used by a random number generator
  static bool seeded;//indicates if the random number generator has been seeded during this program run
	
 public:

  Environment();
  /* Seeds and initiates random number generator.
     This constructor is automatically called when objects of the derived
     classes are created.
  */
	

  virtual void startState(State& start, bool& terminal)=0;
  /* Samples a start state. Sets CurrentState data member to that state 
     and also returns it as "start" paramter. Returns an indicatiof if 
     the sampled state is terminal in "terminal" parameter.   
   */

  virtual void setState(const State& s, bool& terminal)=0;
  /* Sets the CurrentState data member to state "s". Returns an indicatiof if 
     the sampled state is terminal in "terminal" parameter. 
  */

  virtual void transition(const Action& action, State& s_new, double& r_new, bool& terminal)=0;
  /* Implements a transtion form CurrentState in responce to the "action" 
     performed by the agent. Updates its internal variables 
     (CurrentAction and rewrd) and returns values to the agent.
     action: action performed by the agent
     s_new : return value - new state
     r_new : return value - new reward
     terminal: indication of whether s_new is a terminal state
  */

  virtual bool applicable(const State& s, const Action& a)=0;
  /* Checks if action a is applicable in state s.
   */

  virtual void bound(int i, bool& bounded, double& left, double& right)=0;
  /* Gives bounds on state variables' values
     i : index of state variable
     bounded: indicates if i^th variable is bounded
     left : left bound
     right: right bound
  */

  void getStateSpaceBounds(double* left, double* right);
  /* Returns bounds on state variables.
     left : array of left bounds
     right : array of right bounds
  */
	
  virtual void uniformStateSample(State& s)=0;
  /* Implements uniform state space sampling.
   */

  //The following functions empirically measure task attributes 

  void computeAttributes(Attributes& att, const State& startState, int Steps, int Transitions, const int* n, const ActionSet& as, StateActionFA* fa=NULL);
    /* Computes global values of the attributes for the state distribution
       as on the trajectory under some policy.
       att : attributes structureto return computed values;
       startState : state from which to start a random walk;
       Steps : maximum number of steps on the trajectory;
       Transitions: number of sample transitions from each state;
       n : array indicating into how many intervals each state variable ;
       should be discretized for the approximate calculation of attributes;
       as : action set for the current RL system;
       fa : pointer to the architecture that contains action value functions
       for each action. According to these value functions, 
       greedy policy will be exacuted. If it is desired to implement 
       uniformly random policy, make sure that parameters of the 
       architectures for all functions are the same (all values are the same).
    */

    void computeAttributes(Attributes& att, int SampleSize, int Transitions, const int* n, const ActionSet& as);
    /* Computes global values of the attributes for the uniform state 
       distribution. 
       att : attributes structureto return computed values;
       SampleSize : number of uniformly distributed samples across the state 
       space in which attribute values are computed and then averaged;
       Transitions: number of sample transitions from each state;
       n : array indicating into how many intervals each state variable;
       as : action set for the current RL system.
    */


    double multiStepEntropy(int N, int sampleSize, int Transitions, const int* n, const ActionSet& as);
    /* Computes multi-step state transition entropy.
       N : number of steps over which entropy should be computed;
       sampleSize : number of uniformly distributed samples across the state 
       space in which attribute values are computed and then averaged;
       Transitions: number of sample transitions from each state;
       n : array indicating into how many intervals each state variable;
       as : action set for the current RL system.
    */
	
 protected:
    void chooseAction(double epsilon, StateActionFA* fa, const ActionSet& actions, const State& s, Action& a);
    /* Implements an epsilon-greedy strategy based on action value 
       functions in the architecture pointed to by fa.
       epsilon : parameter for the epsilon-greedy strategy;
       fa : pointer to the architecture containing action value functions;
       actions : action set for the current RL system;
       s : state in which to choose action
       a : return value - chosen action
    */

	
    void actionSequence(int num, int n, int as_size, int* seq);
    /*	Used my multiStepEntropy() function.
     */
};

///////////////////////////////////////////////////////////////////////////


class Agent { //implementation of some non-virtual functions in agent.cpp

public:

  Agent(double g, const ActionSet& a_s, StateActionFA* const f, Environment* const e);
  /* Constructor.
     g : discount factor
     a_s : action set available to the agent
     f : pointer to the architectures containing either action-value functions 
     or random policy
     e : pointer to the environment
  */

  int initTrial(int N, bool learning, bool SaveTrajectory, const State* s = NULL, char* fileName = NULL, bool ComputeBellmanError = false); 
    /* Gets the start state from the environment
     and then calls appropriate act function to perform 
     the trial for a maximum of N steps)
     Argument "learning" indicates whether learning should take place.
     If yes, actAndLearn() function is called, otherwise
     act() function is called.
     Computes the return for this trial.
     Function returns the number of steps actually performed during the trial.

     N : maximal number of steps in the trial
     learning : indicates whether learning should take place
     SaveTrajectory : indicates whether the trajectory should be saved
     fileName : name of the file to which the trajectory should be saved.
     ComputeBellmanError : indicates if estimated Bellman Error should be computed. Has a default false value.
    */
			
  double getReturn();
  /* Gets return collected during the last trial
   */

  double getBellmanError();
  /* Returns BellmanError for the last trajectory traversed without learning   */

  virtual void setLearningParameters(int argc, char *argv[])=0;
  /*	Sets parameters of the RL learning algorithm
   */

  void setArchitectureParameters(const Action& a, int argc, char *argv[]);
  /* Sets parameters of the architecture (fa) representing
     value function or a policy distribution
     argc : number of arguments in argv array
     argv : array of arguments
     The two above arguments should be as they would be sent 
     to setArchitectureParameters() function of the derived approximator class.  
  */

  void saveArchitectureParameters(const Action& a, int argc, char *argv[]);
  /* Seves parameters of the architecture (fa) representing
     value function or a policy distribution
     argc : number of arguments in argv array
     argv : array of arguments
     The two above arguments should be as they would be sent 
     to saveArchitectureParameters() function of the derived approximator class.  	
  */

  virtual ~Agent();

 protected:

  //component structures
  struct StageInfo; //fully defined at the end of this class' declaration
  struct Trajectory;//fully defined at the end of this class' declaration

  //Data members
  State CurrentState;//current state of the environment	
  Action CurrentAction;//action chosen in the current state
  bool terminal; //indicates if the state is terminal
  double CurrentReward;
  const ActionSet& actions; //action set of the RL system
  StateActionFA* const fa; /* Pointer to an arcitecture representing
			      either policy probability distribution
			      or action-value functions.
			   */

  double gamma;	//discount factor
  double Return;//return collected during a trial
  Environment* const env;//pointer to the environment object
  int* ApplicableActions;//array to be used by chooseAction() function
  Trajectory* trajectory;
  double BellmanError;
	
  virtual int act(int N, bool SaveTrajectory, bool ComputeBellmanError)=0;

  /* Implements maximum of N successive steps of the trial
     or until a terminal state is entered by the environment
     Communicates with the environment to get current state and reward.
     Computes return collected on this trial.

     N : maximal number of steps in the trial
     SaveTrajectory : indicates whether trajectory should be saved
     ComputeBellmanError : indicates whether (estimated) Bellman error 
     should be computed for the state action pairs on the trajectory.

  */

  virtual int actAndLearn(int N, bool SaveTrajectory)=0;	
  /* Implements maximum of N successive steps of the trial
     or until the terminal state is entered by the environment
     Communicates with the environment to get 
     current state and reward.
     Calls the rlAlgorithm when appropriate. 
     Computes return collected on this trial.

     N : maximal number of steps in the trial;
     SaveTrajectory : indicates whether trajectory should be saved
  */

	
  virtual void chooseAction(const State& s, Action& a) =0 ;
  /* Implements behavior policy
     Uses fa - representation of the random policy or the action value functions 
     s : state in which the action should be performed
     a : chosen action
  */

  // component structures

  struct StageInfo{
    State state;
    Action action;
    double reward;

    double* Qvalue;
    double TDerror;

    StageInfo(){
      Qvalue = new double[Action::count];
    }

    ~StageInfo(){
      delete [] Qvalue;
    }
		
  };

  struct Trajectory{
    StageInfo* stage;
    int length;			//actual length of the recorded trajectory 

    Trajectory(int n){
				// n is the maximal number of stages in the trjectory
      stage = new StageInfo[n];
      length=0;
    }

    ~Trajectory(){
      delete [] stage;
    }

  };

};

int tokenize(char* sep, char* str, int** tokens);
/* Extracts tokens from string "str", which are separated by separators
   specified in "sep". Allocates array (*tokens) of the appropriate size
   and saves extracted tokens in that array. Returns the number of tokens.
*/



