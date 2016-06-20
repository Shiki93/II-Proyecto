#define _CRT_SECURE_NO_WARNINGS
#include "grafo.h"

using namespace std;
NodoLista Grafo::ListaNodos(){
    NodoGrafo *nodo = PrimerNodo;
    Nodolista lista;
    while (nodo != NULL){
        lista.InsertarFinal(std::to_string(nodo->CodVerticeGG));
        nodo = nodo->sig_vertice;
    }
    return lista;
}
NodoLista Grafo::Listaadyacentes(){
    NodoGrafo *nodo = PrimerNodo;
    NodoAdyacente *t;
    Nodolista lista;
    while (nodo != NULL){
        for (t = nodo->siguiente_ady; t != NULL; t = t->siguiente_ady){
            lista.InsertarFinal(nodo->CodVerticeGG);
            lista.InsertarFinal(t->Cod);
            lista.InsertarFinal(t->peso);
        }
        nodo = nodo->sig_vertice;
    }
    return lista;
}

int Grafo::tamano(){
    int cont = 0;
    NodoGrafo *nodo = PrimerNodo;
    while(nodo!=NULL){
        cont++;
        nodo = nodo->sig_vertice;
    }
    return cont;
}
//Constructores inicial
NodoAdyacente::NodoAdyacente(){
    Cod = 0;
    peso = 0;
    pos = 0;
    siguiente_ady = NULL;
}

//Constructor para nodos
NodoAdyacente::NodoAdyacente(int co,int pe,int po,string nombre){
    Cod = co;
    peso = pe;
    pos = po;
    NombrePais = nombre;
    siguiente_ady = NULL;
}


//Constructores inicial
NodoGrafo::NodoGrafo(){
    CodVerticeGG = 0;
    Tipo = 0;
    pos = 0;
    sig_vertice = NULL;
    siguiente_ady = NULL;
}

//Constructor para paises
NodoGrafo::NodoGrafo(int cod, string nombre,int posi){
    CodVerticeGG = cod;
    NombrePais = nombre;
    pos = posi;
    sig_vertice = NULL;
    siguiente_ady = NULL;
}

//Carga los paises
bool Grafo::CargarPaises(){
    char buffer[100] = "";
    char *pch;
    int Cod;
    string Nom;
    ifstream encabezados("VerticesGG.txt");
    if(!encabezados.is_open()){
        cout << "Error archivo Paises no existe\n";
        return true;
    }
    else{
        while(!encabezados.eof()){
            encabezados.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,";");
                Cod = atoi(pch);
                pch = strtok (NULL, ";");
                Nom = pch;
                InsertaVertices(Cod,Nom);
            }
        }
    }
    pch = NULL;
    delete pch;
    return false;
}


//Carga las aristas
bool Grafo::CargarAristasGG(){
    char buffer[100]="";
    char *pch;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("AristasGG.txt");
    if(!encabezados.is_open()){
        cout << "Error archivo Aristas no existe\n";
        return true;
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
                InsertaAristas(codp,codl,peso);
            }
        }
    }
    pch=NULL;
    delete pch;
    return false;
}

