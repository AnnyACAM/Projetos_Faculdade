#ifndef LINESOFACTION_H
#define LINESOFACTION_H

#include "game.hpp"
#include "piece.hpp"

class Lines_of_Action: public Game{

public:
    Lines_of_Action(int X, int Y);
    void Initialize_Pieces(Player *from_player) override; 
    std::string Get_Input_Format() override;
    bool Draw_Condition(int turn_counter) override;
    bool Victory_Condition(int X, int Y) override;

    bool Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values) override;
    bool Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player) override;

};

#endif