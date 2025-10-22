#include "ordernaUniversal.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

//Construtor
template <typename T>
OrdenaUniversal<T>::OrdenaUniversal(Parametros* pd_, Vetor<T>* vetor_): paramet(pd_),  vet(vetor_){
    this->quebras = numQuebras();
    cout << Escrita("size " + to_string(paramet->tam) + " seed " + to_string(paramet->seed) + " breaks " + to_string(this->quebras)) << endl;
}

//Destrutor
template <typename T>
OrdenaUniversal<T>::~OrdenaUniversal(){ vet->~Vetor();}

/* ---------------------------------------------------- */

//Calcula o f(a,b,c) = custo
template <typename T>
double OrdenaUniversal<T>::custo(const Estatistica* est){
    return ((paramet->coef_cmp * est->cmp) + (paramet->coef_mov * est->move) + (paramet->coef_call * est->calls));
}

//Função base para ordernação universal
template <typename T>
void OrdenaUniversal<T>::ordenadorUniversal(T* vetor, int limiarParticao, int tam, int limiarQuebras, int quebras, Estatistica* est){
    if(quebras < limiarQuebras){
        insertionSort(vetor, 0, tam-1, est);
    }else {
        if(tam > limiarParticao){
            quickSort(vetor, 0, tam-1, limiarParticao, est);
        }else{
            insertionSort(vetor, 0, tam-1, est);
        }
    }
}

//Funcao que define o tipo de algoritmo de ordernação do ordernadorUniversal
template <typename T>
void OrdenaUniversal<T>::orderna(T* vetor, int valor_1, int valor_2, Estatistica* est, char tipo){
    if(tipo == 'Q'){
        //algoritmo de ordernação Quicksort
        ordenadorUniversal(vetor, valor_1, valor_2, 0, 0, est);
        
    }else if(tipo == 'I'){
        //algoritmo de ordernação InsertionSort
        ordenadorUniversal(vetor,  paramet->tam, paramet->tam, valor_1, valor_2, est);

    }else if(this->limiarParticao != 0 && this->limiarQuebras!=0){
        //Limiares já definidos
        ordenadorUniversal(vetor, this->limiarParticao, valor_1, this->limiarQuebras, valor_2, est);
    }
}

//Funcao que retorna a quantidade de quebras no vetor
template <typename T>
int OrdenaUniversal<T>::numQuebras(){
    int quebras = 0;
    for(int i = 1; i < paramet->tam; i++){
        if(this->vet->array[i] < this->vet->array[i-1]){
            quebras++;
        }
    }
    return quebras;
}

/* ---------------------------------------------------- */
//Retorna uma string
template <typename T>
string OrdenaUniversal<T>::Escrita(const string& texto){
    return texto;
}

//Retorna uma string com os dados das estatisticas
template <typename T>
string OrdenaUniversal<T>::RegistraEstatistica(const string& tag, int numLimiar, double custo, const Estatistica& est){
    ostringstream oss;
    oss << fixed << setprecision(9); //Define precisao das casas decimais de custo

    oss << tag                      //tipo do limiar
        << " " << numLimiar         //limiar
        << " cost " << custo        //custo do limiar
        << " cmp " << est.cmp       //quantidade de comparacoes
        << " move " << est.move     //quantidade de movimentacoes
        << " calls " << est.calls;  //quantidade de chamadas

    return oss.str();
}

//Retorna uma string com as conclusoes da definicao do limiar
template <typename T>
string OrdenaUniversal<T>::RegistraEstConlusoes(const string& tag, const string& taglim, int numLimiar, int limiar, double diff){
    ostringstream oss;
    oss << fixed << setprecision(6); //Define precisao das casas decimais de custo

    oss << "num" << tag         //nome da varivel do tipo do limiar
        <<  " " <<  numLimiar   //numero de verificacoes para definir o limiar
        << " lim" << taglim     //nome da varivel do tipo do limiar
        <<  " " <<  limiar      //limiar
        << " " << tag           //nome da varivel do tipo do limiar
        << "diff " <<  diff;    //diferenca dos custos

    return oss.str();
}
/* ---------------------------------------------------- */

