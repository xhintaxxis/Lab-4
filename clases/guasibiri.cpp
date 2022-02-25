#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <fstream>
#include "guasibiri.h"
using namespace std;

guasibiri::guasibiri()
{
    //crea una matriz simetrica con diagonal de ceros
        srand(time(NULL));
        nodos=2+rand()%7;
        for(int i=0;i<nodos;i++){
            primitiva[i][i]=0;
        }
        for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                if(i!=j){
                    primitiva[i][j]=rand()%12;
                }
            }
        }
        int cont=0;
        while(cont!=nodos){
            for(int i=0;i<nodos;i++){
                if(i!=cont){
                    if(primitiva[cont][i]!=primitiva[i][cont]){
                        primitiva[cont][i]=primitiva[i][cont];
                    }
                }
            }
            cont++;
        }
    // Fin del codigo de la matriz
    // Crea un diccionario para los nodos
        for(int i=0;i<nodos;i++){
            rednodos[i]=65+i;
        }
    // Fin del diccionario
        for(int i=0;i<nodos;i++){
           inrednodos[rednodos[i]]=i;
         }
    //Creacion de una matriz para guardar los caminos
        for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                if(i==j){
                    CC[j][i]=45;
                }
                else{
                    CC[j][i]=rednodos[i];
                }
            }
        }
    xeno();
}
void guasibiri::xeno(){
    for(int i=0;i<nodos;i++){
        for(int j=0;j<nodos;j++){
            if(primitiva[i][j]==0 and i!=j){
                corto[i][j]=100;
            }
            else {
                corto[i][j]=primitiva[i][j];
            }
        }
    }
    map<int,int> dic;

        /*for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                cout<<corto[i][j]<<" ";
            }
            cout<<endl;
        }*/
        int sum=0;
        int cont=0;
        int fila;
        int colum;
        int index=0;
        while(cont!=nodos){
            for(int i=0;i<nodos;i++){
                if(cont!=i){
                    colum=corto[i][cont];
                    for(int j=0;j<nodos;j++){
                        fila=corto[cont][j];
                        if(cont!=j){
                           sum=colum+fila;
                           index=corto[i][j];
                           if(sum<index){
                               corto[i][j]=sum;
                               CC[i][j]=(rednodos[cont]);
                           }
                        }
                    }
                }
            }
            cont++;
        }
        /*for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                cout<<primitiva[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
              cout<<corto[i][j]<<" ";
            }
            cout<<endl;
        }
        for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                cout<<char(CC[i][j])<<" ";
            }
            cout<<endl;
        }
*/
}

void guasibiri::cargarArchivo(){
    ifstream archivo;
    archivo.open("other.txt");
    char firstL[25];
    archivo.getline(firstL,30);
    nodos=int(firstL[0]-48);
    int cont=nodos;
    char *redesC=new char[nodos];
    for(int i=2;i<nodos+2;i++){
        redesC[i-2]=firstL[i];
        cont--;
    }
    char otherL[25];
    for(int i=0;i<nodos;i++){
        archivo.getline(otherL,25);
        for(int j=0;j<nodos*2;j++){
            if(otherL[j]!=44){
                primitiva[i][j/2]=otherL[j]-48;
            }
        }
    }
    cont=0;
    while(cont!=nodos){
        for(int i=0;i<nodos;i++){
            if(i!=cont){
                if(primitiva[cont][i]!=primitiva[i][cont]){
                    primitiva[cont][i]=primitiva[i][cont];
                }
            }
        }
        cont++;
    }
    for(int i=0;i<nodos;i++){
        rednodos[i]=redesC[i];
    }
    for(int i=0;i<nodos;i++){
       inrednodos[rednodos[i]]=i;
     }
    for(int i=0;i<nodos;i++){
        for(int j=0;j<nodos;j++){
            if(i==j){
                CC[j][i]=45;
            }
            else if(primitiva[i][j]!=0){
                CC[j][i]=rednodos[i];
            }
            else{
                CC[i][j]=45;
            }
        }
    }
    xeno();
    delete[] redesC;
    archivo.close();
}
void guasibiri::agregarRed(){
    if(nodos<=10){
    cout<<"El numero de redes que se puede agregar es "<<9-nodos<<"\n"<<endl;
    nodos=nodos+1;
    char caracter=73;
    cout<<"Redes ya registradas: ";
    for(int i=0;i<nodos-1;i++){
       cout<<rednodos[i]<<",";
    }
    cout<<"\n"<<endl;
    cout<<"ingrese la letra que para la red: ";
    cin>>caracter;
    cout<<endl;
    int posicion=nodos-1;
    int costo=0;
    primitiva[posicion][posicion]=0;
    for(int i=0;i<nodos-1;i++){
        cout<<"Ingrese el costo de "<<caracter<<" y "<<rednodos[i]<<" :";
        cin>>costo;
        cout<<endl;
        primitiva[posicion][i]=costo;
        primitiva[i][posicion]=costo;
    }
    rednodos[posicion]=caracter;
    inrednodos[caracter]=posicion;
    for(int i=0;i<nodos;i++){
        for(int j=0;j<nodos;j++){
            if(i==j){
                CC[j][i]=45;
            }
            else{
                CC[j][i]=rednodos[i];
            }
        }
    }
    xeno();
    cout<<"La red "<<caracter<<" ha sido agregada\n"<<endl;
    }
    else{
        cout<<"No se pueden agregar mas redes."<<endl;
    }
}

