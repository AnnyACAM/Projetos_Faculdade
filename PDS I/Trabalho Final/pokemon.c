#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCESSO 0
#define ERRO 1

// Indice dos jogadores
#define PLAYER1 0
#define PLAYER2 1

#define MAX 500 // Tamanho maximo da string
#define PLAYERS 2 // Quantidade de jogadores

/* ----------------- ESTRUTURA DE DADOS POKEMONS ---------------- */
typedef struct pokemon {
    char nome[MAX];
    float ataque;
    float defesa;
    float vida;
    char tipo[MAX];
} Pokemon;

/* ----------------- DECLARAÇÃO DE FUNÇÕES ---------------- */

/* Funçao que retorna a quantidade de sobreviventes no vetor de Pokemons do player */
int sobreviventes(Pokemon player[], int n);

/* Procedimento que imprime os nomes dos Pokemons sobreviventes e derrotados */
void statusPokemons(Pokemon p1[], Pokemon p2[], int tamanho[]); 

/* Funçao que retorna o bônus de ataque do Pokemon */
float bonusAtaque(char* tp_pokemon, char* tp_oponente);

/* Procedimento que simula a batalha entre os Pokemons calculando o dano ao oponente */
void Batalha(Pokemon *pokemon, Pokemon *oponente);

/* Procedimento que imprime todas as informacoes de todos os pokemons de ambos os jogadores*/
void imprime(Pokemon p1[], Pokemon p2[], int tamanho[]);

/*----------------------------------------------------------*/

int main() {

    /* ---------- LEITURA DE DADOS DO ARQUIVO -------------*/

    char name_file[MAX] = "input.txt";
    // Abre o arquivo apenas para leitura
    FILE* arquivo = fopen(name_file, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }

    int qntd_pokemon[PLAYERS], total = 0;

    // Le a primeira linha do arquivo e verifica se foram lidos 2 numeros
    if (fscanf(arquivo, "%d %d", &qntd_pokemon[PLAYER1], &qntd_pokemon[PLAYER2]) != 2) {
        printf("Erro ao ler do arquivo, os dados fornecidos nao seguem o padrao esperado\n");
        fclose(arquivo);
        return ERRO;
    }

    for (int i = 0; i < PLAYERS; i++) {
        // Verifica a quantidade de pokemons informados
        if (qntd_pokemon[i] > 100 || qntd_pokemon[i] <= 0) {
            printf("Numero invalido de pokemons para cadastro\n");
            return ERRO;
        }

        total += qntd_pokemon[i]; // Atualiza o total de pokemons esperados
    }

    /* -------------- ALOCAÇÃO DE MEMÓRIA --------------*/

    // Aloca vetor de pokemons para cada player
    Pokemon *player1 = malloc(qntd_pokemon[PLAYER1] * sizeof(Pokemon));
    Pokemon *player2 = malloc(qntd_pokemon[PLAYER2] * sizeof(Pokemon));

    if (player1 == NULL || player2 == NULL) {
        printf("Erro ao alocar memoria\n");
        return ERRO;
    }

    int adicionados = 0; // Quantidade de pokemons adicionados
    Pokemon *pokemon;  // Ponteiro para o pokemon atual

    // Loop para ler os dados de cada Pokemon do arquivo
    while (!feof(arquivo)) {
        
        if (adicionados < qntd_pokemon[PLAYER1]) {
            // Adiciona todos os pokemons do player 1
            pokemon = &player1[adicionados]; 
        } else if (adicionados - qntd_pokemon[PLAYER1] < qntd_pokemon[PLAYER2]) {
            // Adiciona pokemons do Player 2 apos todos do Player 1 terem sido adicionados
            pokemon = &player2[adicionados - qntd_pokemon[PLAYER1]];
        }

        // Le os dados do pokemon do arquivo
        int conteudo = fscanf(arquivo, "%s %f %f %f %s\n", pokemon->nome, &pokemon->ataque, &pokemon->defesa, &pokemon->vida, pokemon->tipo);
        //Verifica se os atributos nao sao negativos
        if(pokemon->ataque < 0 || pokemon->defesa < 0 || pokemon->vida < 0){
            printf("Os atributos do seu pokemon nao podem ser negativos\n");
            return ERRO;
        }

        // Verifica se a linha segue o padrao esperado
        if (conteudo != 5) {
            printf("Erro ao ler do arquivo, os dados fornecidos nao seguem o padrao esperado\n");
            return ERRO;
        }

        adicionados++; // Incrementa o contador de pokemons adicionados
    }

    // Verifica se a quantidade de pokemons cadastrados e igual a quantidade de pokemons informados no arquivo
    if (adicionados != total) {
        printf("Numero incorreto de pokemons informado\n");
        return ERRO;
    }

    //Imprime todos os dados
    imprime(player1, player2, qntd_pokemon);

    /* ------------- SIMULAÇÃO DE BATALHA --------------*/

    int player_turno = 0;
    int p1 = 0, p2 = 0; // Indices dos vetores de Pokemons do Players

    // Loop principal da batalha
    while (sobreviventes(player1, qntd_pokemon[PLAYER1]) > 0 && sobreviventes(player2, qntd_pokemon[PLAYER2]) > 0) {
        
        // Determina qual jogador esta atacando neste turno
        if (player_turno == PLAYER1) {
            Batalha(&player1[p1], &player2[p2]);

        } else if (player_turno == PLAYER2) {
            Batalha(&player2[p2], &player1[p1]);
        }

        // Verifica se um Pokemon foi derrotado
        if (player2[p2].vida <= 0) {
            printf("%s venceu %s\n", player1[p1].nome, player2[p2].nome);
            p2++; // Incrementa o Indice do Pokemon do Player 2 derrotado
        }
        
        if (player1[p1].vida <= 0) {
            printf("%s venceu %s\n", player2[p2].nome, player1[p1].nome);
            p1++; // Incrementa o Indice do Pokemon do Player 1 derrotado
        }

        // Alterna entre 0 e 1 para trocar o turno
        player_turno = 1 - player_turno; 
    }
    
    /* --------------- DEFINE VENCEDOR ---------------*/

    // Determina o vencedor com base nos Pokemon sobreviventes
    if (sobreviventes(player1, qntd_pokemon[PLAYER1]) > 0) {
        printf("\nJogador 1 venceu!\n");

    } else if (sobreviventes(player2, qntd_pokemon[PLAYER2]) > 0) {
        printf("\nJogador 2 venceu!\n");
    }

    // Mostra os pokemons sobreviventes e derrotados
    statusPokemons(player1, player2, qntd_pokemon);

    // Libera a memoria alocada
    free(player1);
    free(player2);

    // Fecha o arquivo
    fclose(arquivo);

    return SUCESSO;
}

