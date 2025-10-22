#ifndef PACOTES_HPP
#define PACOTES_HPP

#include <string>

//Status Pacote
#define REARMAZENADO 33
#define REMOVIDO 12

#define NAO_POSTADO 1
#define PRONTO_TRANSPORTE 2 
#define ARMAZENADO 3
#define EM_TRANSITO 4  
#define ENTREGUE 5

/* ----------------- ROTA ------------------*/
struct Rota{
    int* caminho;           //Array com os armazés a serem seguidos
    int tamanho = 0;        //Quantidade de armazén no caminho
    int atual = 0;          //Indice atual no armazem
    bool definida = false;  

    //Defina a rota
    void DefineRota(int* rota, int n) {
        caminho = new int[n];   // aloca espaço para o caminho
        tamanho = n;            // define o tamanho do caminho
        definida = true;        // marca que a rota foi definida

        for(int i = 0; i < n; i++){
            caminho[i] = rota[i];  // copia os elementos da rota original
        }
    }

    // Avança o índice atual da rota, se ainda não chegou ao final
    void AvancaRota(){
        if(atual < tamanho - 1){
            atual += 1;
        }
    }

    // Retorna o indice do armazém atual na rota
    int getArmazemAtual(){
        return caminho[atual];
    }

    // Retorna o indice do proximo armazém atual na rota
    int getArmazemProx(){
        //Se o próximo for o final
        if(atual + 1 > tamanho - 1){
            return caminho[atual];
        }

        return caminho[atual + 1];
    }

    //Destrutor
    void deleteRota(){
        delete[] caminho;
    }

};

/* ------------------ PACOTE -------------------*/
class Pacote{
    private:
        int id_pct;
        int tempo = -1;
        int origem;
        int destino;
        
    public:
        int id_sist;
        int status;
        Rota rota;

        /*Construtores e Destrutor*/
        Pacote();
        ~Pacote();

        /*Setter e Getter*/
        std::string SetStatus(int s_, int tempo);
        int getId();
        int getTempo();
        int getOrigem();
        int getDestino();

        void defineDados(int i, int valor);
        
};

/* ------------------ PILHA DE PACOTES -------------------*/
class Pilha{
    private:
        Pacote** pilha;
        int tamanho;
        int topo;
        bool secao = false; //Se a pilha atual é uma seção

    public:
        int k_secao =-1; //Chave secao

        /*Construtor e Destrutor*/
        Pilha();
        ~Pilha();

        /*Ações na Pilha*/
        void ConstroiPilha(int tamanho);
        void push(Pacote* item); 
        Pacote* pop();
        bool vazia();
        void reset();
        void deletePilha();
        bool pilhaExiste();

        void defineSecao(int k_secao);
        int removiveis();
        
};

#endif