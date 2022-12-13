#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;

class Event{
private:
    // private variables only used by event classes
public:
    // public variables can be used anywhere
    virtual void percept() = 0;
    virtual int encounter(int, int) = 0;
    // virtual void set_location() = 0;

protected:
    // can be used by child classes
    
};


#endif


