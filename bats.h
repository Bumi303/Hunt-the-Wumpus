#ifndef BATS_H
#define BATS_H

#include <iostream>
#include "event.h"

using namespace std;

class Bats : public Event{
private:
    // private variables
    int bat1_location;
    int bat2_location;
public:
    // public variables
    Bats() { };
    void percept();
    int encounter(int, int);
};


#endif


