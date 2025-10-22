#ifndef LIST
#define LIST
#include <iostream>
template <typename T>
struct No {
    T data;
    No<T>* prox;

    No(T new_data){
        data = new_data;
        prox = nullptr;
    }

};

template <typename T>
class List{
    private:  
        No<T>* head;
        No<T>* foot;
        int tam;

    public:
        List();
        void Insere(T data);
        No<T>* GetHead();
        No<T>* GetFoot();
        const No<T>* GetHead() const;
        const No<T>* GetFoot() const;
        int GetTamanho();
        const int GetTamanho() const;
        void deleteList();
        void reset();
        ~List();
   
};

template <typename T>
List<T>::List(){
    this->tam = 0;
    this->head = nullptr;
    this->foot = nullptr;
}

template <typename T>
void List<T>::reset(){
    this->tam = 0;
    this->head = nullptr;
    this->foot = nullptr;
}

template <typename T>
void List<T>::Insere(T data){
    No<T>* novo_no = new No<T>(data);

    if (this->head == nullptr) {
        // Lista vazia
        this->head = this->foot = novo_no;
    } else {
        //Adicionar no fim
        this->foot->prox = novo_no;
        this->foot = novo_no;
    }

    this->tam++;
}

template <typename T>
No<T>* List<T>::GetHead(){
    return this->head;
}

template <typename T>
const No<T>* List<T>::GetHead() const {
    return this->head;
}

template <typename T>
No<T>* List<T>::GetFoot(){
    return this->foot;
}

template <typename T>
const No<T>* List<T>::GetFoot() const {
    return this->foot;
}

template <typename T>
int List<T>::GetTamanho() {
    return this->tam;
}

template <typename T>
const int List<T>::GetTamanho() const {
    return this->tam;
}

template <typename T>
void List<T>::deleteList() {
    while (this->head != nullptr) {
        No<T>* aux = this->head->prox;
        delete this->head;
        this->head = aux;
    }

    this->head = nullptr;
    this->foot = nullptr;
    this->tam = 0;
}

template <typename T>
List<T>::~List(){
    if(this->tam > 0){
        deleteList();
    }
}

#endif