//Inserta un elemento en el grafo al inicio (para pais)
void Grafo::InsertaVertices(int cod,string nombre){
    if(VacioGrafo())
        PrimerNodo=UltimoNodo=new NodoGrafo (cod,nombre,cant);
    else{
        UltimoNodo=UltimoNodo->sig_vertice=new NodoGrafo(cod,nombre,cant);
    }
    cant++;
}
//Inserta un nodo adyacente a final del vertice
void Grafo::InsertaAristas(int CodP,int CodL,int Peso){
    if(VacioGrafo())
        cout<<"No hay Vertices\n";
    else{
        EncontrarNodo(CodP);
        NodoGrafo *p=Elemento;
        if(p!=NULL){
            EncontrarNodo(CodL);
            NodoGrafo *j=Elemento;
            if(j!=NULL){
                if(p->siguiente_ady==NULL){
                    p->siguiente_ady=new NodoAdyacente(CodL,Peso,j->pos,j->NombrePais);
                }
                else{
                    NodoAdyacente *temp=p->siguiente_ady;
                    while(temp->siguiente_ady!=NULL){
                        temp=temp->siguiente_ady;
                    }
                    temp->siguiente_ady=new NodoAdyacente(CodL,Peso,j->pos,j->NombrePais);
                    temp=NULL;
                    delete temp;
                }
            }
            else{
                cout<<"No se encontro punto de llegada\n";
            }
            j=NULL;
            delete j;
        }
        else{
            cout<<"No se encontro punto de partida\n";
        }
        Elemento=NULL;
        p=NULL;
        delete p;
    }
}
//Carga la lista de listas
void Grafo::CrearGrafo(){
    bool a,b,c;
    a=CargarPaises();
    if(!a){
        c=CargarAristasGG();
        if(!c){
            CrearMatrizAdyacencia();
            cout<<"Grafo creado\n";
        }
    }
}
bool Grafo::CrearGrafoPequeno(){
    char buffer[100]="";
    char *pch;
    int Cod;
    pnodografo nodo;
    string Nom;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("VerticesGP.txt");
    if(!encabezados.is_open()){
        cout << "Error archivo Paises no existe\n";
        return true;
    }
    else{
        while(!encabezados.eof()){
            encabezados.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,"; ");
                nodo = BuscarVerticepos(atoi(pch));
                if(nodo!=NULL){
                    pch = strtok (NULL,"; ");
                    Cod = atoi(pch);
                    pch = strtok (NULL, "; ");
                    Nom = pch;
                    nodo->grafoGP.InsertaVertices(Cod,Nom);
                }
                else{
                    cout<<"Pais no encontrado"<<endl;
                }

            }
        }
    ifstream encabezados1 ("AristasGP.txt");
    if(!encabezados1.is_open()){
        cout << "Error archivo Aristas no existe\n";
        return true;
    }
    else{
        while(!encabezados1.eof()){
            encabezados1.getline (buffer,100);
            if(strcmp(buffer,"")){
                pch = strtok (buffer,";");
                nodo = BuscarVerticepos(atoi(pch));
                if(nodo!=NULL){
                    pch = strtok (NULL,";");
                    codp=atoi(pch);
                    pch = strtok (NULL, ";");
                    codl=atoi(pch);
                    pch = strtok (NULL, ";");
                    peso=atoi(pch);
                    nodo->grafoGP.InsertaAristas(codp,codl,peso);
                    nodo->grafoGP.CrearMatrizAdyacencia();
                }
            }
        }
    }
    pch=NULL;
    delete pch;
    return false;

}
}
//Crear la matriz de adyacencia
void Grafo::CrearMatrizAdyacencia(){
    NodoGrafo *p=PrimerNodo;
    NodoAdyacente *temp;
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
void Grafo::ImprimirGrafo(){
    NodoGrafo *p=PrimerNodo;
    NodoAdyacente *temp;
    if(PrimerNodo==NULL){
        cout<<"Grafo Vacio\n";
    }
    else{
        while(p!=NULL){
            cout<<"###################################################################"<<endl;
            cout<<p->NombrePais;
            cout<<": ";
            temp=p->siguiente_ady;
            while(temp!=NULL){
                cout<<"--> "<<temp->NombrePais <<"("<<temp->peso<<") ";
                temp=temp->siguiente_ady;
            }
            cout<<endl;
            cout<<"\n";
            cout<<"Ciudades: "<<endl;

            p->grafoGP.ImprimirGrafo();
            cout<<endl;
            p=p->sig_vertice;
        }
    }
    temp=NULL;
    p=NULL;
    delete temp;
    delete p;
}

//Imprime la matriz
void Grafo::ImprimirMatriz(int D[TamArr][TamArr]){
    if(!VacioGrafo()){
        NodoGrafo *p;
        int i,j;
        //Imprime los encabezados de la tabla
        cout << "\t";
        for(p=PrimerNodo;p!=NULL;p=p->sig_vertice)
            cout << p->CodVerticeGG << "\t";
        cout << endl;
        p=PrimerNodo;
        //ciclo de impresion de valores
        for(j=0;j<cant;j++){
            cout << p->CodVerticeGG << "\t";
            for(i=0;i<cant;i++){
                if(D[j][i]==INF)
                    cout << "INF\t";
                else
                    cout << D[j][i] << "\t";
            }
            cout << endl;
            p=p->sig_vertice;
        }
        p=NULL;
        delete p;
    }
    else
        cout<<"Grafo Vacio\n";
}
void Grafo::Dijkstra(int inicio,int fin){
    NodoAdyacente *t;
    NodoGrafo *nodo;
    Nodolista camino;
    Nodolista resueltos;
    Nodolista resueltosAux;
    NodolistaC colaPrioridad;
    int pesoTotal=0;
    ofstream archivo("Dijsktra.txt",ios::app);
    nodo = BuscarVerticepos(inicio);
    cout<<"Nodo resuelto"<<"\t"<<"Nodo no resuelto"<<"\t"<<"Costo minimo"<<"\t"<<"Costo total"<<"\t\t"<<"UltimaConexion"<<endl;
    archivo<<"Nodo resuelto"<<"\t"<<"Nodo no resuelto"<<"\t"<<"Costo minimo"<<"\t"<<"Costo total"<<"\t\t"<<"UltimaConexion"<<endl;
    if(nodo!=NULL){
        //Proceso para el primero
        cout<<nodo->NombrePais<<endl;
        archivo<<nodo->NombrePais<<endl;
        for (t=nodo->siguiente_ady; t!=NULL; t=t->siguiente_ady){
            colaPrioridad.Insertar(nodo,t,t->peso);
            cout<<"\t\t"<<t->NombrePais<<"("<<t->peso<<")";
            archivo<<"\t\t"<<t->NombrePais<<"("<<t->peso<<")";
            if(t->siguiente_ady==NULL){
                cout<<"\t\t\t"<<colaPrioridad.obtenerInicio()->llegada->peso;
                archivo<<"\t\t\t"<<colaPrioridad.obtenerInicio()->llegada->peso;
                pesoTotal = pesoTotal+colaPrioridad.obtenerInicio()->llegada->peso;
                cout<<"\t\t"<<colaPrioridad.obtenerInicio()->llegada->peso;
                archivo<<"\t\t"<<colaPrioridad.obtenerInicio()->llegada->peso;
                cout<<"\t\t"<<colaPrioridad.obtenerInicio()->origen->NombrePais<<"/"<<colaPrioridad.obtenerInicio()->llegada->NombrePais;
                archivo<<"\t\t"<<colaPrioridad.obtenerInicio()->origen->NombrePais<<"/"<<colaPrioridad.obtenerInicio()->llegada->NombrePais;
                camino.InsertarFinal(colaPrioridad.obtenerInicio()->origen,colaPrioridad.obtenerInicio()->llegada,
                                    colaPrioridad.obtenerInicio()->llegada->peso);
                resueltos.InsertarFinal(colaPrioridad.obtenerInicio()->origen);
                resueltos.InsertarFinal(BuscarVerticepos(colaPrioridad.obtenerInicio()->llegada->Cod));
                resueltosAux.InsertarFinal(BuscarVerticepos(colaPrioridad.obtenerInicio()->llegada->Cod));
            }
            cout<<endl;
            archivo<<endl;
        }
        colaPrioridad.eliminarCoincidencias(colaPrioridad.obtenerInicio()->llegada);
        cout<<"#########################################################################################################################"<<endl;
        archivo<<"#########################################################################################################################"<<endl;
        archivo<<endl;
        cout<<endl;
        //Proceso para el resto
        while(resueltos.largoLista()!= tamano()){
            Nodolista *aux = resueltosAux.primero;
            resueltos.MostrarLista();
            while(aux){
                nodo = BuscarVerticepos(aux->valor->CodVerticeGG);
                if(nodo!=NULL){
                    //cout<<nodo->NombrePais<<endl;
                    for (t=nodo->siguiente_ady; t!=NULL; t=t->siguiente_ady){
                        colaPrioridad.Insertar(nodo,t,t->peso+pesoTotal);
                    }
                }
                aux= aux->siguiente;
            }
            colaPrioridad.MostrarLista();
            //peso minimo
            cout<<"\t\t\t\t\t\t"<<colaPrioridad.obtenerInicio()->llegada->peso;
            archivo<<"\t\t\t\t\t\t"<<colaPrioridad.obtenerInicio()->llegada->peso;
            //peso total
            cout<<"\t\t"<<colaPrioridad.obtenerInicio()->peso;
            archivo<<"\t\t"<<colaPrioridad.obtenerInicio()->peso;
            pesoTotal = colaPrioridad.obtenerInicio()->peso;
            //ultima conexion
            cout<<"\t\t"<<colaPrioridad.obtenerInicio()->origen->NombrePais<<"/"<<colaPrioridad.obtenerInicio()->llegada->NombrePais<<endl;
            archivo<<"\t\t"<<colaPrioridad.obtenerInicio()->origen->NombrePais<<"/"<<colaPrioridad.obtenerInicio()->llegada->NombrePais<<endl;
            //para saber camino despues
            camino.InsertarFinal(colaPrioridad.obtenerInicio()->origen,colaPrioridad.obtenerInicio()->llegada,colaPrioridad.obtenerInicio()->peso);
            resueltos.InsertarFinal(colaPrioridad.obtenerInicio()->origen);
            resueltos.InsertarFinal(BuscarVerticepos(colaPrioridad.obtenerInicio()->llegada->Cod));
            resueltosAux.BorrarFinal();
            resueltosAux.InsertarFinal(BuscarVerticepos(colaPrioridad.obtenerInicio()->llegada->Cod));

            colaPrioridad.eliminarCoincidencias(colaPrioridad.obtenerInicio()->llegada);
            cout<<"#########################################################################################################################"<<endl;
            archivo<<"#########################################################################################################################"<<endl;
            archivo<<endl;
        }
        camino.MostrarCamino(BuscarVerticepos(fin));

    }
}
//Recorre el grafo en profundidad
void Grafo::RecorridoProfundidad(int cod){
    if(!VacioGrafo()){
        NodoGrafo *a;
        NodoAdyacente *t;
        Pila pil;
        ofstream archivo("Produndidad.txt");
        cout<<"Recorrido en Profundidad: \n";
        archivo<<"Recorrido en Profundidad: "<<endl;
        //Resetea la matriz matVisitas
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
                        pil.Push(k);
                        while(!pil.VaciaPila()){
                            BuscarVerticePos(pil.Tope());
                            cout<<Elemento->NombrePais<<"-";
                            archivo<<Elemento->NombrePais<<"-";
                            pil.Pop();
                            a=Elemento;
                            //apila los adyacentes no visitados
                            for (t=a->siguiente_ady; t!=NULL; t=t->siguiente_ady){
                                if (matVisitas[t->pos]==0){
                                    pil.Push(t->pos);
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
            cout<<"Elemento no encontrado";
        }
        cout<<endl;
        a=NULL;
        delete a;
        t=NULL;
        delete t;
    }
    else
        cout<<"Grafo Vacio\n";
}

//Recorre el grafo en anchura
void Grafo::RecorridoAnchura(int cod){
    if(!VacioGrafo()){
        NodoGrafo *a;
        NodoAdyacente *t;
        Cola col;
        ofstream archivo("Anchura.txt");
        //Resetea el la matriz matVisitas
        cout<<"Recorrido en Anchura: "<<endl;
        archivo<<"Recorrido en Anchura: "<<endl;
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
                            cout<<Elemento->NombrePais<<"-";
                            archivo<<Elemento->NombrePais<<"-";
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
            cout<<"Elemento no encontrado";
        }
        cout<<endl;
        a=NULL;
        delete a;
        t=NULL;
        delete t;
    }
    else
        cout<<"Grafo Vacio\n";
}

//Algoritmo de Prim
void Grafo::Prim(int cod){
    ofstream archivo("Prim.txt");
    if(!VacioGrafo()){
        EncontrarNodo(cod);
        if(Elemento!=NULL){
            int i,j,z,e,min,Coste[TamArr],Mas_cerca[TamArr],Con[TamArr],VectMc[TamArr];
            long ct;
            e=Elemento->pos;
            CrearMatrizValoradaNoDirigida();
            cout<<"Algoritmo de Prim: "<<endl;
            archivo<<"Algoritmo de Prim: "<<endl;
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
            cout<<"Aristas seleccionadas: "<<endl;
            archivo<<"Aristas seleccionadas: "<<endl;
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
                        cout<<Elemento->NombrePais<<" -> ";
                        archivo<<Elemento->NombrePais<<" -> ";
                        BuscarVerticePos(Mas_cerca[z]);
                        cout<<Elemento->NombrePais<<endl;
                        archivo<<Elemento->NombrePais<<endl;
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
            cout<<endl<<"Pesos: "<<endl;
            archivo<<endl<<"Pesos: "<<endl;
            cout<<"{ ";
            archivo<<"{ ";
            for(i=0;i<cant;i++){
                if(VectMc[i]!=0){
                    cout<<VectMc[i]<<" ";
                    archivo<<VectMc[i]<<" ";
                }

            }
            cout<<"}"<<endl;
            archivo<<"}"<<endl;
            cout<<endl<<"El costo es: "<<ct<<endl;
            archivo<<endl<<"El costo es: "<<ct<<endl;
        }
    }
    else
        cout<<"Grafo Vacio\n";
}

//Algoritmo de kruskal
void Grafo::Kruskal(){
    ofstream archivo("kruskal.txt");
    if(!VacioGrafo()){
        int i,j,ct;
        //Ordena las aristas en orden ascendente y se las sede a listaOr
        ListaSimple listaOr = OrdenarAristas();
        NodosLista *imp;
        cout<<"Algoritmo de Kruskal:"<<endl;
        archivo<<"Algoritmo de Kruskal:"<<endl;
        if(listaOr.PrimerNodo!=NULL){
            //imprime la primer arista (menor)
            cout<<"Aristas seleccionadas: "<<endl;
            archivo<<"Aristas seleccionadas: "<<endl;
            imp=listaOr.PrimerNodo;
            BuscarVerticePos(imp->partida);
            cout<<Elemento->NombrePais<<" -> ";
            archivo<<Elemento->NombrePais<<" -> ";
            BuscarVerticePos(imp->llegada);
            cout<<Elemento->NombrePais<<" Peso:"<<imp->peso<<endl;
            archivo<<Elemento->NombrePais<<" Peso:"<<imp->peso<<endl;
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
                    cout<<Elemento->NombrePais<<" -> ";
                    archivo<<Elemento->NombrePais<<" -> ";
                    BuscarVerticePos(imp->llegada);
                    cout<<Elemento->NombrePais<<" Peso"<<imp->peso<<endl;
                    archivo<<Elemento->NombrePais<<" Peso"<<imp->peso<<endl;
                    //Inserta la arista que no genero ciclos
                    matTemporal[imp->partida][imp->llegada]=1;
                    matTemporal[imp->llegada][imp->partida]=1;
                }
            }
            cout<<endl<<"El costo es: "<<ct<<endl;
            archivo<<endl<<"El costo es: "<<ct<<endl;
            imp=NULL;
            delete imp;
        }
        else
            cout<<"No hay aristas\n";
    }
    else
        cout<<"Grafo Vacio\n";
}


