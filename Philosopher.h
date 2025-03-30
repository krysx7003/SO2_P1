#pragma once
#include "Chopstick.h"
#include <string>
#include <iomanip>  
#include <sstream>  
using namespace std;

enum class State{
    WAITING = 0,
    THINKING = 1,
    HUNGRY = 2,
    EATING = 3,
};

class Philosopher{
    public:
    int id = 0;
    int numOfPhils = 5;
    State myState = State::WAITING;
    Chopstick *leftChop = nullptr;
    Chopstick *rightChop = nullptr;    
    string toString();
    string stateToString(State state);
    Philosopher(int id,int numOfPhils ) : id(id), numOfPhils(numOfPhils), myState(State::WAITING), leftChop(nullptr), rightChop(nullptr){}
};