void guasibiri::eliminarRed(){
    char caracter=67;
    bool ver=false;
    int posicion=0;
    cout<<"Ingrese la red que quiere eliminar: ";
    cin>>caracter;
    cout<<endl;
    for(int i=0;i<nodos;i++){
        if(rednodos[i]==caracter){
            ver=true;
            posicion=i;
        }
    }
    if(ver==true){
        int next=posicion+1;
        int matrix[10];
        while(next<nodos){
            int j=0;
            int index=0;
            while(j<nodos){
                if(j!=posicion){
                    matrix[index]=primitiva[next][j];
                    index++;
                }
                j++;
            }
            int positionNew=next-1;
            char carDes=rednodos[next];
            rednodos[next-1]=carDes;
            for(int i=0;i<nodos;i++){
                primitiva[i][positionNew]=matrix[i];
                primitiva[positionNew][i]=matrix[i];
            }
            next++;
        }
    nodos--;
    for(int i=0;i<nodos;i++){
        for(int j=0;j<nodos;j++){
            if(i==j){
                CC[j][i]=45;
            }
            else{
                CC[j][i]=rednodos[i];
            }
        }
    }
    xeno();
    cout<<"Red "<<caracter<<" eliminada.\n"<<endl;
    }
    else{
        cout<<"la red no esta registrda.\n"<<endl;
    }
}
void guasibiri::caminoYcosto(){
    char in=65;
    bool ver=true;
    int psi=0;
    while(ver==true){
        cout<<"Ingrese el nodo inicial: ";
        cin>>in;
        cout<<endl;
        for(int i=0;i<nodos;i++){
            if(rednodos[i]==in){
                ver=false;
                psi=i;
            }
        }
        if(ver==false){
            break;
        }
        else{
            cout<<"El caracter ingresado no existe el la red\n"<<endl;
        }

    }
    ver=true;
    char end=66;
    int pse=0;
    while(ver==true){
        cout<<"Ingrese el nodo de destino: ";
        cin>>end;
        cout<<endl;
        for(int i=0;i<nodos;i++){
            if(rednodos[i]==end){
                ver=false;
                pse=i;
            }
        }
        if(ver==false){
            break;
        }
        else{
            cout<<"El caracter ingresado no existe el la red\n"<<endl;
        }

    }
    if(in==end){
        cout<<in<<"-->"<<end<<endl;
        cout<<endl;
        cout<<"costo=0"<<endl;
        cout<<endl;
    }
    else{
    int costo=corto[psi][pse];
    //ver=true;
    cout<<"El costo es de: "<<costo<<endl;
    //char camino[10];
    char letra=0;
    int desplazar=psi;
    cout<<in<<"-->";
    for(int i=0;i<nodos;i++){
        letra=CC[desplazar][pse];
        if(end==letra){
            break;
        }
        else{
            for(int j=0;j<nodos;j++){
                if(rednodos[j]==letra){desplazar=j;}
            }
            cout<<letra<<"-->";
        }
    }
    cout<<end<<endl;
}
}

