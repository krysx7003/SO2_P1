#include "Chopstick.h"

Chopstick::Chopstick(int id){
    this->id = id;
    this->holder_id = -1; 
}
void Chopstick::setHolder(int holder){
    holder_id = holder;
}