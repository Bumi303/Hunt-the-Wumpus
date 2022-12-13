#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "room.h"
#include "event.h"
#include "game.h"

using namespace std;

/*********************************************************************
** Function: Room
** Description: this is the room defualt defualt constructor
** Parameters: there are no parameters
** Pre-Conditions: defualt constructor is called automatically
** Post-Conditions:  n/a
*********************************************************************/
Room::Room(){
    this->cave = {{}};
    this->empty_room = {{}};
    this->cave_size = -1;
}

/*********************************************************************
** Function: start
** Description: this starts the set up of creating the cave
** Parameters: size
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Room::start(int size){
    set_cave_size(size); 
    set_cave(); // sets hazards inside of cave
}

/*********************************************************************
** Function: set_cave_size
** Description: set up of creating the cave
** Parameters: size
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Room::set_cave_size(int size){
    if (size == 0){ // checks if this is the first time or keeping same conditions
        cout << "How big do you want the cave to be? ";
        cin >> this->cave_size;
        cout << endl;

        while (this->cave_size < 4){
            cout << "Your cave is too small try again! ";
            cin >> this->cave_size;
            cout << endl;
        }
    }
    else{
        this->cave_size = size;
    }
}

/*********************************************************************
** Function: set_cave
** Description: this funciton initalizes the cave and the empty slots of the cave
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Room::set_cave(){
    for (int i = 0; i < this->cave_size; i++){
        this->cave.push_back(vector<int>());
        this->empty_room.push_back(vector<int>());
        for (int k = 0; k < this->cave_size; k++){
            this->cave[i].push_back(k);
            this->empty_room[i].push_back(-1);
        }
    }
}


/*********************************************************************
** Function:  print_cave
** Description: this function prints the cave out
** Parameters: int p, int w, int g, int p1, int p2, int b1, int b2
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
//prints map of cave
void Room::print_cave(int p, int w, int g, int p1, int p2, int b1, int b2){
    print_line();

    for (int i = 0; i < this->cave_size; i++){
        for (int k = 0; k <= this->cave_size; k++){
            if ((k == (p % this->cave_size)) && (i == (p / this->cave_size))){
                cout << "| * "; 
            }
            else if((k == (g % this->cave_size)) && (i == (g / this->cave_size))){
                cout << "| G ";
            }
            else if((k == (w % this->cave_size)) && (i == (w / this->cave_size))){
                cout << "| W ";
            }
            else if((k == (p1 % this->cave_size)) && (i == (p1 / this->cave_size))){
                cout << "| O ";
            }
            else if((k == (p2 % this->cave_size)) && (i == (p2 / this->cave_size))){
                cout << "| O ";
            }
            else if((k == (b1 % this->cave_size)) && (i == (b1 / this->cave_size))){
                cout << "| B ";
            }
            else if((k == (b2 % this->cave_size)) && (i == (b2 / this->cave_size))){
                cout << "| B ";
            }
            else{
                cout << "|   ";
            }
        }
        cout << endl;
        print_line();
    }
}


/*********************************************************************
** Function:  print_line
** Description: this helps the print cave function
** Parameters: there are no parameters
** Pre-Conditions: the preconditions if the line count is correct
** Post-Conditions: there are no post conditions
*********************************************************************/
//helps print the map
void Room::print_line(){
    for (int i = 0; i < this->cave_size; i++){
        if (i % 2 == 0){
            cout << "+---+";
        }
        else{
            cout << "---";
        }
    }
    if (this->cave_size % 2 == 0){
        cout << "+";
    }
    cout << endl;
    
}


/*********************************************************************
** Function: change_player_location
** Description: this funcitons allows the use to move through the function
** Parameters: char d
** Pre-Conditions: the user enters a value to move 
** Post-Conditions: there are no post conditions
*********************************************************************/
void Room::change_player_location(char d){
    if (d == 'w'){
        this->player_location = this->player_location - this->cave_size;
    }
    else if (d == 's'){
        this->player_location = this->player_location + this->cave_size;;
    }
    else if (d == 'a'){
        this->player_location = this->player_location - 1;
    }
    else if (d == 'd'){
       this->player_location = this->player_location + 1;
    }
    else{
        cout << "Error!" << endl;
    }
}

/*********************************************************************
** Function: get_random_location
** Description: gets a random empty location in the cave
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
// gets a random location in the cave
int Room::get_random_location(){
    int pos = 99;
    // checks if the random room is empty
    while (this->empty_room[(pos % this->cave_size)][(pos / this->cave_size)] != pos){ 
        pos = rand() % (cave_size * cave_size);
        if (this->empty_room[(pos % this->cave_size)][(pos / this->cave_size)] == -1){
            this->empty_room[(pos % this->cave_size)][(pos / this->cave_size)] = pos;
        }
        else{
            pos = 99;
        }
    }
    return pos;
}

/*********************************************************************
** Function: get_player_location
** Description:  returns player locaiton
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Room::get_player_location(){
    return this->player_location;
}

/*********************************************************************
** Function: get_cave_size
** Description: returns cave size 
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Room::get_cave_size(){
    return this->cave_size;
}


/*********************************************************************
** Function: ~rooms
** Description:  room destructor
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
Room::~Room(){
}

/*********************************************************************
** Function: room assignment operator overload
** Description: used if the user wants to play with the same presets
** Parameters: there are no parameters
** Pre-Conditions: the user selects to play with the same presets
** Post-Conditions: there are no post conditions
*********************************************************************/
//AOO
Room& Room::operator=(const Room& r){
	this->cave_size = r.cave_size;
    this->player_location = r.player_location;
    this->cave = r.cave;
    this->empty_room = r.empty_room;
   
	return *this;
}

/*********************************************************************
** Function: room copy constructor
** Description: used if the user wants to play with the same presets
** Parameters: there are no parameters
** Pre-Conditions: the user selects to play with the same presets
** Post-Conditions: there are no post conditions
*********************************************************************/
//CC
Room::Room(const Room& r){
	cout << "inside CC room..." << endl; 
	this->cave_size = r.cave_size;
    this->player_location = r.player_location;
    this->cave = r.cave;
    this->empty_room = r.empty_room;
}


