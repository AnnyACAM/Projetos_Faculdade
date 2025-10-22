#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include "menager.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //Verifica se o usuário passou algum valor
    if (argc < 2) {
        cout << "Nenhum arquivo foi adicionado\n";
        return 1;
    }

    //Abre o arquivo passado pelo usuario
    string caminhoArquivo = argv[1];    
    fstream arquivo(caminhoArquivo,ios::in);


    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << caminhoArquivo << "\n";
        return 1;
    }

    //Cria o gerenciador de eventos
    Menager menager;

    //Iniciliza
    for (int i = 0; i < 5; i++) {
        int valor;
        arquivo >> valor; 
        menager.setDados(i, valor);
    }

    menager.define();

    //Cria matriz de adjacência
    for(int i = 0; i < menager.getNumeroArmazens(); i++){
        for(int j = 0; j < menager.getNumeroArmazens(); j++){
            int valor_matriz;
            arquivo >> valor_matriz;
            if(valor_matriz == 1){
                menager.getTransporte()->VizinhosGrafo(i, j);
                menager.getArmazem(i)->DefineSecoes(j, menager.getNumeroArmazens());
            }
        }
    }


    int n_pacotes;
    arquivo >> n_pacotes;
    menager.definePacotes(n_pacotes);

    //Define Pacotes
    for(int i = 0; i < n_pacotes; i++){
        Pacote pct_aux;
        string dados_pct;
        for(int j = 0; j < 7; j++){
            arquivo >> dados_pct;
            if(j % 2 == 0){
                pct_aux.defineDados(j, stoi(dados_pct));
            }
        }
        menager.inserePacote(i, pct_aux);
        
    }
    ofstream csv("resultados_analise.csv", ios::app);
    csv << "armazens,pacotes,capacidade,intervalo_tranp,tempo_exec_s" << "\n";
    string texto;
    //Gerencia eventos
    auto start = std::chrono::high_resolution_clock::now();
    texto = menager.ArmazemHanoi();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = end - start;
    std::ostringstream oss;
    oss << tempo.count();
    texto += oss.str();
    csv << texto << "\n";
    
    return 0;
}


