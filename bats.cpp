#include <iostream>
#include "bats.h"
#include "event.h"

using namespace std;

/*********************************************************************
** Function: percept
** Description: gives statement based off hazard being nearby
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Bats::percept(){
    cout << "You hear wings flapping..." << endl;
}

/*********************************************************************
** Function: encounter
** Description: gives statements if user collids with hazard
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Bats::encounter(int size, int pos){
    int temp = pos;
    cout << "Giant bats take you to a random room..." << endl;
    while (temp == pos){
        pos = rand() % (size * size);
    }
    
    return pos;
}