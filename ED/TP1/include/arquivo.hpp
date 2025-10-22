#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <fstream>
#include <string>
#include "lib.hpp"

using namespace std;

class Arquivo{
    private:
        fstream arquivo;
        string caminho;

    public:
        //Contrutor
        Arquivo(string caminho_, bool novo_arq);
        //Desconstrutor
        ~Arquivo();

        //Le parametros do arquivo e armazena na struct parametro
        void leParametros(int n_paramt, Parametros*pt_);
        
        //Fecha o arquivo
        void fechaArquivo();

        //Verifica se o arquivo foi aberto
        bool verificaArquivo();

        //Retorna arquivo
        fstream& getArquivo();

        //Registra em csv
        void Registra(string caminho_, ostringstream& oss);
        
};

#endif