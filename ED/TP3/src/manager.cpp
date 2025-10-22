#include "manager.hpp"
#include <iostream>

Manager::Manager(){
    this->tam_eventos = 200;
    this->eventos = new Evento[tam_eventos];
}

void Manager::AddCliente(Cliente* cl){
    if(this->clientes.BuscaChave(cl->GetNome()) == nullptr){
        this->clientes.Insere(cl->GetNome(), cl);
        this->n_clientes++;
    }
}

void Manager::AddPacote(Pacote* pct){
    if(this->pacotes.BuscaChave(pct->GetID()) == nullptr){
        this->pacotes.Insere(pct->GetID(), pct);
        this->n_pcts++;
    }
}

void Manager::AddEvento(const Evento& e){
    if(e.tipo == RG){
        for(int i = 0; i < 2; i++){
            if(this->clientes.BuscaChave(e.clientes[i]) == nullptr){
                this->AddCliente(new Cliente(e.clientes[i]));
            }
        }
        
        Cliente* remet = this->clientes.BuscaChave(e.clientes[0]);
        Cliente* dest = this->clientes.BuscaChave(e.clientes[1]);

        this->pacotes.Insere(e.id_pct, new Pacote(e.id_pct,e.arm_origem, e.arm_destino,remet, dest));
        remet->SetPacote(this->pacotes.BuscaChave(e.id_pct));
        dest->SetPacote(this->pacotes.BuscaChave(e.id_pct));
        
    }

    Pacote* pct = this->pacotes.BuscaChave(e.id_pct);
    if(pct != nullptr){
        this->eventos[this->n_eventos] = e;

        pct->SetEvento(&this->eventos[this->n_eventos]);
        
        Evento* evt = &this->eventos[this->n_eventos];
        PacoteTempo* pct_t = new PacoteTempo(e.tempo, pct->GetID(), evt);
        this->pacote_tempo.Insere(pct_t->id, pct_t);
        
        this->n_eventos++;
    }
}

void Manager::PrintEventos(const List<PacoteTempo*>* eventos){        
    if(eventos->GetHead() == nullptr) return;
    
    std::cout << eventos->GetTamanho() << std::endl;

    const No<PacoteTempo*>* aux_evt = eventos->GetHead();
    while(aux_evt != nullptr){
        std::cout << aux_evt->data->e->print();
        aux_evt = aux_evt->prox;
    }
}

int Manager::ConsultaCliente(int tempo, std::string id){   
    Cliente* cl = this->clientes.BuscaChave(id);
    List<PacoteTempo*> pct_tempo;

    if(cl != nullptr){
        cl->GetPacotes(pct_tempo);
        return pct_tempo.GetTamanho();
    }else{
        std::cout << 0 << std::endl;
    }
    return 0;
} 

int Manager::ID_PacoteTempo(int tempo, int id){
    return id * 10000000 + tempo*10;
}

int Manager::ConsultaPacote(int tempo, int id){
    int tolerancia = EN;
    Pacote* pct = this->pacotes.BuscaChave(id);
    List<PacoteTempo*> pct_tempo;

    if(pct != nullptr){
        int inicio = ID_PacoteTempo(pct->GetEventoInicio()->tempo, pct->GetID());
        int fim = ID_PacoteTempo(pct->GetEventoFim()->tempo, pct->GetID()) + tolerancia;

        this->pacote_tempo.getInOrder(pct_tempo,inicio, fim);
        return pct_tempo.GetTamanho();
    }

    return 0;
} 


Manager::~Manager(){
    delete[] eventos;
}
