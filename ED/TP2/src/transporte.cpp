#include "transporte.hpp"
#include <iostream>

/*------------------------- TRANSPORTE --------------------------*/

/*Construtor*/
Transporte::Transporte(int capacidade_, int n_armz):capacidade(capacidade_), pilha_tranporte(), grafo_armazens(n_armz), pilha_auxiliar(){
    this->pilha_tranporte.ConstroiPilha(capacidade_); //Aloca pilha de tranporte
    this->pilha_auxiliar.ConstroiPilha(n_armz); //Aloca pilha auxiliar
}

/*Destrutor*/
Transporte::~Transporte(){
    /*this->pilha_tranporte.deletePilha();
    this->pilha_auxiliar.deletePilha();*/
}

/* Define a rota do pacote através da Busca em Largura no Grafo*/
void Transporte::calculaRota(Pacote* pct){
    int* rota;
    int tamanho_rota = 0;
    rota = this->grafo_armazens.BuscaLargura(pct->getOrigem(), pct->getDestino(), tamanho_rota);
    
    if(rota != nullptr){
        pct->rota.DefineRota(rota, tamanho_rota);
        delete[] rota;
    }
    
}
/*Adiciona aresta entre armazens viznhos*/
void Transporte::VizinhosGrafo(int v1, int v2){
    this->grafo_armazens.AddAresta(v1, v2);
}

/* Pilha transporte -----------------------------*/
/*Verifica se a pilha esta vazia*/
bool Transporte::TranporteVazio(){
    return this->pilha_tranporte.vazia();
}

/*Desimpilha*/
Pacote* Transporte::GetPacote(){
    if(TranporteVazio()){
        //Se estive vazio retorna nulo
        return nullptr;
    }
    return this->pilha_tranporte.pop();
}

/*Empilha*/
bool Transporte::SetPacote(Pacote* pct){
    if(!pct->rota.definida){
        //Se o pacote não tem rota definida define
        this->calculaRota(pct);
    }

    //Se a pilha esta vazia reposiciona o topo
    if(this->n_pacotes == 0){
        this->pilha_tranporte.reset();
    }

    //Verifica se a pilha não está cheia
    if(this->n_pacotes < this->capacidade){
        //Se a pilha não está cheia insere pacote
        this->pilha_tranporte.push(pct);
        this->n_pacotes = n_pacotes + 1;
        //Retorna true
        return true;
    }

    //Se a pilha esta cheia retorna falso e o pacote não é inserido
    return false;
}

/* Pilha Auxiliar ---------------------------------*/
/*Verifica se a pilha esta vazia*/
bool Transporte::AuxiliarVazio(){
    return this->pilha_auxiliar.vazia();
}

/*Desempilha*/
Pacote* Transporte::GetPacoteAux(){
    if(AuxiliarVazio()){
        return nullptr;
    }
    return this->pilha_auxiliar.pop();
}

/*Empilha*/
void Transporte::SetPacoteAuxiliar(Pacote* pct){
    if(pct != nullptr){
        this->pilha_auxiliar.push(pct);
    }
}

/* Principal função do transporte */
/* Adicione pacotes da pilha transporte no armazem */
Pacote* Transporte::AcaoTransporte(Armazem *arm_atual){
    Pacote* pct;

    if(this->pilha_tranporte.vazia() && this->n_pacotes == 0){
        //Se a pilha estiver vazia retorna nulo
        return nullptr;
    }

    //Enquanto a pilha não estiver vazia
    while (this->n_pacotes > 0){
        //Desimpilha
        pct = GetPacote();
        
        if(pct == nullptr){ return nullptr;}

        int armazem = pct->rota.getArmazemAtual();
        int secao = pct->rota.getArmazemProx();

        //Se o armazem atual do pacote diferente do atual retorna nulo
        if(armazem != arm_atual->getId()){ return nullptr;  }

        //Avança o pacote para armazenar no próximo
        pct->rota.AvancaRota();

        //Verifica se chegou ao destino final
        if(arm_atual->getId() == secao){
            arm_atual->AdicionaPacote(pct);
            this->n_pacotes -=1 ;
            return pct;

        }else if(arm_atual->SecaoDefinida(secao)){
            //Caso não esteja no destino final adicione a sua respectiva seção se ela for definida
            arm_atual->AdicionaPacoteSecao(secao, pct);
            this->n_pacotes -=1 ;
            return pct;
        }
    }

    return nullptr;
}

