#include <QDebug>
#include "NodoAdyacente.h"
#include "NodoGrafo.h"

class NodolistaC{
    public:
        NodolistaC(){
            this->primero=NULL;
            this->actual = NULL;
        }

        NodolistaC(NodoGrafo *ori, NodoAdyacente *ll,int peso){
            this->origen = ori;
            this->llegada = ll;
            this->peso = peso;
            this->siguiente = new NodolistaC();
        }

        NodolistaC(NodoGrafo *ori, NodoAdyacente *ll,int peso,  NodolistaC * signodo){
            this->origen = ori;
            this->llegada = ll;
            this->peso = peso;
            this->siguiente = signodo;
        }

        ~NodolistaC();
        bool ListaVacia(){
            bool resul=this->primero == NULL;
            return resul;
        }
        void Insertar(NodoGrafo *ori, NodoAdyacente *ll,int peso);
        void Insertarpru(int peso);
        void BorrarFinal();
        void MostrarLista();
        NodolistaC *obtenerInicio();
        void eliminarCoincidencias(NodoAdyacente *adyacente);
        void borrarPosicion(int pos);
        int largoLista();

    public:

        NodoAdyacente *llegada;
        NodoGrafo *origen;
        int peso = 0;
        //ayuda
        bool final = false;

        NodolistaC *siguiente;
        NodolistaC *primero;
        NodolistaC *actual;

};

typedef NodolistaC* pNodocola;
