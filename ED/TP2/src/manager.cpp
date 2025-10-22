#include "manager.hpp"
#include <iostream>
#include <sstream>

/*Construtor*/
Manager::Manager(){}


/*Destrutor*/
Manager::~Manager(){
    delete[] array_armaz;
    delete[] pacotes;
    delete transporte;
    delete filaProridade;
}

/* INICIALIZAÇÃO --------------------------------------------------*/
/*Pega dados a partir da leitura do aquivo*/
void Manager::setDados(int i, int value){
    switch (i){
    case 0:
        this->capacidade_transporte = value;
        break;
    case 1:
        this->latencia_transporte= value;
        break;
    case 2:
        this->intervalo_transporte = value;
        break;
    case 3:
        this->custo_remocao = value;
        break;
    case 4:
        this->n_armazens = value;
        break;
    
    default:
        break;
    }
}

/*Define dados*/
void Manager::define(){
    this->transporte = new Transporte(this->capacidade_transporte, this->n_armazens);
    this->filaProridade = new Escalonador(this->n_armazens);

    this->array_armaz = new Armazem*[this->n_armazens];
    for(int i = 0; i < this->n_armazens; i++){
        this->array_armaz[i] = new Armazem(i,this->n_armazens);
    }
}

/*Define a quantidade de Pacotes*/
void Manager::definePacotes(int n_pcts){
    this->n_pacotes = n_pcts;
    this->pacotes = new Pacote[n_pcts];
}

/*Insere os eventos pacotes*/
void Manager::inserePacote(int ind, Pacote pct){
    if(ind >= 0 || ind < n_pacotes){
        this->pacotes[ind] = pct;
    }

    this->pacotes[ind].id_sist = ind;
    this->pacotes[ind].status = PRONTO_TRANSPORTE;
    this->filaProridade->inserirEvento(EVENTO_PACT, this->pacotes[ind].getTempo(), &this->pacotes[ind]);
}

/* GETTERS ----------------------------------------*/
/*Retorna transporte*/
Transporte* Manager::getTransporte(){
    return this->transporte;
}

/*Retona o de acordo com o indice armazem*/
Armazem* Manager::getArmazem(int ind){
    if(ind < 0 || ind > n_armazens){
        return nullptr;
    }

    return this->array_armaz[ind];
}

/*Retorna número de Armazéns*/
int Manager::getNumeroArmazens(){
    return this->n_armazens;
}

/* GESTÃO EVENTOS ----------------------------*/
/*Retorna o tempo do próximo transporte*/
int Manager::cicloTransporte(int tempo_atual) {

    if(primeiro_transporte == 0){
        //Se o tempo do primerio transporte não estiver definifido
        primeiro_transporte = tempo_atual;
    }

    //Quantidade de transportes ocorridos até o tempo atual
    int quant_transportes = tempo_atual / intervalo_transporte;
    
    return primeiro_transporte + (intervalo_transporte*(quant_transportes - 1));
}

/*Move o pacote do armazém atual ao próximo da rota*/
Evento Manager::Tranporta(const Evento e, Armazem* arm_atual){
    // Se o armazém atual for nulo, retorna um evento inválido
    if(arm_atual == nullptr){
        return Evento(0, -1, nullptr);
    }

    //Obtém o próximo pacote a ser transportado
    Pacote* aux = this->transporte->AcaoTransporte(arm_atual);
    
    if(aux != nullptr){
        // Caso o pacote já esteja no último armazém do caminho
        if(aux->rota.getArmazemAtual() == aux->rota.getArmazemProx()){
            //Mostra Status do pacote                             
            std::cout << aux->SetStatus(EM_TRANSITO, e.tempo); 

            //Agenda evento de entrega
            int tempo = e.tempo + latencia_transporte;
            aux->status = ENTREGUE;
            Evento entrega = Evento(EVENTO_TRANSP, tempo, aux);
            entrega.tipo = EVENTO_PACT;
            return entrega;
        }

        //Mostra status
        std::cout << aux->SetStatus(EM_TRANSITO, e.tempo);

        //Agenda novo evento de armazenamento
        aux->status = PRONTO_TRANSPORTE;
        int tempo = e.tempo + latencia_transporte;
        return Evento(EVENTO_PACT,tempo, aux);

    }
    
    return Evento(0, -1, nullptr);
}
/*



*/

