#include "pila.h"
using namespace std;



//Inserta al final de la pila un elemento
void Pila::Push(int Elem){
    if(VaciaPila())
        PrimerNodo=UltimoNodo=new NodosPila(Elem);
    else
        UltimoNodo=(*UltimoNodo).siguiente=new NodosPila(Elem);
}
//Elimina el ultimo elemento
void Pila::Pop(){
    if(VaciaPila())
        cout <<"No hay elementos\n";
    else{
        if (PrimerNodo == UltimoNodo)
            PrimerNodo=UltimoNodo=NULL;
        else{
            NodosPila *Actual=PrimerNodo;
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
        cout<<"Pila Vacia\n";
    }
    else{
        while(!VaciaPila()){
            cout<<Tope()<<" ";
            temp.Push(Tope());
            Pop();
        }
        while(!temp.VaciaPila()){
            Push(temp.Tope());
            temp.Pop();
        }
        cout<<"\n";
    }
}

