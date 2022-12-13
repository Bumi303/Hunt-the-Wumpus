/*********************************************************************
** Program Filename:assignment4.cpp
** Author: Hayden Henderson
** Date: 11/25/22
** Description: This program replicates the game hunt the wumpus
** Input: The user will input whether want to play in debug mode, where they
** they want to move, if they want to play again, and if they want to keep
** their presets
** Output: the output is the game of hunt the wumpus and the result
** of the the users playing through the game
*********************************************************************/

#include <iostream>
#include <vector>
#include <random>
#include "game.h"
#include "room.h"
#include "gold.h"
#include "wumpus.h"
#include "pits.h"
#include "bats.h"


using namespace std;


/*********************************************************************
** Function: main
** Description: this the is main funciton it calls the classes
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions:  n/a
*********************************************************************/
int main(){
    srand(time(NULL));
    char user_choice = ' ';
    char new_preset_choice = ' ';
    bool again = true;
    bool stop = false;
    do{
        Game g(stop);
        Game g2(again);
        Game g3(again);
        g2 = g;
        g3 = g2;

        g.start_game(stop);
        cout << endl << "Would you like to play again 'y' or 'n'? " ;
        cin >> user_choice;
        cout << endl;
        while (user_choice == 'y'){
            cout << "Would you like to play with the same presets 'y' or 'n'? ";
            cin >> new_preset_choice;
            cout << endl;
            if (new_preset_choice == 'y'){
                g2 = g3;
                g2.start_game(again);
                cout << endl << "Would you like to play again 'y' or 'n'? " ;
                cin >> user_choice;
                cout << endl;
            }
            else{
                break;
            }
        }

    } while (user_choice == 'y');
    
    return 0;
}