/*Executa o loop de eventos até que todos os pacotes sejam entregues.*/
std::string Manager::ArmazemHanoi(){
    int pct_entregues = 0; //Contador de pacotes entregues

    //Enquantos todos os pacotes não forem entregues
    while (pct_entregues < this->n_pacotes) {
        
        if(filaProridade->vazio()){
            // Se a fila de eventos estiver vazia para o loop
            std::ostringstream oss;
            oss << n_armazens << "," << n_pacotes << "," << capacidade_transporte << "," << intervalo_transporte << ",";
            return oss.str();

        }

        //Retira o menor evento, realiza o e gera um novo evento
        Evento e = processaEvento(this->filaProridade->retiraMenorEvento());
        
        /*-----------------------------------------*/

        //Se o pacote foi entregue incrementa o contador e continua o loop
        if(e.tipo == ENTREGUE){
            pct_entregues++;
            continue;
        }

        // Ignora eventos inválidos 
        if(e.pacote == nullptr || e.id == 0){    continue;}

        /*-----------------------------------------*/
        //Caso o evento seja de transporte e seu pacote esteja pronto para transporte
        if(e.tipo == EVENTO_TRANSP && e.pacote->status == PRONTO_TRANSPORTE){
            
            //Armazens do pacote
            int armAtual = e.pacote->rota.getArmazemAtual();
            int armProx = e.pacote->rota.getArmazemProx();

            //Ultimo tempo que foi transportado
            int ult_tempo = 0;
            
            //Enquanto houver pacotes para serem tranportados
            while (!this->transporte->TranporteVazio()){
                ult_tempo = e.tempo;

                //Realiza o transporte
                Evento e_transp = Tranporta(e, this->array_armaz[armAtual]);
                if(e_transp.pacote != nullptr && e.tipo > 0){
                    //Se for válido adiciona o proximo evento na fila de prioridade
                    this->filaProridade->inserirEvento(EVENTO_PACT, e_transp.tempo, e_transp.pacote);
                }
            }

            //Se o houve transporte 
            if(ult_tempo > 0){
                //Enquanto houver pacotes na pilha auxiliar
                while (!this->transporte->AuxiliarVazio()){
                Pacote* aux = this->transporte->GetPacoteAux(); //Retira pacote
                    if(aux != nullptr){
                        //Se o armazem do pacote retirado for igual ao do pacote transportado anteriormente
                        if(aux->rota.getArmazemAtual() == armAtual  && aux->rota.getArmazemProx() == armProx){
                            //Rearmazena o pacote
                            std::cout << aux->SetStatus(REARMAZENADO, ult_tempo);
                            array_armaz[armAtual]->AdicionaPacoteSecao(armProx, aux);
                            aux->status = NAO_POSTADO;

                            //Agenda um novo evento para o pacote rearmazenado
                            //Evento este que vai tornar o paocte rearmazenado apto para transporte
                            this->filaProridade->inserirEvento(EVENTO_PACT, ult_tempo, aux);
                        }
                    }
                }
            }
                
        }else if(e.tipo == EVENTO_PACT || e.tipo == EVENTO_TRANSP){
            // Reagenda o evento se seu pacote não tiver sido entregue ou estiver em trânsito
            if(e.pacote->status != ENTREGUE && e.pacote->status != EM_TRANSITO){
                this->filaProridade->inserirEvento(e.tipo, e.tempo, e.pacote);
            }
        }
        
    }
}


