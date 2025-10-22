#include "player.hpp"

/*Player*/
Player::Player(std::string _nickname, std::string _name)
    :nickname(_nickname), name(_name){
    std::cout << "construtor de Player foi chamado" << std::endl;
    std::cout << name;
};

void Player::Set_Team(int _team){ this->team = _team; };

/* ----Getters---- */
std::string Player::Get_Nickname(){ return this->nickname; };
std::string Player::Get_Name(){ return this->name; };
int Player::Get_Team(){ return this->team; };

