#include "groups.hpp"
#include "heap.hpp"
#include "avl.hpp"

#define CLIENTE "CL"
#define PACOTE "PC"

#define MANAGER
#ifdef MANAGER

class Manager{
    private:
        AVL<int, Pacote*> pacotes;
        AVL<std::string, Cliente*> clientes;
        AVL<int, PacoteTempo*> pacote_tempo;
        Evento* eventos;
        int tam_eventos;

    public:
    int n_eventos = 0;
        int n_pcts = 0;
        int n_clientes = 0;
        Manager();
        void AddCliente(Cliente* cl);
        void AddPacote(Pacote* pct);
        void AddEvento(const Evento& e);
        void AlocaEvento(const Evento& e);
        void RedimensionaEvento();
        void PrintEventos(const List<PacoteTempo*>* eventos);
        int ConsultaCliente(int tempo, std::string id); 
        int ConsultaPacote(int tempo, int id); 
        int ID_PacoteTempo(int tempo, int id); 
        ~Manager();
};

#endif