/* --------------------   FUNÇÕES   ----------------------- */

int sobreviventes(Pokemon player[], int n) {
    int sobreviventes = 0;
    for (int i = 0; i < n; i++) {
        if (player[i].vida > 0) {
            sobreviventes++;
        }
    }
    return sobreviventes;
}

void statusPokemons(Pokemon p1[], Pokemon p2[], int tamanho[]) {
    
    for (int status = 0; status < 2; status++) {
        if (status == 0) {
            printf("\nPokemons sobreviventes:\n");
        }
        if (status == 1) {
            printf("\nPokemons derrotados:\n");
        }

        // Itera sobre os jogadores e seus respectivos Pokemons
        for (int i = 0; i < PLAYERS; i++) {
            for (int j = 0; j < tamanho[i]; j++) {
                // Verifica se o Pokemon esta vivo ou derrotado e imprime seu nome
                if (i == PLAYER1 && ((status == 0 && p1[j].vida > 0) || (status == 1 && p1[j].vida <= 0))) {
                    printf("%s\n", p1[j].nome);
                }
                if (i == PLAYER2 && ((status == 0 && p2[j].vida > 0) || (status == 1 && p2[j].vida <= 0))) {
                    printf("%s\n", p2[j].nome);
                }
            }
        }
    }
}

float bonusAtaque(char* tp_pokemon, char* tp_oponente) {

    // Iniciais dos tipos de Pokemon: e = eletrico, a = agua, f = fogo, g = gelo, p = pedra
    char tipos[5][3] = {
        {'e', 'a', 'p'},      // Coluna 0 = tipo do Pokemon
        {'a', 'f', 'e'},      // Coluna 1 = tipo do oponente (forte)
        {'f', 'g', 'a'},      // Coluna 2 = tipo do oponente (fraco)
        {'g', 'p', 'f'},
        {'p', 'e', 'g'}
    };
    
    char pokemon = tp_pokemon[0], oponente = tp_oponente[0];
    float fraco = 0.8, forte = 1.2, bonus = 1.0;

    // Verifica os tipos e aplica o bônus de ataque conforme a tabela
    for (int i = 0; i < 5; i++) {
        if (pokemon == tipos[i][0]) {
            if (oponente == tipos[i][1]) {
                bonus = forte;
            }
            if (oponente == tipos[i][2]) {
                bonus = fraco;
            }
        }
    }
    return bonus;
}

void Batalha(Pokemon *pokemon, Pokemon *oponente) {
    
    // Calcula o dano
    if (pokemon->vida > 0 && oponente->vida > 0) {
        
        float dano = (pokemon->ataque * bonusAtaque(pokemon->tipo, oponente->tipo)) - oponente->defesa;

        // Reduz a vida do oponente com base no dano calculado
        if (dano > 0) {
            oponente->vida -= dano;
        } else {
            oponente->vida -= 1; // Caso o dano seja negativo ou zero
        }
    }

    // Garante que a vida do oponente nao seja negativa
    if (oponente->vida < 0) {
        oponente->vida = 0;
    }

}

void imprime(Pokemon p1[], Pokemon p2[], int tamanho[]) {
    Pokemon* aux;

    for (int i = 0; i < PLAYERS; i++) {
        printf("JOGADOR %d  -  Quantidade Pokemons: %d\n", i + 1, tamanho[i]);
        printf("%-25s | %-5s | %-5s | %-5s | %-10s\n", "NOME", "DEFESA", "ATAQUE", "VIDA", "TIPO");
        printf("--------------------------------------------------------------\n");
        for (int j = 0; j < tamanho[i]; j++) {
            // Verifica se o Pokemon esta vivo ou derrotado e imprime seu nome
            if (i == PLAYER1) { aux = &p1[j];   }
            if (i == PLAYER2) { aux = &p2[j];   }
            printf("%-25s | %-5.1f  | %-5.1f  | %-5.1f | %-10s\n", aux->nome, aux->defesa, aux->ataque, aux->vida, aux->tipo);
        }
        printf("\n");
  }

}