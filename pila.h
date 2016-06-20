#pragma once
#include <iostream>
//******************  Clase para la Pila  *******************

//Nodo para la Pila
class NodosPila{
    public:
    int datos;
    NodosPila *siguiente;
    //Constructores
    NodosPila(){
        datos=0;
        siguiente=NULL;
    }
    NodosPila(int valor){
        datos=valor;
        siguiente=NULL;
    }
    NodosPila(int valor,NodosPila *signodo){
        datos=valor;
        siguiente=signodo;
    }
};

class Pila{
    public:
    NodosPila *PrimerNodo;
    NodosPila *UltimoNodo;
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
