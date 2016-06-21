#include <QCoreApplication>
#include "Grafo.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Grafo *g = new Grafo();
    g->CrearGrafo();

    //g->GenerarArbolN(11);

    g->Prim(11);
    g->Dijkstra(21, 11);


    return a.exec();
}
