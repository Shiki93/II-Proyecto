#include "Pila.h"
#include <QDebug>

//Inserta al final de la pila un elemento
void Pila::Push(int Elem){
    if(VaciaPila())
        PrimerNodo=UltimoNodo=new NodoPila(Elem);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodoPila(Elem);
}

//Elimina el ultimo elemento
void Pila::Pop(){
    if(VaciaPila())
        qDebug()<<"No hay elementos\n";
    else{
        if (PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodoPila *Actual=PrimerNodo;
            while (Actual->siguiente != UltimoNodo){
                Actual=Actual->siguiente;
            }
            delete UltimoNodo;
            UltimoNodo=Actual;
            UltimoNodo->siguiente = NULL;
            //Actual=Actual->siguiente;
            //delete Actual;
        }
    }
}

//Retorna el tope de la pila
int Pila::Tope(){
    if (UltimoNodo==NULL)
        return -1;
    else
        return (*UltimoNodo).datos;
}

//Imprime la lista
void Pila::Imprimir(){
    Pila temp;
    if(VaciaPila()){
        qDebug()<<"Pila Vacia\n";
    }
    else{
        while(!VaciaPila()){
            qDebug()<<Tope()<<" ";
            temp.Push(Tope());
            Pop();
        }
        while(!temp.VaciaPila()){
            Push(temp.Tope());
            temp.Pop();
        }
        qDebug()<<"\n";
    }
}