//Recorre el grafo en profundidad y genera el arbol n-ario
void Grafo::GenerarArbolNFC(int mac[TamArr]){
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
                Arbol.Insertar(Arbol.Raiz->datos,1,Elemento->CodVerticeGG);
            else
                Arbol.Insertar(0,1,Elemento->CodVerticeGG);
            GenerarArbolNaux(Elemento);
        }
    }
}

//Obtiene los puntos de articulacion de un grafo
void Grafo::PuntosArticulacion(int cod,int nodo){
    ofstream archivo("Puntos de articulacion.txt",ios::app);
    if(!VacioGrafo()){
        //Crea el grafo no dirigido
        Grafo gnd=CreaGrafoNoDirigido();
        //Crea el arbol-nario
        ArbolNario nuevoArbol;
        delete gnd.Arbol.Raiz;
        gnd.Arbol = nuevoArbol;
        //Genera el grafo y pone todas las aristas de retroceso
        gnd.GenerarArbolN(cod);
        //Imprime el Arbol y va poniendo los nums
        gnd.Arbol.Preorden(nodo);
        archivo<<endl;
        cout<<endl;
        //Pone los bajos de cada vertice
        gnd.Arbol.PostOrdenAR();
        //Compara bajo(hijo)>=Num(padre) para cada vertice exceptuando la raiz
        gnd.Arbol.EsPuntoArticulacion(nodo);

    }
    else
        cout<<"Grafo Vacio\n";
}





