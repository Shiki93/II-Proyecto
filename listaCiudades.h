//Librerias para el programa
#pragma once
#include <iostream>
#include <fstream>
#include <QString>
#include <sstream>
#include "NodoAdyacenteC.h"
#include "NodoGrafoC.h"

using namespace std;
typedef class NodolistaCiudades{

    //Constructores
    public:
        NodolistaCiudades(){
            primero = actual = NULL;
        }
        NodolistaCiudades(QString cod, QString nom){
            codigo = cod;
            nombre = nom;
            siguiente = NULL;
            anterior= NULL;
        }

        NodolistaCiudades(QString cod,  NodolistaCiudades * signodo){
            codigo = cod;
            siguiente = signodo;
        }

        //Constructores para entero
        NodolistaCiudades(int val){
            v = val;
        }

        NodolistaCiudades(int val, NodolistaCiudades * signodo){
            v = val;
            siguiente = signodo;
        }

        //Metodos
        bool ListaVacia(){
            return primero == NULL;
        }

        int devolverCodigo(QString nombre);
        void BorrarFinal();
        QString ObtenerTope();
        void Evaluar();
        int largoLista();
        void InsertarFinal(QString cod,QString nombre);
        void Mostrar();
        //Métodos para graficar
        NodolistaCiudades * getSig(){ return siguiente; }
        NodolistaCiudades * getPrimero(){ return primero; }
        int getValor(){ return v; }
        void InsertarFinal(int v);

        int pesoAlmomento;
        int v;		//Para graficar

        QString codigo;
        QString nombre;


        NodolistaCiudades *siguiente;
        NodolistaCiudades *primero;
        NodolistaCiudades *anterior;
        NodolistaCiudades *actual;

}* pNodolistaCiudades;
