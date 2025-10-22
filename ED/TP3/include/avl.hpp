#ifndef AVL_HPP
#define AVL_HPP

#include "list.hpp"
#include <iostream>

template <typename T_key, typename T>
class AVL{
    private:
        struct Node {
            T_key chave;
            T valor;
            Node* esquerda;
            Node* direita;
            int altura;

            Node(T_key ch_, T v_, Node* esq, Node* dir, int alt){
                chave = ch_;
                valor = v_;
                esquerda = esq;
                direita = dir;
                altura = alt;
            }
        };

        Node* raiz;

        int getAltura(Node* no);
        int getFatorBalanceamento(Node* no);
        void atualizaAltura(Node* no);

        Node* rotacaoDireita(Node* y);
        Node* rotacaoEsquerda(Node* x);
        Node* rotacaoEsquerdaDireita(Node* z);
        Node* rotacaoDireitaEsquerda(Node* z);

        Node* encontraMinimo(Node* no);
        Node* busca(Node* no, T_key chave);
        void deleteAVL(Node* no);
        Node* set(Node* no, T_key chave, T valor);
        Node* get(Node* no, T_key chave);
        void getDado(Node* no, List<T>& lista);
        void getDado(Node* no, List<T>& lista, T_key inicio, T_key fim);

    public:
        AVL();
        ~AVL();
        void Insere(T_key chave, T valor);
        void Remove(T_key chave);
        T BuscaChave(T_key chave);
        Node* BuscaNo(T_key chave);
        bool Vazia() const;
        void getInOrder(List<T>& lista);
        void getInOrder(List<T>& lista, T_key inicio, T_key fim);
};

template <typename T_key, typename T>
AVL<T_key, T>::AVL() {
    this->raiz = nullptr;
}

template <typename T_key, typename T>
AVL<T_key, T>::~AVL() {
    deleteAVL(this->raiz);
}

template <typename T_key, typename T>
int AVL<T_key, T>::getAltura(Node* no) {
    if (no == nullptr) return 0;

    return no->altura;
}

template <typename T_key, typename T>
int AVL<T_key, T>::getFatorBalanceamento(Node* no) {
    if (no == nullptr) return 0;

    return getAltura(no->direita) - getAltura(no->esquerda);
}

