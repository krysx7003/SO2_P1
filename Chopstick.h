#pragma once

enum class ChopState{
    DIRTY = 0,
    CLEAN = 1,
};
class Chopstick{
    public:
    int id;
    int holder_id;
    ChopState myState;
    Chopstick(int id);
    void setHolder(int holder);
};