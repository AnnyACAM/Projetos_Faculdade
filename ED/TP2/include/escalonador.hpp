#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#define EVENTO_PACT 1
#define EVENTO_TRANSP 2

#include "transporte.hpp"
#include <cmath>

/* ----------------- EVENTO ------------------------*/
struct Evento{
    long long id;
    int tipo = 0;
    int tempo;
    Pacote* pacote;
    
    void defineID(){
        long long base = (long long)this->tempo * pow10(6 + dezenas(pacote->getOrigem()));

        if (tipo == EVENTO_PACT) {
            this->id = base + 
                       this->pacote->getId() * 10 +
                       this->tipo;

        } else if (tipo == EVENTO_TRANSP) {
            this->id = base + this->pacote->rota.getArmazemAtual() * pow10(3 + dezenas(pacote->rota.getArmazemAtual()))
                            + this->pacote->rota.getArmazemProx() * pow10(dezenas(pacote->rota.getArmazemProx()))
                            + this->tipo;
        }
    }

    long long pow10(int expoente) {
        long long resultado = 1;
        for (int i = 0; i < expoente; ++i) {
            resultado *= 10;
        }
        return resultado;
    }   

    //Conta quantas dezenas tem o número
    int dezenas(int x) {
        if (x < 10) return 1;

        int casas = 0;
        while (x > 0) {
            x /= 10;
            casas++;
        }
        return casas;
    }

    /*Construtores*/
    Evento(int tipo, int tempo, Pacote* pacote){
        this->tipo = tipo;
        this->tempo = tempo;
        this->pacote = pacote;

        if(!(this->pacote == nullptr)){
            defineID();
        }else{
            this->id = 0;
            this->tempo = 0;
        }
    }
    Evento(){}

    /*Operaor menor*/
    bool operator<(const Evento& outro) {
        if(this->tempo <= 0 || this->pacote == nullptr){
            return false;
        }
        if(this->id < outro.id){
            return true;
        }

        return false;
    };

};

/* ---------------------- HEAP -----------------------*/

class MinHeap{
    private:
        //Get indices
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);

        int tamanho;
        int n_elementos = 0;
        Evento* data;

     public:
        /*Construtores*/
        MinHeap(int maxsize);
        /*Destrutor*/
        ~MinHeap();

        void Inserir(Evento x);
        Evento* Remover();
        bool Vazio();
        void HeapifyPorBaixo(int posicao);
        void HeapifyPorCima(int posicao);
        void redimensionaHeap();

};

/* ------------------------ ESCALONADOR -------------------------*/
class Escalonador {
    private:
        MinHeap fila_prioridade;

    public:
        /*Construtores*/
        Escalonador(int n_armazens);
        
        /*destrutor*/
        ~Escalonador();

        void inserirEvento(int tipo, int tempo, Pacote*pct);
        Evento* retiraMenorEvento();
        bool vazio();
        
};


#endif