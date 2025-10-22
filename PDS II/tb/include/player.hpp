#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

//ideia de fazer uma variável de time estática, de tal forma que dá pra auto-designar time
class Player{ 
private:
    int team;
    std::string name, nickname;

public:
    Player();
    Player(std::string _nickname, std::string _name);

    void Set_Team(int _team);

    int Get_Team();
    std::string Get_Name();
    std::string Get_Nickname();
};
#endif