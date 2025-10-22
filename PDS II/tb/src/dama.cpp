#include <cmath>
#include <algorithm>
#include "dama.hpp"
#include "game.hpp"


Dama::Dama(int size, Player* _player1, Player* _player2):Game(size), player1(_player1), player2(_player2){ this->Initialize_Game(); }

char Dama :: Owner_color(Player* _player){
    if(_player == this->player1){
        return WHITE;
    }

    return BLACK;
}

std::string Dama::Get_Input_Format(){
    return "int int int int";
};

bool Dama::Draw_Condition(int turn_counter){
    return Game::Draw_Condition(turn_counter);
}

bool Dama :: Player_Input(std::vector<std::shared_ptr<void>> input_values,Player* current_player){
    int line_piece = *std::static_pointer_cast<int>(input_values[0]);
    int column_piece = *std::static_pointer_cast<int>(input_values[1]);
    int line_destination = *std::static_pointer_cast<int>(input_values[2]);
    int column_destination = *std::static_pointer_cast<int>(input_values[3]);

    Piece* piece = this->Get_Table()->Get_Piece(line_piece, column_piece);
    if (piece == nullptr || piece->Get_Owner() != current_player) {
        return false;
    }

    if (Movement_rules(line_piece, column_piece, line_destination, column_destination, current_player)) {
        return true;
    }

    return false;
}

bool Dama :: Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values){
    int line_piece = *std::static_pointer_cast<int>(input_values[0]);
    int column_piece = *std::static_pointer_cast<int>(input_values[1]);
    int line_destination = *std::static_pointer_cast<int>(input_values[2]);
    int column_destination = *std::static_pointer_cast<int>(input_values[3]);

    if(line_destination >= this->Get_Table()->Get_SizeX() || column_destination >= this->Get_Table()->Get_SizeY()
        || line_destination < 0 || column_destination < 0){
        return false;
    }

    Piece* p = this->Get_Table()->Get_Piece(line_piece, column_piece);
    Piece* d = this->Get_Table()->Get_Piece(line_destination, column_destination);
    if(p == nullptr || d != nullptr){
        if(d->Get_Char() != BLACK && d->Get_Char() != WHITE)
        return false;
    }
    //Peon
    if(p->Get_Type() == 0){
        if(column_piece - column_destination == 0 && abs(line_piece - line_destination) == 1 || (abs(line_piece - line_destination) == 2 &&  abs(column_piece - column_destination) == 2))
            return true;
    }


    return false;

}

void Dama::Initialize_Pieces(Player *from_player){
    int index = 0;

    if (ingame_pieces.size() < 2) {
        ingame_pieces.resize(2);  
    }

    ingame_pieces.push_back(std::vector<Piece*>());  
    if(from_player == this->player2){
        index = 1;
    }             
    for(int i = 0; i < 12; i++)
        ingame_pieces[index].push_back(new Piece(0, this->Owner_color(from_player), from_player));

}

void Dama :: Initialize_Game(){
    /* Dama starts with two pieces for each 
       player in the center of the board   */

    int n_pieces = 12;
    int line = 3;
    int column = 4;
    int index = 0;

    ///Initialize_Pieces(this->player1);
    //Initialize_Pieces(this->player2);

    std::cout << ingame_pieces.size() << "--------------------------------\n";

    this->Get_Table()->Set_Piece(1, 1,new Piece(0, 'o', player1));
    std::cout << this->Get_Table()->Get_Piece(1,1)->Get_Char() << '\n';

    /*this->Get_Table()->Set_Piece(5, 5, ingame_pieces[1][0]);
    std::cout << this->Get_Table()->Get_Piece(5,5)->Get_Char() << '\n';*/

    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; i++){
            std::cout << i << " " <<j*2 << "--------------------------------\n";
            if(index >= 8 || index < 0){
                break;
            }
            //this->Get_Table()->Set_Piece(1, 1,new Piece(0, 'o', player1));
            //this->Get_Table()->Set_Piece((this->Get_Table()->Get_SizeX() - 1) - i, j + 1, ingame_pieces[1][index]);
            index++;
        }
    }
    
    this->Get_Table()->Table_Print();
}

/*End Game*/

Dama :: ~Dama(){
    std::cout << "desconstrutor";
}

bool Dama :: Victory_Finish(){
    int player1_pieces;
    int player2_pieces;

    for (const auto& piece : this->Get_Player_Pieces(player1)) {
        if(piece->Get_Char() == WHITE){
            player1_pieces++;
        }
    }

    for (const auto& piece : this->Get_Player_Pieces(player2)) {
        if(piece->Get_Char() == BLACK){
            player2_pieces++;
        }
    }

    if(player1_pieces > 0 || player2_pieces > 0){
        return Victory_Condition(player1_pieces, player2_pieces);
    }

    return false;

}

