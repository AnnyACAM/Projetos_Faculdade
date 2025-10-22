#ifndef REVERSI_H
#define REVERSI_H

#include <memory>

#include "game.hpp"
#include "player.hpp"
#include "piece.hpp"

#define MAX_PIECES 64
#define BLACK 'B'
#define WHITE 'W'

class Reversi : public Game{
    private:
        Player* player1;
        Player* player2;

        std::vector<Piece*> ingame_pieces;
    public:
        //Constructor
        Reversi (int size, Player* player1, Player* player2);

        //Derived class
        void Initialize_Game();
        std::string Get_Input_Format() override;
        bool Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values);
        bool Player_Input(std::vector<std::shared_ptr<void>> input_values,Player* current_player) override;
        bool Draw_Condition(int turn_counter) override;
        bool Victory_Condition(int X, int Y) override;
        bool Victory_Finish() override;
        
        //Possible movements
        /* add smart pointer all functions*/
        std::array<int, 2> Find_piece_in_direction(int line_piece, int column_piece, int line_path, int column_path, Player* owner);
        bool Swap_piece_in_direction(int line_piece, int column_piece, std::array<int, 2> posc, int line_path, int column_path, Player* owner);

        //Game
        void Valid_movement(int line_piece, int column_piece, int line_path, int column_path, Player* owner);
        Piece* Game_define_piece(Player* owner, char table_char);
        bool Game_swap_piece(int line, int column);
        char Owner_color(Player* _player);
        void Input_piece(int line, int column,Player* owner);
        void Who_wins();
        //Desconstructor
        ~Reversi() override;
};

#endif