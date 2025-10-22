#include "lines_of_action.hpp"
#include "tabletop.hpp"
#include "player.hpp"

bool is_valid_direction(std::string dir_test);
int count_direction_pcs(int X, int Y, std::string dir, Tabletop *game_table);
bool is_connected(std::pair<int, int> piece1, std::pair<int, int> piece2);
std::vector<std::pair<int,int>> get_coordinates(Player *current_player, Tabletop *game_table);//retorna as coordenadas que contém peças do dono dessa peça
std::pair<int,int> vertical_movement(int X, int Y, std::string direction, Tabletop *game_table);
std::pair<int,int> horizontal_movement(int X, int Y, std::string direction, Tabletop *game_table);
std::pair<int,int> main_diag_movement(int X, int Y, std::string direction, Tabletop *game_table);
std::pair<int,int> sec_diag_movement(int X, int Y, std::string direction, Tabletop *game_table);

Lines_of_Action::Lines_of_Action(int X, int Y):Game(X, Y){};

void Lines_of_Action::Initialize_Pieces(Player *from_player){
    ingame_pieces.push_back(std::vector<Piece*>());
    if(from_player->Get_Team() == 0){
        ingame_pieces[0].push_back(new Piece(1, 'O', from_player));
        for(int i = 1; i < this->Get_Table()->Get_SizeX() - 1; i++){                 
            this->Get_Table()->Set_Piece(i, 0, ingame_pieces[0][0]);  //Inicializa as peças na coluna da esquerda
            this->Get_Table()->Set_Piece(i, this->Get_Table()->Get_SizeY() - 1, ingame_pieces[0][0]); //Inicializa as peças na coluna de direita
        }
    }else if(from_player->Get_Team() == 1){
        ingame_pieces[1].push_back(new Piece(2, 'X', from_player));
        for(int j = 1; j < this->Get_Table()->Get_SizeY() - 1; j++){                 
            this->Get_Table()->Set_Piece(0, j, ingame_pieces[1][0]);
            this->Get_Table()->Set_Piece(this->Get_Table()->Get_SizeX() - 1, j , ingame_pieces[1][0]);
        }
    }else if(from_player->Get_Team() >= 3){
        std::cout << "Esse jogo só suporta 2 jogaores" << std::endl;
        std::exit(1);
    }
}

std::string Lines_of_Action::Get_Input_Format(){
    return "int int str";
}

bool Lines_of_Action::Draw_Condition(int turn_counter){///vou fazer ainda;
    return Game::Draw_Condition(turn_counter);
};
 
bool Lines_of_Action::Victory_Condition(int X, int Y){
    Tabletop *game_table = this->Get_Table();
    Player *current_player = game_table->Get_Piece(X, Y)->Get_Owner();
    
    std::vector<std::pair<int,int>> connected;
    std::vector<std::pair<int,int>> player_pieces = get_coordinates(current_player, this->Get_Table());

    if(player_pieces.size() == 1){
        return 1;
    }

    connected.push_back(player_pieces[player_pieces.size()-1]);
    player_pieces.pop_back();

    bool disconnected_flag;

    while(player_pieces.size() != 0){
        disconnected_flag = 1;
        for(auto remaining = player_pieces.begin(); remaining != player_pieces.end(); remaining++){
            for(auto grouped = connected.begin(); grouped != connected.end(); grouped++){
                if(is_connected(*grouped, *remaining)){
                    connected.push_back(*remaining);
                    player_pieces.erase(remaining);
                    disconnected_flag = 0;
                }
            }
        }
        if(disconnected_flag){
            return 0;
        }
    }
    return 1;

}

bool Lines_of_Action::Is_Play_Valid(std::vector<std::shared_ptr<void>> input_values){
    int X = *std::static_pointer_cast<int>(input_values[0]);
    int Y = *std::static_pointer_cast<int>(input_values[1]);
    if(X > 0)
        X--;
    if(Y > 0)
        Y--;
    std::string direction = *std::static_pointer_cast<std::string>(input_values[2]);
    Player* current_player = this->Get_Table()->Get_Piece(X,Y)->Get_Owner();

    int direction_pc_counter = count_direction_pcs(X, Y, direction, this->Get_Table());
    std::cout << direction_pc_counter << std::endl;



    //vertical
    // if(direction == "N" || direction == "S"){
    //     int i = (direction == "N") ? direction_pc_counter : direction_pc_counter * (-1); //ponto máximo em ralação ao ponto inicial da peça
    //     int j = 0;
    //     while(j != i){
    //         if(X + j < 0){
    //             (direction == "N") ? j-- : j++;
    //             continue;
    //         }
    //         if(X + j >= this->Get_Table()->Get_SizeX()){
    //             (direction == "N") ? j-- : j++;
    //             continue;
    //         }
    //         if(this->Get_Table()->Get_Piece(X+j, Y)->Get_Owner()!=current_player 
    //            && this->Get_Table()->Get_Piece(X+j, Y)->Get_Owner()!=nullptr
    //            && X+j != i){
    //             throw std::invalid_argument("Essa peça está bloqueada");
    //         }
    //     }
    // }



    return 1;
}