bool Dama :: Victory_Condition(int player1_pieces, int player2_pieces){

    if(player1_pieces == 0 || player2_pieces == 0){
        if(player1_pieces > player2_pieces){
            /* player 1 wins*/
        }else if(player1_pieces < player2_pieces){
            /* player 2 wins*/
        }
        return true;
    }

    return false;
}


/* Movement*/

std::array<int, 2> Dama::Find_piece(int line_piece, int column_piece, int line_path, int column_path, Player* owner, int distance) {
    int brother_line = line_piece;
    int brother_column = column_piece;
    
    do{
        brother_line += line_path;
        brother_column += column_path;
        
        Piece* p = this->Get_Table()->Get_Piece(brother_line , brother_column);
        if (p && std::max(abs(line_piece - brother_line), abs(column_piece - brother_column)) <= distance) {
            return {brother_line, brother_column};
        }

    }while( brother_line > 0 && brother_line < this->Get_Table()->Get_SizeX() - 1 && 
            brother_column > 0 && brother_column < this->Get_Table()->Get_SizeY() - 1);

    return {-1,-1};
}

bool Dama::Movement_rules(int line_piece, int column_piece, int line_destination, int column_destination, Player* owner){

    Piece* p = this->Get_Table()->Get_Piece(line_piece, column_piece);
    //Peon
    if(p->Get_Type() == 0){
        if(line_piece == this->Get_Table()->Get_SizeX()){
            p->Set_Type(1);
        }

        if(column_piece - column_destination == 0 && abs(line_piece - line_destination) == 1){
            this->Peon_movement(line_piece,column_piece);
            
        }else{
            int diference = abs(line_piece - line_destination);
            if(diference == 2){
                if(column_piece - diference == column_destination){
                    //diagonal secondary
                    this->Peon_attack(line_piece,column_piece,p->Get_Owner(), 's');
                }else if(column_piece + diference == column_destination){
                    //diagonal principal
                    this->Peon_attack(line_piece,column_piece,p->Get_Owner(), 'p');
                }
            }
        }
    }

    if(p->Get_Type() == 1){
        int diference = line_piece - line_destination;
        if(column_piece - diference == column_destination){
            //diagonal secondary
            this->Queen_movement(line_piece,column_piece, diference, p->Get_Owner(), 's');
        }else if(column_piece + diference == column_destination){
            //diagonal principal
            this->Queen_movement(line_piece,column_piece, diference, p->Get_Owner(), 'p');
        }
    }
}

bool Dama:: Move_piece(int line, int column, int line_distance, int column_distance){
    bool valid_move = false;
    Piece *p = this->Get_Table()->Get_Piece(line + line_distance, column + column_distance);

    if(p && p->Get_Owner() != player1 && p->Get_Owner() != player2){
        valid_move = true;

        Piece* piece_actual = this->Get_Table()->Get_Piece(line, column);
        this->Get_Table()->Set_Piece(line + line_distance, column + column_distance, piece_actual /*colocar o smart pointer que faz copia*/);
        this->Get_Table()->Set_Piece(line, column, new Piece(0, ' ', nullptr));
    } 

    return valid_move;
}

bool Dama:: Remove_piece(int line, int column){
    Piece* p = this->Get_Table()->Get_Piece(line, column);
    if(p && p->Get_Char() != Owner_color(p->Get_Owner()) && p->Get_Char() != ' '){
        p->Set_Owner(nullptr);
        p->Set_Char(' ');

        return true;
    }

    return false;
}

bool Dama :: Peon_movement(int line, int column){
    return Move_piece(line, column, 1, 0);

}

bool Dama :: Peon_attack(int line, int column, Player* owner, char diagonal){
    int line_path, column_path;

    if(diagonal == 'p'){
        line_path = 1;
        column_path = 1;
    }else if(diagonal == 's'){
        line_path = 1;
        column_path = -1;
    }
    
    if(this->Move_piece(line, column, 2*line_path, 2*column_path)){
       return Remove_piece(line + line_path, column + column_path);
    } 

    return false;
}

bool Dama :: Queen_movement(int line, int column, int distance, Player* owner, char diagonal){
    std::array<int, 2> posc;
    int line_path, column_path;

    if(diagonal == 'p'){
        line_path = 1;
        column_path = 1;
    }else if(diagonal == 's'){
        line_path = 1;
        column_path = -1;
    }
    
    Piece *piece_destination = this->Get_Table()->Get_Piece(line + distance*line_path, column + distance*column_path);

    if(piece_destination){
        return false;
    }else{

        if(Move_piece(line, column, distance*line_path, distance*column_path)){
            posc = this->Find_piece(line, column, line_path,column_path, owner, distance);
            
            if(posc[0] > 1){
                Remove_piece(posc[0],posc[1]);
            }

            return true;
        }
    }
    return false;
}
