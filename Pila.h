#pragma once
#include <iostream>

class NodoPila{
    public:
    int datos;
    NodoPila *siguiente;
    //Constructores
    NodoPila(){
        datos=0;
        siguiente=NULL;
    }
    NodoPila(int valor){
        datos=valor;
        siguiente=NULL;
    }
    NodoPila(int valor,NodoPila *signodo){
        datos=valor;
        siguiente=signodo;
    }
};

class Pila{
    public:
        NodoPila *PrimerNodo;
        NodoPila *UltimoNodo;
        //Constructor
        Pila(){
            PrimerNodo=UltimoNodo=NULL;
        }
        //Retorna si esta vacia la lista
        int VaciaPila(){
            return PrimerNodo==NULL;
        }
        //Apila un elemento
        void Push(int);
        //Desapila un elemento
        void Pop();
        //Retorna el tope de la pila
        int Tope();
        //Imprime la lista
        void Imprimir();
};
