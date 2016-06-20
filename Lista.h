//Librerias para el programa
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "NodoAdyacente.h"
#include "NodoGrafo.h"
#include <QString>

//Clase Nodolista
using namespace std;
typedef class Nodolista{
    //Constructores
    public:
        Nodolista(){
            primero = actual = NULL;
        }

        Nodolista(NodoGrafo *ori, NodoAdyacente *ll,int peso){
            origen = ori;
            llegada = ll;
            pesoAlmomento = peso;
            siguiente = NULL;
            anterior= NULL;
        }
        Nodolista(NodoGrafo *ori, NodoAdyacente *ll,int peso,  Nodolista * signodo){
            origen = ori;
            llegada = ll;
            pesoAlmomento = peso;
            siguiente = signodo;
        }
        Nodolista(NodoGrafo *val){
            valor = val;
            siguiente = NULL;
            anterior= NULL;
        }

        Nodolista(NodoGrafo *val,  Nodolista * signodo){
            valor = val;
            siguiente = signodo;
        }
        Nodolista(QString cod){
            codigo = cod;
            siguiente = NULL;
            anterior= NULL;
        }

        Nodolista(QString cod,  Nodolista * signodo){
            codigo = cod;
            siguiente = signodo;
        }

        //Constructores para entero
        Nodolista(int val){
            v = val;
        }

        Nodolista(int val, Nodolista * signodo){
            v = val;
            siguiente = signodo;
        }

        //Metodos
        bool ListaVacia(){
            return primero == NULL;
        }
        void InsertarFinal(NodoGrafo *ori, NodoAdyacente *ll,int peso);

        int devolverCodigo(QString nombre);
        void BorrarFinal();
        QString ObtenerTope();
        void Evaluar();
        void MostrarLista();
        void MostrarCamino(NodoGrafo *val);

        void insertarCola(NodoGrafo *ori, NodoAdyacente *ll,int peso);
        int largoLista();
        void InsertarFinal(NodoGrafo *val);
        bool estaElemento(NodoGrafo *val);
        void InsertarFinal(QString cod);
        bool buscarElemento(QString);

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

}* pNodolista;
