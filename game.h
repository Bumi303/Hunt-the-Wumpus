#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "room.h"

using namespace std;

class Game: public Room{
private:
    // private variables
    char direction;
    int player_location;
    int rope_location;
    int wumpus_location;
    int gold_location;
    int pit1_location;
    int pit2_location;
    int bat1_location;
    int bat2_location;
    int arrow_location;
    int arrow_count;
    bool is_over;
    bool is_awake;
    bool cheat_view;
    int cave_size;
    
public:
    // public variables
    Game(bool);
    void set_game(int);
    void move_player();
    void set_up_interface();
    void make_sound(Event &);
    void direct_event(Event &);
    void upward(bool &);
    void downward(bool &);
    void right(bool &);
    void left(bool &);
    template <class T1, typename T2> void nearby(T1 &, T2);
    template <class T1, typename T2> void collision_test(T1 &, T2);
    void end_game();
    void ask_arrow();
    void shoot_arrow();
    void wake_wumpus();
    void check_win();
    void start_game(bool);
    int get_size();
    

    ~Game();
	//Assignment Operator overload
	Game& operator = (const Game&);
	//Copy Constructor 
	Game(const Game&);
    
};


#endif


