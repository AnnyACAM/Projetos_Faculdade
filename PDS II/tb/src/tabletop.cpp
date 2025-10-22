#include "tabletop.hpp"

/*Tabletop*/
Piece Tabletop::basepiece = Piece(0);

Tabletop::Tabletop(int B, int H):sizeX(B), sizeY(H){
    int i, j;

    //inicializa o vetor com o tamanho certo;
    table_grid_p.resize(B);           
    for (auto& row : table_grid_p) {
        row.resize(H);
    }

    for(i = 0; i < B; i++){
        for(j = 0; j < H; j++){
            table_grid_p[i][j] = &basepiece;
        }
    }
    std::cout << "construtor do tabuleiro foi chamado\n";
};

Tabletop::Tabletop(int S): Tabletop(S, S){};

Tabletop::~Tabletop(){
    std::cout << "destrutor do tabuleiro foi chamado\n";
};

int Tabletop::Get_SizeX(){ return sizeX; };
int Tabletop::Get_SizeY(){ return sizeY; };
Piece *Tabletop::Get_Piece(int X, int Y){ return table_grid_p[X][Y]; };

void Tabletop::Set_Piece(int X, int Y, Piece *p){
    
    std::cout << X << ", " << Y << " " << p->Get_Type() << std::endl;
    table_grid_p[X][Y] = p;
};

void Tabletop::Table_Print(){
    
    int i,j;
    
    for(i = 0; i < sizeX; i++){
        std::cout << "| ";
        for(j = 0; j < sizeY; j++){
            if(table_grid_p[i][j]->Get_Type()==0){
                std::cout << ' ';
            }
            else{
                std::cout << table_grid_p[i][j]->Get_Char();
            }
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
};