Evento Manager::processaEvento(const Evento* e){
    //Ignora eventos sem pacote
    if(e->pacote == nullptr){
        return Evento(0, 0, nullptr);
    }

    //Se a rota do pacote não estiver definida, define
    if(!e->pacote->rota.definida){
        this->transporte->calculaRota(e->pacote);
    }


    //Armazéme seção atual do pacote
    int armAtual = e->pacote->rota.getArmazemAtual();
    int secAtual = e->pacote->rota.getArmazemProx();

    //Se o evento for do tipo pacote
    if(e->tipo == EVENTO_PACT){
        
        if(armAtual == secAtual && e->pacote->status == ENTREGUE){
            /* Evento entrega --------------------------------*/
            //Se o pacote esteja no destino final
            std::cout << e->pacote->SetStatus(ENTREGUE,e->tempo);
            array_armaz[armAtual]->AdicionaPacote(e->pacote);
            return Evento(ENTREGUE, 0, nullptr);

            
        }else if(e->pacote->status == NAO_POSTADO){
            /* Evento após rearmazenar ------------------*/
            //Torna o pacote apto a ser transportado
            int temp = cicloTransporte(e->tempo + custo_remocao + intervalo_transporte);
            e->pacote->status = ARMAZENADO;
            return Evento(EVENTO_TRANSP, temp, e->pacote);

        }else if(e->pacote->status == PRONTO_TRANSPORTE){
            /* Evento após rearmazenar ------------------*/
            //Armazena pacote
            std::cout << e->pacote->SetStatus(ARMAZENADO, e->tempo);
            array_armaz[armAtual]->AdicionaPacoteSecao(secAtual, e->pacote);
            int tempo =  cicloTransporte(e->tempo + custo_remocao + intervalo_transporte);
            
            return Evento(EVENTO_TRANSP, tempo, e->pacote);
        }

    /* EVENTO DE TRANSPORTE ---------------*/
    }else if(e->tipo == EVENTO_TRANSP){

        /*REMOÇÃO DE PACOTES DA PILHA DE SEÇÃO*/
        //Se o pacote está armazenado
        if(e->pacote->status == ARMAZENADO){

            if(this->array_armaz[armAtual]->getSecao(secAtual) == nullptr || this->array_armaz[armAtual]->SecaoVazia(secAtual)){
                return Evento(0, 0, nullptr);
            }

            int ult_tempo = 0;          //Ultimo tempo de remoção
            Pacote *atual = nullptr;    //Ultimo pacote removido

            int capacidade = this->capacidade_transporte;

            //Quantidade de elementos na pilha aptos de serem removidos
            int elementos_pilha = this->array_armaz[armAtual]->getSecao(secAtual)->removiveis();
            //Remocoes até que alcance a capacidade
            int remocoes_capacidade = elementos_pilha;
            //Quantidade de elementos removidos
            int removidos = 0;                 
            
            /*Enquanto a pilha não estiver vazia*/
            while (!this->array_armaz[armAtual]->SecaoVazia(secAtual)){
                if(removidos == elementos_pilha || this->array_armaz[armAtual]->getId() != armAtual){
                    break;
                }

                // Retira pacote da pilha
                Pacote* pct = this->array_armaz[armAtual]->getSecao(secAtual)->pop();

                // Pula pacotes inválidos ou já no destino final
                if(pct == nullptr || pct->rota.getArmazemAtual() == pct->rota.getArmazemProx()){
                    remocoes_capacidade--;
                    continue;
                }

                // Pula pacotes que não estejam armazenados
                if (pct->status != ARMAZENADO) continue;

                //Atualiza tempo de remoção e atualiza status
                ult_tempo = e->tempo + (removidos) *custo_remocao;
                std::cout << pct->SetStatus(REMOVIDO, ult_tempo);

                //Tenta colocar na pilha de transporte; se não conseguir, coloca como auxiliar
                if(remocoes_capacidade <= capacidade){
                    removidos++;
                    
                    if(!this->transporte->SetPacote(pct)){
                        break;
                    }
                }else{
                    this->transporte->SetPacoteAuxiliar(pct);
                    remocoes_capacidade--;
                    removidos++;
                }

                atual = pct; // Atualiza o último pacote removido
            }
            //Agenda evento de transporte para os pacotes removidos
            return Evento(EVENTO_TRANSP, ult_tempo, atual);
        }
            
    }
    return Evento(0, 0, nullptr);
}

