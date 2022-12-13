#include <iostream>
#include <random>
#include "gold.h"
#include "event.h"
#include "room.h"
#include "game.h"

using namespace std;

/*********************************************************************
** Function: percept
** Description: gives statement based off hazard being nearby
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Gold::percept(){
    cout << "You see a glimmer nearby..." << endl;
}

/*********************************************************************
** Function: encounter
** Description: gives statements if user collids with hazard
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Gold::encounter(int size, int pos){
    cout << "You found the Wumpus's gold!" << endl;
    return pos;
}



