#include <sstream>
#include <iostream>
#include "groups.hpp"

Pacote::Pacote(int id, int arm_o, int arm_d, Cliente* remet, Cliente* dest){
    this->id_pct = id;
    this->arm_origem = arm_o;
    this->arm_destino = arm_d;
    this->remetente = remet;
    this->destinatario = dest;
}

int Pacote::GetID(){
    return this->id_pct;
}

const List<Evento*>& Pacote::GetEvento(int i){
    return this->eventos[i];
}

Evento* Pacote::GetEventoInicio(){
    const No<Evento*>* no = this->eventos[0].GetFoot();
    return no->data;
}

Evento* Pacote::GetEventoFim(){
    const No<Evento*>* no = this->eventos[1].GetFoot();
    return no->data;
}

void Pacote::SetEvento(Evento* e){
    
    if(this->eventos[0].GetHead() == nullptr && this->eventos[1].GetHead() == nullptr){
        this->eventos[0].Insere(e);

    }else if(this->eventos[1].GetFoot() != nullptr){

        if(this->eventos[1].GetFoot()->data->tempo < e->tempo){
            this->eventos[1].reset();
            this->eventos[1].Insere(e);
        }else if(this->eventos[1].GetFoot()->data->tempo == e->tempo){
            this->eventos[1].Insere(e);
        }

    }else if(this->eventos[1].GetFoot() == nullptr){
        this->eventos[1].Insere(e);
    }
}


Pacote::~Pacote(){
    
}


Cliente::Cliente(std::string nome){
    this->nome = nome;
}

void Cliente::SetPacote(Pacote* pct){
    this->pacotes.Insere(pct);
}

std::ostream& operator<<(std::ostream& os, const PacoteTempo& pt) {
    os << "ID: " << pt.id << " | Tempo: " << pt.tempo;

    if (pt.e != nullptr) {
        os << " | Evento: " << pt.e->print();
    } else {
        os << " | Evento: [null]";
    }

    return os;
}

void Cliente::GetPacotes(List<PacoteTempo*>& eventos){
    AVL<int, PacoteTempo*> avl_eventos;
    No<Pacote*>* aux_pct = this->pacotes.GetHead();

    while (aux_pct != nullptr) {
        Evento* ini_eventos = aux_pct->data->GetEventoInicio(); 
        Evento* fim_eventos = aux_pct->data->GetEventoFim(); 

        PacoteTempo* pct_tempo_i = new PacoteTempo(ini_eventos->tempo, ini_eventos->id_pct, ini_eventos);
        avl_eventos.Insere(pct_tempo_i->tempo, pct_tempo_i);

        PacoteTempo* pct_tempo_f = new PacoteTempo(fim_eventos->tempo, fim_eventos->id_pct, fim_eventos);
        avl_eventos.Insere(pct_tempo_f->tempo, pct_tempo_f);        

        aux_pct = aux_pct->prox;      
    }
 
    avl_eventos.getInOrder(eventos);
}

std::string Cliente::GetNome(){
    return this->nome;
}

Cliente::~Cliente(){
    this->pacotes.deleteList();
}
