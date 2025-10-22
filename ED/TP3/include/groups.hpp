#include <string>
#include <sstream>
#include <iomanip>
#include "avl.hpp"
#include "list.hpp"

#define RG 1   //Pct ainda não foi postado 
#define AR 2   //Pct foi armazenado
#define RM 3   //Pct foi removido da seção
#define UR 4   //Pct foi rearmazenado
#define TR 5   //Pct em transporte
#define EN 6   //Pct entregue

#ifndef GROUPS
#define GROUPS

class Pacote;
class Cliente;

struct Evento{
    
    int tempo;
    std::string tipo_c;
    int tipo;
    int id_pct;
    std::string clientes[2];

    int arm_destino;
    int arm_origem;
    int secao;
    
    Evento(){}

    Evento(int temp_, std::string tipo_, int id, int arm_d)
        : tempo(temp_), tipo_c(tipo_), tipo(str_tipo(tipo_c)), id_pct(id), arm_destino(arm_d), arm_origem(-1), secao(-1) {}

    Evento(int temp_, std::string tipo_, int id, int arm_d, int arm_o)
        : Evento(temp_, tipo_, id, arm_d) // chama o outro construtor
    {
        arm_origem = arm_o;
        if (tipo == AR || tipo == RM || tipo == UR) {
            secao = arm_o;
        }
    }

    Evento(int temp_, std::string tipo_, int id, int arm_d, int arm_o, std::string remet,std::string dest)
        : Evento(temp_, tipo_, id, arm_d, arm_o) // chama o construtor acima
    {
        clientes[0] = remet;
        clientes[1] = dest;
    }

    std::string print(){
        std::string texto;

        std::ostringstream oss_p;
        std::ostringstream oss;

        oss_p <<  std::setw(7) << std::setfill('0') << tempo << " " 
            << "EV " << tipo_c << " " 
            << std::setw(3) << std::setfill('0') << id_pct << " ";

        texto += oss_p.str();

        if(tipo == RG){
            oss << clientes[0] << " " << clientes[1] << " " 
                << std::setw(3) << std::setfill('0') << arm_origem << " " 
                << std::setw(3) << std::setfill('0') << arm_destino << std::endl;
        
        }else if(tipo == AR || tipo == RM || tipo == UR){
            oss << std::setw(3) << std::setfill('0') << secao << " " 
                << std::setw(3) << std::setfill('0') << arm_destino << std::endl;
        
        }else if(tipo == TR){
            oss << std::setw(3) << std::setfill('0') << arm_origem << " " 
                << std::setw(3) << std::setfill('0') << arm_destino << std::endl;
        
        }else if(tipo == EN){
            oss << std::setw(3) << std::setfill('0') << arm_destino << std::endl;
        }
        
        texto += oss.str();
        return texto;
    }

    int str_tipo(std::string str_t){
        if(str_t == "RG"){   return RG;  }
        if(str_t == "AR"){   return AR;  }
        if(str_t == "RM"){   return RM;  }
        if(str_t == "UR"){   return UR;  }
        if(str_t == "TR"){   return TR;  }
        if(str_t == "EN"){   return EN;  }

        return -1;
    }

};

struct PacoteTempo{
    Evento* e;
    int id;
    int tempo;

    PacoteTempo(int tempo_, int id_pct, Evento*e_): e(e_){
        tempo = tempo_ * 100000 + id_pct;
        id = id_pct * 10000000 + tempo_*10 + e_->tipo;
    }

    PacoteTempo(): e(nullptr), id(-1) {}
    friend std::ostream& operator<<(std::ostream& os, const PacoteTempo& pt);


    ~PacoteTempo(){
        std::cout << "estoa apagando" << e->print();
    };
    
};

class Pacote{
    private:
        int id_pct;
        int arm_origem;
        int arm_destino;
        Cliente* remetente;
        Cliente* destinatario;
        List<Evento*> eventos[2];

    public:
        Pacote(int id, int arm_o, int arm_d, Cliente* remet, Cliente* dest);
        int GetID();
        const List<Evento*>& GetEvento(int i);
        Evento* GetEventoInicio();
        Evento* GetEventoFim();
        void SetEvento(Evento* e);
        std::string GetDados();
        ~Pacote();
};

class Cliente{
    private:
       std::string nome;
       List<Pacote*> pacotes;
    public:

        Cliente(std::string nome);
        void SetPacote(Pacote* pct);
        void GetPacotes(List<PacoteTempo*>& eventos);
        std::string GetNome();
        ~Cliente();
};

#endif