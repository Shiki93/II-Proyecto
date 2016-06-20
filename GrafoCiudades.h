#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QString>
#include "Colas.h"
#include "ArbolNario.h"
#include "Pila.h"
#include "ListaSimpleAN.h"
#include "NodoGrafoC.h"
#include "NodoAdyacenteC.h"
#include "listaCiudades.h"
#define INF 999
#define TamArr 100



class GrafoCiudades{
    public:
    //Matriz para corroborar si fue visitado un vertice
    int matVisitas[TamArr];
    //Matriz de adyacencia
    int mat[TamArr][TamArr];
    //Matriz para floyd y Warshall
    int matTemporal[TamArr][TamArr];
    //Para almacenar las posiciones de los elementos visitados
    int matPosVis[TamArr];
    //Arbol para puntos de articulacion
    ArbolNario Arbol;
    //Primer vertice de un grafo
    NodoGrafoC *PrimerNodo;
    //Ultimo vertice de un grafo
    NodoGrafoC *UltimoNodo;
    //Nodo para las busquedas
    NodoGrafoC *Elemento;
    //cantidad de vertices de un grafo
    int cant,las;
    //Inserta un elemento como una arista de un vertice
    void InsertaAristas(int CodP,int CodL,int);
    //Inserta un elemento como un vertice para ciudad
    void InsertaVertices(int, QString);
    //variable para saber si hay ciclos
    bool encCiclo;
    //Constructores
    GrafoCiudades(){
        encCiclo=false;
        cant=0;
        las=0;
        PrimerNodo=UltimoNodo=NULL;
        Elemento=NULL;
    }
    private:
    bool CargarAristasGP(int cod);
    //Carga los los paises
    bool CargarCiudades();
    public:
    //Carga el grafo
    void CrearGrafo(int cod);
    //Crea la matriz de adyacencia
    void CrearMatrizAdyacencia();
    //Imprime la lista
    void ImprimirGrafo();
    //Imprime la matriz de adyacencia
    void ImprimirMatriz(int [TamArr][TamArr]);
    //Recorre el grafo en profundidad
    void RecorridoProfundidad(int,int);
    //Recorre el grafo en anchura
    void RecorridoAnchura(int,int);
    //Algoritmo de Prim
    void Prim(int,int);
    //Algoritmo de Kruskal
    void Kruskal(int);
    //Obtiene los puntos de articulacion de un grafo
    void PuntosArticulacion(int cod,int);
    int tamano();
    //lista de nodos
    NodolistaCiudades ListaNodos();
    //listadeadayacentes
    NodolistaCiudades Listaadyacentes();
    private:
    pnodografoC BuscarVerticepos(int vas);
    //Ordena las aristas del grafo y retorna la lista de ellas
    ListaSimple OrdenarAristas();
    //Crear la matriz de valorada
    void CrearMatrizValorada();
    //Crear la matriz de valorada no dirigida
    void CrearMatrizValoradaNoDirigida();
    //Copia la matriz de adyacencia a la matriz temporal
    void CopiarMatAdyacencia();
    //Encuentra al nodo de origen
    void BuscarVerticePos(int);
    //Encuentra al nodo de origen
    void EncontrarNodo(int val);
    //Corrobora si genera ciclos
    bool GeneraCiclos(int,int);
    //Corrobora si hay ciclo
    void GeneraCiclosaux(int,int);
    //Elimina los ciclos y genera un nuevo grafo
    GrafoCiudades EliminaCiclosGrafo();
    //Crea el grafo invertido
    GrafoCiudades CreaGrafoInvertido();
    //Recorre el grafo desde un punto y retorna el vector de visitas
    bool VacioGrafo(){
        return PrimerNodo==NULL;
    }
    //Recorre el grafo en profundidad y genera el arbol n-ario
    void GenerarArbolNFC(int mac[TamArr]);
    //Crea el grafo no dirigido
    GrafoCiudades CreaGrafoNoDirigido();
    //Genera el arbol Nario
    void GenerarArbolN(int cod);
    //Ayuda a generar el arbol Nario
    void GenerarArbolNaux(NodoGrafoC *nodo);
    //Retorna si es adyacente un QString a un nodo
    bool EsAdyacente(NodoGrafoC *nodo,int cod);
    //busca el nodo que cumple que sea: adyacente,el tipo sea igual al random y el peso sea el menor
};
