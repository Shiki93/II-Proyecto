#include <QCoreApplication>
#include "Grafo.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Grafo *g = new Grafo();
    g->CrearGrafo();
    g->CrearGrafoPequeno();
    //g->ImprimirGrafo();

    //g->Dijkstra(21,100);
    //qDebug() << "\nSali del Dijkstra";

    g->Kruskal();
    g->Prim(21);
    //g->PuntosArticulacion(21,21);
    g->GenerarArbolNFC(&g->cant-1);

    if(g->Arbol.VacioArbol()){
        qDebug() << "Error";
    }


    return a.exec();
}
