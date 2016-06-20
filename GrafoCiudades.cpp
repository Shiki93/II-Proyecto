#define _CRT_SECURE_NO_WARNINGS
#include "GrafoCiudades.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//Constructores inicial
NodoAdyacenteC::NodoAdyacenteC(){
    Cod=0;
    peso=0;
    pos=0;
    siguiente_ady=NULL;
}

//Constructor para nodos
NodoAdyacenteC::NodoAdyacenteC(int co,int pe,int po,QString nombre){
    Cod=co;
    peso=pe;
    pos=po;
    NombreCiudad = nombre;
    siguiente_ady=NULL;
}
//Constructores inicial
NodoGrafoC::NodoGrafoC(){
    CodVerticeGP=0;
    Tipo=0;
    /*Costo_pasaje=0;
    Costo_salida=0;*/
    pos=0;
    sig_vertice=NULL;
    siguiente_ady=NULL;
}


//Constructor para ciudades
NodoGrafoC::NodoGrafoC(int cod, QString nombre,int posi){
    CodVerticeGP = cod;
    NombreCiudad = nombre;
    pos=posi;
    sig_vertice=NULL;
    siguiente_ady=NULL;
}


//cargar ciudades
bool GrafoCiudades::CargarCiudades(){
    char buffer[100]="";
    char *pch;
    int Cod;
    QString Nom;
    ifstream encabezados ("VerticesGP.txt");
    if(!encabezados.is_open()){
        qDebug() << "Error archivo Paises no existe\n";
        return true;
    }
    else{
        while(!encabezados.eof()){
            encabezados.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,"; ");
                Cod = atoi(pch);
                pch = strtok (NULL, ";");
                Nom = pch;
                InsertaVertices(Cod,Nom);
            }
        }
    }
    pch=NULL;
    delete pch;
    return false;
}

//Carga las aristas
bool GrafoCiudades::CargarAristasGP(int cod){
    char buffer[100]="";
    char *pch;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("AristasGP.txt");
    if(!encabezados.is_open()){
        qDebug() << "Error archivo Aristas no existe\n";
        return true;
    }
    else{
        while(!encabezados.eof()){
            encabezados.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,";");
                if(cod == atoi(pch));{
                    pch = strtok (buffer,";");
                    codp=atoi(pch);
                    pch = strtok (NULL, ";");
                    codl=atoi(pch);
                    pch = strtok (NULL, ";");
                    peso=atoi(pch);
                    InsertaAristas(codp,codl,peso);
                }
            }
        }
    }
    pch=NULL;
    delete pch;
    return false;
}

//Inserta un elemento en el grafo al inicio (para pais)
void GrafoCiudades::InsertaVertices(int cod, QString nombre){
    if(VacioGrafo())
        PrimerNodo=UltimoNodo=new NodoGrafoC (cod,nombre,cant);
    else{
        UltimoNodo=UltimoNodo->sig_vertice=new NodoGrafoC(cod, nombre,cant);
    }
    cant++;
}


//Inserta un nodo adyacente a final del vertice
void GrafoCiudades::InsertaAristas(int CodP,int CodL,int Peso){
    if(VacioGrafo())
        qDebug()<<"No hay Vertices\n";
    else{
        EncontrarNodo(CodP);
        NodoGrafoC *p=Elemento;
        if(p!=NULL){
            EncontrarNodo(CodL);
            NodoGrafoC *j=Elemento;
            if(j!=NULL){
                if(p->siguiente_ady==NULL){
                    p->siguiente_ady=new NodoAdyacenteC(CodL,Peso,j->pos,j->NombreCiudad);
                }
                else{
                    NodoAdyacenteC *temp=p->siguiente_ady;
                    while(temp->siguiente_ady!=NULL){
                        temp=temp->siguiente_ady;
                    }
                    temp->siguiente_ady=new NodoAdyacenteC(CodL,Peso,j->pos,j->NombreCiudad);
                    temp=NULL;
                    delete temp;
                }
            }
            else{
                qDebug()<<"No se encontro punto de llegada\n";
            }
            j=NULL;
            delete j;
        }
        else{
            qDebug()<<"No se encontro punto de partida\n";
        }
        Elemento=NULL;
        p=NULL;
        delete p;
    }
}

