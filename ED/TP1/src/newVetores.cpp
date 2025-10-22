#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#include "vetor.hpp"
#include "lib.hpp"

using namespace std;
using namespace std::chrono; 

//Cria novos vetores para Análise Experimental

template <typename T>
double ordena(Vetor<T>* v, int tamanho, char tipo){
    auto inicio  = high_resolution_clock::now();
    if(tipo == 'Q'){
        quickSort(v->array, 0, tamanho - 1, 50, &v->est);
    }else{
        insertionSort(v->array, 0, tamanho -1, &v->est);
    }

    auto fim = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(fim - inicio).count();

    return dur;
};

int main(int argc, char* argv[]) {
    string caminho = "dados.csv";
    ofstream arquivo(caminho);
    arquivo << "tamanho,quebras,tipo,duracao,cmp,call,move" << endl;  // cabeçalho do CSV
    
    for(int j = 200; j < 10000 + 200; j += 200){
        srand(time(nullptr) + j);
    
        Vetor<int> vet(j);
        Vetor<int> vet2(vet);
        
        for(int i = 0; i < j; i++){
            vet.array[i] = rand();
        }

        int quebras = 0;
        for(int i = 0; i < j - 2; i++){
            if(vet.array[i] > vet.array[i+1]){
                quebras++;
            }
        }

        double dur_in = ordena<int>(&vet, j, 'Q');
        double dur_qs = ordena<int>(&vet2, j, 'I');

        arquivo << j << "," << quebras << "," << "in" << "," << dur_in << "," << vet2.est.cmp << "," << vet2.est.calls << "," << vet2.est.move << endl;
        arquivo << j << "," << quebras << "," << "qs" << "," << dur_qs << "," << vet.est.cmp << "," << vet.est.calls << "," << vet.est.move << endl;

    }

    arquivo.close();
    return 0;
}

