#ifndef UNIVERVAL_HPP
#define UNIVERVAL_HPP

#include "lib.hpp"
#include "vetor.hpp"
#include "arquivo.hpp"
#include <string>

using namespace std;

template <typename T>
class OrdenaUniversal{
    private:
        Parametros* paramet;

        //Limiares variaveis
        int limiarParticao;
        int limiarQuebras;
        int numMPS, numQUB;
        int quebras;
        Vetor<T>* vet;
    public:   
        //Constrututor
        OrdenaUniversal(Parametros* pd_,Vetor<T>* vetor);
        //Destrutor
        ~OrdenaUniversal();

        //Calcula o custo a partir das estatiticas
        double custo(const Estatistica* est); //funcao f de custo
        
        //Funcoes que chamam os algorimos de ordernacao
        void ordenadorUniversal(T* vetor, int limiarParticao, int tam, int limiarQuebras, int quebras, Estatistica* est); //Funcao Principal
        void orderna(T* vetor, int limiar, int parametro, Estatistica* est, char tipo);

        /* ------------- Partição  --------------*/
        void determinaLimiarParticao();
        void calculaNovaFaixa(int& minMPS, int&maxMPS, int& passoMPS, int posclimiar, float& diff_custo, int hist_add, const Faixa* est_custo);

        /* ------------- Quebra --------------*/
        void determinaLimiarQuebra();
        void calculaNovaQuebra(int& minQUB, int&maxQUB, int& passoQUB, int posclimiar, float& diff_custo, int hist_add, const Faixa* est_custo);
        int numQuebras();
        
        /* ------------- Registro Conclusoes  --------------*/
        string Escrita(const string& texto);
        string RegistraEstatistica(const string& tag, int numLimiar, double custo, const Estatistica& est);
        string RegistraEstConlusoes(const string& tag, const string& taglim, int numLimiar, int limiar, double diff);

};
#endif