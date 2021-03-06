#include "colas.h"
using namespace std;


//Inserta al final un elemento
void Cola::Encolar(int Elem){
    if(VaciaCola())
        PrimerNodo=UltimoNodo=new NodosCola(Elem);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodosCola(Elem);
}

//Elimina al Inicio un elemento
void Cola::Desencolar(){
    if(VaciaCola())
        cout<<"No hay elementos\n";
    else
        if(PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodosCola *aux=PrimerNodo;
            PrimerNodo=PrimerNodo->siguiente;
            delete aux;
        }
}

//retorna el frente de la cola
int Cola::Frente(){
    if(!VaciaCola())
        return PrimerNodo->datos;
    else
        return -1;
}

//Retorna si es miembro un elemento
bool Cola::Miembro(int ele){
    bool enc=false;
    NodosCola *aux=PrimerNodo;
    while((aux != NULL) && (enc == false)){
        if(ele==aux->datos){
            enc=true;
        }
        else{
            aux=aux->siguiente;
        }
    }
    aux=NULL;
    delete aux;
    return enc;
}

//Imprime la Cola
void Cola::Imprimir(){
    NodosCola *p;
    p=PrimerNodo;
    if(PrimerNodo==NULL){
        cout<<"Cola Vacia\n";
        p=NULL;
        delete p;
    }
    else{
        while(p != NULL){
            cout <<(*p).datos<<"\n";
            p=p->siguiente;
        }
        delete p;
    }
}

