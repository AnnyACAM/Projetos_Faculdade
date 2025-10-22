#ifndef LIB_HPP
#define LIB_HPP

#include <string>
using namespace std;

//Struct que armazena os dados das instâncias ao definir o limiares
struct Faixa {
    //dados dos limiares de uma faixa
    int limiar;
    double custo;
    int posc; //MPB ou QUB

    //Setter
    void registra(int l, double c, int m){
        limiar = l;
        custo = c;
        posc = m;
    }
};

/* ---------------------------------------------------*/
//Struct que armazena os parâmetros lidos do arquivo
struct Parametros {
    //dados iniciais do arquivo
    int seed;
    double limiarCusto;
    double coef_cmp, coef_mov, coef_call;
    int tam;

    template <typename T>
    void SetParametro(int posc, T valor){
        switch (posc){
            case 0:
                seed = valor;
                break;
            case 1:
                limiarCusto = valor;
                break;
            case 2:
                coef_cmp = valor;
                break;
            case 3:
                coef_mov = valor;
                break;
            case 4:
                coef_call = valor;
                break;
            case 5:
                tam = valor;
                break;
            
            default:
                break;
        }
    }
};

/* ---------------------------------------------------*/

struct Estatistica {
    int cmp = 0;    //comparacoes
    int move = 0;   //movimentacoes
    int calls = 0;  //chamadas

    //zera todos os dados
    void reset(){  cmp = 0; move = 0; calls = 0;  }

    //incrementa o numero de comparacoes  
    void addcmp(int num){   cmp += num;     }
    
    //incrementa o numero de movimentacoes de dados  
    void addmove(int num){  move += num;    }

    //incrementa o numero de chamadas de função  
    void addcalls(int num){  calls += num;  }

};

 /* ---------------------------------------------------*/
    
 //Ordernadores
template <typename T>
void swap(T *xp, T *yp, Estatistica *est);

template <typename T>
void insertionSort(T *v, int l, int r, Estatistica* est);

template <typename T>
void partition3(T * A, int l, int r, int *i, int *j, Estatistica *est);

template <typename T>
T mediana(T a, T b, T c);

template <typename T>
void quickSort(T * A, int l, int r, int limiar, Estatistica *est);

 /* ---------------------------------------------------*/


#endif

