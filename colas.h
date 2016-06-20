#pragma once
#include <iostream>
//******************  Clase para las Colas *******************
//Nodo para la Cola
class NodosCola{
    public:
    int datos;
    NodosCola *siguiente;
    //Constructores
    NodosCola(){
        datos=0;
        siguiente=NULL;
    }
    NodosCola(int valor){
        datos=valor;
        siguiente=NULL;
    }
    NodosCola(int valor,NodosCola *signodo){
        datos=valor;
        siguiente=signodo;
    }
};
//Prototipo Cola
//-----------------------------------------------------
class Cola{
    public:
    NodosCola *PrimerNodo;
    NodosCola *UltimoNodo;
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
