#include "ListaInt.h"
#include <QDebug>

//Constructores
NodoListaInt::NodoListaInt(int as){
    partida=0;
    llegada=0;
    peso=0;
    siguiente=NULL;
    arr=as;
}
NodoListaInt::NodoListaInt(){
    partida=0;
    llegada=0;
    peso=0;
    siguiente=NULL;
    arr=0;
}
NodoListaInt::NodoListaInt(int valor,int valor2,int valor3){
    partida=valor;
    llegada=valor2;
    peso=valor3;
    siguiente=NULL;
    arr=0;
}
NodoListaInt::NodoListaInt(int valor,int valor2,int valor3,NodoListaInt *signodo){
    partida=valor;
    llegada=valor2;
    peso=valor3;
    siguiente=signodo;
    arr=0;
}

//Inserta al inicio un elemento
void ListaInt::InsertaInicio(int Elem,int Elem2,int Elem3){
    if(VaciaLista())
        PrimerNodo=UltimoNodo=new NodoListaInt(Elem,Elem2,Elem3);
    else
        PrimerNodo=new NodoListaInt(Elem,Elem2,Elem3,PrimerNodo);
}

//Inserta al final un elemento
void ListaInt::InsertaFinal(int Elem,int Elem2,int Elem3){
    if(VaciaLista())
        PrimerNodo=UltimoNodo=new NodoListaInt(Elem,Elem2,Elem3);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodoListaInt(Elem,Elem2,Elem3);
}

//Inserta al final un elemento
void ListaInt::InsertaFinal(int ass){
    if(VaciaLista())
        PrimerNodo=UltimoNodo=new NodoListaInt(ass);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodoListaInt(ass);
}

//Elimina al Inicio un elemento
void ListaInt::EliminaInicio(){
    if(VaciaLista())
        qDebug()<<"No hay elementos\n";
    else
        if(PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodoListaInt *aux=PrimerNodo;
            PrimerNodo=PrimerNodo->siguiente;
            delete aux;
        }
}

//Elimina el ultimo elemento
void ListaInt::EliminaFinal(){
    if(VaciaLista())
        qDebug() <<"No hay elementos\n";
    else{
        if (PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodoListaInt *Actual=PrimerNodo;
            while (Actual->siguiente != UltimoNodo){
                Actual=Actual->siguiente;
            }
            delete UltimoNodo;
            UltimoNodo=Actual;
            UltimoNodo->siguiente = NULL;
        }
    }
}

//Imprime la lista
void ListaInt::Imprimir(){
    NodoListaInt *p;
    p=PrimerNodo;
    if(PrimerNodo==NULL){
        qDebug()<<"No hay elementos\n";
        p=NULL;
        delete p;
    }
    else{
        while(p != NULL){
            qDebug() <<(*p).partida<<"-> "<<(*p).llegada<<"\n";
            p=p->siguiente;
        }
        delete p;
    }
}

//Imprime la lista
void ListaInt::ImprimirAR(){
    NodoListaInt *p;
    p=PrimerNodo;
    if(PrimerNodo==NULL){
        qDebug()<<"No hay aristas de retroceso\n";
        p=NULL;
        delete p;
    }
    else{
        while(p != NULL){
            qDebug() <<p->arr<<" ";
            p=p->siguiente;
        }
        delete p;
    }
}

