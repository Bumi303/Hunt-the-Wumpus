#include <iostream>
#include "pits.h"
#include "bats.h"

using namespace std;

/*********************************************************************
** Function: percept
** Description: gives statement based off hazard being nearby
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Pits::percept(){
    cout << "You feel a breeze..." << endl;
}

/*********************************************************************
** Function: encounter
** Description: gives statements if user collids with hazard
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Pits::encounter(int size, int pos){
    cout << "The abyss draws you in..." << endl;
    cout << "You fell into a bottomless pit!" << endl;


    return -1;
}
