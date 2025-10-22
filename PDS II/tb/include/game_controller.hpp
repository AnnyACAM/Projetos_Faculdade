#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include "game.hpp"
#include <string>
class Game_Controller{
private:
    Game *menaged_game;
    std::vector<Player*> ingame_players;
    int turn_counter;
    Player *victor;

public:
    Game_Controller(Game *_game, std::vector<Player*> players);
    
    Game *Get_Game();
    int Get_Turn_Counter();
    
    std::vector<std::shared_ptr<void>> Filter_Input(std::string &input_type, std::string &input_str);
    bool Game_Loop();
    
    ~Game_Controller();
};

#endif