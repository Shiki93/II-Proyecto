#include "Grafo.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

NodoLista Grafo::ListaNodos(){
    NodoGrafo *nodo = PrimerNodo;
    NodoLista lista;
    while (nodo != NULL){
        lista.InsertarFinal(QString::number(nodo->CodigoVertice));
        nodo = nodo->sig_vertice;
    }
    return lista;
}

NodoLista Grafo::Listaadyacentes(){
    NodoGrafo *nodo = PrimerNodo;
    NodoAdyacente *t;
    NodoLista lista;
    while (nodo != NULL){
        for (t = nodo->siguiente_ady; t != NULL; t = t->siguiente_ady){
            lista.InsertarFinal(nodo->CodigoVertice);
            lista.InsertarFinal(t->codigo);
            lista.InsertarFinal(t->peso);
        }
        nodo = nodo->sig_vertice;
    }
    return lista;
}

int Grafo::tamanio(){
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
    codigo = 0;
    peso = 0;
    pos = 0;
    siguiente_ady = NULL;
}

//Constructor para nodos
NodoAdyacente::NodoAdyacente(int co,int pe,int po,QString nombre){
    codigo = co;
    peso = pe;
    pos = po;
    Nombre = nombre;
    siguiente_ady = NULL;
}

//Constructores inicial
NodoGrafo::NodoGrafo(){
    CodigoVertice = 0;
    Tipo = 0;
    pos = 0;
    sig_vertice = NULL;
    siguiente_ady = NULL;
}

//Constructor para paises
NodoGrafo::NodoGrafo(int cod, QString nombre,int posi){
    CodigoVertice = cod;
    Nombre = nombre;
    pos = posi;
    sig_vertice = NULL;
    siguiente_ady = NULL;
}

//Carga los paises
bool Grafo::CargarPaises(){
    int Cod;
    QString Nom;
    QStringList data;
    QString line;
    QFile encabezados("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/VerticesGG.txt");
    if(!encabezados.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Error archivo Paises no existe\n";
        return true;
    }
    else{
        QTextStream in(&encabezados);
        while(!in.atEnd()){
            line = in.readLine();
            data = line.split(";");
            Cod = data.at(0).toInt();
            Nom = data.at(1);
            InsertaVertices(Cod, Nom);
        }
    }
    encabezados.close();
    return false;
}

//Carga las aristas
bool Grafo::CargarAristas(){
    int idPartida = 0, idLlegada = 0;
    int peso;
    QStringList data;
    QString line;
    QFile encabezados("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/AristasGG.txt");
    if(!encabezados.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Error archivo Aristas no existe\n";
        return true;
    }
    else{
        QTextStream in(&encabezados);
        while(!in.atEnd()){
            line = in.readLine();
            data = line.split(";");
            idPartida = data.at(0).toInt();
            idLlegada = data.at(1).toInt();
            peso = data.at(2).toInt();
            InsertaAristas(idPartida, idLlegada, peso);
        }
    }
    encabezados.close();
    return false;
}

//Inserta un elemento en el grafo al inicio (para pais)
void Grafo::InsertaVertices(int cod,QString nombre){
    if(VacioGrafo())
        PrimerNodo = UltimoNodo = new NodoGrafo(cod, nombre, cant);
    else{
        UltimoNodo = UltimoNodo->sig_vertice = new NodoGrafo(cod, nombre, cant);
    }
    cant++;
}

