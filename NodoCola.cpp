#include "NodoCola.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

NodolistaC::~NodolistaC(){
    pNodocola aux;

   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   actual = NULL;
}

void NodolistaC::Insertar(NodoGrafo *ori, NodoAdyacente *ll, int pPeso){
   bool entro=false;
   if(ListaVacia()){
      qDebug()<<"entro a lista vacia";
      primero = new NodolistaC(ori, ll,peso);
   }
   else{
       if(pPeso < this->peso){
           qDebug() << "El peso A es: " << pPeso;
           qDebug() << "El peso B es: " << this->peso;
           qDebug()<<"entro a peso menor";
           primero = new NodolistaC(ori, ll, peso, primero);
       }
       else{
           qDebug() << "Entro a else 2";
           NodolistaC *aux = this->primero;
           while (aux->siguiente!=NULL){
               qDebug()<<"entro al while";
               if (aux->siguiente->peso >= peso){
                   NodolistaC *temp = new NodolistaC(ori,ll,peso);
                   temp->siguiente = aux->siguiente;
                   aux->siguiente = temp;
                   entro = true;
                   break;
               }
               aux = aux->siguiente;
           }

           if(!entro){
                qDebug()<<"entro a un not enter";
                aux->siguiente = new NodolistaC(ori,ll,peso);
           }
       }
   }

}

NodolistaC *NodolistaC::obtenerInicio(){
    return this->primero;
}

void NodolistaC::BorrarFinal(){
   if (ListaVacia()){
      cout<<"No hay elementos en la lista:"<<endl;
   }
   else{
      if (primero->siguiente == NULL) {
         primero= NULL;
      }
      else {
         NodolistaC *aux = primero;
         while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
         }
         NodolistaC *temp = aux->siguiente;
         aux->siguiente= NULL;
         delete temp;
         final=true;
      }
   }
}

void NodolistaC::eliminarCoincidencias(NodoAdyacente *adyacente){
    NodolistaC *aux = primero;
    int cont = 0;
    if(!ListaVacia()){
        while(aux){
            if(aux->llegada->NombrePais==adyacente->NombrePais){
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

void NodolistaC:: borrarPosicion(int pos){
     if(ListaVacia()){
        cout << "Lista vacia" <<endl;
    }
    else{
        if((pos>largoLista())||(pos<0)){
            cout << "Error en posicion" << endl;
        }else{
            if(pos==0){
            primero=primero->siguiente;
            }
            else{
                int cont=1;
                NodolistaC *aux=  primero;
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

int NodolistaC::largoLista(){
    int cont=0;

    NodolistaC *aux;
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

void NodolistaC::MostrarLista(){
    QFile archivo("Dijsktra.txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    NodolistaC *aux = primero;
    if(!ListaVacia()){
        while(aux){
            if(aux!=NULL){
                qDebug() << "\t\t" << aux->llegada->NombrePais << "(" << aux->peso << ")" << endl;
                out << "\t\t"<<aux->llegada->NombrePais<<"("<<aux->peso<<")"<<endl;
                aux = aux->siguiente;
            }
        }
   }
   cout<<endl;

   archivo.flush();
   archivo.close();
}
