#include "Lista.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

//Inserción al final de un elmento
void NodoLista::InsertarFinal(NodoGrafo *ori, NodoAdyacente *ll,int peso){
   if (ListaVacia()){
      primero = new NodoLista(ori,ll,peso);
   }
   else{
      NodoLista *aux = primero;
      while (aux->siguiente != NULL){
         aux = aux->siguiente;
      }
      aux->siguiente = new NodoLista(ori,ll,peso);
      aux->siguiente->anterior = aux;
   }
}

void NodoLista::InsertarFinal(NodoGrafo *val){
   if (ListaVacia()){
      primero = new NodoLista(val);
   }
   else{
       if(!estaElemento(val)){
            NodoLista *aux = primero;
            while (aux->siguiente != NULL){
                 aux = aux->siguiente;
            }
            aux->siguiente = new NodoLista(val);
            aux->siguiente->anterior = aux;
        }
   }
}

void NodoLista::InsertarFinal(QString cod){
   if (ListaVacia()){
      primero = new NodoLista(cod);
   }
   else{
        NodoLista *aux = primero;
        while (aux->siguiente != NULL){
                aux = aux->siguiente;
        }
        aux->siguiente = new NodoLista(cod);
        aux->siguiente->anterior = aux;
   }
}

//Sobrecarga de insertar se usa en la parte gráfica
void NodoLista::InsertarFinal(int v){
    if (ListaVacia()){
        primero = new NodoLista(v);
    }
    else{
        NodoLista *aux = primero;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = new NodoLista(v);
        aux->siguiente->anterior = aux;
    }
}

bool NodoLista::estaElemento(NodoGrafo *val){
    NodoLista *aux = primero;
    while(aux){
        if(aux->valor->Nombre==val->Nombre)
            return true;
        aux = aux->siguiente;

    }
    return false;
}

//Borra el último elemento de la lista enazada
void NodoLista::BorrarFinal(){
   if (ListaVacia()){
      qDebug()<<"No hay elementos en la lista:"<<endl;
   }
   else{
      if (primero->siguiente == NULL) {
         primero= NULL;
      }
      else {
         NodoLista *aux = primero;
         while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
         }
         NodoLista *temp = aux->siguiente;
         aux->siguiente= NULL;
         delete temp;
      }
   }
}

int NodoLista::largoLista(){
    int cont=0;

    NodoLista *aux;
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

//Muestra elcontenido de la lista enlazada
void NodoLista::MostrarLista(){
   QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Dijsktra.txt");
   if(!archivo.open(QFile::ReadWrite | QFile::Text)){
       return;
   }
   QTextStream out(&archivo);
   NodoLista *aux = primero;
   while(aux){
       qDebug() << aux->valor->Nombre << endl;
       out << aux->valor->Nombre << endl;
       aux = aux->siguiente;
   }
   qDebug() << endl;

   archivo.flush();
   archivo.close();
}

void NodoLista::MostrarCamino(NodoGrafo *val){
   NodoLista *aux = primero;
   NodoLista *aux2 = primero;
   QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Dijsktra.txt");
   if(!archivo.open(QFile::ReadWrite | QFile::Text)){
       return;
   }
   QTextStream out(&archivo);
   while(aux){
       if(aux->llegada->Nombre == val->Nombre){
           qDebug() << "Peso: " << aux->pesoAlmomento << endl;
           out << "Peso: " << aux->pesoAlmomento << endl;
           qDebug() << aux->llegada->Nombre << "-" << aux->origen->Nombre;
           out << aux->llegada->Nombre << "-" << aux->origen->Nombre;
           NodoLista *reversa = aux2;
           while(reversa->anterior != NULL){
               if(aux2->origen->Nombre == reversa->anterior->llegada->Nombre){
                   qDebug() << "-"<<reversa->anterior->origen->Nombre;
                   out << "-" << reversa->anterior->origen->Nombre;
                   aux2 = reversa->anterior;
               }
               reversa = reversa->anterior;

           }
       }
       aux = aux->siguiente;
       aux2 = aux2->siguiente;
   }

   out << endl;
   qDebug() << endl;

   archivo.flush();
   archivo.close();
}

bool NodoLista::buscarElemento(QString elem){
    NodoLista *aux = this->primero;
    while(aux){
        if(aux->codigo == elem){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}
