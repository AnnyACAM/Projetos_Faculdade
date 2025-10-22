#include "game_controller.hpp"
#include <sstream>
#include <memory>

/*Game_Controller*/
Game_Controller::Game_Controller(Game *_game, std::vector<Player*> players)
    : menaged_game(_game), turn_counter(0){

    int i;
    for(i = 0; i < players.size(); i++){
        ingame_players.push_back(players[i]); 
        ingame_players[i]->Set_Team(i);
        menaged_game->Initialize_Pieces(players[i]);
    }
};

Game *Game_Controller::Get_Game(){
    return this->menaged_game;
};

int Game_Controller::Get_Turn_Counter(){
    return this->turn_counter;
};

/// @brief Separa uma linha de input em inteiros ou str, de acordo com o formato.
/// @param input_format Fornece informações sobre o que o input do jogo espera receber, como "int int".
/// @param input_str Linha fornecida pelo jogador.
/// @return Retorna um vetor void* com os pointers. Deve ser revertido estáticamente pelos próprios jogos.
std::vector<std::shared_ptr<void>> Game_Controller::Filter_Input(std::string &input_format, std::string &input_str){
    std::istringstream input_stream(input_str), format_stream(input_format);
    std::string aux_format_str;
    std::vector<std::shared_ptr<void>> input_values;
    int x;
    size_t i;

    while(format_stream >> aux_format_str){
        std::string buffer_str;

        if(aux_format_str == "int"){
            if(input_stream >> buffer_str){
                for(char c : buffer_str){
                    if(!isdigit(c)){
                        throw std::invalid_argument("Argumento fornecido não é inteiro");
                    }
                }
                x = std::stoi(buffer_str);
                input_values.push_back(std::make_shared<int>(x));
            }else{
                std::cout << buffer_str;
                throw std::invalid_argument("Nao foi possivel ler o inteiro");
            }
        }
        else if(aux_format_str == "str"){
            if(input_stream >> buffer_str){
                input_values.push_back(std::make_shared<std::string>(buffer_str));
            }else{
                throw std::invalid_argument("Nao foi possivel ler a string");
            }
        }  
    }
    
    if(format_stream.eof() && !input_stream.eof()){
        throw std::invalid_argument("Argumento fornecido possui informação demais");
    }

    return input_values;

};

//controlando o turno por (turn % ingame_players[size])
//consegue-se inserir mais players caso haja essa vontade
bool Game_Controller::Game_Loop(){

    Player *current_player = ingame_players[turn_counter % ingame_players.size()];
    std::cout << "Current player:" << current_player->Get_Name() << " ";
    std::cout << turn_counter << " --- " << turn_counter % ingame_players.size()<< std::endl;

    std::string p_input, i_format = menaged_game->Get_Input_Format() ;
    std::vector<std::shared_ptr<void>> input_values;

    int i_flag = 0;
    bool victory_flag = 0;
    do{
        try{      
            std::getline(std::cin, p_input);
            if(p_input == "FS"){
                throw std::domain_error("Finalizando sistema"); // X-- exceção temporária, domain_error não faz sentido pra essa função
//                                                              //---- mas não conheço uma exceção melhor
            }
            input_values = this->Filter_Input(i_format, p_input);
            victory_flag = this->menaged_game->Player_Input(input_values, current_player);

            i_flag = 1;
        }catch(std::invalid_argument(&e)){
            std::cout << e.what() << "\nTente novamente:" << std::endl;
            i_flag = 0;
        }catch(std::domain_error(&e)){
            std::exit(1);
        }
    }while(!i_flag);

    if(victory_flag == 1){
        std::cout << "The player " << current_player->Get_Nickname() << " has won the game, congratulations!!" << std::endl;
        this->victor = current_player;
    }

    if(menaged_game->Draw_Condition(turn_counter)){
        std::cout << "the game has been draw";
        return 0;
    }

    this->turn_counter++;
    return 1;
};



Game_Controller::~Game_Controller(){};