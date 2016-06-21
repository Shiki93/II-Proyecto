#pragma once
#include <iostream>
#include <QString>
#include "Colas.h"
#include "ArbolNario.h"
#include "ListaInt.h"
#include "NodoGrafo.h"
#include "NodoAdyacente.h"
#include "Lista.h"
#include "NodoCola.h"
#define INF 999
#define TamArr 100

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
        pNodoGrafo BuscarVerticepos(int vas);
        //Constructores
        Grafo(){
            encCiclo=false;
            cant=0;
            las=0;
            PrimerNodo=UltimoNodo=NULL;
            Elemento=NULL;
        }
        //Carga los destinos
        bool CargarAristas();
        //Carga los los paises
        bool CargarPaises();
        //Inserta un elemento como un vertice para pais
        void InsertaVertices(int cod, QString nombre);
        //Inserta un elemento como una arista de un vertice
        void InsertaAristas(int CodP,int CodL,int);

        //lista de nodos
        NodoLista ListaNodos();
        //listadeadayacentes
        NodoLista Listaadyacentes();
        //Carga el grafo
        void CrearGrafo();
        //Crea la matriz de adyacencia
        void CrearMatrizAdyacencia();
        //Imprime la lista
        void ImprimirGrafo();
        //Imprime la matriz de adyacencia
        void ImprimirMatriz(int [TamArr][TamArr]);
        //Algoritmo de Prim
        void Prim(int);
        //Algoritmo de Dikstra
        void Dijkstra(int,int);
        //Algoritmo de Kruskal
        void Kruskal();
        //Obtiene los puntos de articulacion de un grafo
        void PuntosArticulacion(int cod,int nodo);
        int tamanio();

        //Ordena las aristas del grafo y retorna la lista de ellas
        ListaInt OrdenarAristas();
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
        //Retorna si esta vacia la lista
        bool VacioGrafo(){
            return PrimerNodo==NULL;
        }
        //Crea el grafo no dirigido
        Grafo CreaGrafoNoDirigido();
        //Genera el arbol Nario
        void GenerarArbolN(int cod);
        //Ayuda a generar el arbol Nario
        void GenerarArbolNaux(NodoGrafo *nodo);
        //Retorna si es adyacente un QString a un nodo
        bool EsAdyacente(NodoGrafo *nodo,int cod);
        bool EsConexo();
};
