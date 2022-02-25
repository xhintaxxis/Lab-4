#include <iostream>
#include <guasibiri.h>
#include <map>
using namespace std;

int main(){
   guasibiri red;
   while(true){
        int opcion=2;
        char continuar=78;
        while(true){
            cout<<"Seleccione la opcion deseada:\n"<<endl;
            cout<<"-Para generar una red aleatoria digite 1.\n"<<endl;
            cout<<"-Para cargar una red desde un archivo digite 2.\n"<<endl;
            cout<<"-Agregar una un nodo a la red digite 3.\n"<<endl;
            cout<<"-Eliminar una un nodo de la red digite 4.\n"<<endl;
            cout<<"-Conocer el camino de un nodo a otro y su costo digite 5.\n"<<endl;
            cout<<"---> ";
            cin>>opcion;
            cout<<endl;
            if(opcion>=1 and opcion<=5){
                break;
            }
            else{
                cout<<"LA OPCION INGRESADA NO ES CORRECTA.\n"<<endl;
            }
        }
        if(opcion==1){
            cout<<"la red aleatoria a sido agregada\n"<<endl;
        }
        else if(opcion==2){
            red.cargarArchivo();
            cout<<"Red cargada\n"<<endl;
        }
        else if(opcion==3){
            red.agregarRed();
        }
        else if(opcion==4){
            red.eliminarRed();
        }
        else if(opcion==5){
            red.caminoYcosto();
        }
        cout<<"Quieres salir?(S/N): ";
        cin>>continuar;
        cout<<endl;
        if(continuar==83){
            break;
        }
    }
    return 0;
}
