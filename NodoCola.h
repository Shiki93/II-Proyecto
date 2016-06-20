#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "NodoAdyacente.h"
#include "NodoGrafo.h"

using namespace std;

class NodolistaC{
    public:
        NodolistaC(){
            primero = actual = NULL;
        }

        NodolistaC(NodoGrafo *ori, NodoAdyacente *ll,int peso){
            origen = ori;
            llegada = ll;
            this->peso = peso;
            siguiente = NULL;
        }

        NodolistaC(NodoGrafo *ori, NodoAdyacente *ll,int peso,  NodolistaC * signodo){
            origen = ori;
            llegada = ll;
            this->peso = peso;
            siguiente = signodo;
        }

        ~NodolistaC();
        bool ListaVacia(){ return primero == NULL; }
        void Insertar(NodoGrafo *ori, NodoAdyacente *ll,int peso);
        void Insertarpru(int peso);
        void BorrarFinal();
        void MostrarLista();
        NodolistaC *obtenerInicio();
        void eliminarCoincidencias(NodoAdyacente *adyacente);
        void borrarPosicion(int pos);
        int largoLista();

    public:

        NodoAdyacente *llegada;
        NodoGrafo *origen;
        int peso;
        //ayuda
        bool final;

        NodolistaC *siguiente;
        NodolistaC *primero;
        NodolistaC *actual;

};

typedef NodolistaC* pNodocola;
