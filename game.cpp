#include <iostream>
#include <random>
#include "game.h"
#include "room.h"
#include "gold.h"
#include "wumpus.h"
#include "pits.h"
#include "bats.h"

using namespace std;

/*********************************************************************
** Function: game defualt constructor
** Description: sets up the game and gets it ready for the player to play 
** Parameters: bool again
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
Game::Game(bool again) : Room(){
    if (again == false){
        char choice;
        this->is_over = false;
        this->arrow_count = 3;
        this->is_awake = false;
        cout << endl << "Welcome to Hunt the Wumpus!" << endl;
        cout << "Run in debug mode 't' or 'f'? ";
        cin >> choice;
        if (choice == 't'){
            cheat_view = true;
        }
        else{
            cheat_view = false;
        }
        set_game(0);
        this->cave_size = Room::get_cave_size();

    }
}

/*********************************************************************
** Function: start game
** Description: starts the game off checking if it is the first time on presets
** Parameters: bool again
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::start_game(bool again){
    if (again == true){
        set_game(this->cave_size);
        if (cheat_view == true){
            Room::print_cave(this->player_location, this->wumpus_location, this->gold_location, this->pit1_location, this->pit2_location, this->bat1_location, this->bat2_location);
        }
        else{
            Room::print_cave(this->player_location, -99, -99, -99, -99, -99, -99);
        }
    }

    int temp_p_loc = player_location;
    while (is_over == false){
        if (temp_p_loc != player_location){
            cin.get();
            cout << "Press Enter to Continue" << endl;
            cin.ignore();
        }
        else{
            move_player(); 
            check_win(); 
        }
        if (cheat_view == true){
            Room::print_cave(this->player_location, this->wumpus_location, this->gold_location, this->pit1_location, this->pit2_location, this->bat1_location, this->bat2_location);
        }
        else{
            Room::print_cave(this->player_location, -99, -99, -99, -99, -99, -99);
        }
        temp_p_loc = player_location;
        set_up_interface(); 
    }
}

/*********************************************************************
** Function: set_game
** Description: sets the game and calls some stuff in the room class
** Parameters: int size
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::set_game(int size){
    Room::start(size);

    if (size == 0){
        this->player_location = Room::get_random_location();
        this->rope_location = this->player_location;
        this->wumpus_location = Room::get_random_location();
        this->gold_location = Room::get_random_location();
        this->pit1_location = Room::get_random_location();      
        this->pit2_location = Room::get_random_location();  
        this->bat1_location = Room::get_random_location();     
        this->bat2_location = Room::get_random_location();  

        if (cheat_view == true){
            Room::print_cave(this->player_location, this->wumpus_location, this->gold_location, this->pit1_location, this->pit2_location, this->bat1_location, this->bat2_location);
        }
        else{
            Room::print_cave(this->player_location, -99, -99, -99, -99, -99, -99);
        }
        
        set_up_interface();  
    }     
}

/*********************************************************************
** Function: move_player
** Description:  allows the player to move through the map
** Parameters: there are no parameters
** Pre-Conditions: the user selects on of the four directions
** Post-Conditions: there are no post conditions
*********************************************************************/
//explanation for size: use of switch statements makes it big I didn't
//think it was necessary to modularize futher
void Game::move_player(){
    cout << "Which direction would you like to move or shoot an aroow ('w','s','a','d','q' - up,down,left,right,shoot) ";
    cin >> this->direction;
    cout << endl;
    switch (this->direction){
        case 'w':
            if (this->player_location - Room::get_cave_size() < 0){
                cout << "There is a wall in the direciton you want to move" << endl;
            }
            else{
                this->player_location = this->player_location - Room::get_cave_size();   
            }
            break;
        case 's':
            if (this->player_location + Room::get_cave_size() >= (Room::get_cave_size() * Room::get_cave_size())){
                cout << "There is a wall in the direciton you want to move" << endl;
            }
            else{
                this->player_location = this->player_location + Room::get_cave_size();    
            }
            break;
        case 'd':
            if ((this->player_location + 1) % Room::get_cave_size()  == 0){
                cout << "There is a wall in the direciton you want to move" << endl;
            }
            else{
                this->player_location = this->player_location + 1;  
            }
            break;
        case 'a':
            if ((this->player_location) % (Room::get_cave_size()) == 0){
                cout << "There is a wall in the direciton you want to move" << endl;
            }
            else{
                this->player_location = this->player_location - 1;    
            }
            break;
        case 'q':
            shoot_arrow();
            break;
    }
    if(this->is_awake == true){
        wake_wumpus();
    }
}

