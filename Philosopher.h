#pragma once
#include "Chopstick.h"
#include <string>
using namespace std;

enum class State{
    WAITING = 0,
    THINKING = 1,
    HUNGRY = 2,
    EATING = 3,
};

class Philosopher{
    const int MAX_TIME = 5;
    const int US_TO_S = 1000000;
    public:
    int id = 0;
    int numOfPhils = 5;
    State myState = State::WAITING;
    Chopstick *leftChop = nullptr;
    Chopstick *rightChop = nullptr;    
    void think();
    void takeChop();
    void eat();
    void returnChop();
    void run();
    string toString();
    string stateToString(State state);
    Philosopher();
    //TODO - Kolejny konstruktor 
    static void* runThread(void* arg) {
        Philosopher* phil = static_cast<Philosopher*>(arg);  
        if (phil) {
            phil->run(); 
        }
        return nullptr;
    }
};