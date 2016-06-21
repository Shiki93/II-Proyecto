#pragma once
#include <iostream>
#include "ListaInt.h"

class NodosArbolNario{
    public:
    ListaInt ListaAR;
    int datos;
    int num,bajo;
    NodosArbolNario *padre;
    NodosArbolNario *hijo;
    NodosArbolNario *hermanoD;
    NodosArbolNario *hermanoI;
    //Constructores
    NodosArbolNario();
    NodosArbolNario(int valor);
};

class ArbolNario{
    public:    
        NodosArbolNario *ElementoB;
        bool enco,tienepts;
        int va,niv,ia;
        QString matpts[200];
        NodosArbolNario *Raiz;
        //Constructor
        ArbolNario(){
            ElementoB=NULL;
            Raiz=NULL;
            enco=false;
            tienepts=false;
            va=1;
            ia=0;
            niv=1;
    }
    //Retorna si esta vacio el Arbol N-ario
    int VacioArbol(){
        return Raiz==NULL;
    }
    //Inserta un elemento en el arbol con el sig formato
    //Padre,Tipo,Valor,Peso
    //donde Tipo es 1:insercion como hermano
    //				0:insercion como hijo
    void Insertar(int,int,int);
    //Imprime el arbol N-Ario por referencias del hermano
    void ImprimirRefHermano();
    //Imprime el arbol N-Ario por referencias del padre
    void ImprimirRefPadre();
    //Retorna el nodo donde esta el elemento Nota:El elemento esta en ElementoB
    void EncontrarElem(int);
    //Recorre el arbol en Preorden
    void Preorden(int);
    //Retorna si un valor es hijo de un nodo
    bool EsHijo(int,NodosArbolNario *nodo);
    //Inserta la arista de retroceso
    void insertarAR(int,int);
    //Retorna el nivel de insercion (entre mas bajo mayor prioridad a la hora de
    //insercion de las aristas de retroceso
    int Nivel(int cod);
    //Retorna le nivel del nodo
    void Nivelaux(NodosArbolNario *raizaux,int);
    //Recorr el arbol y va poniendo los bajos
    void PostOrdenAR();
    //Recorre el arbol en postorden para poner los bajos
    void PostOrdenARaux(NodosArbolNario *raizaux);
    //Compara los nums y bajos
    void EsPuntoArticulacion(int nodo);
    //Compara los nums y bajos
    void EsPuntoArticulacionaux(NodosArbolNario *raizaux,int nodo);
    //Imprime el arbol en preorden desde un punto de inicio
    void ImprimirAdesdeVertice(NodosArbolNario *raizaux,NodosArbolNario *rai);
    //Preorden (aux)
    void Preordenaux(NodosArbolNario *raizaux,int nodo);
    //Imprime el arbol N-Ario por referencias del padre (aux)
    void ImprimirRefPadreaux(NodosArbolNario *raizaux);
    //Imprime el arbol N-Ario por referencias del hermano (aux)
    void ImprimirRefHermanoaux(NodosArbolNario *raizaux);
    //Retorna el nodo donde esta el papa
    void EncontrarElemaux(NodosArbolNario *raizaux,int);
    void Postorden(int nodo);
    void PostOrdenaux(NodosArbolNario *raizaux, int nodo);
};