//Carga la lista de listas
void GrafoCiudades::CrearGrafo(int cod){
    bool a,b,c;
    a=CargarCiudades();
    //b=CargarAeropuertos();
    if(!a){//&!b){
        c=CargarAristasGP(cod);
        if(!c){
            CrearMatrizAdyacencia();
            qDebug()<<"Grafo creado\n";
        }
    }
}

//Crear la matriz de adyacencia
void GrafoCiudades::CrearMatrizAdyacencia(){
    NodoGrafoC *p=PrimerNodo;
    NodoAdyacenteC *temp;
    if(p!=NULL){
        int i;
        for(i=0;i<cant;i++){
            temp=p->siguiente_ady;
            while(temp!=NULL){
                mat[i][temp->pos]=1;
                temp=temp->siguiente_ady;
            }
            p=p->sig_vertice;
        }
    }
    temp=NULL;
    p=NULL;
    delete temp;
    delete p;
}

//Imprime el grafo
void GrafoCiudades::ImprimirGrafo(){
    NodoGrafoC *p=PrimerNodo;
    NodoAdyacenteC *temp;
    if(PrimerNodo==NULL){
        qDebug()<<"Grafo Vacio\n";
    }
    else{
        while(p!=NULL){
            qDebug() << p->NombreCiudad;
            qDebug() << ": ";
            temp = p->siguiente_ady;
            while(temp != NULL){
                qDebug() << "--> " << temp->NombreCiudad << "(" << temp->peso << ") ";
                temp = temp->siguiente_ady;
            }
            qDebug() << "\n";
            p = p->sig_vertice;
        }
    }
    temp=NULL;
    p=NULL;
    delete temp;
    delete p;
}

//Imprime la matriz
void GrafoCiudades::ImprimirMatriz(int D[TamArr][TamArr]){
    if(!VacioGrafo()){
        NodoGrafoC *p;
        int i,j;
        //Imprime los encabezados de la tabla
        qDebug() << "\t";
        for(p=PrimerNodo;p!=NULL;p=p->sig_vertice)
            qDebug() << p->NombreCiudad << "\t";
        qDebug() << endl;
        p = PrimerNodo;
        //ciclo de impresion de valores
        for(j = 0; j < cant; j++){
            qDebug() << p->NombreCiudad << "\t";
            for(i=0;i<cant;i++){
                if(D[j][i]==INF)
                    qDebug() << "INF\t";
                else
                    qDebug() << D[j][i] << "\t";
            }
            qDebug() << endl;
            p = p->sig_vertice;
        }
        p = NULL;
        delete p;
    }
    else
        qDebug() << "Grafo Vacio\n";
}

//Recorre el grafo en profundidad
void GrafoCiudades::RecorridoProfundidad(int cod,int nodo){
    QFile archivo("ProdundidadCiudades"+QString::number(nodo)+".txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        NodoGrafoC *a;
        NodoAdyacenteC *t;
        Pila pil;
        qDebug() << "Recorrido en Profundidad: \n";
        out<<"Recorrido en Profundidad: "<<endl;
        //Resetea la matriz matVisitas
        int k, e, i;
        for (k = 0; k < cant; k++)
            matVisitas[k]=0;

        EncontrarNodo(cod);
        if(Elemento != NULL){
            e = Elemento->pos;
            for(i = 0; i < 2; i++){
                for(k = e; k < cant; k++){
                    if (matVisitas[k] == 0){
                        matVisitas[k] = 1;
                        pil.Push(k);
                        while(!pil.VaciaPila()){
                            BuscarVerticePos(pil.Tope());
                            qDebug()<<Elemento->NombreCiudad<<"-";
                            out<<Elemento->NombreCiudad<<"-";
                            pil.Pop();
                            a=Elemento;
                            //apila los adyacentes no visitados
                            for (t = a->siguiente_ady; t != NULL; t = t->siguiente_ady){
                                if (matVisitas[t->pos] == 0){
                                    pil.Push(t->pos);
                                    matVisitas[t->pos]=1;
                                }
                            }
                        }
                    }
                }
                e = 0;
            }

        }
        else{
            qDebug()<<"Elemento no encontrado";
        }
        qDebug()<<endl;
        a=NULL;
        delete a;
        t=NULL;
        delete t;
    }
    else
        qDebug()<<"Grafo Vacio\n";

    archivo.flush();
    archivo.close();
}

