#include "ArbolNario.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//Constructor
NodosArbolNario::NodosArbolNario(){
    datos=0;
    num=0;
    bajo=0;
    padre=NULL;
    hijo=NULL;
    hermanoD=NULL;
    hermanoI=NULL;
}

//Constructor
NodosArbolNario::NodosArbolNario(int valor){
    datos=valor;
    padre=NULL;
    hijo=NULL;
    num=0;
    bajo=0;
    hermanoD=NULL;
    hermanoI=NULL;
}

//Inserta al inicio un elemento
void ArbolNario::Insertar(int Padre, int HijooHermano, int Valor){
    if(VacioArbol()){
        this->Raiz=new NodosArbolNario (Valor);
    }
    else{
        EncontrarElem(Padre);
        if(ElementoB == NULL){
        }
        else{
            NodosArbolNario *elementoBusqueda = ElementoB;
            if(HijooHermano == 1){
                if(elementoBusqueda->hermanoD != NULL){
                    NodosArbolNario *temp = elementoBusqueda->hermanoD;
                    elementoBusqueda->hermanoD = new NodosArbolNario(Valor);
                    elementoBusqueda->hermanoD->hermanoI = elementoBusqueda;
                    elementoBusqueda->hermanoD->hermanoD = temp;
                    temp->hermanoI = elementoBusqueda->hermanoD;
                    temp = NULL;
                    delete temp;
                }
                else{
                    elementoBusqueda->hermanoD=new NodosArbolNario (Valor);
                    elementoBusqueda->hermanoD->hermanoI=elementoBusqueda;
                }
                if(ElementoB->padre!=NULL){
                    elementoBusqueda->hermanoD->padre=ElementoB->padre;
                }
            }
            else{
                if(elementoBusqueda->hijo!=NULL){
                    elementoBusqueda=elementoBusqueda->hijo;
                    while(elementoBusqueda->hermanoD!=NULL){
                        elementoBusqueda=elementoBusqueda->hermanoD;
                    }
                    elementoBusqueda->hermanoD=new NodosArbolNario (Valor);
                    elementoBusqueda->hermanoD->padre=ElementoB;
                    elementoBusqueda->hermanoD->hermanoI=elementoBusqueda;
                }
                else{
                    elementoBusqueda->hijo=new NodosArbolNario (Valor);
                    elementoBusqueda->hijo->padre=ElementoB;
                }
            }
            elementoBusqueda=NULL;
            delete elementoBusqueda;
        }
        ElementoB=NULL;
        delete ElementoB;
    }
}

//Retorna el nodo donde esta el elemento (aux)
void ArbolNario::EncontrarElemaux(NodosArbolNario *raizaux,int elem){
    if(raizaux==NULL){
        return;
    }
    else{
        if(enco==false){
            if(elem == raizaux->datos){
                ElementoB=raizaux;
                enco=true;
                return;
            }
            else{
                EncontrarElemaux(raizaux->hermanoD,elem);
                EncontrarElemaux(raizaux->hijo,elem);
            }
        }
        else{
            return;
        }
    }
}

//Retorna si un valor es hijo de un nodo
bool ArbolNario::EsHijo(int a,NodosArbolNario *nodo){
    NodosArbolNario *h;
    //Corrobora que nodo no tenga como hijo a a
    for(h=nodo->hijo;h!=NULL;h=h->hermanoD){
        if(h->datos==a){
            h=NULL;
            delete h;
            return true;
        }
    }
    //Corrobora que a no tenga como hijo a nodo
    EncontrarElem(a);
    for(h=ElementoB->hijo;h!=NULL;h=h->hermanoD){
        if(h->datos==nodo->datos){
            h=NULL;
            delete h;
            return true;
        }
    }
    h=NULL;
    delete h;
    return false;
}

//Retorna el nodo donde esta el elemento
void ArbolNario::EncontrarElem(int elem){
    enco=false;
    ElementoB=NULL;
    EncontrarElemaux(Raiz,elem);
    enco=false;
}

//Inserta la arista de retroceso
void ArbolNario::insertarAR(int a,int b){
    EncontrarElem(a);
    ElementoB->ListaAR.InsertaFinal(b);
}

//Imprime el arbol por referencia del hermano
void ArbolNario::ImprimirRefHermano(){
    if(VacioArbol())
            qDebug()<<"No hay elementos\n";
        else{
            qDebug()<<"Arbol por Ref Hermano es: ";
            ImprimirRefHermanoaux(Raiz);
            qDebug()<<"\n";
    }
}

//Imprime el arbol por referencia del hermano (aux)
void ArbolNario::ImprimirRefHermanoaux(NodosArbolNario *raizaux){
    if(raizaux==NULL){
        return;
    }
    else{
        ImprimirRefHermanoaux(raizaux->hermanoD);
        if(raizaux->hermanoD!=NULL || raizaux->hermanoI!=NULL)
            qDebug()<<raizaux->datos<<" ";
        ImprimirRefHermanoaux(raizaux->hijo);
    }
}

