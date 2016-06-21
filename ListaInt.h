#pragma once
#include <QString>

class NodoListaInt{
    public:
    int arr;
    int partida;
    int llegada;
    int peso;
    NodoListaInt *siguiente;
    //Constructores
    NodoListaInt();
    NodoListaInt(int as);
    NodoListaInt(int valor,int valor2,int valor3);
    NodoListaInt(int valor,int valor2,int valor3,NodoListaInt *signodo);
};

class ListaInt{
    public:
    NodoListaInt *PrimerNodo;
    NodoListaInt *UltimoNodo;
    //Constructor
    ListaInt(){
        PrimerNodo=UltimoNodo=NULL;
    }
    //Retorna si esta vacia la lista
    int VaciaLista(){
        return PrimerNodo==NULL;
    }
    //Inserta al inicio un elemento
    void InsertaInicio(int,int,int);
    //Inserta al final un elemento
    void InsertaFinal(int,int,int);
    //Inserta al final un elemento
    void InsertaFinal(int);
    //Elimina al Inicio un elemento
    void EliminaInicio();
    //Elimina el ultimo elemento
    void EliminaFinal();
    //Imprime la lista
    void Imprimir();
    //Imprime la lista de aristas de retoceso
    void ImprimirAR();
};