//Recorre el grafo en anchura
void GrafoCiudades::RecorridoAnchura(int cod,int nodo){
    if(!VacioGrafo()){
        NodoGrafoC *a;
        NodoAdyacenteC *t;
        Cola col;
        QFile archivo("AnchuraCiudades"+QString::number(nodo)+".txt");
        if(!archivo.open(QFile::WriteOnly | QFile::Text)){
            return;
        }
        QTextStream out(&archivo);
        //Resetea el la matriz matVisitas
        qDebug()<<"Recorrido en Anchura: "<<endl;
        out<<"Recorrido en Anchura: "<<endl;
        int k,e,i;
        for (k=0; k<cant; k++)
            matVisitas[k]=0;

        EncontrarNodo(cod);
        if(Elemento!=NULL){
            e=Elemento->pos;
            for(i=0;i<2;i++){
                for (k=e; k<cant; k++){
                    if (matVisitas[k]==0){
                        matVisitas[k]=1;
                        col.Encolar(k);
                        while(!col.VaciaCola()){
                            BuscarVerticePos(col.Frente());
                            qDebug() << Elemento->NombreCiudad << "-";
                            out<<Elemento->NombreCiudad<<"-";
                            col.Desencolar();
                            a=Elemento;
                            //encola los adyacentes no visitados
                            for (t=a->siguiente_ady; t!=NULL; t=t->siguiente_ady){
                                if (matVisitas[t->pos]==0){
                                    col.Encolar(t->pos);
                                    matVisitas[t->pos]=1;
                                }
                            }
                        }
                    }
                }
                e=0;
            }
        }
        else{
            qDebug()<<"Elemento no encontrado";
        }
        qDebug()<<endl;
        a=NULL;
        delete a;
        t=NULL;
        delete t;

        archivo.flush();
        archivo.close();

    }
    else
        qDebug()<<"Grafo Vacio\n";
}
int GrafoCiudades::tamano(){
    int cont=0;
    NodoGrafoC *nodo = PrimerNodo;
    while(nodo!=NULL){
        cont++;
        nodo = nodo->sig_vertice;
    }
    return cont;
}
//Encuentra al nodo de origen y retorna dicho nodo
pnodografoC GrafoCiudades::BuscarVerticepos(int vas){
    //pnodografo h;
    if(VacioGrafo()){
        return NULL;
    }
    else{
        bool enc=false;
        NodoGrafoC *p=PrimerNodo;
        while(p!=NULL & enc==false){
            if(p->CodVerticeGP == vas){
                return p;
                //enc=true;
            }
            else{
                p=p->sig_vertice;
            }
        }
        return NULL;
    }
}
//Algoritmo de Prim
void GrafoCiudades::Prim(int cod,int nodo){
    QFile archivo("PrimCiudades"+QString::number(nodo)+".txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        EncontrarNodo(cod);
        if(Elemento!=NULL){
            int i,j,z,e,min,Coste[TamArr],Mas_cerca[TamArr],Con[TamArr],VectMc[TamArr];
            long ct;
            e=Elemento->pos;
            CrearMatrizValoradaNoDirigida();
            qDebug()<<"Algoritmo de Prim: "<<endl;
            out<<"Algoritmo de Prim: "<<endl;
            //Inicializa el vector de conjuntos
            for(i=0;i<cant;i++){
                Con[i]=0;
                VectMc[i]=0;
            }
            ct=0;
            //Visita el primer vertice
            Con[e]=1;
            //Carga los pesos del primer vector en el vector de comparacion
            for (i=0;i<cant;i++){
                if(i!=e){
                    Coste[i]=matTemporal[e][i];
                    Mas_cerca[i]=e;
                }
            }
            qDebug() << "Aristas seleccionadas: " << endl;
            out << "Aristas seleccionadas: " << endl;
            for(i=0;i<cant;i++){
                if(i!=e){
                    min=Coste[e+1];
                    z=e+1;
                    //busca el menor de los pesos
                    for(j=0;j<cant;j++){
                        if(j!=e & j!=e+1){
                            if(Coste[j]<min){
                                min=Coste[j];
                                z=j;
                            }
                        }
                    }
                    if(min!=INF){
                        VectMc[i]=min;
                        //suma el peso
                        ct=ct+min;
                        //marca el valor para no repetirlo
                        //Imprime la arista que selecciono como minima
                        BuscarVerticePos(z);
                        qDebug() << Elemento->NombreCiudad << " -> ";
                        out << Elemento->NombreCiudad << " -> ";
                        BuscarVerticePos(Mas_cerca[z]);
                        qDebug() << Elemento->NombreCiudad << endl;
                        out<<Elemento->NombreCiudad<<endl;
                        //lo marca como inf para no tomarlo en cuenta
                        Coste[z]=INF;
                    }
                    Con[z]=1;
                    //verifica ciclos
                    for(j=0;j<cant;j++){
                        if(j!=e){
                            if(matTemporal[z][j]<Coste[j] & Con[j]==0){
                                Coste[j]=matTemporal[z][j];
                                Mas_cerca[j]=z;
                            }
                        }
                    }
                }
            }
            qDebug()<<endl<<"Pesos: "<<endl;
            out<<endl<<"Pesos: "<<endl;
            qDebug()<<"{ ";
            out<<"{ ";
            for(i=0;i<cant;i++){
                if(VectMc[i]!=0){
                    qDebug()<<VectMc[i]<<" ";
                    out<<VectMc[i]<<" ";
                }

            }
            qDebug()<<"}"<<endl;
            out<<"}"<<endl;
            qDebug()<<endl<<"El costo es: "<<ct<<endl;
            out<<endl<<"El costo es: "<<ct<<endl;
        }
    }
    else
        qDebug()<<"Grafo Vacio\n";

    archivo.flush();
    archivo.close();
}

