#include <QCoreApplication>
#include "Grafo.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Grafo *g = new Grafo();
    g->CrearGrafo();

    g->GenerarArbolN(11);

    g->Arbol.ImprimirRefPadre();

    g->Arbol.Preorden(11);
    g->Arbol.PostOrdenAR();

    g->Arbol.ImprimirRefPadre();


    return a.exec();
}
