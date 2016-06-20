#include <QCoreApplication>
#include "Grafo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Grafo *g = new Grafo();
    g->CrearGrafo();
    g->CrearGrafoPequeno();
    //g->ImprimirGrafo();
    g->Dijkstra(21,100);
    g->Kruskal();
    g->Prim(21);

    return a.exec();
}
