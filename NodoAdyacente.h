#pragma once
#include <QString>
using namespace std;
class NodoAdyacente{
    public:
    NodoAdyacente *siguiente_ady;
    int Cod;
    int peso = 0;
    int pos = 0;
    QString NombrePais;
    //Constructores inicial
    NodoAdyacente();
    //Constructor para nodos
    NodoAdyacente(int,int,int,QString);
};
