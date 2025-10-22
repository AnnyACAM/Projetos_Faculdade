#include "game.hpp"

/*Game*/
Game::Game(int sizeX, int sizeY){
    
    table = new Tabletop(sizeX, sizeY);   
    std::cout << "construtor do jogo foi chamado\n";
}
//Relaciona a posição de turno, paralelo ao vetor de ingame_players
//Método virtual, pode ser modificado de acordo com o tipo das peças e das necessidades do jogo
void Game::Initialize_Pieces(Player *from_player){

    ingame_pieces.push_back(std::vector<Piece*>());                 
    ingame_pieces[from_player->Get_Team()].push_back(new Piece(1, from_player->Get_Nickname()[0], from_player));
    //Ex.jogo da velha: a peça do p1 é incializada com new piece(1, from_player, 'o')
    // e o p2 new piece(1, from_player, 'x')
};
 
std::vector<Piece*> Game::Get_Player_Pieces(Player *from_player){
    return ingame_pieces[from_player->Get_Team()];
};

Game::Game(int SIZE):Game(SIZE,SIZE){};

Tabletop *Game::Get_Table(){
    return this->table;
};

std::string Game::Get_Input_Format(){
    return "int int";
};

// --X Precisa ser virtual, pois o input pode ser diferente, como no lig4, que só espera uma coluna 
bool Game::Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player){ 
    
    //Essa operação é segura devido à natureza já tratada de input, ou seja, se as primeiras duas posições de
    //input não fossem "castaveis" pra int, o Game_Controller::Filter_Input não teria retornado
    
    int X = *std::static_pointer_cast<int>(input_values[0]);
    int Y = *std::static_pointer_cast<int>(input_values[1]);
    
    ///por padrão, a peça jogada é a de índice 0 pois só existe um tipo de peça de player, mas em jogos
    ///que possuem mais peças, uma lógica deve ser implementada para saber qual peça está sendo posicionada ou movida.
    table->Set_Piece(X-1, Y-1, ingame_pieces[current_player->Get_Team()][0]);
};

bool Game::Draw_Condition(int turn_counter){
    //Por padrão, na maioria dos jogos o empate é decidido ao preencher todo o tabuleiro:
    if(turn_counter + 1 == this->Get_Table()->Get_SizeX() * this->Get_Table()->Get_SizeY()){
        return 1;
    }else{
        return 0;
    }
};

Game::~Game(){
    std::cout << "destrutor chamado\n";
};

bool Game::Victory_Finish(){}
bool Game::Victory_Condition(int x, int y){}