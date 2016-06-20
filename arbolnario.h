#ifndef ARBOLNARIO_H
#define ARBOLNARIO_H
#include <QtCore>
#include <QString>
#include "listasimplean.h"


class NodosArbolNario{
public:
    ListaSimple ListaAR;
    int datos;
    int num,bajo;
    NodosArbolNario *padre;
    NodosArbolNario *hijo;
    NodosArbolNario *hermanoD;
    NodosArbolNario *hermanoI;
    //Constructores
    NodosArbolNario();
    NodosArbolNario(int valor);
};

class ArbolNario{
public:
    NodosArbolNario *ElementoB;
    bool enco, tienepts;
    int va, niv, ia;
    QString matpts[200];
    NodosArbolNario *Raiz;

    ArbolNario();
    int VacioArbol(){return Raiz == NULL;}
    void Insertar(int, int, int);
    void ImprimirRefHermano();
    void ImprimirRefPadre();
    void EncontrarElem(int);
    void Preorden(int);
    bool EsHijo(int, NodosArbolNario *);
    void insertarAR(int, int);
    int  Nivel(int);
    void Nivelaux(NodosArbolNario *, int);
    void PostOrdenAR();
    void PostOrdenARaux(NodosArbolNario *);
    void EsPuntoArticulacion(int);
    void EsPuntoArticulacionaux(NodosArbolNario *,int);
    void ImprimirAdesdeVertice(NodosArbolNario *, NodosArbolNario *);

private:
    void Preordenaux(NodosArbolNario *,int);
    void ImprimirRefPadreaux(NodosArbolNario *);
    void ImprimirRefHermanoaux(NodosArbolNario *);
    void EncontrarElemaux(NodosArbolNario *, int);
};
#endif // ARBOLNARIO_H
