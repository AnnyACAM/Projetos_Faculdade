#ifndef Manager_HPP
#define Manager_HPP

#include "armazem.hpp"
#include "escalonador.hpp"

class Manager{
    private:
        int latencia_transporte;
        int custo_remocao;
        int intervalo_transporte;
        int capacidade_transporte;
        int n_pacotes = 0;
        int n_armazens;
        int primeiro_transporte = 0;

        Armazem** array_armaz;
        Transporte* transporte;
        Escalonador* filaProridade;
        Pacote* pacotes;

    public:
        /*Construtor*/
        Manager();
        /*Destrutor*/
        ~Manager();

        /*Inicialização*/
        void setDados(int i, int value);
        void define();
        void definePacotes(int n_pcts);
        void inserePacote(int ind, Pacote pct);

        /*Getter*/
        Transporte* getTransporte();
        Armazem* getArmazem(int ind);
        int getNumeroArmazens();
        
        /*Gestão de Eventos*/
        int cicloTransporte(int tempo_atual);
        std::string ArmazemHanoi();
        Evento Tranporta(const Evento e,  Armazem* arm_atual);
        Evento processaEvento(const Evento* e);
        
};

#endif