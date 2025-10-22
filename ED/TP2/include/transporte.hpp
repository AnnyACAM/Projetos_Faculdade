#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "armazem.hpp"

/*------------------------- GRAFO --------------------------*/
class Grafo{
    private:
        int** matrizAdjacencia;
        int tamanho; //Número de linhas e colunas

    public:
        /*Construtor e Destrutor*/
        Grafo(int tam);
        ~Grafo();

        int* BuscaLargura(int origem, int destino, int& tamanho);
        void AddAresta(int v1, int v2);
        
};

/*------------------------- TRANSPORTE --------------------------*/

class Transporte{
    private:
        int capacidade; 
        int n_pacotes;          //Quantidade de pacotes em transporte
        Pilha pilha_tranporte;    //Pilha de pacotes a serem tranportados
        Grafo grafo_armazens;

    public:
        Pilha pilha_auxiliar;    //Pilha auxiliar

        /*Construtor e Destrutor*/
        ~Transporte();
        Transporte(int capacidade, int n_armz);

        /* Ações Grafo */
        void VizinhosGrafo(int v1, int v2);
        void calculaRota(Pacote* pct);

        /* Pilha de Tranporte*/
        bool TranporteVazio();
        bool SetPacote(Pacote* pct);
        Pacote* GetPacote();
        
        /*Pilha Auxilar*/
        bool AuxiliarVazio();
        void SetPacoteAuxiliar(Pacote* pct);
        Pacote* GetPacoteAux();
        
        /*Tranporta Pacotes*/
        Pacote* AcaoTransporte(Armazem *arm);
              
};



#endif