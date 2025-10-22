#ifndef LIG4_GAME_H
#define LIG4_GAME_H

#include "game.hpp"
#include "player.hpp"

class Lig4_Game: public Game{
public:
    Lig4_Game(int X, int Y);
    void Initialize_Pieces(Player *from_player) override; 
    std::string Get_Input_Format() override;

    bool Draw_Condition(int turn_counter) override;
    bool Victory_Condition(int X, int Y) override;
    bool Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values) override;
    bool Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player) override;

    ~Lig4_Game() override;
};

#endif