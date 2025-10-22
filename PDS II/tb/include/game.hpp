#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "player.hpp"
#include "tabletop.hpp"
#include "piece.hpp"
#include <string>
#include <memory>

class Game{
private:
    Tabletop *table;
protected:
    std::vector<std::vector<Piece*>> ingame_pieces;
    
public:
    Game(int sizeX, int sizeY);
    Game(int SIZE);
    virtual void Initialize_Pieces(Player *from_player); 

    std::vector<Piece*> Get_Player_Pieces(Player *from_player);
    Tabletop *Get_Table();
    virtual std::string Get_Input_Format();

    virtual bool Draw_Condition(int turn_counter);
    virtual bool Victory_Condition(int X, int Y) = 0; 
    virtual bool Victory_Finish(); 
    virtual bool Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values) = 0;
    virtual bool Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player);
    
    virtual ~Game();
};
#endif