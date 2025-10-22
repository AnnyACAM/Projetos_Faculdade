#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "pacote.hpp"

class Armazem{
    private:
        int id_armazem; 
        int n_vizinhos; //Quantidade de Armazens
        Pilha** secoes; //Conjunto de Pilhas de Pacote
        
    public:
        /*Construtor e Destrutor*/
        Armazem(int id, int n_vizinhos);
        ~Armazem();

        /*Ações no armazem*/
        Pacote* RetiraPacote();
        void AdicionaPacote(Pacote* pct);
        int getId();

        /*Ações nas secoes armazem*/
        Pilha* getSecao(int secao);
        Pacote* RetiraPacoteSecao(int secao);
        bool SecaoDefinida(int secao);
        void AdicionaPacoteSecao(int secao, Pacote* pct);
        void DefineSecoes(int chave, int capacidade);
        bool SecaoVazia(int secao);
        
};



#endif