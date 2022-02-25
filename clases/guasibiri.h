#ifndef GUASIBIRI_H
#define GUASIBIRI_H
#include <map>
using namespace std;
class guasibiri
{
private:
    int primitiva[10][10];// tabla de conexion de nodos
    int corto[10][10];// tabla con el costo menor para cada nodo
    int nodos;// numero de nodos de la red
    char CC[10][10];//tabla con el camino mas corto para cada nodo
    map<int,char> rednodos;// diccionarrio con la posicion del nodo
    map<char,int> inrednodos;// inverso del rednodos
public:
    guasibiri();
    void xeno();
    void cargarArchivo();
    void agregarRed();
    void eliminarRed();
    void caminoYcosto();
};
#endif // GUASIBIRI_H