template <typename T_key, typename T>
void AVL<T_key, T>::atualizaAltura(Node* no) {
    if (no != nullptr){
        no->altura = 1 + std::max(getAltura(no->esquerda), getAltura(no->direita));
    }
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::rotacaoDireita(Node* no) {
    Node* left = no->esquerda;
    Node* right = left->direita;

    left->direita = no;
    no->esquerda = right;

    atualizaAltura(no);
    atualizaAltura(left);

    return left;
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::rotacaoEsquerda(Node* no) {
    Node* right = no->direita;
    Node* left = right->esquerda;

    right->esquerda = no;
    no->direita = left;

    atualizaAltura(no);
    atualizaAltura(right);

    return right;
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::rotacaoEsquerdaDireita(Node* no) {
    no->esquerda = rotacaoEsquerda(no->esquerda);
    return rotacaoDireita(no);
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::rotacaoDireitaEsquerda(Node* no) {
    no->direita = rotacaoDireita(no->direita);
    return rotacaoEsquerda(no);
}

template <typename T_key, typename T>
void AVL<T_key, T>::deleteAVL(Node* no) {
    if (no == nullptr) return;
    deleteAVL(no->esquerda);
    deleteAVL(no->direita);
    delete no;
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::set(Node* no, T_key chave, T valor) {
    if (no == nullptr) {
        Node* novoNode = new Node(chave, valor, nullptr, nullptr, 1);
        return novoNode;
    }

    if (chave < no->chave) {
        no->esquerda = set(no->esquerda, chave, valor);
    } else if (chave > no->chave) {
        no->direita = set(no->direita, chave, valor);
    } else {
        return no;
    }

    atualizaAltura(no);
    int balanceamento = getFatorBalanceamento(no);

    if (balanceamento < -1 && chave < no->esquerda->chave) return rotacaoDireita(no);
    if (balanceamento > 1 && chave > no->direita->chave) return rotacaoEsquerda(no);
    if (balanceamento < -1 && chave > no->esquerda->chave) return rotacaoEsquerdaDireita(no);
    if (balanceamento > 1 && chave < no->direita->chave) return rotacaoDireitaEsquerda(no);

    return no;
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::busca(Node* no, T_key chave) {
    if (no == nullptr) return nullptr;

    if (chave < no->chave) {
        return busca(no->esquerda, chave);
    } else if (chave > no->chave) {
        return busca(no->direita, chave);
    } else {
        return (no);
    }
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::encontraMinimo(Node* no){
    Node* atual = no;
    while (atual != nullptr && atual->esquerda != nullptr) {
        atual = atual->esquerda;
    }
    return atual;
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::get(Node* no, T_key chave){
    
    if (no == nullptr) return no;

    if (chave < no->chave) {
        no->esquerda = get(no->esquerda, chave);

    } else if (chave > no->chave) {
        no->direita = get(no->direita, chave);

    } else {
        if (no->esquerda == nullptr || no->direita == nullptr) {
            
            Node* temp = no->esquerda ? no->esquerda : no->direita;
            if (temp == nullptr) {
                temp = no;
                no = nullptr;
            } else {
                *no = *temp;
            }
            delete temp;
        } else {
            Node* temp = encontraMinimo(no->direita);
            no->chave = temp->chave;
            no->valor = temp->valor;
            no->direita = get(no->direita, temp->chave);
        }
    }

    if (no == nullptr) return no;

    atualizaAltura(no);
    int balanceamento = getFatorBalanceamento(no);

    if (balanceamento < -1) {
        if (getFatorBalanceamento(no->esquerda) <= 0) return rotacaoDireita(no);
        else return rotacaoEsquerdaDireita(no);
    }

    if (balanceamento > 1) {
        if (getFatorBalanceamento(no->direita) >= 0) return rotacaoEsquerda(no);
        else return rotacaoDireitaEsquerda(no);
    }

    return no;
}

template <typename T_key, typename T>
bool AVL<T_key, T>::Vazia() const {
    return this->raiz == nullptr;
}

template <typename T_key, typename T>
T AVL<T_key, T>::BuscaChave(T_key chave) {
    Node* no = busca(this->raiz, chave);
    if (no == nullptr) return nullptr; // Funciona apenas se T for ponteiro
    return no->valor;
}

template <typename T_key, typename T>
typename AVL<T_key, T>::Node* AVL<T_key, T>::BuscaNo(T_key chave) {
    
    Node* no = busca(this->raiz, chave);
    if (no == nullptr) return nullptr; 
    return no;
}

template <typename T_key, typename T>
void AVL<T_key, T>::Insere(T_key chave, T valor) {
    this->raiz = set(this->raiz, chave, valor);
}

template <typename T_key, typename T>
void AVL<T_key, T>::Remove(T_key chave) {
    this->raiz = get(this->raiz, chave);
}

template <typename T_key, typename T>
void AVL<T_key, T>::getInOrder(List<T>& lista) {
    getDado(this->raiz, lista); 
}

template <typename T_key, typename T>
void AVL<T_key, T>::getInOrder(List<T>& lista, T_key inicio, T_key fim) {    
    getDado(this->raiz,lista, inicio, fim);
}

template <typename T_key, typename T>
void AVL<T_key, T>::getDado(Node* no, List<T>& lista, T_key inicio, T_key fim){
    if (no == nullptr) return;

    if (no->chave >= inicio)
        getDado(no->esquerda, lista, inicio, fim);

    if (no->chave >= inicio && no->chave <= fim){
        //std::cout << no->valor;
        lista.Insere(no->valor);
    }

    if (no->chave <= fim)
        getDado(no->direita, lista, inicio, fim);
}

template <typename T_key, typename T>
void AVL<T_key, T>::getDado(Node* no, List<T>& lista) {
    if (no == nullptr) return;
    
    getDado(no->esquerda, lista);
    lista.Insere(no->valor);
    getDado(no->direita, lista);
}

#endif 
