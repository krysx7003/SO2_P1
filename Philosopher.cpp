#include "Philosopher.h"

string Philosopher::stateToString(PhilState state){
    switch (state) {
        case PhilState::WAITING: return "WAITING";
        case PhilState::THINKING: return "THINKING";
        case PhilState::HUNGRY: return "HUNGRY";
        case PhilState::EATING: return "EATING";
        default: return "UNKNOWN";
    }
}
string Philosopher::toString(){
    string leftChopstick =  " ";
    if(leftChop != -1){
        leftChopstick = to_string( leftChop ); 
    }
    string rightChopstick = " ";
    if(rightChop != -1){
        rightChopstick = to_string( rightChop );
    }
    ostringstream oss; 
    oss << "Philosopher: " << setw(3) << id << " | " 
        << setw(5) << leftChopstick << " | " 
        << setw(5) << rightChopstick << " | " 
        << setw(12) << stateToString( myState ) << " | "
        << setw(5) << timesThinking << " | " 
        << setw(5) << timesEating << " | " 
        << setw(5) << timesHungry << " |\n";
    return oss.str();
}
void Philosopher::setLeftChop(int left){
    leftChop = left;
}
void Philosopher::setRightChop(int right){
    rightChop = right;
}