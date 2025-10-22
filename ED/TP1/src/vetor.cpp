#include "vetor.hpp"
#include <cstdlib>

template class Vetor<int>;  // instanciar explicitamente para int


//Construtor
template <typename T>
Vetor<T>::Vetor(int tamanho_){
    this->tamanho = tamanho_;
    this->array = new T[tamanho];
}

//Destrutor
template <typename T>
Vetor<T>::~Vetor(){
    delete[] array;
}

//Constutor que copia elemento do tipo vetor
template <typename T>
Vetor<T>::Vetor(const Vetor<T>& original) {
    this->tamanho = original.tamanho;
    this->array = new T[this->tamanho];

    for (int i = 0; i < this->tamanho; ++i)
        this->array[i] = original.array[i];
}
/* ---------------------------------------------------- */
//Define a quantidade de quebras de maneira a aleatoria no vetor
template <typename T>
int Vetor<T>::newShuffle(int numShuffle, int seed){
    srand48(seed);
    int p1 = 0, p2 = 0;
    for (int t = 0; t < numShuffle; t++) {
        /* Gera dois índices distintos no intervalo [0..size-1] */
        while (p1 == p2) {
            p1 = ((int)(drand48() * tamanho));
            p2 = ((int)(drand48() * tamanho));
        }
        /* Realiza a troca para introduzir uma quebra */
        swap<T>(&array[p1], &array[p2],&est);
        this->est.reset();
        p1 = p2 = 0;
    }
    return 0;
}

//Funcao que copia o array de um Vetor para o outro
template <typename T>
void Vetor<T>::Copia(const Vetor<T>& original){
    if(array && this->tamanho == original.tamanho){
        for (int i = 0; i < this->tamanho; ++i)
            this->array[i] = original.array[i];
    }
    this->est.reset();
}

//Funcao que retorna tamanho do vetor
template <typename T>
int Vetor<T>::getTamanho(){
    return this->tamanho;
}



