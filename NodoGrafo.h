#pragma once
#include "NodoAdyacente.h"
#include "GrafoCiudades.h"
#include <QString>
using namespace std;
class NodoGrafo{
    public:

    NodoGrafo *sig_vertice = NULL;
    NodoAdyacente *siguiente_ady;
    int Tipo;
    //grafopequeño
    //Para Paises
    int CodVerticeGG;
    QString NombrePais;
    //la Posicion en donde esta
    int pos;
    //Constructores inicial
    NodoGrafo();
    //Constructor para paises
    NodoGrafo(int,QString,int);
    GrafoCiudades grafoGP;
};
typedef NodoGrafo *pnodografo;
