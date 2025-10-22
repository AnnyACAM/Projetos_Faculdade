#include "piece.hpp"

/*Piece*/

Piece::Piece(int _type, char _print_char, Player* _owner)
    :type(_type), print_char(_print_char), owner(_owner){
        std::cout << "construtor de Piece\n";
};

Piece::Piece(int _type, Player *_owner)
    :Piece(_type, 'O', _owner){};

Piece::Piece(int _type)
//talvez valha a pena trocar esse nullptr por um ponteiro pro jogo, talvez? pro menager? aberto à ideias
    :Piece(_type, nullptr){};

Piece::~Piece(){ std::cout << "destrutor de piece\n"; };
// bool Piece::Movement_Rules(){ return 1; };

/* ----Getters---- */
int Piece::Get_Type(){ return this->type; };
char Piece::Get_Char(){ return this->print_char; };
Player *Piece::Get_Owner(){ return this->owner; };

/* -- Setters -- */
void Piece::Set_Owner(Player* _owner){ this->owner = _owner; };
void Piece::Set_Type(int _type){ this->type = _type; };
void Piece::Set_Char(char _c){ this->print_char = _c; };