//Crear la matriz de valorada
void Grafo::CrearMatrizValorada(){
    NodoGrafo *p=PrimerNodo;
    NodoAdyacente *temp;
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
void Grafo::CrearMatrizValoradaNoDirigida(){
    NodoGrafo *p=PrimerNodo;
    NodoAdyacente *temp;
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

//Encuentra al nodo de origen
void Grafo::EncontrarNodo(int val){
    if(VacioGrafo())
        Elemento=NULL;
    else{
        bool enc=false;
        NodoGrafo *p=PrimerNodo;
        while(p!=NULL & enc==false){
            if(p->CodVerticeGG==val){
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
void Grafo::BuscarVerticePos(int vas){
    if(VacioGrafo())
        Elemento=NULL;
    else{
        bool enc=false;
        NodoGrafo *p=PrimerNodo;
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

//Encuentra al nodo de origen y retorna dicho nodo
pnodografo Grafo::BuscarVerticepos(int vas){
    //pnodografo h;
    if(VacioGrafo()){
        return NULL;
    }
    else{
        bool enc=false;
        NodoGrafo *p=PrimerNodo;
        while(p!=NULL & enc==false){
            if(p->CodVerticeGG == vas){
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


//Corrobora si genera ciclos
bool Grafo::GeneraCiclos(int p,int lle){
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
void Grafo::GeneraCiclosaux(int lle,int part){
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
ListaSimple Grafo::OrdenarAristas(){
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
Grafo Grafo::CreaGrafoInvertido(){
    Grafo gi;
    //Carga los vertices
    gi.CargarPaises();
    //gi.CargarAeropuertos();
    gi.las=0;
    char buffer[100]="";
    char *pch;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("AristasGG.txt");
    if(!encabezados.is_open()){
        cout << "Error archivo Aristas no existe\n";
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
Grafo Grafo::CreaGrafoNoDirigido(){
    Grafo gi;
    //Carga los vertices
    gi.CargarPaises();
    //gi.CargarAeropuertos();
    char buffer[100]="";
    char *pch;
    int codp=0,codl=0;
    int peso;
    ifstream encabezados ("AristasGG.txt");
    if(!encabezados.is_open()){
        cout << "Error archivo Aristas no existe\n";
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
void Grafo::GenerarArbolN(int cod){
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
                        Arbol.Insertar(Arbol.Raiz->datos,1,Elemento->CodVerticeGG);
                    else
                        Arbol.Insertar(0,1,Elemento->CodVerticeGG);
                    GenerarArbolNaux(Elemento);
                }
            }
            e=0;
        }
    }
    else{
        cout<<"Elemento no encontrado";
    }
    cout<<endl;
}

//Visita un nodo y lo imprime
void Grafo::GenerarArbolNaux(NodoGrafo *a){
    //Visitar
    int i;
    matVisitas[a->pos]=1;
    matPosVis[las]=a->pos;
    las++;
    NodoAdyacente *t;
    for (t=a->siguiente_ady; t!=NULL; t=t->siguiente_ady){
        if (matVisitas[t->pos]==0){
            BuscarVerticePos(t->pos);
            Arbol.Insertar(a->CodVerticeGG,0,Elemento->CodVerticeGG);
            GenerarArbolNaux(Elemento);
        }
    }
    t=NULL;
    delete t;
    for(i=0;i<cant;i++){
        BuscarVerticePos(i);
        if(EsAdyacente(a,Elemento->CodVerticeGG)){
            if(matVisitas[i]==0){
                Arbol.Insertar(a->CodVerticeGG,0,Elemento->CodVerticeGG);
                GenerarArbolNaux(Elemento);
            }
            else{
                Arbol.EncontrarElem(Elemento->CodVerticeGG);
                if(!Arbol.EsHijo(a->CodVerticeGG,Arbol.ElementoB) & Elemento->CodVerticeGG!=a->CodVerticeGG){
                    Arbol.insertarAR(a->CodVerticeGG,Elemento->CodVerticeGG);
                }
            }
        }
    }
}



//Retorna si el parametro es adyacente al nodo
bool Grafo::EsAdyacente(NodoGrafo *nodo,int cod){
    NodoAdyacente *p;
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

