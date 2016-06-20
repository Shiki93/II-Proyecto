#pragma once
#include <QString>
using namespace std;
class NodoAdyacente{
    public:
    NodoAdyacente *siguiente_ady;
    int Cod;
    int peso,pos;
    QString NombrePais;
    //Constructores inicial
    NodoAdyacente();
    //Constructor para nodos
    NodoAdyacente(int,int,int,QString);
};
