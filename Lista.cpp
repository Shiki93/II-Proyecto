#include "Lista.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

//Métodos de clase Nodolista
//Inserción al final de un elmento
void Nodolista::InsertarFinal(NodoGrafo *ori, NodoAdyacente *ll,int peso){
   if (ListaVacia()){
      primero = new Nodolista(ori,ll,peso);
   }
   else{
      Nodolista *aux = primero;
      while (aux->siguiente != NULL){
         aux = aux->siguiente;
      }
      aux->siguiente = new Nodolista(ori,ll,peso);
      aux->siguiente->anterior = aux;
   }
}

void Nodolista::InsertarFinal(NodoGrafo *val){
   if (ListaVacia()){
      primero = new Nodolista(val);
   }
   else{
       if(!estaElemento(val)){
            Nodolista *aux = primero;
            while (aux->siguiente != NULL){
                 aux = aux->siguiente;
            }
            aux->siguiente = new Nodolista(val);
            aux->siguiente->anterior = aux;
        }
   }
}

void Nodolista::InsertarFinal(QString cod){
   if (ListaVacia()){
      primero = new Nodolista(cod);
   }
   else{
        Nodolista *aux = primero;
        while (aux->siguiente != NULL){
                aux = aux->siguiente;
        }
        aux->siguiente = new Nodolista(cod);
        aux->siguiente->anterior = aux;
   }
}

//Sobrecarga de insertar se usa en la parte gráfica
void Nodolista::InsertarFinal(int v){
    if (ListaVacia()){
        primero = new Nodolista(v);
    }
    else{
        Nodolista *aux = primero;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = new Nodolista(v);
        aux->siguiente->anterior = aux;
    }
}

bool Nodolista::estaElemento(NodoGrafo *val){
    Nodolista *aux = primero;
    while(aux){
        if(aux->valor->NombrePais==val->NombrePais)
            return true;
        aux = aux->siguiente;

    }
    return false;

}
//Borra el último elemento de la lista enazada
void Nodolista::BorrarFinal(){
   if (ListaVacia()){
      cout<<"No hay elementos en la lista:"<<endl;
   }
   else{
      if (primero->siguiente == NULL) {
         primero= NULL;
      }
      else {
         Nodolista *aux = primero;
         while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
         }
         Nodolista *temp = aux->siguiente;
         aux->siguiente= NULL;
         delete temp;
      }
   }
}

int Nodolista::largoLista(){
    int cont=0;

    Nodolista *aux;
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
void Nodolista::MostrarLista(){
   QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Dijsktra.txt");
   if(!archivo.open(QFile::ReadWrite | QFile::Text)){
       return;
   }
   QTextStream out(&archivo);
   Nodolista *aux = primero;
   while(aux){
       qDebug() << aux->valor->NombrePais << endl;
       out << aux->valor->NombrePais << endl;
       aux = aux->siguiente;
   }
   cout << endl;

   archivo.flush();
   archivo.close();
}

void Nodolista::MostrarCamino(NodoGrafo *val){
   Nodolista *aux = primero;
   Nodolista *aux2 = primero;
   QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Dijsktra.txt");
   if(!archivo.open(QFile::ReadWrite | QFile::Text)){
       return;
   }
   QTextStream out(&archivo);
   while(aux){
       if(aux->llegada->NombrePais == val->NombrePais){
           qDebug() << "Peso: " << aux->pesoAlmomento << endl;
           out << "Peso: " << aux->pesoAlmomento << endl;
           qDebug() << aux->llegada->NombrePais << "-" << aux->origen->NombrePais;
           out << aux->llegada->NombrePais << "-" << aux->origen->NombrePais;
           Nodolista *reversa = aux2;
           while(reversa->anterior != NULL){
               if(aux2->origen->NombrePais == reversa->anterior->llegada->NombrePais){
                   qDebug() << "-"<<reversa->anterior->origen->NombrePais;
                   out << "-" << reversa->anterior->origen->NombrePais;
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

bool Nodolista::buscarElemento(QString elem){
    Nodolista *aux = this->primero;
    while(aux){
        if(aux->codigo == elem){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}