//Algoritmo de kruskal
void GrafoCiudades::Kruskal(int nodo){
    QFile archivo("KruskalCiudades"+QString::number(nodo)+".txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        int i,j,ct;
        //Ordena las aristas en orden ascendente y se las sede a listaOr
        ListaSimple listaOr = OrdenarAristas();
        NodosLista *imp;
        qDebug()<<"Algoritmo de Kruskal:"<<endl;
        out<<"Algoritmo de Kruskal:"<<endl;
        if(listaOr.PrimerNodo!=NULL){
            //imprime la primer arista (menor)
            qDebug()<<"Aristas seleccionadas: "<<endl;
            out<<"Aristas seleccionadas: "<<endl;
            imp=listaOr.PrimerNodo;
            BuscarVerticePos(imp->partida);
            qDebug() << Elemento->NombreCiudad << " -> ";
            out<<Elemento->NombreCiudad<<" -> ";
            BuscarVerticePos(imp->llegada);
            qDebug() << Elemento->NombreCiudad << " Peso:" << imp->peso << endl;
            out<<Elemento->NombreCiudad<<" Peso:"<<imp->peso<<endl;
            ct=imp->peso;
            //Resetea la matriz temporal
            for(i=0;i<cant;i++){
                for(j=0;j<cant;j++){
                    matTemporal[i][j]=INF;
                }
            }
            //inserta la primera arista
            matTemporal[imp->partida][imp->llegada]=1;
            matTemporal[imp->llegada][imp->partida]=1;

            //imprime las aristas en orden omitiendo los ciclos
            for(imp=listaOr.PrimerNodo->siguiente;imp!=NULL;imp=imp->siguiente){
                if(!GeneraCiclos(imp->partida,imp->llegada)){
                    //guarda el peso
                    ct=ct+imp->peso;
                    //Imprime la arista seleccionada
                    BuscarVerticePos(imp->partida);
                    qDebug() << Elemento->NombreCiudad << " -> ";
                    out<<Elemento->NombreCiudad<<" -> ";
                    BuscarVerticePos(imp->llegada);
                    qDebug() << Elemento->NombreCiudad << " Peso" << imp->peso << endl;
                    out<<Elemento->NombreCiudad<<" Peso"<<imp->peso<<endl;
                    //Inserta la arista que no genero ciclos
                    matTemporal[imp->partida][imp->llegada]=1;
                    matTemporal[imp->llegada][imp->partida]=1;
                }
            }
            qDebug() << endl << "El costo es: " << ct << endl;
            out << endl << "El costo es: " << ct << endl;
            imp = NULL;
            delete imp;
        }
        else
            qDebug()<<"No hay aristas\n";
    }
    else
        qDebug()<<"Grafo Vacio\n";

    archivo.flush();
    archivo.close();
}

