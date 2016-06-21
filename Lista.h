#pragma once
#include "NodoAdyacente.h"
#include "NodoGrafo.h"
#include <QString>

typedef class NodoLista{
    //Constructores
    public:
        NodoLista(){
            primero = actual = NULL;
        }
        NodoLista(NodoGrafo *ori, NodoAdyacente *ll,int peso){
            origen = ori;
            llegada = ll;
            pesoAlmomento = peso;
            siguiente = NULL;
            anterior= NULL;
        }
        NodoLista(NodoGrafo *ori, NodoAdyacente *ll,int peso,  NodoLista * signodo){
            origen = ori;
            llegada = ll;
            pesoAlmomento = peso;
            siguiente = signodo;
        }
        NodoLista(NodoGrafo *val){
            valor = val;
            siguiente = NULL;
            anterior= NULL;
        }
        NodoLista(NodoGrafo *val,  NodoLista * signodo){
            valor = val;
            siguiente = signodo;
        }
        NodoLista(QString cod){
            codigo = cod;
            siguiente = NULL;
            anterior= NULL;
        }
        NodoLista(QString cod,  NodoLista * signodo){
            codigo = cod;
            siguiente = signodo;
        }

        //Constructores para entero
        NodoLista(int val){
            v = val;
        }
        NodoLista(int val, NodoLista * signodo){
            v = val;
            siguiente = signodo;
        }

        //Metodos
        bool ListaVacia(){
            return primero == NULL;
        }        
        void InsertarFinal(int v);
        void InsertarFinal(NodoGrafo *val);
        void InsertarFinal(NodoGrafo *ori, NodoAdyacente *ll,int peso);
        void BorrarFinal();
        void MostrarLista();
        void MostrarCamino(NodoGrafo *val);
        int largoLista();
        bool estaElemento(NodoGrafo *val);
        void InsertarFinal(QString cod);
        bool buscarElemento(QString);

        NodoAdyacente *llegada;
        NodoGrafo *origen;
        int pesoAlmomento;
        int v;		//Para graficar
        NodoGrafo *valor;

        QString codigo;
        QString inicio;
        QString fin;
        QString peso;

        NodoLista *siguiente;
        NodoLista *primero;
        NodoLista *anterior;
        NodoLista *actual;

}* pNodoLista;
