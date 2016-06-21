#pragma once
#include "NodoAdyacente.h"
#include <QString>

class NodoGrafo{
    public:
        NodoGrafo *sig_vertice = NULL;
        NodoAdyacente *siguiente_ady;
        int Tipo;
        //Para Paises
        int CodigoVertice;
        QString Nombre;
        //la Posicion en donde esta
        int pos;
        //Constructores inicial
        NodoGrafo();
        //Constructor para paises
        NodoGrafo(int,QString,int);
};
typedef NodoGrafo *pNodoGrafo;
