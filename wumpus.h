#ifndef WUMPUS_H
#define WUMPUS_H

#include <iostream>
#include "event.h"

using namespace std;

class Wumpus: public Event{
private:
    // private variables
public:
    // public variables
    Wumpus() { };
    void percept();
    int encounter(int, int);
};


#endif

