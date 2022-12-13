#ifndef GOLD_H
#define GOLD_H

#include <iostream>
#include "event.h"

using namespace std;

class Gold: public Event{
private:
    // private variables
    int gold_location;
public:
    // public variables
    Gold() { };
    void percept();
    int encounter(int, int);
};


#endif


