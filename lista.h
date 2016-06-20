//Librerias para el programa
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "grafo.h"

//Clase Nodolista
class Nodolista{

    //Constructores
    public:
        Nodolista(){
            primero = actual = NULL;
        }

        Nodolista(class NodoGrafo *ori, class NodoAdyacente *ll,int peso){
            origen = ori;
            llegada = ll;
            pesoAlmomento = peso;
            siguiente = NULL;
            anterior= NULL;
        }

        Nodolista(class NodoGrafo *ori, class NodoAdyacente *ll,int peso,  Nodolista * signodo){
            origen = ori;
            llegada = ll;
            pesoAlmomento = peso;
            siguiente = signodo;
        }

        Nodolista(class NodoGrafo *val){
            valor = val;
            siguiente = NULL;
            anterior= NULL;
        }

        Nodolista(class NodoGrafo *val, class Nodolista * signodo){
            valor = val;
            siguiente = signodo;
        }

        Nodolista(QString cod){
            codigo = cod;
            siguiente = NULL;
            anterior= NULL;
        }

        Nodolista(QString cod, class Nodolista * signodo){
            codigo = cod;
            siguiente = signodo;
        }

        //Constructores para entero
        Nodolista(int val){
            v = val;
        }

        Nodolista(int val,class Nodolista * signodo){
            v = val;
            siguiente = signodo;
        }

        //Metodos
        bool ListaVacia(){
            return primero == NULL;
        }
        void InsertarFinal(class NodoGrafo *ori,class NodoAdyacente *ll,int peso);

        int devolverCodigo(QString nombre);
        void BorrarFinal();
        QString ObtenerTope();
        void Evaluar();
        void MostrarLista();
        void MostrarCamino(class NodoGrafo *val);

        void insertarCola(class NodoGrafo *ori,class NodoAdyacente *ll,int peso);
        int largoLista();
        void InsertarFinal(class NodoGrafo *val);
        bool estaElemento(class NodoGrafo *val);
        void InsertarFinal(QString cod);

        //Métodos para graficar
        Nodolista * getSig(){ return siguiente; }
        Nodolista * getPrimero(){ return primero; }
        int getValor(){ return v; }
        void InsertarFinal(int v);

        NodoAdyacente *llegada;
        NodoGrafo *origen;
        int pesoAlmomento;
        int v;		//Para graficar
        NodoGrafo *valor;

        QString codigo;
        QString inicio;
        QString fin;
        QString peso;

        Nodolista *siguiente;
        Nodolista *primero;
        Nodolista *anterior;
        Nodolista *actual;

};

typedef Nodolista* pNodolista;






