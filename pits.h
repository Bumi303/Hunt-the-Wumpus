#ifndef PITS_H
#define PITS_H

#include <iostream>
#include "event.h"

using namespace std;

class Pits: public Event{
private:
    // private variables
    int pit1_location;
    int pit2_location;
public:
    // public variables
    Pits() { };
    void percept();
    int encounter(int, int);
};


#endif


