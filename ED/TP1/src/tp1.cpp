#include <iostream>
#include <fstream>
#include <string>
#include "ordernaUniversal.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //Verifica se o usuário passo alguma valor
    if (argc < 2) {
        cout << "Nenhum arquivo foi adicionado\n";
        return 1;
    }

    //Abre o arquivo passado pelo usuario
    string caminhoArquivo = argv[1];    
    Arquivo arquivo(caminhoArquivo, false);

    if (!arquivo.verificaArquivo()) {
        cout << "Erro ao abrir o arquivo: " << caminhoArquivo << "\n";
        return 1;
    }

    //A partir da leitura do arquivo
    //Define os parametros
    Parametros dados;
    arquivo.leParametros(6, &dados);
    
    //Define o vetor
    Vetor<int> vet(dados.tam);
    string linha;
    for(int i = 0; i < dados.tam && getline(arquivo.getArquivo(), linha); i++){
        vet.array[i] = stoi(linha);
    }

    //Fecha o arquivo
    arquivo.~Arquivo();

    //Cria um ordernado universal do tipo inteiro
    OrdenaUniversal<int> uni(&dados,&vet);
    uni.determinaLimiarParticao();
    uni.determinaLimiarQuebra();

    return 0;
}