//Imprime el arbol por referencia del padre
void ArbolNario::ImprimirRefPadre(){
    if(VacioArbol()){
        qDebug()<<"No hay elementos\n";
        return;
    }
    else{
        qDebug()<<"Arbol por Ref Padre es: ";
        ImprimirRefPadreaux(Raiz);
        qDebug()<<"\n";
    }
}

//Imprime el arbol por referencia del padre (aux)
void ArbolNario::ImprimirRefPadreaux(NodosArbolNario *raizaux){
    if(raizaux==NULL){
        return;
    }
    else{
        if(raizaux->hijo!=NULL){
            qDebug()<<raizaux->datos<<" ";
        }
        ImprimirRefPadreaux(raizaux->hijo);
        ImprimirRefPadreaux(raizaux->hermanoD);
    }
}

//Imprime el arbol en preorden
void ArbolNario::Preorden(int nodo){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/PreOrden.txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(VacioArbol())
        qDebug()<<"No hay elementos\n";
    else{
        qDebug()<<"Recorrido en Preorden: "<<endl;
        out<<"Recorrido en Preorden: "<<endl;
        Preordenaux(Raiz,nodo);
        va=1;
        out<<endl;
        qDebug()<<endl;
    }
    archivo.flush();
    archivo.close();
}

//Retorna el nivel de insercion (
//entre mas bajo mayor prioridad a la hora de insercion de las aristas de retroceso
int ArbolNario::Nivel(int cod){
    niv=1;
    Nivelaux(Raiz,cod);
    va=1;
    enco=false;
    return niv;
}

//Retorna el nivel del nodo
void ArbolNario::Nivelaux(NodosArbolNario *raizaux,int cod){
    if(raizaux==NULL){
        return;
    }
    else{
        if(enco!=true){
            if(raizaux->datos==cod){
                niv=va;
                enco=true;
                return;
            }
            else{
                va++;
                Nivelaux(raizaux->hijo,cod);
                Nivelaux(raizaux->hermanoD,cod);
            }
        }
    }
}

