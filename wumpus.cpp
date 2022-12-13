#include <iostream>
#include "wumpus.h"
#include "event.h"

using namespace std;

/*********************************************************************
** Function: percept
** Description: gives statement based off hazard being nearby
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Wumpus::percept(){
    cout << "You smell a terrible stench..." << endl;
}

/*********************************************************************
** Function: encounter
** Description: gives statements if user collids with hazard
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Wumpus::encounter(int size, int pos){
    cout << "A beast roars..." << endl;
    cout << "The Wumpus ate you!" << endl;
    return -1;
}