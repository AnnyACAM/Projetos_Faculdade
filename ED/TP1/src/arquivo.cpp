#include "arquivo.hpp"
#include <iostream>
#include <iomanip>

//Construtor
Arquivo::Arquivo(string caminho_, bool novo_arq): caminho(caminho_){
    this->arquivo.open(caminho,ios::in);

    if (!this->arquivo.is_open() && novo_arq) {
        // Cria o arquivo vazio com out
        this->arquivo.open(caminho, ios::out);
        this->arquivo.close();
    }
}

//Lê parametros dados no arquivo e armazena na struct
void Arquivo::leParametros(int n_paramt, Parametros*pt_){
    string linha;
    for(int i = 0; i < n_paramt && getline(this->arquivo, linha); i++){
        if(i == 0 || i == 5){
            //Armazenando seed e tamanho
            pt_->SetParametro<int>(i, stoi(linha));
        }else if(i > 0){
            //Armazenando limiar e coeficientes
            pt_->SetParametro<double>(i, stod(linha));
        }
    }
}

//Retorna Arquivo
fstream& Arquivo::getArquivo(){
    return this->arquivo;
}

//Verifica se o arquivo está aberto
bool Arquivo::verificaArquivo(){
    return this->arquivo.is_open();
}

//Fecha o arquivo se este estiver aberto
void Arquivo::fechaArquivo(){
    if(this->arquivo.is_open()){
        this->arquivo.close();
    }
}

//Destrutor
Arquivo::~Arquivo(){
    fechaArquivo();
}

//Registra em csv
void Arquivo::Registra(string caminho_, ostringstream& oss){
    if(verificaArquivo()){
        fechaArquivo();
    }
    arquivo.open(caminho_, ios::app);
    this->arquivo << oss.str() << endl;
}