#ifndef VETOR_HPP
#define VETOR_HPP

#include "lib.hpp"

template <typename T>
class Vetor{
    private:
        int tamanho;
        
    public:
        T* array; 
        Estatistica est;

        /* --------------------------------------------------- */
        
        //Construtores
        Vetor(int tamanho_); //Cria um vetor
        Vetor(const Vetor<T>& copia); //Cria um vetor com os dados de outro
        
        //Operador de chaves para editar diretamente o vetor
        T& operator[](int i);

        //Destrutor
        ~Vetor();

        //Adiciona quebras ao vetor
        int newShuffle(int numShuffle, int seed); //Novas Quebras
        
        //Copia os dados de um vetor
        void Copia(const Vetor<T>& original);

        int getTamanho();
};



#endif