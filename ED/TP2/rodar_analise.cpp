#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <cstdio>   
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

int main() {
    vector<int> numArmazens = {5, 100}; 
    vector<int> numPacotes = {10,50,100,250,400,500}; 

    ofstream csv("resultados_analise.csv", ios::app);

    for (auto armazens : numArmazens) {
        for (auto pacotes : numPacotes) {
            string arquivo = "entrada_" + to_string(armazens) + "_" + to_string(pacotes) + ".txt";

            string comando = "./genwkl " + to_string(armazens) + " " + to_string(pacotes) + " > " + arquivo;
            if (system(comando.c_str()) != 0) {
                return -1;
            }

            int capacidade = -1, custo_transp = -1, intervalo_transp = -1, remocao_custo = -1;
            ifstream entrada(arquivo);
            if (entrada.is_open()) {
                entrada >> capacidade >> custo_transp >> intervalo_transp >> remocao_custo;
                entrada.close();
            } else {
                continue;
            }

            string comandoSimulador = "./tp2.out " + arquivo;

            FILE* pipe = popen(comandoSimulador.c_str(), "r");
            if (!pipe) {
                continue;
            }

            char buffer[128];
            string resultado = "";
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                resultado += buffer;
            }
            pclose(pipe);

            double tempoExec = -1;
            size_t pos = resultado.find("Tempo de execução:");
            if (pos != string::npos) {
                size_t start = resultado.find(" ", pos + 18);
                size_t end = resultado.find("s", start);
                if (start != string::npos && end != string::npos) {
                    string tempoStr = resultado.substr(start + 1, end - start - 1);
                    tempoExec = stod(tempoStr);
                }
            }

            csv << armazens << "," << pacotes << ","
                << capacidade << "," 
                << intervalo_transp << "," 
                << tempoExec << "\n";
            csv.flush();
        }
    }

    csv.close();
    return 0;
}
