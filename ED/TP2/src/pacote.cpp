#include "pacote.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

/* ------------------- PACOTE ------------------------*/

/*Construtor*/
Pacote::Pacote(){}

/*Destrutor*/
Pacote::~Pacote() {
    this->rota.deleteRota();
}

/*Define Status e retorna o texto com a alteração*/
std::string Pacote::SetStatus(int s_, int tempo){
    std::ostringstream oss;
    std::ostringstream ini_oss;
    std::string texto = "";

    ini_oss <<  std::setw(7) << std::setfill('0') << tempo                      
        << " pacote " << std::setw(3) << std::setfill('0') << this->id_sist;
    
    texto += ini_oss.str();

    switch (s_){
    case NAO_POSTADO:
        this->status = NAO_POSTADO;
        break;
    
    case PRONTO_TRANSPORTE:
        this->status = PRONTO_TRANSPORTE;
        break;

    case ARMAZENADO:
        oss << " armazenado em " << std::setw(3) << std::setfill('0') << this->rota.getArmazemAtual() 
            << " na secao " << std::setw(3) << std::setfill('0') << this->rota.getArmazemProx()      
            << "\n";
        
        texto += oss.str();
        this->status = ARMAZENADO;
        break;

    case REARMAZENADO:
        oss << " rearmazenado em " << std::setw(3) << std::setfill('0') << this->rota.getArmazemAtual() 
            << " na secao " << std::setw(3) << std::setfill('0') << this->rota.getArmazemProx()      
            << "\n";
        
        texto += oss.str();
        this->status = ARMAZENADO;
        break;

    case EM_TRANSITO:
        //Incrementa e desincrementa o atual pois o transporte é feito antes de mudar o status
        if(rota.atual == 0){
            break;
        }
        rota.atual -= 1;
        oss << " em transito de " << std::setw(3) << std::setfill('0') << this->rota.getArmazemAtual()  
            << " para " << std::setw(3) << std::setfill('0') << this->rota.getArmazemProx()      
            << "\n";
        
        texto += oss.str();
        rota.atual += 1;
        this->status = EM_TRANSITO;
        break;

    case REMOVIDO:
        oss << " removido de " << std::setw(3) << std::setfill('0') << this->rota.getArmazemAtual() 
            << " na secao " << std::setw(3) << std::setfill('0') << this->rota.getArmazemProx()      
            << "\n";
        
        texto += oss.str();
        this->status = PRONTO_TRANSPORTE;
        break;
    
    case ENTREGUE:
        oss << " entregue em " << std::setw(3) << std::setfill('0') << this->rota.getArmazemAtual()  
            << "\n";
        
        texto += oss.str();
        this->status = ENTREGUE;
        break;
    
    default:
        break;
    }

    /*if(this->status == EM_TRANSITO || this->status == PRONTO_TRANSPORTE){*/
        return texto;
    /*}
    return "";*/
}

/*Getter*/
int Pacote::getId()     {   return this->id_pct;  }
int Pacote::getTempo()  {   return this->tempo;   }
int Pacote::getOrigem() {   return this->origem;  }
int Pacote::getDestino(){   return this->destino; }

/*Define dados a partir da leitura do arquivo*/
void Pacote::defineDados(int i, int valor){
    switch (i){
        case 0:
            this->tempo = valor;
            break;

        case 2:
            this->id_pct = valor;
            break;

        case 4:
            this->origem = valor;
            break;

        case 6:
            this->destino= valor;
            break;
    
        default:
            break;
    }
}



/* ------------------- PILHA DE PACOTES ------------------------*/

/*Construtor*/
Pilha::Pilha(){}

/*Destrutor*/
Pilha::~Pilha(){
    //Se a pilha não for nula deleta
    if(pilha){
        deletePilha();
    }
}

/*Aloca pilha*/
void Pilha::ConstroiPilha(int tamanho){
    this->topo = -1;
    this->tamanho = tamanho;
    this->pilha = new Pacote*[tamanho];
}

/*Empilha pacote*/
void Pilha::push(Pacote* item){
    if(item != nullptr && topo < tamanho -1){
        this->topo += 1;
        this->pilha[topo] = item;
    }
} 

/*Desempilha pacote*/
Pacote* Pilha::pop(){
    if(topo >= 0){
        this->topo -= 1;
        return this->pilha[topo + 1];
    }
    this->topo -= 1;
    return nullptr;
}

/*Verifica se a pilha esta vazia*/
bool Pilha::vazia(){
    if(topo < 0){
        return true;
    }
    
    return false;
}

/*Libera memória pilha*/
void Pilha::deletePilha(){
    delete[] pilha;
}

/*Define a pilha como uma secao*/
void Pilha::defineSecao(int k_secao){
    this->k_secao = k_secao;
    this->secao = true;
}

/*Reinicia o topo da pilha*/
void Pilha::reset(){
    if(vazia()){
        this->topo = -1;
    }
}

/* Retorna a quantidade de pacotes que podem ser removidos em uma seçaõ*/
int Pilha::removiveis() {
    int count = 0;
    //Verifica todos os pacotes
    for (int i = 0; i <= topo; i++) {
        //Adiciona ao contador se o pacote não for nulo, não for entregue e estiver na secao certa
        if (pilha[i] != nullptr && pilha[i]->status != ENTREGUE &&
            pilha[i]->rota.getArmazemAtual() != pilha[i]->rota.getArmazemProx()) {
            count++;
            if(secao && pilha[i]->rota.getArmazemProx() != k_secao){
                count--;
            }
        }
    }
    return count;
}