/* ----------------------- GRAFO -------------------- */

/* Fila para auxiliar na Busca em Largura*/
struct Fila{
    int* dados;
    int inicio = 0;
    int fim = 0;
    int n_elementos = 0;
    int tamanho = 0;

    /*Construtor*/
    Fila(int n){
        tamanho = n;
        dados = new int[tamanho];
    }

    /*Destrutor*/
    ~Fila(){
        if(dados){ 
            delete[] dados;
            this->inicio = this->fim = 0; 
        }
    }

    /*Adiciona*/
    void enfileirar(int x){
        if(this->n_elementos < tamanho){
            dados[fim] = x;
            fim = (fim + 1) % tamanho;
            this->n_elementos++;
        }
    }

    /*Remove*/
    int desenfileirar() {
        if(this->n_elementos == 0){
            return -1;
        }
        int valor = dados[inicio];
        inicio = (inicio + 1) % tamanho;
        this->n_elementos--;
        return valor;
    }

    /*Verifica se esta vazia*/
    bool vazia() {
        if(this->n_elementos == 0){
            return true;
        }
        return false;
    }
};

/*Construtor*/
Grafo::Grafo(int tam){
    this->tamanho = tam;
    //Define matriz e inicializa com zero
    this->matrizAdjacencia = new int*[tam];
    for(int i = 0; i < tam; i++){
        this->matrizAdjacencia[i] = new int[tam]{};
    }
}

/*Destrutor*/
Grafo::~Grafo(){
    //Libera memória alocada
    for(int i = 0; i < tamanho; i++){
        delete this->matrizAdjacencia[i];
    }

    delete[]  this->matrizAdjacencia;
}

/*Adiciona Aresta*/
void Grafo::AddAresta(int v1, int v2){
    if(v1 >= 0 && v1 < tamanho && v2 >= 0 && v2 < tamanho){
        this->matrizAdjacencia[v1][v2] = 1;
    }
}



/*Busca e define a menor rota pacote entre os armazéns de origem e destino*/
// O tamanho da rota é retornado por referência
int* Grafo::BuscaLargura(int origem, int destino, int& tam_){   
    
    bool* visitado = new bool[this->tamanho];       //Vetor que marca se o indice foi visitado
    int* vertices_ant = new int[this->tamanho];     //Vetor que guarda o indice anterior ao atual  

    //Inicializa os vetores
    for (int i = 0; i < this->tamanho; i++){
        visitado[i] = false;
        vertices_ant[i] = -1;
    }

    Fila fila(this->tamanho);

    //Começa a partir da origem
    fila.enfileirar(origem);
    visitado[origem] = true;

    while (!fila.vazia()) {
        //Remove o próximo vértice da fila
        int atual = fila.desenfileirar();
        //Verifica se o valor é válido
        if (atual < 0 || atual >= this->tamanho) {
            continue;
        }
        
        //Se chegar ao destino
        if (atual == destino){
            int tamanho_caminho = 0;
            int v = destino;

            //Conta quantos armazéns tem a rota
            while (v != -1) {
                if (v < 0 || v >= this->tamanho) break; 
                tamanho_caminho++;
                v = vertices_ant[v];
            }

            //Cria o vetro para armazenar o caminho
            int* caminho = new int[tamanho_caminho];
            v = destino;

            //Preenche o caminho
            for (int i = tamanho_caminho - 1; i >= 0; i--) {
                caminho[i] = v;
                v = vertices_ant[v];
            }

            //Libera Memória
            delete[] visitado;
            delete[] vertices_ant;

            //Retorna o caminho e seu tamanho
            tam_ = tamanho_caminho;
            return caminho;
        }

        for (int i = 0; i < this->tamanho; i++) {
            //Se há aresta e viznho não foi visitado
            if (this->matrizAdjacencia[atual][i] == 1 && !visitado[i]) {
                visitado[i] = true;       
                vertices_ant[i] = atual;
                fila.enfileirar(i);
            }
        }
    }

    //libera memória
    delete[] visitado;
    delete[] vertices_ant;

    //Retorna caso a rota não seja encontrada
    tam_ = 0;
    return nullptr;

}