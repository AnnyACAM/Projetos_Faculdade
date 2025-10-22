#include "lig4_game.hpp"
#include <cstdlib>

int Horizontal(int X, int Y, int radius, Tabletop *game_table);     //Checa sequência na horizontal
int Vertical(int X, int Y, int radius, Tabletop *game_table);       //Checa sequência na vertical
int Main_Diagonal(int X, int Y, int radius, Tabletop *game_table);  //Checa sequência na diagonal principal
int Sec_Diagonal(int X, int Y, int radius, Tabletop *game_table);   //Checa sequência na diagonal secundária  

Lig4_Game::Lig4_Game(int X, int Y):Game(X, Y){};

void Lig4_Game::Initialize_Pieces(Player *from_player){
    Game::Initialize_Pieces(from_player);
};

std::string Lig4_Game::Get_Input_Format(){
    return "int";
};

bool Lig4_Game::Draw_Condition(int turn_counter){
    return Game::Draw_Condition(turn_counter);
};

bool Lig4_Game::Victory_Condition(int X, int Y){

    int victory_flag = 0;
    Player *current_player = this->Get_Table()->Get_Piece(X, Y)->Get_Owner();

    if(Main_Diagonal(X, Y, 3, this->Get_Table())>= 4){
        std::cout << "------Victory------ Diagonal";
        victory_flag++;
    }
    if(Sec_Diagonal(X, Y, 3, this->Get_Table())>= 4){
        std::cout << "------Victory------ Secondary diagonal\n";
        victory_flag++;
    }
    if(Horizontal(X, Y, 3, this->Get_Table())>= 4){
        std::cout << "------Victory------ Horizontal";
        victory_flag++;
    }
    if(Vertical(X, Y, 3, this->Get_Table())>= 4){
        std::cout << "------Victory------ Vertical\n";
        victory_flag++;
    }

    if(victory_flag != 0){
        std::cout << "o jogador " << current_player->Get_Nickname() << " ganhou!!\n";
        return 1;
    }else{
        return 0;
    }
};

//talvez seja interessante fazer um overload pra fornecer apenas o Y, 
//ao invés de fornecer o x como constante 0 (já que o input é apenas o Y)
bool Lig4_Game::Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values){
    int i;
    int Y = *std::static_pointer_cast<int>(input_values[0]);
    if(Y!=0)
        Y--;

    if(Y > (this->Get_Table()->Get_SizeY() - 1) || Y < 0){
        return 0;
    }
    for(i = 0; i < this->Get_Table()->Get_SizeX(); i++){
        if(this->Get_Table()->Get_Piece(i, Y)->Get_Type() != 0){
            break;
        }
    }
    if(i!=0){
        return 1;
    }else{
        return 0;
    }
};

bool Lig4_Game::Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player){

    int i, flag = 0;
    int Y = *std::static_pointer_cast<int>(input_values[0]);

    if(Y!=0)
        Y--; //é mais intuitívo que no input a primeira casa seja 1, porém no vetor ela é 0, por isso o Y--
        
    if(Is_Play_Valid(input_values)){
        for(i = 0; i < this->Get_Table()->Get_SizeX(); i++){
            if(this->Get_Table()->Get_Piece(i, Y)->Get_Type() != 0){
                break;
            }
        }
        this->Get_Table()->Set_Piece(i-1, Y, this->Get_Player_Pieces(current_player)[0]);
    }else{
        throw std::invalid_argument("Jogada Invalida tente novamente");
    }

    if(Victory_Condition(i-1, Y)){
        std::cout << current_player->Get_Nickname() << " ganhou e agora? why are we still here?\n";
        return 1;
    }
    return 0;
};



Lig4_Game::~Lig4_Game(){ std::cout << "destruindo lig4_game\n"; };

///  Funções de leituras direcionais

int Horizontal(int X, int Y, int radius, Tabletop *game_table){     //Checa sequência na horizontal
    Player *current_player = game_table->Get_Piece(X, Y)->Get_Owner();
    int i, counter = 0;
    for(i = radius * -1; i <= radius && X + i < game_table->Get_SizeX() && Y + i < game_table->Get_SizeY(); i++){
        if(X+i < 0){continue;}
        if(Y+i < 0){continue;}
        if(game_table->Get_Piece(X, Y+i)->Get_Owner() == current_player){
            counter++;
        }else{
            counter = 0;
        }
        if(counter == 4){
            return counter;
        }
    }
    return counter;
}

int Vertical(int X, int Y, int radius, Tabletop *game_table){       //Checa sequência na vertical
    Player *current_player = game_table->Get_Piece(X, Y)->Get_Owner();
    int i, counter = 0;
    for(i = radius * -1; i <= radius && X + i < game_table->Get_SizeX() && Y + i < game_table->Get_SizeY(); i++){
        if(X+i < 0){continue;}
        if(Y+i < 0){continue;}
        if(game_table->Get_Piece(X+i, Y)->Get_Owner() == current_player){
            counter++;
        }else{
            counter = 0;
        }
        if(counter == 4){
            return counter;
        }
    }
    return counter;

}

int Main_Diagonal(int X, int Y, int radius, Tabletop *game_table){      //Checa diagonal principal
    Player *current_player = game_table->Get_Piece(X, Y)->Get_Owner();
    int i, counter = 0;
    for(i = radius * -1; i <= radius && X + i < game_table->Get_SizeX() && Y + i < game_table->Get_SizeY(); i++){

        if(X+i < 0){continue;}
        if(Y+i < 0){continue;}

        if(game_table->Get_Piece(X+i, Y+i)->Get_Owner() == current_player){
            counter++;
        }else{
            counter = 0;
        }
        if(counter == 4){
            return counter;
        }
        if(counter == 0 && i == 1){
            break;
        }
    }
    return counter;
}

int Sec_Diagonal(int X, int Y, int radius, Tabletop *game_table){   //Checa sequência na diagonal secundária
    Player *current_player = game_table->Get_Piece(X, Y)->Get_Owner();
    int i, counter = 0;

    for(i = radius * -1; i <= radius && X - i > 0 && Y + i < game_table->Get_SizeY(); i++){

        if(X-i > game_table->Get_SizeX() - 1){continue;}
        if(Y+i < 0){continue;}

        if(game_table->Get_Piece(X-i, Y+i)->Get_Owner() == current_player){
            counter++;
        }else{
            counter = 0;
        }
        if(counter == 4){
            return counter;
        }
        if(counter == 0 && i == 1){
            break;
        }
    }
    return counter;
}