//Inserta un nodo adyacente a final del vertice
void Grafo::InsertaAristas(int CodP,int CodL,int Peso){
    if(VacioGrafo())
        qDebug()<<"No hay Vertices\n";
    else{
        EncontrarNodo(CodP);
        NodoGrafo *p=this->Elemento;
        if(p!=NULL){
            EncontrarNodo(CodL);
            NodoGrafo *j=this->Elemento;
            if(j!=NULL){
                if(p->siguiente_ady==NULL){
                    p->siguiente_ady=new NodoAdyacente(CodL,Peso,j->pos,j->Nombre);
                }
                else{
                    NodoAdyacente *temp=p->siguiente_ady;
                    while(temp->siguiente_ady!=NULL){
                        temp=temp->siguiente_ady;
                    }
                    temp->siguiente_ady=new NodoAdyacente(CodL,Peso,j->pos,j->Nombre);
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
void Grafo::CrearGrafo(){
    bool falloAlCargarPaises,falloAlCargarAristas;
    falloAlCargarPaises = CargarPaises();
    if(!falloAlCargarPaises){
        falloAlCargarAristas = CargarAristas();
        if(!falloAlCargarAristas){
            CrearMatrizAdyacencia();
            qDebug()<<"Grafo creado\n";
        }
    }
}

//Crear la matriz de adyacencia
void Grafo::CrearMatrizAdyacencia(){
    NodoGrafo *p = PrimerNodo;
    NodoAdyacente *temp;
    if(p != NULL){
        int i;
        for(i = 0; i < cant; i++){
            temp=p->siguiente_ady;
            while(temp!=NULL){
                mat[i][temp->pos]=1;
                temp=temp->siguiente_ady;
            }
            p=p->sig_vertice;
        }
    }
    temp = NULL;
    p = NULL;
    delete temp;
    delete p;
}

//Imprime el grafo
void Grafo::ImprimirGrafo(){
    NodoGrafo *p = PrimerNodo;
    NodoAdyacente *temp;
    if(PrimerNodo == NULL){
        qDebug() << "Grafo Vacio\n";
    }
    else{
        while(p != NULL){
            qDebug() << "###################################################################" << endl;
            qDebug() << p->Nombre << p->CodigoVertice << ": ";
            temp = p->siguiente_ady;
            while(temp != NULL){
                qDebug() << "--> " << temp->Nombre << "(" << temp->peso<< ") ";
                temp=temp->siguiente_ady;
            }
            qDebug()<<endl;
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
        qDebug() << "\t";
        for(p=PrimerNodo;p!=NULL;p=p->sig_vertice)
            qDebug() << p->CodigoVertice << "\t";
        qDebug() << endl;
        p=PrimerNodo;
        //ciclo de impresion de valores
        for(j=0;j<cant;j++){
            qDebug() << p->CodigoVertice << "\t";
            for(i=0;i<cant;i++){
                if(D[j][i]==INF)
                    qDebug() << "INF\t";
                else
                    qDebug() << D[j][i] << "\t";
            }
            qDebug() << endl;
            p=p->sig_vertice;
        }
        p=NULL;
        delete p;
    }
    else
        qDebug()<<"Grafo Vacio\n";
}

void Grafo::Dijkstra(int inicio,int fin){
    NodoAdyacente *t;
    NodoGrafo *nodo;
    NodoLista camino;
    NodoLista resueltos;
    NodoLista resueltosAux;
    NodoCola *colaPrioridad = new NodoCola();
    int pesoTotal = 0;
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Dijsktra.txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    else{
        QTextStream out(&archivo);
        nodo = BuscarVerticepos(inicio);
        qDebug() << "Nodo resuelto" << "\t" << "Nodo no resuelto" << "\t" << "Costo minimo" << "\t" << "Costo total" << "\t\t" << "UltimaConexion" << endl;
        out << "Nodo resuelto" << "\t" << "Nodo no resuelto" << "\t" << "Costo minimo" << "\t" << "Costo total" << "\t\t" << "UltimaConexion" << endl;
        if(nodo != NULL){
            //Proceso para el primero
            qDebug() << nodo->Nombre << endl;
            out << nodo->Nombre << endl;
            for(t = nodo->siguiente_ady; t != NULL; t = t->siguiente_ady){
                colaPrioridad->Insertar(nodo, t, t->peso);
                qDebug() << "\t\t" << t->Nombre << "(" << t->peso << ")";
                out << "\t\t" << t->Nombre << "(" << t->peso << ")";
                if(t->siguiente_ady == NULL){
                    qDebug()<<"\t\t\t"<<colaPrioridad->obtenerInicio()->llegada->peso;
                    out<<"\t\t\t"<<colaPrioridad->obtenerInicio()->llegada->peso;
                    pesoTotal = pesoTotal + colaPrioridad->obtenerInicio()->llegada->peso;
                    qDebug()<< "\t\t" << colaPrioridad->obtenerInicio()->llegada->peso;
                    out<< "\t\t" << colaPrioridad->obtenerInicio()->llegada->peso;
                    qDebug()<< "\t\t" << colaPrioridad->obtenerInicio()->origen->Nombre << "/" << colaPrioridad->obtenerInicio()->llegada->Nombre;
                    out << "\t\t" << colaPrioridad->obtenerInicio()->origen->Nombre << "/" << colaPrioridad->obtenerInicio()->llegada->Nombre;
                    camino.InsertarFinal(colaPrioridad->obtenerInicio()->origen, colaPrioridad->obtenerInicio()->llegada,
                                        colaPrioridad->obtenerInicio()->llegada->peso);
                    resueltos.InsertarFinal(colaPrioridad->obtenerInicio()->origen);
                    resueltos.InsertarFinal(BuscarVerticepos(colaPrioridad->obtenerInicio()->llegada->codigo));
                    resueltosAux.InsertarFinal(BuscarVerticepos(colaPrioridad->obtenerInicio()->llegada->codigo));
                }
                qDebug() << endl;
                out<<endl;
            }
            colaPrioridad->eliminarCoincidencias(colaPrioridad->obtenerInicio()->llegada);
            qDebug()<<"#########################################################################################################################"<<endl;
            out << "#########################################################################################################################"<<endl;
            out << endl;
            qDebug()<<endl;
            //Proceso para el resto
            while(resueltos.largoLista()!= tamanio()){
                //qDebug() << "Entro al While";
                NodoLista *aux = resueltosAux.primero;
                resueltos.MostrarLista();
                //qDebug() << "Paso de mostrar";
                while(aux){
                    //qDebug() << "Entro al while 2";
                    nodo = BuscarVerticepos(aux->valor->CodigoVertice);
                    //qDebug() << "Cargo el nodo";
                    if(nodo != NULL){
                        //qDebug() << "Entro al if";
                        //qDebug()<<nodo->NombrePais<<endl;
                        for (t = nodo->siguiente_ady; t != NULL; t=t->siguiente_ady){
                            //qDebug() << "Entro al for";
                            colaPrioridad->Insertar(nodo, t, t->peso + pesoTotal);
                        }
                        //qDebug() << "Salgo del for";
                    }
                    aux = aux->siguiente;
                    //qDebug() << "Avanzo en el while 1";
                }

                colaPrioridad->MostrarLista();
                qDebug() << "Paso de mostrar 2";
                //peso minimo
                qDebug() << "\t\t\t\t\t\t" << colaPrioridad->obtenerInicio()->llegada->peso;
                out << "\t\t\t\t\t\t" << colaPrioridad->obtenerInicio()->llegada->peso;
                //peso total
                qDebug() << "\t\t" << colaPrioridad->obtenerInicio()->peso;
                out << "\t\t" << colaPrioridad->obtenerInicio()->peso;
                pesoTotal = colaPrioridad->obtenerInicio()->peso;
                //ultima conexion
                qDebug() << "\t\t" << colaPrioridad->obtenerInicio()->origen->Nombre << "/" << colaPrioridad->obtenerInicio()->llegada->Nombre << endl;
                out << "\t\t" << colaPrioridad->obtenerInicio()->origen->Nombre << "/" << colaPrioridad->obtenerInicio()->llegada->Nombre << endl;
                //para saber camino despues
                camino.InsertarFinal(colaPrioridad->obtenerInicio()->origen, colaPrioridad->obtenerInicio()->llegada, colaPrioridad->obtenerInicio()->peso);
                resueltos.InsertarFinal(colaPrioridad->obtenerInicio()->origen);
                resueltos.InsertarFinal(BuscarVerticepos(colaPrioridad->obtenerInicio()->llegada->codigo));
                resueltosAux.BorrarFinal();
                resueltosAux.InsertarFinal(BuscarVerticepos(colaPrioridad->obtenerInicio()->llegada->codigo));

                colaPrioridad->eliminarCoincidencias(colaPrioridad->obtenerInicio()->llegada);
                qDebug()<<"#########################################################################################################################"<<endl;
                out<<"#########################################################################################################################"<<endl;
                out<<endl;
            }
            qDebug() << "Lo que sea";
            camino.MostrarCamino(BuscarVerticepos(fin));
            qDebug() << "FIN!";
        }
        archivo.flush();
        archivo.close();
    }
}

//Algoritmo de Prim
void Grafo::Prim(int cod){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Prim.txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        EncontrarNodo(cod);
        if(Elemento != NULL){
            int i, j, z, e, min, Coste[TamArr], Mas_cerca[TamArr], Con[TamArr], VectMc[TamArr];
            long ct;
            e = Elemento->pos;
            CrearMatrizValoradaNoDirigida();
            qDebug() << "Algoritmo de Prim: " << endl;
            out << "Algoritmo de Prim: " << endl;
            //Inicializa el vector de conjuntos
            for(i = 0; i < cant; i++){
                Con[i] = 0;
                VectMc[i] = 0;
            }
            ct = 0;
            //Visita el primer vertice
            Con[e] = 1;
            //Carga los pesos del primer vector en el vector de comparacion
            for (i = 0;i < cant; i++){
                if(i != e){
                    Coste[i] = matTemporal[e][i];
                    Mas_cerca[i] = e;
                }
            }
            qDebug() << "Aristas seleccionadas: " << endl;
            out << "Aristas seleccionadas: " << endl;
            for(i = 0; i < cant; i++){
                if(i != e){
                    min = Coste[e+1];
                    z = e+1;
                    //busca el menor de los pesos
                    for(j = 0; j < cant; j++){
                        if((j != e) & (j != e+1)){
                            if(Coste[j] < min){
                                min = Coste[j];
                                z = j;
                            }
                        }
                    }
                    if(min != INF){
                        VectMc[i] = min;
                        //suma el peso
                        ct = ct + min;
                        //marca el valor para no repetirlo
                        //Imprime la arista que selecciono como minima
                        BuscarVerticePos(z);
                        qDebug() << Elemento->Nombre << " -> ";
                        out << Elemento->Nombre << " -> ";
                        BuscarVerticePos(Mas_cerca[z]);
                        qDebug() << Elemento->Nombre << endl;
                        out << Elemento->Nombre << endl;
                        //lo marca como inf para no tomarlo en cuenta
                        Coste[z] = INF;
                    }
                    Con[z] = 1;
                    //verifica ciclos
                    for(j = 0; j < cant; j++){
                        if(j != e){
                            if((matTemporal[z][j] < Coste[j]) & (Con[j] == 0)){
                                Coste[j] = matTemporal[z][j];
                                Mas_cerca[j] = z;
                            }
                        }
                    }
                }
            }
            qDebug() << endl << "Pesos: " << endl;
            out << endl << "Pesos: " << endl;
            qDebug() << "{ ";
            out << "{ ";
            for(i = 0; i < cant; i++){
                if(VectMc[i] != 0){

                    qDebug() << VectMc[i] << " ";
                    out << VectMc[i] << " ";
                }
            }
            qDebug() << "}" << endl;
            out << "}" << endl;
            qDebug() << endl << "El costo es: " << ct << endl;
            out << endl <<"El costo es: " << ct << endl;
        }
    }
    else{
        qDebug()<<"Grafo Vacio\n";
    }
    archivo.flush();
    archivo.close();
}

//Algoritmo de kruskal

void Grafo::Kruskal(){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/kruskal.txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "Error en el kruskal";
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        int i, j, ct;
        //Ordena las aristas en orden ascendente y se las sede a listaOr
        ListaInt listaOr = OrdenarAristas();
        NodoListaInt *imp;
        qDebug()<<"Algoritmo de Kruskal:" << endl;
        out << "Algoritmo de Kruskal: " << endl;
        if(listaOr.PrimerNodo != NULL){
            //imprime la primer arista (menor)
            qDebug() << "Aristas seleccionadas: " << endl;
            out << "Aristas seleccionadas: " << endl;
            imp = listaOr.PrimerNodo;
            BuscarVerticePos(imp->partida);
            qDebug()<<Elemento->Nombre<<" -> ";
            out<<Elemento->Nombre<<" -> ";
            BuscarVerticePos(imp->llegada);
            qDebug()<<Elemento->Nombre<<" Peso: "<<imp->peso<<endl;
            out<<Elemento->Nombre<<" Peso: "<<imp->peso<<endl;
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
                    qDebug()<<Elemento->Nombre<<" -> ";
                    out<<Elemento->Nombre<<" -> ";
                    BuscarVerticePos(imp->llegada);
                    qDebug()<<Elemento->Nombre<<" Peso: "<<imp->peso<<endl;
                    out<<Elemento->Nombre<<" Peso: "<<imp->peso<<endl;
                    //Inserta la arista que no genero ciclos
                    matTemporal[imp->partida][imp->llegada]=1;
                    matTemporal[imp->llegada][imp->partida]=1;
                }
            }
            qDebug()<<endl<<"El costo es: "<<ct<<endl;
            out<<endl<<"El costo es: "<<ct<<endl;
            imp=NULL;
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

//Obtiene los puntos de articulacion de un grafo
void Grafo::PuntosArticulacion(int cod,int nodo){
    QFile archivo("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/Puntos de articulacion.txt");
    if(!archivo.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "Error en el archivo Puntos de Articulacion";
        return;
    }
    QTextStream out(&archivo);
    if(!VacioGrafo()){
        //Crea el grafo no dirigido
        Grafo gnd = CreaGrafoNoDirigido();
        //Crea el arbol-nario
        ArbolNario nuevoArbol;
        delete gnd.Arbol.Raiz;
        gnd.Arbol = nuevoArbol;
        //Genera el grafo y pone todas las aristas de retroceso
        gnd.GenerarArbolN(cod);
        //Imprime el Arbol y va poniendo los nums
        gnd.Arbol.Preorden(nodo);
        out << endl;
        qDebug() << endl;
        //Pone los bajos de cada vertice
        gnd.Arbol.PostOrdenAR();
        //Compara bajo(hijo)>=Num(padre) para cada vertice exceptuando la raiz
        gnd.Arbol.EsPuntoArticulacion(nodo);
    }
    else
        qDebug()<<"Grafo Vacio\n";
}

//Crear la matriz de valorada
void Grafo::CrearMatrizValorada(){
    NodoGrafo *p = PrimerNodo;
    NodoAdyacente *temp;
    //Inicializa cada valor en Infinito
    int h, g;
    for(h = 0; h < cant; h++){
        for(g = 0; g < cant; g++){
            matTemporal[h][g] = INF;
        }
    }
    if(p != NULL){
        int i;
        for(i = 0; i < cant; i++){
            temp = p->siguiente_ady;
            while(temp != NULL){
                matTemporal[i][temp->pos] = temp->peso;
                temp = temp->siguiente_ady;
            }
            p = p->sig_vertice;
        }
    }
    temp = NULL;
    p = NULL;
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
        while((p!=NULL) & (enc==false)){
            if(p->CodigoVertice==val){
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
    if(VacioGrafo()){
        Elemento = NULL;
    }
    else{
        bool enc = false;
        NodoGrafo *p = PrimerNodo;
        while((p != NULL) & (enc == false)){
            if(p->pos == vas){
                enc = true;
            }
            else{
                p = p->sig_vertice;
            }
        }
        Elemento = p;
        p = NULL;
        delete p;
    }
}

//Encuentra al nodo de origen y retorna dicho nodo

pNodoGrafo Grafo::BuscarVerticepos(int vas){
    if(VacioGrafo()){
        return NULL;
    }
    else{
        NodoGrafo *primer_Nodo=PrimerNodo;
        while(primer_Nodo!=NULL){
            if(primer_Nodo->CodigoVertice == vas){
                return primer_Nodo;
            }
            else{
                primer_Nodo=primer_Nodo->sig_vertice;
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
        for(i=0;((i<cant) & (encCiclo==false));i++){
            if ((matVisitas[i]==0) & (matTemporal[lle][i]!=INF)){
                GeneraCiclosaux(i,part);
            }
        }
    }
}

//Ordena las aristas de menor a mayor y retorna la lista de ellas
ListaInt Grafo::OrdenarAristas(){
    CrearMatrizValorada();
    ListaInt listaOr;
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

//Crea el grafo no dirigido
Grafo Grafo::CreaGrafoNoDirigido(){
    Grafo gi;
    //Carga los vertices
    gi.CargarPaises();
    int codp = 0, codl = 0;
    int peso;
    QStringList data;
    QString line;
    QFile encabezados("/home/shiki/Documentos/Datos/Proyecto 2/Grafos/AristasGG.txt");
    if(!encabezados.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Error archivo Aristas no existe\n";
        return gi;
    }
    else{
        QTextStream in(&encabezados);
        while(!in.atEnd()){
            line = in.readLine();
            data = line.split(";");
            codp = data.at(0).toInt();
            codl = data.at(1).toInt();
            peso = data.at(2).toInt();
            gi.InsertaAristas(codp,codl,peso);
            //Inserta la arista invertida
            gi.InsertaAristas(codl,codp,peso);
        }
    }
    gi.CrearMatrizAdyacencia();
    encabezados.close();
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
                        Arbol.Insertar(Arbol.Raiz->datos,1,Elemento->CodigoVertice);
                    else
                        Arbol.Insertar(0,1,Elemento->CodigoVertice);
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
void Grafo::GenerarArbolNaux(NodoGrafo *a){
    //Visitar
    int i;
    matVisitas[a->pos] = 1;
    matPosVis[las] = a->pos;
    las++;
    NodoAdyacente *t;
    for (t = a->siguiente_ady; t != NULL; t = t->siguiente_ady){
        if (matVisitas[t->pos] == 0){
            BuscarVerticePos(t->pos);
            Arbol.Insertar(a->CodigoVertice,0,Elemento->CodigoVertice);
            GenerarArbolNaux(Elemento);
        }
    }
    t = NULL;
    delete t;
    for(i = 0; i < cant; i++){
        BuscarVerticePos(i);
        if(EsAdyacente(a,Elemento->CodigoVertice)){
            if(matVisitas[i]==0){
                Arbol.Insertar(a->CodigoVertice,0,Elemento->CodigoVertice);
                GenerarArbolNaux(Elemento);
            }
            else{
                Arbol.EncontrarElem(Elemento->CodigoVertice);
                if(!Arbol.EsHijo(a->CodigoVertice,Arbol.ElementoB) & (Elemento->CodigoVertice!=a->CodigoVertice)){
                    Arbol.insertarAR(a->CodigoVertice,Elemento->CodigoVertice);
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
        if(p->codigo==cod){
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

//Retorna si el grafo es conexo o no
bool Grafo::EsConexo(){
    NodoGrafo *nodoG = PrimerNodo;
    NodoAdyacente *nodoA;
    NodoLista lista;
    if (nodoG == NULL){
        qDebug() << "Grafo vacio" << endl;
        return false;
    }
    else{
        if(lista.buscarElemento(nodoG->Nombre) == false){
                    lista.InsertarFinal(nodoG->Nombre);
        }
        while (nodoG!=NULL&&lista.buscarElemento(nodoG->Nombre)==true){
            nodoA=nodoG->siguiente_ady;
            while(nodoA!=NULL){
                if (lista.buscarElemento(nodoA->Nombre)==false){
                    lista.InsertarFinal(nodoA->Nombre);
                    qDebug() << nodoA->Nombre << "->";
                }
                nodoA=nodoA->siguiente_ady;
            }
            nodoG=nodoG->sig_vertice;
        }
        if (lista.largoLista()==tamanio()){
            return true;
        }
        else{
            return false;
        }
    }
}
