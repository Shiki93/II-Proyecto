#include "Colas.h"
#include <QDebug>

//Inserta al final un elemento
void Cola::Encolar(int Elem){
    if(VaciaCola())
        PrimerNodo=UltimoNodo=new Nodocola(Elem);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new Nodocola(Elem);
}

//Elimina al Inicio un elemento
void Cola::Desencolar(){
    if(VaciaCola())
        qDebug()<<"No hay elementos\n";
    else
        if(PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            Nodocola *aux=PrimerNodo;
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
    Nodocola *aux=PrimerNodo;
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
    Nodocola *p;
    p=PrimerNodo;
    if(PrimerNodo==NULL){
        qDebug()<<"Cola Vacia\n";
        p=NULL;
        delete p;
    }
    else{
        while(p != NULL){
            qDebug() <<(*p).datos<<"\n";
            p=p->siguiente;
        }
        delete p;
    }
}