//Recorre el grafo en profundidad y genera el arbol n-ario
void GrafoCiudades::GenerarArbolNFC(int mac[TamArr]){
    //Resetea el la matriz matVisitas
    int k,i;
    for (k=0; k<cant; k++)
        matVisitas[k]=0;
    for (k=0; k<cant; k++){
        i=mac[k];
        if (matVisitas[i]==0){
            BuscarVerticePos(i);
            //Inserta al padre
            if(Arbol.Raiz!=NULL)
                Arbol.Insertar(Arbol.Raiz->datos,1,Elemento->CodVerticeGP);
            else
                Arbol.Insertar(0,1,Elemento->CodVerticeGP);
            GenerarArbolNaux(Elemento);
        }
    }
}

//Obtiene los puntos de articulacion de un grafo
void GrafoCiudades::PuntosArticulacion(int cod,int nodo){
    QFile archivo("Puntos de articulacion"+QString::number(nodo)+".txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        //Crea el grafo no dirigido
        GrafoCiudades gnd=CreaGrafoNoDirigido();
        //Crea el arbol-nario
        ArbolNario nuevoArbol;
        delete gnd.Arbol.Raiz;
        gnd.Arbol=nuevoArbol;
        //Genera el grafo y pone todas las aristas de retroceso
        gnd.GenerarArbolN(cod);
        //Imprime el Arbol y va poniendo los nums
        gnd.Arbol.Preorden(nodo);
        out<<endl;
        qDebug()<<endl;
        //Pone los bajos de cada vertice
        gnd.Arbol.PostOrdenAR();
        //Compara bajo(hijo)>=Num(padre) para cada vertice exceptuando la raiz
        gnd.Arbol.EsPuntoArticulacion(nodo);

    }
    else
        qDebug()<<"Grafo Vacio\n";

    archivo.flush();
    archivo.close();
}

//Crear la matriz de valorada
void GrafoCiudades::CrearMatrizValorada(){
    NodoGrafoC *p=PrimerNodo;
    NodoAdyacenteC *temp;
    //Inicializa cada valor en Infinito
    int h,g;
    for(h=0;h<cant;h++){
        for(g=0;g<cant;g++){
            matTemporal[h][g]=INF;
        }
    }
    //--------
    if(p!=NULL){
        int i;
        for(i=0;i<cant;i++){
            temp=p->siguiente_ady;
            while(temp!=NULL){
                matTemporal[i][temp->pos]=temp->peso;
                temp=temp->siguiente_ady;
            }
            p=p->sig_vertice;
        }
    }
    temp=NULL;
    p=NULL;
    delete temp;
    delete p;
}

//Crear la matriz de valorada
void GrafoCiudades::CrearMatrizValoradaNoDirigida(){
    NodoGrafoC *p=PrimerNodo;
    NodoAdyacenteC *temp;
    //Inicializa cada valor en Infinito
    int h,g;
    for(h=0;h<cant;h++){
        for(g=0;g<cant;g++){
            matTemporal[h][g]=INF;
        }
    }
    //--------
    if(p!=NULL){
        int i;
        for(i=0;i<cant;i++){
            temp=p->siguiente_ady;
            while(temp!=NULL){
                matTemporal[i][temp->pos]=temp->peso;
                matTemporal[temp->pos][i]=temp->peso;
                temp=temp->siguiente_ady;
            }
            p=p->sig_vertice;
        }
    }
    temp=NULL;
    p=NULL;
    delete temp;
    delete p;
}

//Copia la matriz de adyacencia a la matriz temporal
void GrafoCiudades::CopiarMatAdyacencia(){
    int i,j;
    for(i=0;i<cant;i++){
        for(j=0;j<cant;j++){
            matTemporal[i][j]=mat[i][j];
        }
    }
}

