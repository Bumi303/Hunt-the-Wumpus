#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "event.h"

using namespace std;

class Room{
private:
    // private variables
    vector <vector<int>> cave;
    vector <vector<int>> empty_room;
    int cave_size;
    int player_location;
    
public:
    Room();
    void start(int);
    void set_cave_size(int);
    void set_cave();
    void print_cave(int, int, int, int, int, int, int);
    void print_line();
    
    int get_random_location();
    void change_player_location(char);
    int get_cave_size();
    int get_player_location();

    ~Room();
	//Assignment Operator overload
	Room& operator=(const Room&);
	//Copy Constructor 
	Room(const Room&);

};


#endif


