#ifndef TABLETOP_H
#define TABLETOP_H

#include <vector>
#include "piece.hpp"

class Tabletop{
private:
    static Piece basepiece;
    int sizeX, sizeY;
    std::vector<std::vector<Piece*>> table_grid_p;

public:
    Tabletop(int S); //inicia tabela com SxS
    Tabletop(int B, int H); //inicia tabela com valores diferentes caso queira - B -base H -altura
    
    void Table_Print();

    int Get_SizeX();
    int Get_SizeY();
    Piece *Get_Piece(int X, int Y);

    void Set_Piece(int X, int Y, Piece *p);

    ~Tabletop();
};

#endif