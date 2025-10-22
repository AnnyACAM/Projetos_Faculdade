#include "groups.hpp"

#define HEAP
#ifdef HEAP

class Heap{
    private:
        //Get indices
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);

        int tamanho;
        int n_elementos = 0;
        Evento** data;

     public:
        /*Construtores*/
        Heap(int maxsize);
        /*Destrutor*/
        ~Heap();

        void Inserir(Evento* x);
        Evento* Remover();
        bool Vazio();
        void HeapifyPorBaixo(int posicao);
        void HeapifyPorCima(int posicao);
        void redimensionaHeap();

};

#endif