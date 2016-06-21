#include "ListaSimpleAN.h"
#include <QDebug>
using namespace std;
//Constructores
NodosLista::NodosLista(int as){
    partida=0;
    llegada=0;
    peso=0;
    siguiente=NULL;
    arr=as;
}
NodosLista::NodosLista(){
    partida=0;
    llegada=0;
    peso=0;
    siguiente=NULL;
    arr=0;
}
NodosLista::NodosLista(int valor,int valor2,int valor3){
    partida=valor;
    llegada=valor2;
    peso=valor3;
    siguiente=NULL;
    arr=0;
}
NodosLista::NodosLista(int valor,int valor2,int valor3,NodosLista *signodo){
    partida=valor;
    llegada=valor2;
    peso=valor3;
    siguiente=signodo;
    arr=0;
}


//Prototipo ListaSimple
//-----------------------------------------------------

//------------------------------------------------------
//Metodos para ListaSimple
//------------------------------------------------------
//Inserta al inicio un elemento
void ListaSimple::InsertaInicio(int Elem,int Elem2,int Elem3){
    if(VaciaLista())
        PrimerNodo=UltimoNodo=new NodosLista(Elem,Elem2,Elem3);
    else
        PrimerNodo=new NodosLista(Elem,Elem2,Elem3,PrimerNodo);
}
//Inserta al final un elemento
void ListaSimple::InsertaFinal(int Elem,int Elem2,int Elem3){
    if(VaciaLista())
        PrimerNodo=UltimoNodo=new NodosLista(Elem,Elem2,Elem3);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodosLista(Elem,Elem2,Elem3);
}
//Inserta al final un elemento
void ListaSimple::InsertaFinal(int ass){
    if(VaciaLista())
        PrimerNodo=UltimoNodo=new NodosLista(ass);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodosLista(ass);
}
//Elimina al Inicio un elemento
void ListaSimple::EliminaInicio(){
    if(VaciaLista())
        qDebug()<<"No hay elementos\n";
    else
        if(PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodosLista *aux=PrimerNodo;
            PrimerNodo=PrimerNodo->siguiente;
            delete aux;
        }
}
//Elimina el ultimo elemento
void ListaSimple::EliminaFinal(){
    if(VaciaLista())
        qDebug() <<"No hay elementos\n";
    else{
        if (PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodosLista *Actual=PrimerNodo;
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
void ListaSimple::Imprimir(){
    NodosLista *p;
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
void ListaSimple::ImprimirAR(){
    NodosLista *p;
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

int ListaSimple::largoLista(){
    int cont = 0;
    if(this->VaciaLista()){
        return 0;
    }
    else{
        NodosLista *tmp = this->PrimerNodo;
        while(tmp){
            cont++;
            tmp = tmp->siguiente;
        }
    }
    return cont;
}

bool ListaSimple::existeConjunto(int valor){
    if(this->VaciaLista()){
        return false;
    }
    else{
        NodosLista *tmp = this->PrimerNodo;
        while(tmp){
            if(tmp->arr == valor){
                return true;
            }
            else{
                tmp = tmp->siguiente;
            }
        }
        return false;
    }
}
