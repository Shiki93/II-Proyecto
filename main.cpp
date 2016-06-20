#include <QCoreApplication>
#include "Grafo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Grafo *g = new Grafo();
    g->CrearGrafo();
    g->ImprimirGrafo();

    return a.exec();
}
