#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include "player.hpp"

class Piece{
private:
    int type;
    //caractere impresso no tabuleiro quando o print_table() é chamado
    char print_char;
    Player *owner;

public:
    Piece(int _type, char _print_char, Player *_owner);
    Piece(int _type, Player *_owner);
    Piece(int  _type);

    int Get_Type();
    char Get_Char();
    Player *Get_Owner();

    //virtual std::vector<std::pair<int, int>> Valid_Moves(int X, int Y); //Se a peça pode se mover, retorna um vetor com as coordenadas permitidas;

    virtual ~Piece();

    void Set_Type(int _typr);
    void Set_Owner(Player *_owner);
    void Set_Char(char _c);
};
#endif