/*********************************************************************
** Function: set_up_interface
** Description: sets up an interface where polymorphism can occur checks near by
** and see if play collids with hazard
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::set_up_interface(){
    Wumpus w;
    Gold g;
    Pits p;
    Bats b; 

    //gives all percepts for events
    nearby<Wumpus>(w, wumpus_location);
    nearby<Gold>(g, gold_location); 
    nearby<Pits>(p, pit1_location);
    nearby<Pits>(p, pit2_location);
    nearby<Bats>(b, bat1_location);
    nearby<Bats>(b, bat2_location);

    // tests the collisions of the hazards
    collision_test<Wumpus>(w, wumpus_location);
    collision_test<Gold>(g, gold_location); 
    collision_test<Pits>(p, pit1_location);
    collision_test<Pits>(p, pit2_location);
    collision_test<Bats>(b, bat1_location);
    collision_test<Bats>(b, bat2_location);
}

/*********************************************************************
** Function: nearby
** Description: this is a template class that checks if things are near player pos
** Parameters: T1 &h, T2 pos
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
template <class T1, typename T2> 
void Game::nearby(T1 &h, T2 pos){
    // makes sure that the events are not going through walls
    if ((this->player_location + Room::get_cave_size() == pos) || (this->player_location - Room::get_cave_size() == pos) || (this->player_location - 1 == pos) || (this->player_location + 1 == pos)){
        if (((pos + 1) % Room::get_cave_size() != 0) || ((this->player_location - 1) != pos)){
            if (((pos) % Room::get_cave_size() != 0) || ((this->player_location + 1) != pos)){
                make_sound(h);
            }
        }
    }
}

/*********************************************************************
** Function: make_sound
** Description: checks all inherited funcitons for percept
** Parameters: Event &e
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
//gives percepts 
void Game::make_sound(Event &e){
    e.percept();
}

/*********************************************************************
** Function: collision_test
** Description: template function that checks for collision
** Parameters: T1 &h, T2 pos
** Pre-Conditions: there are no pre conditions
** Post-Conditions: if ther user collids with something it calls the collision 
** function using polymorphism
*********************************************************************/
//this funciton tests if the player encounters a hazard/event
template <class T1, typename T2>
void Game::collision_test(T1 &h, T2 pos){
    if (this->player_location == pos){
        direct_event(h);
    }
}

/*********************************************************************
** Function: direct_event
** Description: works withs collision test and directs to an ecounter
** Parameters: Event &e
** Pre-Conditions: there has to be a collision between player and a hazard
** Post-Conditions: there are no post conditions
*********************************************************************/
// directs and interpets events
void Game::direct_event(Event &e){
    int temp = this->player_location;
    //checks for encounter
    this->player_location = e.encounter(Room::get_cave_size(), this->player_location);
    if (this->player_location == -1){
        end_game();
    }
    else if (temp == this->player_location){
        gold_location = -98;
    }
}

