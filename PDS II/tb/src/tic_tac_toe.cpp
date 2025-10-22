#include "tic_tac_toe.hpp"
#include <cstdlib>

Tic_tac_toe::Tic_tac_toe(int X, int Y):Game(X, Y){};

void Tic_tac_toe::Initialize_Pieces(Player *from_player){
    Game::Initialize_Pieces(from_player);
};

std::string Tic_tac_toe::Get_Input_Format(){
    return "int int";
};

bool Tic_tac_toe::Draw_Condition(int turn_counter){
    return Game::Draw_Condition(turn_counter);
}

bool Tic_tac_toe::Victory_Condition(int X, int Y){

    int i, j, aux_X, aux_Y, counter = 0, victory_flag = 0;
    int sizeX = this->Get_Table()->Get_SizeX(), sizeY = this->Get_Table()->Get_SizeY();
    Player *current_player = this->Get_Table()->Get_Piece(X, Y)->Get_Owner();

    //Vitoria Horizontal
    for (size_t i = 0; i < sizeX; i++)
    {
        if (this->Get_Table()->Get_Piece(X, i)->Get_Owner() == current_player)
        {
            counter++;
        }
        if(counter == 3){
            std::cout << "\n-------victory------ Horizontal\n";
            victory_flag++;
            break;
        }
    }
    counter = 0;
    //Vitoria Vertical
    for (size_t i = 0; i < sizeY; i++)
    {
        if (this->Get_Table()->Get_Piece(i, Y)->Get_Owner() == current_player)
        {
            counter++;
        }
        if(counter == 3){
            std::cout << "\n-------victory------ Vertical\n";
            victory_flag++;
            break;
        }
    }
    counter = 0;

    //Vitoria Diagonal Principal
    for (size_t i = 0; i < sizeX; i++)
    {
        if (this->Get_Table()->Get_Piece(i, i)->Get_Owner() == current_player)
        {
            counter++;
        }
        if(counter == 3){
            std::cout << "\n-------victory------ Diagonal\n";
            victory_flag++;
            break;
        }
    }
    counter = 0;
    
    //Vitoria Diagonal Secundaria
    for (size_t i = 0; i < sizeX; i++)
    {
        if (this->Get_Table()->Get_Piece(i, 2-i)->Get_Owner() == current_player)
        {
            counter++;
        }
        if(counter == 3){
            std::cout << "\n-------victory------ Diagonal\n";
            victory_flag++;
            break;
        }
    }
    counter = 0;

    if(victory_flag != 0){
        std::cout << "o jogador " << current_player->Get_Nickname() << " ganhou!!\n";
        return 1;
    }else{
        return 0;
    }

}


bool Tic_tac_toe::Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values){
    int X, Y;
    X = *std::static_pointer_cast<int>(input_values[0]);
    Y = *std::static_pointer_cast<int>(input_values[1]);
    if(Y!=0)
        Y--;
    if(X!=0)    
        X--;

    if (X < 0 || X > 2 || Y < 0 || Y > 2)
    {
        return 0;
    }
    if(this->Get_Table()->Get_Piece(X, Y)->Get_Type() != 0){
        return 0;
    }
    else{
        return 1;
    }
};

bool Tic_tac_toe::Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player){
    int i, X, Y, flag = 0;
    
    X = *std::static_pointer_cast<int>(input_values[0]);
    Y = *std::static_pointer_cast<int>(input_values[1]);

    if(Y!=0)
        Y--;
    if(X!=0)    
        X--;

    if(Is_Play_Valid(input_values)){
        this->Get_Table()->Set_Piece(X, Y, this->Get_Player_Pieces(current_player)[0]);
        // std::cout << X << " " << "Y ";
        // std::cout << this->Get_Player_Pieces(current_player)[0]->Get_Owner()->Get_Nickname() << std::endl;
    }else{
        throw std::invalid_argument("jogada invalida, tente novamente\n");
    }

    if(Victory_Condition(X, Y)){
        return 1;
    }else{
        return 0;
    }
};

Tic_tac_toe::~Tic_tac_toe(){ std::cout << "destruindo Tic_tac_toe\n"; };