//Preorden (aux)
void ArbolNario::Preordenaux(NodosArbolNario *raizaux,int nodo){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/PreOrden.txt");
    if(!archivo.open(QFile::ReadWrite | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(raizaux==NULL){
        return;
    }
    else{
        QString x = out.readAll();
        out << x;
        qDebug() << raizaux->datos << ":" << endl;
        out << raizaux->datos << ":" << endl;
        //Imprime las aristas de retroceso
        raizaux->ListaAR.ImprimirAR();
        qDebug() << endl;
        out<<endl;
        raizaux->num=va;
        raizaux->bajo=va;
        va++;
        Preordenaux(raizaux->hijo,nodo);
        Preordenaux(raizaux->hermanoD,nodo);
    }
    archivo.flush();
    archivo.close();
}

//Imprime el arbol desde un punto de incio sin contar el hermano de la raiz
void ArbolNario::ImprimirAdesdeVertice(NodosArbolNario *raizaux,NodosArbolNario *rai){
    if(raizaux==NULL){
        return;
    }
    else{
        qDebug()<<raizaux->datos<<" ";
        if(raizaux->datos==rai->datos){
            ImprimirAdesdeVertice(raizaux->hijo,rai);
        }
        else{
            ImprimirAdesdeVertice(raizaux->hijo,rai);
            ImprimirAdesdeVertice(raizaux->hermanoD,rai);
        }
    }
}

//Recorre el arbol en postOrden para poner los bajos
void ArbolNario::PostOrdenAR(){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/PostOrden.txt");
    if(!archivo.open(QFile::ReadWrite | archivo.Text)){
        return;
    }
    QTextStream out(&archivo);
    out << "Recorrido PostOrden" << endl;
    PostOrdenARaux(Raiz);
}

//Recorre el arbol en postOrden para poner los bajos
void ArbolNario::PostOrdenARaux(NodosArbolNario *raizaux){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/PostOrden.txt");
    if(!archivo.open(QFile::ReadWrite | archivo.Text)){
        return;
    }
    QTextStream out(&archivo);
    QString x = out.readAll();
    out << x << endl;
    if(raizaux == NULL){
        return;
    }
    else{
        qDebug() << raizaux->datos << ":" << endl;
        out << raizaux->datos << ":" << endl;
        PostOrdenARaux(raizaux->hijo);
        PostOrdenARaux(raizaux->hermanoD);
        //Calcula el bajo del nodo
        int minAR = -1, minHijos = -1, mini;
        //Obtiene el menor bajo de las aristas de retroceso
        if(raizaux->ListaAR.PrimerNodo != NULL){
            NodoListaInt *pde = raizaux->ListaAR.PrimerNodo;
            EncontrarElem(pde->arr);
            minAR = ElementoB->bajo;
            for(pde = raizaux->ListaAR.PrimerNodo->siguiente; pde != NULL; pde = pde->siguiente){
                EncontrarElem(pde->arr);
                if(ElementoB->bajo < minAR)
                    minAR = ElementoB->bajo;
            }
            pde = NULL;
            delete pde;
        }
        //Obtiene el menor bajo de los hijos
        if(raizaux->hijo!=NULL){
            NodosArbolNario *ps=raizaux->hijo;
            minHijos=ps->bajo;
            for(ps=raizaux->hijo->hermanoD;ps!=NULL;ps=ps->hermanoD){
                if(ps->bajo<minHijos)
                    minHijos=ps->bajo;
            }
            ps=NULL;
            delete ps;
        }

        //Por si no tiene hijos ni aristas
        if(minAR==-1)
            minAR=999;
        if(minHijos==-1)
            minHijos=999;

        //Obtiene el menor bajo entre los hijos, las aristas de retroceso y el mismo
        if(minAR<minHijos)
            mini=minAR;
        else
            mini=minHijos;

        if(mini<raizaux->bajo)
            raizaux->bajo=mini;
    }
}

//Compara los nums y bajos
void ArbolNario::EsPuntoArticulacion(int nodo){
    QFile archivo("Puntos de articulacion"+QString::number(nodo)+".txt");
    if(archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    int isf;
    qDebug()<<"\tHijo\tBH\t>=\tNP\tEs Punto?\n";
    out<<"\tHijo\tBH\t>=\tNP\tEs Punto?"<<endl;
    tienepts=false;
    //resetea el vector de puntos
    for(isf=0;matpts[isf]!="";isf++){
        matpts[isf]="";
    }
    EsPuntoArticulacionaux(Raiz,nodo);
    if(tienepts==false){
        qDebug()<<"\nGrafo Biconexo\n";
        out<<endl<<"Grafo Biconexo"<<endl;
    }
    else{
        qDebug()<<"\nPuntos Art: ";
        out<<endl<<"Puntos Art: ";
        for(isf=0;matpts[isf]!="";isf++){
            qDebug() << matpts[isf] << "-";
            out << matpts[isf] << "-";
        }
        qDebug()<<endl;
    }
    archivo.flush();
    archivo.close();
}

//Compara los nums y bajos
void ArbolNario::EsPuntoArticulacionaux(NodosArbolNario *raizaux,int nodo){
    QFile archivo("Puntos de articulacion"+QString::number(nodo)+".txt");
    if(archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(raizaux==NULL){
        return;
    }
    else{
        if(raizaux->datos==Raiz->datos){
            qDebug()<<Raiz->datos<<"\t\t-\t\t-\tExcepcion\n";
            qDebug()<<"-----------------------------------------------------\n";
            out<<Raiz->datos<<"\t\t-\t\t-\tExcepcion"<<endl;
            out<<"-----------------------------------------------------"<<endl;
        }
        else{
            NodosArbolNario *pas=raizaux->hijo;
            if(pas==NULL){
                qDebug()<<raizaux->datos<<"\t\t-\t\t-\tNo -sin hijos\n";
                qDebug()<<"-----------------------------------------------------\n";
                out<<raizaux->datos<<"\t\t-\t\t-\tNo -sin hijos"<<endl;
                out<<"-----------------------------------------------------"<<endl;
            }
            else{
                bool tien=false;
                qDebug()<<raizaux->datos;
                out<<raizaux->datos;
                for(pas=raizaux->hijo;pas!=NULL;pas=pas->hermanoD){
                    if(pas->bajo>=raizaux->num){
                        tienepts=true;
                        tien=true;
                        matpts[ia]=raizaux->datos;
                        qDebug()<<"\t"<<pas->datos<<"\t"<<pas->bajo<<"\t\t"<<raizaux->num<<"\tSI\n";
                        out<<"\t"<<pas->datos<<"\t"<<pas->bajo<<"\t\t"<<raizaux->num<<"\tSI"<<endl;
                    }
                    else{
                        qDebug()<<"\t"<<pas->datos<<"\t"<<pas->bajo<<"\t\t"<<raizaux->num<<"\tNo\n";
                        out<<"\t"<<pas->datos<<"\t"<<pas->bajo<<"\t\t"<<raizaux->num<<"\tNo"<<endl;
                    }
                }
                if(tien)
                    ia++;
                qDebug()<<"-----------------------------------------------------"<<endl;
                out<<"-----------------------------------------------------"<<endl;
            }
            pas=NULL;
            delete pas;
        }
        EsPuntoArticulacionaux(raizaux->hijo,nodo);
        EsPuntoArticulacionaux(raizaux->hermanoD,nodo);
    }
    archivo.flush();
    archivo.close();
}


