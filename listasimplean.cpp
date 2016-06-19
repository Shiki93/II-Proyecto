#include "listasimplean.h"
#include <QDebug>

//Constructores
NodoLista::NodoLista(){
    arr = 0;
    partida = 0;
    llegada = 0;
    peso = 0;
    siguiente = NULL;
}

NodoLista::NodoLista(int as){
    arr = as;
    partida = 0;
    llegada = 0;
    peso = 0;
    siguiente = NULL;
}

NodoLista::NodoLista(int valor, int valor2, int valor3){
    arr = 0;
    partida = valor;
    llegada = valor2;
    peso = valor3;
    siguiente = NULL;
}

NodoLista::NodoLista(int valor, int valor2, int valor3, NodoLista *signodo){
    arr = 0;
    partida = valor;
    llegada = valor2;
    peso = valor3;
    siguiente = signodo;
}

//Prototipo ListaSimple
//-----------------------------------------------------

//------------------------------------------------------
//Metodos para ListaSimple
//------------------------------------------------------
//Inserta al inicio un elemento
void ListaSimple::InsertaInicio(int Elem, int Elem2, int Elem3){
    if(VaciaLista()){
        PrimerNodo = UltimoNodo = new NodoLista(Elem, Elem2, Elem3);
    }
    else{
        PrimerNodo = new NodoLista(Elem, Elem2, Elem3, PrimerNodo);
    }
}

//Inserta al final un elemento
void ListaSimple::InsertaFinal(int Elem, int Elem2, int Elem3){
    if(VaciaLista()){
        PrimerNodo = UltimoNodo = new NodoLista(Elem,Elem2,Elem3);
    }
    else{
        UltimoNodo = UltimoNodo->siguiente = new NodoLista(Elem,Elem2,Elem3);
    }
}

//Inserta al final un elemento
void ListaSimple::InsertaFinal(int ass){
    if(VaciaLista()){
        PrimerNodo = UltimoNodo = new NodoLista(ass);
    }
    else{
        UltimoNodo = UltimoNodo->siguiente = new NodoLista(ass);
    }
}

//Elimina al Inicio un elemento
void ListaSimple::EliminaInicio(){
    if(VaciaLista()){
        qDebug() <<"No hay elementos\n";
    }
    else{
        if(PrimerNodo == UltimoNodo){
            PrimerNodo = UltimoNodo = NULL;
        }
        else{
            NodoLista *aux = PrimerNodo;
            PrimerNodo = PrimerNodo->siguiente;
            delete aux;
        }
    }
}

//Elimina el ultimo elemento
void ListaSimple::EliminaFinal(){
    if(VaciaLista()){
        qDebug() <<"No hay elementos\n";
    }
    else{
        if (PrimerNodo == UltimoNodo){
            PrimerNodo = UltimoNodo = NULL;
        }
        else{
            NodoLista *Actual = PrimerNodo;
            while(Actual->siguiente != UltimoNodo){
                Actual = Actual->siguiente;
            }
            delete UltimoNodo;
            UltimoNodo = Actual;
            UltimoNodo->siguiente = NULL;
        }
    }
}

//Imprime la lista
void ListaSimple::Imprimir(){
    NodoLista *p;
    p = PrimerNodo;
    if(PrimerNodo == NULL){
        qDebug() << "No hay elementos\n";
        p = NULL;
        delete p;
    }
    else{
        while(p != NULL){
            qDebug() << p->partida << "-> " << p->llegada<< "\n";
            p = p->siguiente;
        }
        delete p;
    }
}

//Imprime la lista
void ListaSimple::ImprimirAR(){
    NodoLista *p = PrimerNodo;
    if(PrimerNodo == NULL){
        qDebug() << "No hay aristas de retroceso\n";
        p = NULL;
        delete p;
    }
    else{
        while(p != NULL){
            qDebug() << p->arr << " ";
            p = p->siguiente;
        }
        delete p;
    }
}
