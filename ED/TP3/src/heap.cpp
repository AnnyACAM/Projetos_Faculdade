#include "heap.hpp"

/*Construtor*/
Heap::Heap(int n){
    this->tamanho = n;
    this->n_elementos = 0;
    this->data = new Evento*[n];
}

/*Destrutor*/
Heap::~Heap(){
    delete[] data;
}

/*Getters -------------------------------------*/
int Heap::GetAncestral(int posicao){
    if(posicao < 0 || posicao >= tamanho){
        return posicao;
    }
    return (posicao - 1)/2;
}

int Heap::GetSucessorEsq(int posicao){
    if(posicao < 0 || posicao >= tamanho || posicao >= tamanho - tamanho/2){
        return posicao;
    }
    return (2 * posicao) + 1;
}

int Heap::GetSucessorDir(int posicao){
    if(posicao < 0 || posicao >= tamanho || posicao >= tamanho - tamanho/2){
        return posicao;
    }
    return (2 * posicao) + 2;
}

/*Insere evento*/
void Heap::Inserir(Evento* x){
    if (n_elementos == tamanho) {
        //Se heap estiver cheio redimensiona
        redimensionaHeap();
    }
    //Insere e reordena
    data[n_elementos] = x;
    HeapifyPorCima(n_elementos);
    this->n_elementos += 1;
}

/*Remove o menor evento*/
Evento* Heap::Remover(){
    if (n_elementos < 0) {
        //Se o heap estive vazio retorna nulo
        return nullptr;
    }
    
    //Troca a raiz com uma folha
    Evento* raiz = data[0];
    data[0] = data[n_elementos - 1];
    data[n_elementos - 1] = nullptr;
    this->n_elementos -= 1;
    //Reordena
    HeapifyPorBaixo(0);

    return raiz;
}

/*Verifica se está vazio*/
bool Heap::Vazio(){
    if(n_elementos == 0){
        return true;
    }

    return false;
}

void swap(Evento **xp, Evento **yp){
    Evento* temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*Reestrutura o heap de forma top-down*/
void Heap::HeapifyPorBaixo(int posicao){
    int menor = posicao;
    int esq = GetSucessorEsq(posicao);
    int dir = GetSucessorDir(posicao);

    // Verifica se o sucessor a esquerda é menor que o atual
    if (esq < tamanho && data[esq] < data[menor])
        menor = esq;
    // Verifica se o sucessor a direita é menor que o atual
    if (dir < tamanho && data[dir] < data[menor])
        menor = dir;

    //Se o sucessor é menor que atual, troca e chama a função recursivamente
    if (menor != posicao) {
        swap(&data[posicao], &data[menor]);
        HeapifyPorBaixo(menor);
    }
}

/*Reestrutura o heap de forma bottom-up*/
void Heap::HeapifyPorCima(int posicao){
    //Enquanto não estiver na raiz e o valor for menor que do antecessor
    while (posicao != 0 && data[posicao] < data[GetAncestral(posicao)]) {
        //Troca os elementos e a posição
        swap(&data[posicao], &data[GetAncestral(posicao)]);
        posicao = GetAncestral(posicao);
    }
}

/*Dobra a capacidade do heap*/
void Heap::redimensionaHeap(){
    int novaCapacidade = this->tamanho * 2;
    Evento** novoHeap = new Evento*[novaCapacidade];

    //Copia os elementos
    for (int i = 0; i < tamanho; i++) {
        novoHeap[i] = data[i];
    }

    //libera memória
    delete[] data;

    //Atualiza ponteiro
    data = novoHeap;
    tamanho = novaCapacidade;  
}