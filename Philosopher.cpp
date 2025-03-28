#include "Philosopher.h"
#include <random>
#include <unistd.h>
#include <iostream>
#include "draw.h"

void Philosopher::think(){
    //TODO - Logika??
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void Philosopher::takeChop(){
    //TODO - Logika??
    myState = State::HUNGRY;
    draw();
}
void Philosopher::eat(){
    //TODO - Logika??
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
    myState = State::EATING;
    draw();
}
void Philosopher::returnChop(){
    //TODO - Logika??
    myState = State::THINKING;
    draw();
}
void Philosopher::run(){
    while (true){
        think();
        takeChop();
        eat();
        returnChop();
    }
}
string Philosopher::stateToString(State state){
    switch (state) {
        case State::WAITING: return "WAITING";
        case State::THINKING: return "THINKING";
        case State::HUNGRY: return "HUNGRY";
        case State::EATING: return "EATING";
        default: return "UNKNOWN";
    }
}
string Philosopher::toString(){
    string leftChopstick =  "";
    if(leftChop != nullptr){
        leftChopstick = to_string( leftChop->id );
    }
    string rightChopstick = "";
    if(rightChop != nullptr){
        rightChopstick = to_string( rightChop->id );
    }
    return string( "Philosopher: " ) + to_string( id ) + " | " + leftChopstick + " | " + rightChopstick + " | " + stateToString( myState ) + " |\n";
}
Philosopher::Philosopher(){
    id = 0;
    numOfPhils = 5;
    myState = State::WAITING;
    leftChop = nullptr;
    rightChop = nullptr;    
}