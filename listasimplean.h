#ifndef LISTASIMPLEAN_H
#define LISTASIMPLEAN_H
#include <QtCore>
class NodoLista{
public:
    int arr;
    int partida;
    int llegada;
    int peso;
    NodoLista *siguiente;
    //Constructores
    NodoLista();
    NodoLista(int as);
    NodoLista(int valor, int valor2, int valor3);
    NodoLista(int valor, int valor2, int valor3, NodoLista *signodo);
};

class ListaSimple{
public:
    NodoLista *PrimerNodo;
    NodoLista *UltimoNodo;

    //Constructor
    ListaSimple(){
        UltimoNodo = NULL;
        PrimerNodo = UltimoNodo;
    }
    //Retorna si esta vacia la lista
    int VaciaLista(){return PrimerNodo == NULL;}
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

#endif // LISTASIMPLEAN_H