/*********************************************************************
** Function: wake_wumpus
** Description: wakes up the wumpus and allows it to move around the cave
** Parameters: there are no parameters
** Pre-Conditions: the player shoots an arrow and misses
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::wake_wumpus(){
    int random_chance = 0;
    this->is_awake = true;

    random_chance = rand() % 3; //75 percent chance to move
    if (random_chance != 0 && wumpus_location != -99){
        wumpus_location = Room::get_random_location();
    }

}

/*********************************************************************
** Function: shoot_arrow
** Description: controls the arrow that the user shoots and asks
** for a direction 
** Parameters: there are no parameters
** Pre-Conditions: user has to select that they want to shoot an arrow
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::shoot_arrow(){
    this->arrow_location = this->player_location;
    bool stop = false;
    cout << "Which direction would you like to shoot your arrow (w,s,a,d - up,down,left,right) ";
    cin >> this->direction;
    cout << endl;

    // checks wher ethe arrow is going
    switch (this->direction){
        case 'w':
            upward(stop);
            break;
        case 's':
            downward(stop);
            break;
        case 'd':
            right(stop);
            break;
        case 'a':
            left(stop);
            break;
    }

    //gives statement in case of miss
    if (this->wumpus_location != -99){
        cout << "Your arrow missed..." << endl;
        if (is_awake == false){
            cout << "You have awaken the Wumpus..." << endl;
        }
        this->is_awake = true;
    }
}

/*********************************************************************
** Function: upward
** Description: moves the arrow up until it goes 3 rooms, hits wall, or hits
** wumpus
** Parameters: bool &stop
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::upward(bool &stop){
    int room_count = 0;
    while (stop == false){
        if (this->arrow_location - Room::get_cave_size() < 0 || room_count == 3){
            stop = true;
        }
        else{
            this->arrow_location = this->arrow_location - Room::get_cave_size(); 
            if (this->arrow_location == wumpus_location){
                cout << "Your arrow killed the Wumpus!" << endl;
                wumpus_location = -99;
            }   
            room_count++;
        }
    }
}

/*********************************************************************
** Function: downward
** Description: moves the arrow down until it goes 3 rooms, hits wall, or hits
** wumpus
** Parameters: bool &stop
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::downward(bool &stop){
    int room_count = 0;
    while (stop == false){
        if (this->arrow_location + Room::get_cave_size() > (Room::get_cave_size() * Room::get_cave_size()) || room_count == 3){
            stop = true;
        }
        else{
            this->arrow_location = this->arrow_location + Room::get_cave_size();    
            if (this->arrow_location == wumpus_location){
                cout << "Your arrow killed the Wumpus!" << endl;
                wumpus_location = -99;
            }   
            room_count++;
        }
    }
}

/*********************************************************************
** Function: right
** Description: moves the arrow right until it goes 3 rooms, hits wall, or hits
** wumpus
** Parameters: bool &stop
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::right(bool &stop){
    int room_count = 0;
    while (stop == false){
        if ((this->arrow_location) % Room::get_cave_size() + 1 == 0 || room_count == 3){
            stop = true;
        }
        else{
            this->arrow_location = this->arrow_location + 1;   
            if (this->arrow_location == wumpus_location){
                cout << "Your arrow killed the Wumpus!" << endl;
                wumpus_location = -99;
            }    
            room_count++;
        }
    }
}

/*********************************************************************
** Function: left 
** Description: moves the arrow left until it goes 3 rooms, hits wall, or hits
** wumpus
** Parameters: bool &stop
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::left(bool &stop){
    int room_count = 0;
    while (stop == false){
        if ((this->arrow_location) % Room::get_cave_size() == 0 || room_count == 3){
            stop = true;
        }
        else{
            this->arrow_location = this->arrow_location - 1;    
            if (this->arrow_location == wumpus_location){
                cout << "Your arrow killed the Wumpus!" << endl;
                wumpus_location = -99;
            }   
            room_count++;
        }
    }
}

/*********************************************************************
** Function: check_win
** Description: checks if win condition is met ie the user killed
** wumpus got the gold and went back to starting location
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::check_win(){
    if (this->player_location == this->rope_location){
        if (wumpus_location == -99 && gold_location == -98){
            cout << "You escaped the wumpus cave!" << endl;
            end_game();
        }
    }
}

/*********************************************************************
** Function: get size
** Description: gets size of cave
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
int Game::get_size(){
    return this->cave_size;
}

/*********************************************************************
** Function: end game
** Description: assigns true to is over member variable
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
void Game::end_game(){
    this->is_over = true;
}

/*********************************************************************
** Function: ~game
** Description: game destructor
** Parameters: there are no parameters
** Pre-Conditions: there are no pre conditions
** Post-Conditions: there are no post conditions
*********************************************************************/
Game::~Game(){
}

/*********************************************************************
** Function: game assignment operator overload
** Description: used if the user wants to play with the same presets
** Parameters: there are no parameters
** Pre-Conditions: the user selects to play with the same presets
** Post-Conditions: there are no post conditions
*********************************************************************/
//AOO
Game& Game::operator=(const Game& g){
	this->direction = g.direction;
    this->player_location = g.player_location;
    this->rope_location = g.rope_location;
    this->wumpus_location = g.wumpus_location;
    this->gold_location = g.gold_location;
    this->pit1_location = g.pit1_location;
    this->pit2_location = g.pit2_location;
    this->bat1_location = g.bat1_location;
    this->bat2_location = g.bat2_location;
    this->arrow_location = g.arrow_location;
    this->arrow_count = g.arrow_count;
    this->is_over = g.is_over;
    this->is_awake = g.is_awake;
    this->cheat_view = g.cheat_view; 
    this->cave_size = g.cave_size;

	return *this;
}

/*********************************************************************
** Function: game copy constructor
** Description: used if the user wants to play with the same presets
** Parameters: there are no parameters
** Pre-Conditions: the user selects to play with the same presets
** Post-Conditions: there are no post conditions
*********************************************************************/
//CC
Game::Game(const Game& g){
	this->direction = g.direction;
    this->player_location = g.player_location;
    this->rope_location = g.rope_location;
    this->wumpus_location = g.wumpus_location;
    this->gold_location = g.gold_location;
    this->pit1_location = g.pit1_location;
    this->pit2_location = g.pit2_location;
    this->bat1_location = g.bat1_location;
    this->bat2_location = g.bat2_location;
    this->arrow_location = g.arrow_location;
    this->arrow_count = g.arrow_count;
    this->is_over = g.is_over;
    this->is_awake = g.is_awake;
    this->cheat_view = g.cheat_view; 
    this->cave_size = g.cave_size;
}


