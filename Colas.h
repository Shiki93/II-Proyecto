#pragma once
#include <QDebug>

class Nodocola{
    public:
    int datos;
    Nodocola *siguiente;
    //Constructores
    Nodocola(){
        datos=0;
        siguiente=NULL;
    }
    Nodocola(int valor){
        datos=valor;
        siguiente=NULL;
    }
    Nodocola(int valor,Nodocola *signodo){
        datos=valor;
        siguiente=signodo;
    }
};

class Cola{
    public:
    Nodocola *PrimerNodo;
    Nodocola *UltimoNodo;
    //Constructor
    Cola(){
        PrimerNodo=UltimoNodo=NULL;
    }
    //Retorna si esta vacia la lista
    int VaciaCola(){
        return PrimerNodo==NULL;
    }
    //Inserta al final un elemento
    void Encolar(int);
    //Elimina al Inicio un elemento
    void Desencolar();
    //Retorna si es miembro un elemento
    bool Miembro(int);
    //retorna el frente de la cola
    int Frente();
    //Imprime la lista
    void Imprimir();
};
