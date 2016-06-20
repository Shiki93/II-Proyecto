#pragma once
#include "NodoAdyacenteC.h"
#include "GrafoCiudades.h"
#include <QString>

using namespace std;
typedef class NodoGrafoC{
    public:

    NodoGrafoC *sig_vertice;
    NodoAdyacenteC *siguiente_ady;
    int Tipo;
    //Para Paises
    int CodVerticeGP;
    QString NombreCiudad;

    int pos;
    //Constructores inicial
    NodoGrafoC();
    //Constructor para paises
    NodoGrafoC(int, QString, int);

}*pnodografoC;