//Encuentra al nodo de origen
void GrafoCiudades::EncontrarNodo(int val){
    if(VacioGrafo())
        Elemento=NULL;
    else{
        bool enc=false;
        NodoGrafoC *p=PrimerNodo;
        while(p!=NULL & enc==false){
            if(p->CodVerticeGP==val){
                enc=true;
            }
            else{
                p=p->sig_vertice;
            }
        }
        Elemento=p;
        p=NULL;
        delete p;
    }
}

//Encuentra al nodo de origen y lo deja en el puntero Elemento
void GrafoCiudades::BuscarVerticePos(int vas){
    if(VacioGrafo())
        Elemento=NULL;
    else{
        bool enc=false;
        NodoGrafoC *p=PrimerNodo;
        while(p!=NULL & enc==false){
            if(p->pos==vas){
                enc=true;
            }
            else{
                p=p->sig_vertice;
            }
        }
        Elemento=p;
        p=NULL;
        delete p;
    }
}


//Corrobora si genera ciclos
bool GrafoCiudades::GeneraCiclos(int p,int lle){
    int k;
    encCiclo=false;
    //Resetea el vector de visitas
    for (k=0; k<cant; k++)
        matVisitas[k]=0;
    //Comienza a recorrer el grafo en profundidad para encontrar ciclos
    GeneraCiclosaux(lle,p);
    return encCiclo;
}

//Corrobora si hay ciclo
void GrafoCiudades::GeneraCiclosaux(int lle,int part){
    int i;
    //Lo marca como visitado
    matVisitas[lle]=1;
    //Si el visitado es el punto de partida retorna que si hay ciclo
    if(matVisitas[part]==1){
        encCiclo=true;
    }
    else{
        //revisa los adyacentes
        for(i=0;i<cant & encCiclo==false;i++){
            if (matVisitas[i]==0 & matTemporal[lle][i]!=INF){
                GeneraCiclosaux(i,part);
            }
        }
    }
}

//Ordena las aristas de menor a mayor y retorna la lista de ellas
ListaSimple GrafoCiudades::OrdenarAristas(){
    CrearMatrizValorada();
    ListaSimple listaOr;
    int min,i,j,p,tam;
    tam=cant*cant;
    //ordena las aristas de menor a mayor
    p=0;
    while(p<tam){
        min=matTemporal[0][0];
        //obtiene el menor
        for(i=0;i<cant;i++){
            for(j=1;j<cant;j++){
                if(matTemporal[i][j]<min){
                    min=matTemporal[i][j];
                }
            }
        }
        //busca los menores y tacha los que ya paso
        if(min!=INF){
            for(i=0;i<cant;i++){
                for(j=0;j<cant;j++){
                    if(matTemporal[i][j]==min){
                        listaOr.InsertaFinal(i,j,matTemporal[i][j]);
                        matTemporal[i][j]=INF;
                        p++;
                    }
                }
            }
        }
        else{
            p=tam;
        }
    }
    return listaOr;
}


//Crea el grafo invertido
GrafoCiudades GrafoCiudades::CreaGrafoInvertido(){
    GrafoCiudades gi;
    //Carga los vertices
    gi.CargarCiudades();
    //gi.CargarAeropuertos();
    gi.las=0;
    char buffer[100]="";
    char *pch;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("AristasGP.txt");
    if(!encabezados.is_open()){
        qDebug() << "Error archivo Aristas no existe\n";
    }
    else{
        while(!encabezados.eof()){
            encabezados.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,"; ");
                codp=atoi(pch);
                pch = strtok (NULL, ";");
                codl=atoi(pch);
                pch = strtok (NULL, ";");
                peso=atoi(pch);
                //Inserta la arista invertida
                gi.InsertaAristas(codl,codp,peso);
            }
        }
    }
    gi.CrearMatrizAdyacencia();
    pch=NULL;
    delete pch;
    return gi;
}

//Crea el grafo no dirigido
GrafoCiudades GrafoCiudades::CreaGrafoNoDirigido(){
    GrafoCiudades gi;
    //Carga los vertices
    gi.CargarCiudades();
    //gi.CargarAeropuertos();
    char buffer[100]="";
    char *pch;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("AristasGP.txt");
    if(!encabezados.is_open()){
        qDebug() << "Error archivo Aristas no existe\n";
    }
    else{
        while(!encabezados.eof()){
            encabezados.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,"; ");
                codp=atoi(pch);
                pch = strtok (NULL, ";");
                codl=atoi(pch);
                pch = strtok (NULL, ";");
                peso=atoi(pch);
                gi.InsertaAristas(codp,codl,peso);
                //Inserta la arista invertida
                gi.InsertaAristas(codl,codp,peso);
            }
        }
    }
    gi.CrearMatrizAdyacencia();
    pch=NULL;
    delete pch;
    return gi;
}

