#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "manager.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //Verifica se o usuário passou algum valor
    if (argc < 2) {
        cout << "Nenhum arquivo foi adicionado\n";
        return 1;
    }

    //Abre o arquivo passado pelo usuario
    string caminhoArquivo = argv[1];    
    ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << caminhoArquivo << "\n";
        return 1;
    }

    ofstream csv("analise", ios::app);
    if (!csv.is_open()) {
        cout << "Erro ao abrir o arquivo CSV: " << "\n";
        return 1;
    }

    //Cria o gerenciador de eventos
    Manager manager;

    auto inicio_leitura = chrono::high_resolution_clock::now();
    string conclusao = ",,,";

    //Iniciliza
    string linha;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        
        int tempo;
        string tipo_linha;

        iss >> tempo >> tipo_linha;

        /*Entrada do tipo EVENTO*/
        if (tipo_linha == "EV") {
            string tipo_evento;
            iss >> tipo_evento;

            int id_pct;
            iss >> id_pct;

            if (tipo_evento == "RG") {
                /*EVENTO do tipo registro*/
                string remetente, destinatario;
                int arm_origem, arm_destino;
                iss >> remetente >> destinatario >> arm_origem >> arm_destino;

                Evento evt (tempo, tipo_evento, id_pct, arm_destino,arm_origem, remetente,destinatario);
                manager.AddEvento(evt);
            }
            else if (tipo_evento == "AR" || tipo_evento == "RM" || tipo_evento == "UR" || tipo_evento == "TR") {
                /*EVENTO do tipo armazenamento ou rearmazenamento ou removido seção ou transporte*/
                /* Esse tipos tem parametros parecidos então sao inseridos com o mesmo construtor
                    -preservando cada tipo
                */
                int arm_atual, arm_destino;
                iss >> arm_atual >> arm_destino;

                Evento evt (tempo, tipo_evento, id_pct, arm_destino, arm_atual);
                manager.AddEvento(evt);
            }

            else if (tipo_evento == "EN") {
                /*EVENTO do tipo entregue*/
                int arm_destino;
                iss >> arm_destino;

                Evento evt (tempo, tipo_evento, id_pct, arm_destino);
                manager.AddEvento(evt);
            }
        }else{
            /*Entrada do tipo CONSULTA*/
            std::ostringstream oss;
            oss <<  std::setw(6) << std::setfill('0') << tempo << " " << tipo_linha;
            std::ostringstream c;
            int quantd_eventos = 0;
            auto inicio_consulta = chrono::high_resolution_clock::now();
            if (tipo_linha == "CL") {
                /*Consulta do tipo cliente*/
                string nome_cliente;
                iss >> nome_cliente;
                
                cout << oss.str() << " " << nome_cliente << endl; //Imprime a chamada da consulta
                quantd_eventos = manager.ConsultaCliente(0,nome_cliente);
            }
            else if (tipo_linha == "PC") {
                /*Consulta do tipo Pacote*/
                int id_pacote;
                iss >> id_pacote;

                cout << oss.str() << " " << std::setw(3) << std::setfill('0') <<id_pacote << endl; //Imprime a chamada da consulta
                quantd_eventos = manager.ConsultaPacote(0,id_pacote);
            }

            auto fim_consulta = chrono::high_resolution_clock::now();
            auto tempo_consulta = chrono::duration_cast<chrono::milliseconds>(fim_consulta - inicio_consulta).count();
            c <<  tipo_linha << "," << tempo_consulta << "," << quantd_eventos;
            conclusao = c.str();
        }
    }
    auto fim_leitura = chrono::high_resolution_clock::now();
    auto tempo_leitura = chrono::duration_cast<chrono::milliseconds>(fim_leitura - inicio_leitura).count();

    // Escreve o cabeçalho se o CSV estiver vazio
    csv.seekp(0, ios::end);
    if (csv.tellp() == 0) {
        csv << "n_clientes,n_pacotes,n_eventos, tipo_consulta, tempo_cosulta, quant_eventos_consulta, tempo_total\n";
    }

    csv << manager.n_clientes << "," << manager.n_pcts << "," << manager.n_eventos << ","
        << conclusao << "," << tempo_leitura << "\n";

    csv.close();

    return 0;
}