bool Lines_of_Action::Player_Input(std::vector<std::shared_ptr<void>> input_values, Player *current_player){
    int X, Y;
    std::string direction;
    bool is_test = 0;

    X = *std::static_pointer_cast<int>(input_values[0]);
    Y = *std::static_pointer_cast<int>(input_values[1]);
    direction = *std::static_pointer_cast<std::string>(input_values[2]);

    if(X > 0)
        X--;
    if(Y > 0)
        Y--;

    if(is_valid_direction(direction)){
        if(direction == "?"){
            is_test = 1;
        }        
    }else{
        throw std::invalid_argument("Direção invalida");
    }

    std::cout << "Valores teste:" << X << ' ' << Y << ' ' << direction;
    // std::pair<int,int> destiny;
    // if(direction == "N" || direction == "S"){
    //     destiny = vertical_movement(X, Y, direction, this->Get_Table());
    // }
    
    // std::vector<std::shared_ptr<void>> testing_input = {destiny.first, destiny.second};
    // Is_Play_Valid(input_values);
    return 1; 

}

bool is_valid_direction(std::string dir_test){
    std::string valid_directions[9] = {
        "NW", "N", "NE",
        "W",  "?", "E", 
        "SW", "S", "SE"
    };
    for(int i = 0; i < 9; i++){
        if(valid_directions[i] == dir_test){
            return 1;
        }
    }
    return 0;
}
bool is_connected(std::pair<int, int> piece1, std::pair<int, int> piece2){
    if(piece1.first == piece2.first + 1 || piece2.first == piece2.first - 1 || piece1.first == piece2.first){
        if(piece1.second == piece2.second + 1 || piece2.second == piece2.second - 1 || piece1.second == piece2.second){
            return 1;
        }
    }
    return 0;
}
int count_direction_pcs(int X, int Y, std::string dir, Tabletop *game_table){
    int counter = 0, radius = game_table->Get_SizeX()-1;
    Player *current_player = game_table->Get_Piece(X, Y)->Get_Owner();
    if(dir == "S" || dir == "N"){ //conta as peças na vertical
        for(int i = 0; i < game_table->Get_SizeX(); i++){
            if(game_table->Get_Piece(i,Y)->Get_Type() != 0)
                counter++;
        }
    }
    if(dir == "W" || dir == "E"){
        for(int i = 0; i < game_table->Get_SizeX(); i++){
            if(game_table->Get_Piece(X,i)->Get_Type() != 0)
                counter++;
        }
    }
    if(dir == "NW" || dir == "SE"){
        for(int i = radius * -1; i <= radius && X - i > 0 && Y + i < game_table->Get_SizeY(); i++){

            if(X-i > game_table->Get_SizeX() - 1){continue;}
            if(Y+i < 0){continue;}

            if(game_table->Get_Piece(X-i, Y+i)->Get_Type() != 0)
                counter++;
        }
    }
    if(dir == "NE" || dir == "SW"){
        for(int i = radius * -1; i <= radius && X + i < game_table->Get_SizeX() && Y + i < game_table->Get_SizeY(); i++){

            if(X+i < 0){continue;}
            if(Y+i < 0){continue;}

            if(game_table->Get_Piece(X+i, Y+i)->Get_Type() != 0)
                counter++;
        }
    }
    return counter;
}
std::vector<std::pair<int,int>> get_coordinates(Player *current_player, Tabletop *game_table){
    std::vector<std::pair<int,int>> buf_coordinates;
    int i, j;

    for(i = 0; i < game_table->Get_SizeX(); i++){
        for(j = 0; j < game_table->Get_SizeY(); j++){
            if(game_table->Get_Piece(i,j)->Get_Owner() == current_player)
                buf_coordinates.push_back({i, j});
        }
    }
    return buf_coordinates;
}
std::pair<int,int> vertical_movement(int X, int Y, std::string direction, Tabletop *game_table){

}
std::pair<int,int> horizontal_movement(int X, int Y, std::string direction, Tabletop *game_table){

}
std::pair<int,int> main_diag_movement(int X, int Y, std::string direction, Tabletop *game_table){

}
std::pair<int,int> sec_diag_movement(int X, int Y, std::string direction, Tabletop *game_table){

}