//Recorre el grafo en profundidad y genera el arbol n-ario
void GrafoCiudades::GenerarArbolN(int cod){
    //Resetea el la matriz matVisitas
    int k,e,i;
    for (k=0; k<cant; k++)
        matVisitas[k]=0;
    EncontrarNodo(cod);
    if(Elemento!=NULL){
        e=Elemento->pos;
        for(i=0;i<2;i++){
            for (k=e; k<cant; k++){
                if (matVisitas[k]==0){
                    BuscarVerticePos(k);
                    //Inserta al padre
                    if(Arbol.Raiz!=NULL)
                        Arbol.Insertar(Arbol.Raiz->datos,1,Elemento->CodVerticeGP);
                    else
                        Arbol.Insertar(0,1,Elemento->CodVerticeGP);
                    GenerarArbolNaux(Elemento);
                }
            }
            e=0;
        }
    }
    else{
        qDebug()<<"Elemento no encontrado";
    }
    qDebug()<<endl;
}

//Visita un nodo y lo imprime
void GrafoCiudades::GenerarArbolNaux(NodoGrafoC *a){
    //Visitar
    int i;
    matVisitas[a->pos]=1;
    matPosVis[las]=a->pos;
    las++;
    NodoAdyacenteC *t;
    for (t=a->siguiente_ady; t!=NULL; t=t->siguiente_ady){
        if (matVisitas[t->pos]==0){
            BuscarVerticePos(t->pos);
            Arbol.Insertar(a->CodVerticeGP,0,Elemento->CodVerticeGP);
            GenerarArbolNaux(Elemento);
        }
    }
    t=NULL;
    delete t;
    for(i=0;i<cant;i++){
        BuscarVerticePos(i);
        if(EsAdyacente(a,Elemento->CodVerticeGP)){
            if(matVisitas[i]==0){
                Arbol.Insertar(a->CodVerticeGP,0,Elemento->CodVerticeGP);
                GenerarArbolNaux(Elemento);
            }
            else{
                Arbol.EncontrarElem(Elemento->CodVerticeGP);
                if(!Arbol.EsHijo(a->CodVerticeGP,Arbol.ElementoB) & Elemento->CodVerticeGP!=a->CodVerticeGP){
                    Arbol.insertarAR(a->CodVerticeGP,Elemento->CodVerticeGP);
                }
            }
        }
    }
}
//Retorna si el parametro es adyacente al nodo
bool GrafoCiudades::EsAdyacente(NodoGrafoC *nodo,int cod){
    NodoAdyacenteC *p;
    bool encont=false;
    for(p=nodo->siguiente_ady;p!=NULL;p=p->siguiente_ady){
        if(p->Cod==cod){
            p=NULL;
            delete p;
            encont=true;
            return encont;
        }
    }
    p=NULL;
    delete p;
    return encont;
}
NodolistaCiudades GrafoCiudades::ListaNodos(){
    NodoGrafoC *nodo = PrimerNodo;
    NodolistaCiudades lista;
    while (nodo != NULL){
        lista.InsertarFinal(QString::number(nodo->CodVerticeGP),nodo->NombreCiudad);
        nodo = nodo->sig_vertice;
    }
    return lista;
}

NodolistaCiudades GrafoCiudades::Listaadyacentes(){
    NodoGrafoC *nodo = PrimerNodo;
    NodoAdyacenteC *t;
    NodolistaCiudades lista;
    while (nodo != NULL){
        for (t = nodo->siguiente_ady; t != NULL; t = t->siguiente_ady){
            lista.InsertarFinal(nodo->CodVerticeGP);
            lista.InsertarFinal(t->Cod);
            lista.InsertarFinal(t->peso);
        }
        nodo = nodo->sig_vertice;
    }
    return lista;
}

