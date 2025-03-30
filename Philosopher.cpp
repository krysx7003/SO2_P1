#include "Philosopher.h"
#include <random>
#include <unistd.h>
#include "draw.h"

void Philosopher::think(){
    lock_guard<mutex> lock(*out);
    myState = State::THINKING;
    cout<<id;
    draw();
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void Philosopher::takeChop(){
    lock_guard<mutex> lock(*out);
    myState = State::HUNGRY;
    cout<<id;
    draw();
}
void Philosopher::eat(){
    lock_guard<mutex> lock(*out);
    myState = State::EATING;
    cout<<id;
    draw();
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void Philosopher::returnChop(){

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