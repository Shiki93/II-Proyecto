#include "NodoCola.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

NodoCola::~NodoCola(){
    pNodocola aux;

   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   actual = NULL;
}

void NodoCola::Insertar(NodoGrafo *ori, NodoAdyacente *ll, int pPeso){
   bool entro=false;
   if(ListaVacia()){
      primero = new NodoCola(ori, ll,peso);
   }
   else{
       if(pPeso < this->peso){
           primero = new NodoCola(ori, ll, peso, primero);
       }
       else{
           NodoCola *aux = this->primero;
           while (aux->siguiente!=NULL){
               if (aux->siguiente->peso >= peso){
                   NodoCola *temp = new NodoCola(ori,ll,peso);
                   temp->siguiente = aux->siguiente;
                   aux->siguiente = temp;
                   entro = true;
                   break;
               }
               aux = aux->siguiente;
           }

           if(!entro){
                aux->siguiente = new NodoCola(ori,ll,peso);
           }
       }
   }

}

NodoCola *NodoCola::obtenerInicio(){
    return this->primero;
}

void NodoCola::BorrarFinal(){
   if (ListaVacia()){
      qDebug()<<"No hay elementos en la lista:"<<endl;
   }
   else{
      if (primero->siguiente == NULL) {
         primero= NULL;
      }
      else {
         NodoCola *aux = primero;
         while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
         }
         NodoCola *temp = aux->siguiente;
         aux->siguiente= NULL;
         delete temp;
         final=true;
      }
   }
}

void NodoCola::eliminarCoincidencias(NodoAdyacente *adyacente){
    NodoCola *aux = primero;
    int cont = 0;
    if(!ListaVacia()){
        while(aux){
            if(aux->llegada->Nombre==adyacente->Nombre){
                borrarPosicion(cont);
            }
            if(!final){
                aux=aux->siguiente;
                cont++;
            }
            else{
                break;
            }
        }
    }
}

void NodoCola:: borrarPosicion(int pos){
     if(ListaVacia()){
         qDebug() << "Lista vacia" << endl;
    }
    else{
         if((pos > largoLista()) || (pos < 0)){
             qDebug() << "Error en posicion" << endl;
         }
         else{
             if(pos==0){
                 primero = primero->siguiente;
             }
             else{
                 int cont = 1;
                 NodoCola *aux=  primero;
                while(cont<pos){
                    aux=aux->siguiente;
                    cont++;
                }
                if(aux->siguiente!=NULL){
                    aux->siguiente=aux->siguiente->siguiente;
                }
                else{
                    BorrarFinal();
                }
            }
        }
     }

}

int NodoCola::largoLista(){
    int cont = 0;
    NodoCola *aux = this->primero;
    if(ListaVacia()){
        return cont;
    }
    else{
        while(aux != NULL){
            cont++;
            aux = aux->siguiente;
        }
        return cont;
    }
}

void NodoCola::MostrarLista(){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Dijsktra.txt");
    if(!archivo.open(QFile::ReadWrite | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    QString a = out.readAll();
    qDebug() << "\nAqui Inicio A\n";
    qDebug() << a;
    NodoCola *aux = primero;
    if(!ListaVacia()){
        while(aux != NULL){
            qDebug() << "\t\t" << aux->llegada->Nombre << "(" << aux->peso << ")" << endl;
            out << "\t\t"<<aux->llegada->Nombre<<"("<<aux->peso<<")"<<endl;
            aux = aux->siguiente;
        }
    }
    qDebug() << endl;

    archivo.flush();
    archivo.close();
}
