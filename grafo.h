#ifndef GRAFO_H
#define GRAFO_H

#include <QString>
#include "colas.h"
#include "arbolnario.h"
#include "pila.h"
#include "listasimplean.h"
#include "lista.h"
#define INF 999
#define TamArr 100

typedef class NodoGrafo{
public:
    NodoGrafo *sig_vertice;
    class NodoAdyacente *siguiente_ady;
    int Tipo;
    QString nombre;
    //Constructores inicial
    NodoGrafo();
    //Constructor para paises
    NodoGrafo(int, QString, int);
}*pnodografo;

class NodoAdyacente{
public:
    NodoAdyacente *siguiente_ady;
    int Cod;
    int peso, pos;
    QString nombre;
    //Constructores inicial
    NodoAdyacente();
    //Constructor para nodos
    NodoAdyacente(int, int, int, QString);
};

class Grafo{
public:
    //Matriz para corroborar si fue visitado un vertice
    int matVisitas[TamArr];
    //Matriz de adyacencia
    int mat[TamArr][TamArr];
    int matTemporal[TamArr][TamArr];
    //Para almacenar las posiciones de los elementos visitados
    int matPosVis[TamArr];
    //Arbol para puntos de articulacion
    ArbolNario Arbol;
    //Primer vertice de un grafo
    NodoGrafo *PrimerNodo;
    //Ultimo vertice de un grafo
    NodoGrafo *UltimoNodo;
    //Nodo para las busquedas
    NodoGrafo *Elemento;
    //cantidad de vertices de un grafo
    int cant,las;
    //variable para saber si hay ciclos
    bool encCiclo;
    pnodografo BuscarVerticepos(int vas);
    //Constructores
    Grafo();
private:
    //Carga los destinos
    bool CargarAristasGG();
    bool CargarAristasGP();
    //Carga los los paises
    bool CargarPaises();
    //Inserta un elemento como un vertice para pais
    void InsertaVertices(int, QString);
    //Inserta un elemento como una arista de un vertice
    void InsertaAristas(int, int, int);

public:
    //lista de nodos
    NodoLista ListaNodos();
    //listadeadayacentes
    NodoLista Listaadyacentes();
    //Carga el grafo
    void CrearGrafo();
    bool CrearGrafoPequeno();
    //Crea la matriz de adyacencia
    void CrearMatrizAdyacencia();
    //Imprime la lista
    void ImprimirGrafo();
    //Imprime la matriz de adyacencia
    void ImprimirMatriz(int [TamArr][TamArr]);
    //Recorre el grafo en profundidad
    void RecorridoProfundidad(int);
    //Recorre el grafo en anchura
    void RecorridoAnchura(int);
    //Algoritmo de Prim
    void Prim(int);
    //Algoritmo de Dikstra
    void Dijkstra(int,int);
    //Algoritmo de Kruskal
    void Kruskal();
    //Obtiene los puntos de articulacion de un grafo
    void PuntosArticulacion(int cod,int nodo);
    int tamano();

private:
    //Ordena las aristas del grafo y retorna la lista de ellas
    ListaSimple OrdenarAristas();
    //Crear la matriz de valorada
    void CrearMatrizValorada();
    //Crear la matriz de valorada no dirigida
    void CrearMatrizValoradaNoDirigida();
    //Encuentra al nodo de origen
    void BuscarVerticePos(int);
    //Encuentra al nodo de origen
    void EncontrarNodo(int val);
    //Corrobora si genera ciclos
    bool GeneraCiclos(int,int);
    //Corrobora si hay ciclo
    void GeneraCiclosaux(int,int);
    //Elimina los ciclos y genera un nuevo grafo
    Grafo EliminaCiclosGrafo();
    //Crea el grafo invertido
    Grafo CreaGrafoInvertido();
    //Retorna si esta vacia la lista
    bool VacioGrafo(){return PrimerNodo == NULL;}
    //Recorre el grafo en profundidad y genera el arbol n-ario
    void GenerarArbolNFC(int mac[TamArr]);
    //Crea el grafo no dirigido
    Grafo CreaGrafoNoDirigido();
    //Genera el arbol Nario
    void GenerarArbolN(int cod);
    //Ayuda a generar el arbol Nario
    void GenerarArbolNaux(NodoGrafo *nodo);
    //Retorna si es adyacente un string a un nodo
    bool EsAdyacente(NodoGrafo *nodo,int cod);
};

#endif // GRAFO_H
