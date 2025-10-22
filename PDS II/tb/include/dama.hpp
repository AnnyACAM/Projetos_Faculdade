#ifndef DAMA_H
#define DAMA_H

#include <memory>

#include "C:\Users\annyc\OneDrive\Documentos\Coding\Codigos\2_SEMESTRE\Trabalho\Trabalho Final\tb\include\game.hpp"
#include "C:\Users\annyc\OneDrive\Documentos\Coding\Codigos\2_SEMESTRE\Trabalho\Trabalho Final\tb\include\player.hpp"
#include "C:\Users\annyc\OneDrive\Documentos\Coding\Codigos\2_SEMESTRE\Trabalho\Trabalho Final\tb\include\piece.hpp"

#define BLACK 'B'
#define WHITE 'W'

class Dama : public Game{
    private:
        Player* player1;
        Player* player2;

    public:
        //Constructor
        Dama (int size, Player* player1, Player* player2);

        //Derived class
        void Initialize_Game();
        void Initialize_Pieces(Player *from_player) override;
        std::string Get_Input_Format() override;
        bool Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values);
        bool Player_Input(std::vector<std::shared_ptr<void>> input_values,Player* current_player) override;
        bool Draw_Condition(int turn_counter) override;
        bool Victory_Condition(int x, int y) override;
        bool Victory_Finish() override;
        
        //Game
        Piece* Game_define_piece(Player* owner, char table_char);
        void Input_piece(int line, int column,Player* owner);
        int Who_wins();
        char Owner_color(Player* _player);

        bool Peon_movement(int line, int column);
        bool Peon_attack(int line, int column,Player* owner, char diagonal);

        bool Queen_movement(int line, int column, int distance, Player* owner, char diagonal);

        std::array<int, 2> Find_piece(int line_piece, int column_piece, int line_path, int column_path, Player* owner, int distance);
        bool Movement_rules(int line_piece, int column_piece, int line_destination, int column_destination, Player* owner);
        bool Move_piece(int line_piece, int column_piece, int line_destination, int column_destination);
        bool Remove_piece(int line_piece, int column_piece);

        //Desconstructor
        ~Dama() override;
};

#endif