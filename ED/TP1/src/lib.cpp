#include "lib.hpp"
#include <cmath>
#include <iostream>

// instanciar explicitamente para int
template void swap <int> (int *xp, int *yp, Estatistica *est);
template void insertionSort <int> (int *v, int l, int r, Estatistica* est);
template void partition3 <int> (int * A, int l, int r, int *i, int *j, Estatistica *est);
template int mediana <int> (int a, int b, int c);
template void quickSort <int> (int * A, int l, int r, int limiar, Estatistica *est);


template <typename T>
//Troca elementos
void swap(T *xp, T *yp, Estatistica *est){
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
    est->addmove(3);
}

template <typename T>
//Algoritmo de ordernação de inserção
void insertionSort(T *v, int l, int r, Estatistica* est){
    int j;
    T aux;
    
    est->addcalls(1);
      for (int i = l+1; i <= r; i++) {
        est->addmove(1);
        aux = v[i];
        j = i - 1;

        est->addcmp(1);
        while (( j >= l ) && (aux < v[j])) {
            est->addcmp(1);
            v[j + 1] = v[j]; 
            est->addmove(1);
            j--;
        }
        v[j + 1] = aux;
        est->addmove(1);
      }

}


template <typename T>
//Calcula a mediana
T mediana (T a, T b, T c) {
    if ((a <= b) && (b <= c)) return b;  
    if ((a <= c) && (c <= b)) return c;  
    if ((b <= a) && (a <= c)) return a;  
    if ((b <= c) && (c <= a)) return c;  
    if ((c <= a) && (a <= b)) return a;  
    return b;                            
}


template <typename T>
//Algoritmo de partição de 3
void partition3(T * A, int l, int r, int *i, int *j, Estatistica *est) {
    *i = l;
    *j = r;
    T pivo = mediana(A[l], A[r], A[((l+r)/2)]);
   
    do{
      est->addcmp(1);
      while (pivo > A[*i]) {est->addcmp(1); (*i)++;}
      est->addcmp(1);
      while (pivo < A[*j]) {est->addcmp(1); (*j)--;}
      

      if (*i <= *j){ 
        swap(&A[*i], &A[*j], est);
        (*i)++; (*j)--;
      }
    
    } while (*i <= *j);
}


template <typename T>
//Algoritmo de ordernação de quick sort
void quickSort(T * A, int l, int r, int limiar, Estatistica *est){ 
    int i_esq = l, j_dir = r;

    est->addcalls(2);
    partition3(A,l,r,&i_esq,&j_dir, est);
    
    if(j_dir > l) {
        if (abs(j_dir - l) < limiar) { 
            insertionSort(A, l, j_dir,est);
        } else {
            quickSort(A, l, j_dir,limiar,est);
        }
    }
    
    if (i_esq < r){
        if (abs(r - i_esq) < limiar) {
            insertionSort(A, i_esq, r,est);
        } else {
            quickSort(A, i_esq, r,limiar,est);
        }
    }
}




