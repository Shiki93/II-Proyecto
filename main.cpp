#include <QCoreApplication>
#include "Grafo.h"
#include <QDebug>
#include "Grafo.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

void guardar(Grafo *g){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Escena.txt");
    if(!archivo.open(QFile::ReadWrite | QFile::Text)){
        qDebug() << "Error con el archivo de escena";
    }
    else{
        QTextStream out(&archivo);
        QString x = out.readAll();
        out << x << endl;
        NodoGrafo *tmp = g->PrimerNodo;
        while(tmp != NULL){
            QString nombre = tmp->Nombre;
            QString cod = QString::number(tmp->CodigoVertice);
            NodoAdyacente *adyacente = tmp->siguiente_ady;
            QString pos = QString::number(tmp->pos);
            QString tipo = QString::number(tmp->Tipo);
            QString x = "";
            NodoAdyacente *tmp2 = adyacente;
            while(tmp2 != NULL){
                QString c = QString::number(tmp2->codigo);
                QString origen = tmp2->Nombre;
                QString peso = QString::number(tmp2->peso);
                x = x + "," + c + "," + origen + "," + peso + ",";
                tmp2 = tmp2->siguiente_ady;
            }
            QString data = cod + ";" + pos + ";" + tipo + ";" + nombre + x;
            qDebug() << data << endl;
            out << data << endl;
            tmp = tmp->sig_vertice;
        }
    }
    archivo.flush();
    archivo.close();
}


int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);
    Grafo *g = new Grafo();
    g->CrearGrafo();
    guardar(g);
    g->GenerarArbolN(11);

    g->Arbol.Preorden(11);
    g->Arbol.PostOrdenAR();
    g->Arbol.ImprimirRefPadre();

    qDebug() << "Algoritmos de Ordenamientos";

    g->Prim(11);
    g->Kruskal();
    g->Dijkstra(11, 21);

    return a.exec();
}
