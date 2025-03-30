#pragma once
#include "Chopstick.h"
#include <string>
#include <iomanip>  
#include <sstream>  
using namespace std;

enum class PhilState{
    WAITING = 0,
    THINKING = 1,
    HUNGRY = 2,
    EATING = 3,
};

class Philosopher{
    public:
    int id;
    int left,right;
    int leftChop,rightChop;
    int timesThinking,timesEating,timesHungry;
    bool boothLocked;
    PhilState myState;
    string toString();
    string stateToString(PhilState state);
    void setLeftChop(int left);
    void setRightChop(int right);
    Philosopher(int id, int numOfPhil) : id(id), myState(PhilState::WAITING), leftChop(-1), rightChop(-1){
        left = ( id - 1 + numOfPhil)%numOfPhil;
        right = ( id )%numOfPhil;
        boothLocked = false;
        timesThinking = 0;
        timesEating = 0;
        timesHungry = 0;
    }
};