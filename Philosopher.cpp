#include "Philosopher.h"

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
    ostringstream oss; 
    oss << "Philosopher: " << setw(3) << id << " | " 
        << setw(3) << leftChopstick << " | " 
        << setw(3) << rightChopstick << " | " 
        << setw(12) << stateToString( myState ) << " |\n";
    return oss.str();
}