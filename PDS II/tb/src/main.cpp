#include <iostream>
#include <string>
#include <limits>
#include <memory>
//#include <variant>
#include "game.hpp"
#include "piece.hpp"
#include "tabletop.hpp"
#include "game_controller.hpp"
#include "player.hpp"
#include "lig4_game.hpp"
#include "tic_tac_toe.hpp"
#include "reversi.hpp"
#include "dama.hpp"
#include "lines_of_action.hpp"

void Menager_Game(Game* game, std::vector<Player*> players){
    Game_Controller menager = Game_Controller(game, players);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Limpa o buffer do std::cin
    while(menager.Game_Loop()){
        std::cout << "\n" << menager.Get_Turn_Counter() << "\n";
        menager.Get_Game()->Get_Table()->Table_Print();
    }
}

int main(){
    
    int i, j, flag = 0;
    int opc;

    std::vector<Player*> test_players;
    //std::vector<std::variant<int, std::string>> test_in_vector;
    std::string input, test_format = "int int";

    test_players.push_back(new Player("tulhao77", "Tulio Faustino"));   // Esses players são placeholders para poder testar se as baseClasses conseguem rodar o jogo.
    test_players.push_back(new Player("enzoVII", "Enzo Romano"));

    std::cout << "O jogo sendo jogado eh o padrao\n" << "o jogo a ser testado 1 para lig4 e 2 pra ttt:\n";

    do{
        Game *game =nullptr;
        std::cin >> opc;

        switch (opc){
            case 1:
                game = new Lig4_Game(5, 5); 
                Menager_Game(game,test_players);
            break;

            case 2:
                game = new Tic_tac_toe(3, 3); 
                Menager_Game(game,test_players);
            break;

            case 3:
                //game = new JogoDaVelha; 
                //Menager_Game(game,test_players);
            break;

            case 4:
                game = new Reversi(8, test_players[0], test_players[1]); 
                Menager_Game(game,test_players);
            break;

            case 5:
                game = new Dama(8, test_players[0], test_players[1]); 
                Menager_Game(game,test_players);
            break;

            if(game != nullptr){

                delete game;
            }

        default:
            break;
        }

    }while (opc > 0);
    

    /*Game *test_gameL = new Lig4_Game(5, 5);
    Game *test_gameT = new Tic_tac_toe(3, 3);
    Game *test_gameLoA = new Lines_of_Action(8, 8);

    Game_Controller test_menagerL = Game_Controller(test_gameL, test_players);
    Game_Controller test_menagerT = Game_Controller(test_gameT, test_players);
    Game_Controller test_menagerLoA = Game_Controller(test_gameLoA, test_players);

    if (j == 1)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Limpa o buffer do std::cin
        while(test_menagerL.Game_Loop()){
            std::cout << "\n" << test_menagerL.Get_Turn_Counter() << "\n";
            test_menagerL.Get_Game()->Get_Table()->Table_Print();
        }
    }
    if (j == 2)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(test_menagerT.Game_Loop()){
            std::cout << "\n" << test_menagerT.Get_Turn_Counter() << "\n";
            test_menagerT.Get_Game()->Get_Table()->Table_Print();
        }
    }
    if (j == 3)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(test_menagerLoA.Game_Loop()){
            std::cout << "\n" << test_menagerLoA.Get_Turn_Counter() << "\n";
            test_menagerLoA.Get_Game()->Get_Table()->Table_Print();
        }
    }*/
    
    
    
    // Piece test_piece = Piece(1, test_players[0]);
    return 0;
}