//Funcao que encontra o limiar de particao
template <typename T>
void OrdenaUniversal<T>::determinaLimiarParticao(){
    Faixa* est_custo = new Faixa[20];           //vetor de custos e estatisticas
    int poscLimiar = 0;                         //indice do limiar no vetor de custos e estatisticas
    float diff_custo = 0;                       //diferenca entre o maior e o menor custo
    Vetor<T> vetor(*this->vet);                 //Copia vetor original
    int iter = 0;                               //Numero de iteracoes

    int minMPS = 2;                     //tamanho minimo da particao
    int maxMPS = paramet->tam;          //tamanho maximo da particao
    int passoMPS = (maxMPS-minMPS)/5;   //quantidade de passos

    //Altera variveis para poder entrar no for
    this->numMPS = 5;
    diff_custo = paramet->limiarCusto;
    
    while ((diff_custo >= paramet->limiarCusto) && (numMPS >= 5)){
        cout << Escrita(string("\niter ") + to_string(iter)) << endl; //registra a iteracao
        iter++;
        numMPS = 0;
        
        int addCustos = 0; //indice do vetor de custos e estatisticas

        for(int t = minMPS; t <= maxMPS; t += passoMPS){
            vetor.Copia(*this->vet); //Faz copia do vetor
            orderna(vetor.array, t, paramet->tam, &vetor.est, 'Q');//Orderna usando o quicksort
            
            est_custo[addCustos].registra(t, custo(&vetor.est), numMPS); //Armazena dados
            /*O vetor est_custo é sobrescrito afim de facilitar a implementação da função*/

            if(est_custo[poscLimiar].custo > est_custo[addCustos].custo){
                //Encontra indice com menor custo
                poscLimiar = addCustos;
            }

            cout << this->RegistraEstatistica("mps",t, est_custo[addCustos].custo, vetor.est) << endl; //registra estatisticas

            numMPS++;
            addCustos++; //soma o indice
        }
        
        this->limiarParticao = est_custo[poscLimiar].limiar; //define limiar de particao
        calculaNovaFaixa(minMPS, maxMPS, passoMPS, poscLimiar,diff_custo, addCustos, est_custo); //define novo minMPS, maxMPS, passoMPS e diffcusto
        cout << RegistraEstConlusoes("mps","Particao",numMPS, limiarParticao, diff_custo) << endl; //registra conclusoes
    }
    
    delete[] est_custo; //libera espaço na memória
}

//Funcao que define o novo valor de variveis a partir do maior e menor custo
template <typename T>
void OrdenaUniversal<T>::calculaNovaFaixa(int& minMPS, int&maxMPS, int& passoMPS, int posclimiar, float& diff_custo, int hist_add, const Faixa* est_custo){
    int newMin, newMax;
    if(posclimiar == 0){
        //Se o limiar está na primeira posicao
        newMin = 0;
        newMax = 2;
    }else if(posclimiar == numMPS - 1){
        //Se o limiar está na ultima posicao
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    }else{
        //Se o limiar esta entre a primeira e a ultima posicao
        newMin = posclimiar - 1;
        newMax = posclimiar + 1;
    }
    /*posicao em relacao a ordem de registro no vetor est_custo*/

    int min, max;
    if(newMax <= hist_add && newMin >= 0){
        min = est_custo[newMin].posc;
        max = est_custo[newMax].posc;
    }else{
        min = est_custo[0].posc;
        max = est_custo[hist_add].posc;
    }

    //define valores
    diff_custo = abs(est_custo[max].custo - est_custo[min].custo);
    minMPS = est_custo[min].limiar;
    maxMPS = est_custo[max].limiar;
    passoMPS = (est_custo[max].limiar - est_custo[min].limiar) / 5 ;
    if ( passoMPS == 0 ) passoMPS++;

}

/* ---------------------------------------------------- */

