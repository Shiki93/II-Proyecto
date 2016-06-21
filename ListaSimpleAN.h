#pragma once
#include <iostream>
#include <QString>

using namespace std;
class NodosLista{
    public:
    int arr;
    int partida;
    int llegada;
    int peso;
    NodosLista *siguiente;
    //Constructores
    NodosLista();
    NodosLista(int as);
    NodosLista(int valor,int valor2,int valor3);
    NodosLista(int valor,int valor2,int valor3,NodosLista *signodo);
};


class ListaSimple{
    public:
    NodosLista *PrimerNodo;
    NodosLista *UltimoNodo;
    //Constructor
    ListaSimple(){
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
    //Retorna el largo de la lista
    int largoLista();
    //Buscar elemento
    bool existeConjunto(int);
};
