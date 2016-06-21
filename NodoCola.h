#pragma once
#include <QDebug>
#include "NodoAdyacente.h"
#include "NodoGrafo.h"

class NodoCola{
    public:
        NodoCola(){
            this->primero = NULL;
            this->actual = NULL;
            this->siguiente = NULL;
        }
        NodoCola(NodoGrafo *ori, NodoAdyacente *ll,int peso){
            this->origen = ori;
            this->llegada = ll;
            this->peso = peso;
            this->siguiente = new NodoCola();
        }
        NodoCola(NodoGrafo *ori, NodoAdyacente *ll,int peso,  NodoCola * signodo){
            this->origen = ori;
            this->llegada = ll;
            this->peso = peso;
            this->siguiente = signodo;
        }
        ~NodoCola();

        bool ListaVacia(){
            bool resul = this->primero == NULL;
            return resul;
        }
        void Insertar(NodoGrafo *ori, NodoAdyacente *ll,int peso);
        void BorrarFinal();
        void MostrarLista();
        NodoCola *obtenerInicio();
        void eliminarCoincidencias(NodoAdyacente *adyacente);
        void borrarPosicion(int pos);
        int largoLista();

        NodoAdyacente *llegada;
        NodoGrafo *origen;
        int peso = 0;
        //ayuda
        bool final = false;

        NodoCola *siguiente = NULL;
        NodoCola *primero = NULL;
        NodoCola *actual = NULL;

};typedef NodoCola* pNodocola;