//Funcao que define limiar de quebra
template <typename T>
void OrdenaUniversal<T>::determinaLimiarQuebra(){
    Vetor<T> vetor(*this->vet);                     //Copia vetor original
    orderna(vetor.array, this->limiarParticao,paramet->tam, &vetor.est, 'Q'); //Orderna o vetor com quicksort (pois já se sabe o limiarParticao)
    vetor.est.reset();                              //zera a struct de estatisticas

    float diff_custo = 0;                   //diferenca entre o maior e menor custo
    int iter = 0;                           //quantidade de iteracoes
    int minQUB = 1;                         //tamanho minimo de quebras
    int maxQUB = paramet->tam/2;            //tamanho maximo de quebras
    int passoQUB = (maxQUB - minQUB)/5;     //quantidade de quebras
    
    Vetor<T> v_in(vetor);                   //vetor a ser ordernado com insertion, faz copia do vetro ordernado
    Vetor<T> v_qs(vetor);                   //vetor a ser ordernado com quicksort, faz copia do vetro ordernado
    Faixa* est_custo = new Faixa[40];       //vetor de estatisticas e custos

    //Altera variveis para poder entrar no for
    this->numQUB = 5;
    diff_custo = paramet->limiarCusto;

    while ((diff_custo >= paramet->limiarCusto) && (numQUB >= 5)){
        cout << Escrita(string("\niter ") + to_string(iter)) << endl;
        
        iter++;
        numQUB = 0;

        int addCustos = 0;      //indice do vetor de custos e estatisticas
        int poscLimiar = 0;     //indice do limiar no vetor de custos e estatisticas
        
        for(int t = minQUB; t <= maxQUB; t += passoQUB){
            auto inicio = std::chrono::high_resolution_clock::now(); //incializa tempo de duracao

            v_in.newShuffle(t, paramet->seed);                      //Adiciona t quebras ao vetor ordernado
            orderna(v_in.array, t, this->quebras, &v_in.est, 'I');  //Orderna usando insertion

            v_qs.newShuffle(t, paramet->seed);                                      //Adiciona t quebras ao vetor ordernado
            orderna(v_qs.array, this->limiarParticao, paramet->tam, &v_qs.est, 'Q');//Ordena usando quicksort

            est_custo[addCustos].registra(t, custo(&v_qs.est), numQUB); //Armazena dados insertion
            est_custo[addCustos+1].registra(t, custo(&v_in.est), numQUB); //Armazena dados quicksort

            if(abs(est_custo[addCustos+1].custo - est_custo[addCustos].custo) <= abs(est_custo[poscLimiar].custo - est_custo[poscLimiar-1].custo)){
                //Encontra indice com menor custo
                poscLimiar = addCustos+1;
            }

            cout << this->RegistraEstatistica("qs lq",t, est_custo[addCustos].custo, v_qs.est) << endl;  //registra estatisitica do vetor ordernado por quicksort
            cout << this->RegistraEstatistica("in lq",t, est_custo[addCustos+1].custo, v_in.est) << endl; //registra estatisitica do vetor ordernado por insertionsort
            v_in.Copia(vetor); //Copia vetor ordernado
            v_qs.Copia(vetor); //Copia vetor ordernado
            numQUB++;
            addCustos += 2;

            auto fim = std::chrono::high_resolution_clock::now(); //finaliza cronometro
            std::chrono::duration<double, std::milli> duracao = fim - inicio; // Calcula a duração em milissegundos
            ostringstream oss;
            oss << t << "," << est_custo[addCustos].custo << "," << est_custo[addCustos+1].custo << "," << abs(est_custo[poscLimiar].custo - est_custo[poscLimiar-1].custo) << "," << duracao.count();
        }

        this->limiarQuebras = est_custo[poscLimiar].limiar; //Define limiar de quebras
        calculaNovaQuebra(minQUB, maxQUB, passoQUB, poscLimiar,diff_custo, addCustos, est_custo); //define novo minQUB, maxQUB, passoQUB e diffcusto
        cout << RegistraEstConlusoes("lq","Quebras",numQUB, limiarQuebras, diff_custo) << endl; //registra conclusoes
    }

    delete[] est_custo; //libera espaço na memória

}

//Funcao que define o novo valor de variveis a partir do maior e menor custo
template <typename T>
void OrdenaUniversal<T>::calculaNovaQuebra(int& minQUB, int&maxQUB, int& passoQUB, int posclimiar, float& diff_custo, int hist_add, const Faixa* est_custo){
    int newMin, newMax;
    if(posclimiar == 1){
        //Se o limiar foi o primeiro a ser adicionado
        newMin = 1;
        newMax = 5;
       
    }else if(posclimiar/2 == numQUB - 1){
        //Se o limiar foi o ultimo a ser adicionado
        newMin = posclimiar - 4;
        newMax = posclimiar;
    }else{
        //Se o limiar foi adicionado entre o primeiro e o ultimo elemento
        newMin = posclimiar - 2;
        newMax = posclimiar + 2;
    }
    /*posicao em relacao a ordem de registro no vetor est_custo, para o limiar definido a 
      partir da posicao do dado dos insertion*/

    //define valores
    diff_custo = abs(est_custo[newMax].custo - est_custo[newMin].custo);
    minQUB = est_custo[newMin].limiar;
    maxQUB = est_custo[newMax].limiar;
    passoQUB = (est_custo[newMax].limiar - est_custo[newMin].limiar) / 5 ;
    if ( passoQUB == 0 ) passoQUB++;
}





template class OrdenaUniversal<int>;  // instanciar explicitamente para int
//template class OrdenaUniversal<string>;  // instanciar explicitamente para string
