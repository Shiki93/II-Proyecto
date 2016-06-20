#include "Lista.h"
#include <QDebug>

//Métodos de clase Nodolista
//Inserción al final de un elmento

void NodolistaCiudades::InsertarFinal(QString cod, QString nombre){
   if (ListaVacia()){
      primero = new NodolistaCiudades(cod,nombre);
   }
   else{
        NodolistaCiudades *aux = primero;
        while (aux->siguiente != NULL){
                aux = aux->siguiente;
        }
        aux->siguiente = new NodolistaCiudades(cod,nombre);
        aux->siguiente->anterior = aux;
   }
}

//Sobrecarga de insertar se usa en la parte gráfica
void NodolistaCiudades::InsertarFinal(int v){
    if (ListaVacia()){
        primero = new NodolistaCiudades(v);
    }
    else{
        NodolistaCiudades *aux = primero;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = new NodolistaCiudades(v);
        aux->siguiente->anterior = aux;
    }
}
//Borra el último elemento de la lista enazada
void NodolistaCiudades::BorrarFinal(){
   if (ListaVacia()){
      qDebug()<<"No hay elementos en la lista:"<<endl;
   }
   else{
      if (primero->siguiente == NULL) {
         primero= NULL;
      }
      else {
         NodolistaCiudades *aux = primero;
         while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
         }
         NodolistaCiudades *temp = aux->siguiente;
         aux->siguiente= NULL;
         delete temp;
      }
   }
}

int NodolistaCiudades::largoLista(){
    int cont=0;

    NodolistaCiudades *aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }

}

void NodolistaCiudades::Mostrar(){
    pNodolistaCiudades aux = primero;
    while(aux){
        qDebug()<<aux->v;
        aux = aux->siguiente;
    }
}
