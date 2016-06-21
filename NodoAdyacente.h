#pragma once
#include <QString>

class NodoAdyacente{
    public:
        NodoAdyacente *siguiente_ady;
        int codigo;
        int peso = 0;
        int pos = 0;
        QString Nombre;
        //Constructores inicial
        NodoAdyacente();
        //Constructor para nodos
        NodoAdyacente(int,int,int,QString);
};
