#pragma once
#include <QString>

using namespace std;
class NodoAdyacenteC{
    public:
    NodoAdyacenteC *siguiente_ady;
    int Cod;
    int peso,pos;
    QString NombreCiudad;
    //Constructores inicial
    NodoAdyacenteC();
    //Constructor para nodos
    NodoAdyacenteC(int, int, int, QString);
};
