#include <cmath>
#include <algorithm>
#include "reversi.hpp"
#include "game.hpp"

Reversi::Reversi(int size, Player* _player1, Player* _player2)
:Game(size), player1(_player1), player2(_player2){ this->Initialize_Game(); }

Piece* Reversi :: Game_define_piece(Player* owner, char print_c){
    this->ingame_pieces.push_back(new Piece(1, print_c, owner));
    return ingame_pieces.back();
}

char Reversi :: Owner_color(Player* _player){
    if(_player == this->player1){
        return BLACK;
    }

    return WHITE;
}

void Reversi :: Valid_movement(int line, int column, int line_path, int column_path, Player* owner){
    std::array<int, 2> posc;
    bool valid_move = false;

    posc = Find_piece_in_direction(line, column, line_path, column_path, owner);
    if(posc[0] > -1){
        valid_move = Swap_piece_in_direction(line, column, posc, line_path, column_path, owner);
    } 

    if(valid_move){
        this->Input_piece(line,column,owner);
    }

}

bool Reversi :: Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values){
    int line = *std::static_pointer_cast<int>(input_values[0]);
    int column = *std::static_pointer_cast<int>(input_values[1]);
    Player * owner = this->Get_Table()->Get_Piece(line, column)->Get_Owner();

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if(!(x==0 && y==0) && Find_piece_in_direction(line, column, x, y, owner)[0] > -1){
                return true;
            }
        }
    }

    return false;
}

bool Reversi :: Player_Input(std::vector<std::shared_ptr<void>> input_values, Player* owner){
    /* There are four possible moves (swap of pieces)*/
    int line = *std::static_pointer_cast<int>(input_values[0]);
    int column = *std::static_pointer_cast<int>(input_values[1]);

    if(line > 0 && column > 0 && line < this->Get_Table()->Get_SizeX() && column < this->Get_Table()->Get_SizeY()){
        if(!this->Get_Table()->Get_Piece(line, column)->Get_Type()){

            /* ---- In same column*/
            //Bellow to piece
            Valid_movement(line, column, -1, 0, owner);
            //Above to piece
            Valid_movement(line, column, 1, 0, owner);

            /* ---- In same line*/
            //Left to piece
            Valid_movement(line, column, 0, -1, owner);
            //Right to piece
            Valid_movement(line, column, 0, 1, owner);

            /* ---- In same diagonal primary*/
            //Up and right to piece
            Valid_movement(line, column, 1, 1, owner);
            //Down and left to piece
            Valid_movement(line, column, -1, -1, owner);

            /* ---- In same diagonal secondary*/
            //Up and Left to piece
            Valid_movement(line, column, 1, -1, owner);
            //Down and right to piece
            Valid_movement(line, column, -1, 1, owner);
        }
    }

}

void Reversi :: Input_piece(int line, int column, Player* current_player){
    this->Get_Table()->Set_Piece(line, column, Game_define_piece(current_player, this->Owner_color(current_player)));
}

void Reversi :: Initialize_Game(){
    /* Reversi starts with two pieces for each 
       player in the center of the board   */

    int middle_board = (this->Get_Table()->Get_SizeX()/2) - 1;
    //Player 1 in principal diagonal - black pieces
    Input_piece(middle_board, middle_board + 1, this->player1);
    Input_piece(middle_board + 1, middle_board, this->player1);
    //Player 2 in second diagona - white pieces
    Input_piece(middle_board, middle_board, this->player2);
    Input_piece(middle_board +1, middle_board + 1, this->player2);

    this->Get_Table()->Table_Print();

}

/*End Game*/

Reversi :: ~Reversi(){
    this->ingame_pieces.clear();
    std::cout << "desconstrutor";
}

bool Reversi :: Victory_Finish(){
    
    int player1_pieces = 0;
    int player2_pieces = 0;

    if(ingame_pieces.size() == MAX_PIECES){
        for (const auto& piece : this->ingame_pieces) {
            if(piece->Get_Char() == BLACK){
                player1_pieces++;
            }
        }

        player2_pieces = MAX_PIECES - player1_pieces;
        return Victory_Condition(player1_pieces, player2_pieces);
    }
    return false;
}

bool Reversi :: Victory_Condition(int player1_pieces, int player2_pieces){
    /*All pieces must be on the board 
    at the end of the game. The pieces that do not belong 
    to player 1 then belong to player 2.*/

    if(player1_pieces + player2_pieces == MAX_PIECES){
        if(player1_pieces > player2_pieces){
            std::cout << "player 1 wins\n";
        }else if(player1_pieces < player2_pieces){
            std::cout << "player 2 wins\n";
        }else{
            std::cout << "tie\n";
        }
        return true;
    }
    return false;

}

/* Swap pieces */
bool Reversi :: Game_swap_piece(int line, int column){
    /*add smart point*/
    Piece* p =  this->Get_Table()->Get_Piece(line, column);
    Player* owner_piece = p->Get_Owner();
    bool erro = true;

    if(owner_piece == this->player1){
        p->Set_Owner(player2);
        p->Set_Char(this->Owner_color(player2));
        erro = false;
    }else if(owner_piece == this->player2){
        p->Set_Owner(player1);
        p->Set_Char(this->Owner_color(player1));
        erro = false;
    }

    return erro;
}

/* Movement*/

std::array<int, 2> Reversi::Find_piece_in_direction(int line_piece, int column_piece, int line_path, int column_path, Player* owner) {
    int brother_line = line_piece;
    int brother_column = column_piece;

    do{
        brother_line += line_path;
        brother_column += column_path;
        
        Piece* p = this->Get_Table()->Get_Piece(brother_line , brother_column);
        if (p && p->Get_Owner() == owner && std::max(abs(line_piece - brother_line), abs(column_piece - brother_column)) > 1) {
            return {brother_line, brother_column};
        }else if((p->Get_Char() != BLACK && p->Get_Char() != WHITE)){
            return {-1,-1};
        }

    }while( brother_line > 0 && brother_line < this->Get_Table()->Get_SizeX() - 1 && 
            brother_column > 0 && brother_column < this->Get_Table()->Get_SizeY() - 1);

    return {-1,-1};
}

bool Reversi::Swap_piece_in_direction(int line_piece, int column_piece, std::array<int, 2> posc, int line_path, int column_path, Player* owner) {
    int brother_line;
    int brother_column;
    int distance = std::max(abs(line_piece - posc[0]), abs(column_piece - posc[1]));

    if(distance > 0){
        for(int i = 1; i < distance + 1; i++){
            brother_line = line_piece + i*(line_path);
            brother_column = column_piece + i*(column_path);
            
            if( brother_line > 0 && brother_column > 0 && distance > 0 &&
                brother_line < this->Get_Table()->Get_SizeX() && brother_column < this->Get_Table()->Get_SizeY()){
                    Piece* p = this->Get_Table()->Get_Piece(brother_line, brother_column);
                    if(p && p->Get_Owner() != owner && p->Get_Type())
                        this->Game_swap_piece(brother_line,brother_column); 
            }else{return false;} 
        }
    }
    return true;
}

std::string Reversi::Get_Input_Format(){
    return "int int";
};

bool Reversi::Draw_Condition(int turn_counter){
    return Game::Draw_Condition(turn_counter);
}