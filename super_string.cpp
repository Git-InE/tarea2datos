#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class super_string {
    private:

        struct nodo {                                               // Struct 

            nodo *left = nullptr, *right = nullptr;                 // Definimos *left y *right como puntero nulos
            int index;                                              // Indice
            char c;                                                 // Elemento
            nodo(int index, char c){}
            nodo(){}
            };
            
        int height = 0;                                             // Altura del árbol
        int length = 0;                                             // Largo del super-string
        nodo* root = nullptr;                                       // Raíz del super-string
        void inordenArreglo(nodo* nodoActual, nodo** arreglo, int& indice);
        void inordenIndice(nodo* nodoActual, int& indice);
        void reversoHelp(nodo* root);
        void limpiarRecursivo(nodo*& nodoActual);                   //nuevo
        void stringizarRecursivo(nodo* nodoActual, string &str);
        void juntarRecursivo(nodo* nodoActual, super_string &ss_total);
        int calcularAltura(nodo* nodoActual);
        void recortarHelp(nodo*& nodoActual, nodo** arreglo, int inicio, int fin);
    public:
        bool esArbol = false;
        super_string(){};
        void juntar(super_string &s);
        void nuevoNodo(char c, int index);
        void insertar(int index, char c);
        void agregar(char c);                                       // Insertar un caracter en la última posición
        void separar(int i, super_string &a, super_string &b);      // En la izquierda esta el super_string a y en la derecha el super_string despuesDe
        void limpiar();                                             // Se deben borrar todos los nodos del super-string
        void reverso();                                             // No debe cambiar la altura del árbol
        int recortar();                                             // Retorna this->height después de recortar
        string stringizar();                                        // Debe ser O(n)     
};
//REVISAR
int super_string::recortar() {
    if (root == nullptr) return 0;
    esArbol = true;
    nodo** arreglo = new nodo*[length];
    int indice = 0;
    inordenArreglo(root, arreglo, indice);
    recortarHelp(root, arreglo, 0, length - 1);
    inordenIndice(root, indice=0);
    delete[] arreglo;
    return height=calcularAltura(root);
}

void super_string::inordenArreglo(nodo* nodoActual, nodo** arreglo, int& indice) { //lo mismo que stringizar pero en un arreglo ahora
    if (nodoActual == nullptr) return;
    inordenArreglo(nodoActual->left, arreglo, indice);
    arreglo[indice++] = nodoActual;

    inordenArreglo(nodoActual->right, arreglo, indice);
}

void super_string::recortarHelp(nodo*& nodoActual, nodo** arreglo, int inicio, int fin) {
    if (inicio > fin) {
        nodoActual = nullptr;
        return;
    }
    int medio = (inicio + fin) / 2;
    if (arreglo[medio] == nullptr) {
        return;
    }
    if (medio == 0){
        nuevoNodo(arreglo[medio]->c,arreglo[medio]->index);
    }
    nodoActual = arreglo[medio];
    if (nodoActual == nullptr) {
        return;
    }
    recortarHelp(nodoActual->left, arreglo, inicio, medio - 1);
    recortarHelp(nodoActual->right, arreglo, medio + 1, fin);
}

int super_string::calcularAltura(nodo* nodoActual) {
    if (nodoActual == nullptr) return 0;
    int alturaIzquierda = calcularAltura(nodoActual->left);
    int alturaDerecha = calcularAltura(nodoActual->right);
    return 1 + max(alturaIzquierda, alturaDerecha);
}
//.......................................................................................................

void super_string::nuevoNodo(char c, int index){
    nodo* nuevo = new nodo(index, c);
    nuevo->c = c;
    nuevo->index = index;
    return;
}
void super_string::insertar(int index, char c) {
        nodo* nuevoNodo = new nodo(index, c);
        if (root == nullptr) {
            root = nuevoNodo;
            length++;
            height = 1;
            return;
        }

        nodo* actual = root;
        nodo* padre = nullptr;
        while (actual != nullptr) {
            padre = actual;
            if (index < actual->index)
                actual = actual->left;
            else if (index > actual->index)
                actual = actual->right;
            else // índice duplicado, puedes manejar este caso según tus necesidades
                return;
        }

        if (index < padre->index)
            padre->left = nuevoNodo;
        else
            padre->right = nuevoNodo;

        length++;
        height = calcularAltura(root);
    }

void super_string::separar(int i, super_string& izquierdo, super_string& derecho) {
    if (i >= length)
        return;

    if (esArbol == true) {
        nodo** enOrden = new nodo*[length];
        int indice = 0;
        inordenArreglo(root, enOrden, indice);
        recortarHelp(izquierdo.root, enOrden, 0, i - 1);
        recortarHelp(derecho.root, enOrden, i, length - 1);
        izquierdo.length = i;
        derecho.length = length - i;
        izquierdo.height = calcularAltura(izquierdo.root);
        derecho.height = calcularAltura(derecho.root);

        delete[] enOrden;
    }
    else{
        if (i>length) return;
        super_string aux;
        nodo* temp = izquierdo.root;
        int round=0;
        while(temp!=nullptr){
            round++;
            if (round<=i){
                aux.agregar(temp->c);
            }
         else{
                derecho.agregar(temp->c);
            }
            temp=temp->right;
        }
        izquierdo=aux;
    }
}

//.......................................................................................................
void super_string::reverso() {
    if (root == nullptr) return;
    reversoHelp(root);
    int indice = 0;
    inordenIndice(root, indice);
}
void super_string::reversoHelp(nodo* root) {
    if (root == nullptr) return;

    // Intercambiar los subárboles izquierdo y derecho
    nodo* temp = root->left;
    root->left = root->right;
    root->right = temp;
    // Revertir los subárboles izquierdo y derecho recursivamente
    reversoHelp(root->left);
    reversoHelp(root->right);
}
// ACTUALIZA INDICES
void super_string::inordenIndice(nodo* nodoActual, int& indice) {
    if (nodoActual == nullptr) return;
    inordenIndice(nodoActual->left, indice);
    nodoActual->index = indice++;
    inordenIndice(nodoActual->right, indice);
}
//.......................................................................................................
string super_string::stringizar() {
    string str;
    stringizarRecursivo(root, str);
    return str;
}

void super_string::stringizarRecursivo(nodo* nodoActual, string& str) {
    if (nodoActual == nullptr) return;
    stringizarRecursivo(nodoActual->left, str);
    str += nodoActual->c;
    stringizarRecursivo(nodoActual->right, str);
}

//Agregar esta listo

void super_string::agregar(char c){
    if (c == '\0') return;
    nodo* nuevo = new nodo(length, c); // Creamos un espacio de memoria para el nuevo nodo
    nuevo->c = c;
    if (root == nullptr){              // Caso en el que el arbol este vacio 
        root = nuevo;                  // El nodo sera la raiz
    } 
    else
    {                                  // Caso en donde ya exista una raiz
        nodo* temp = root;
        while (temp->right){           // Mientras haya un nodo a su derecha
            temp = temp->right;        // va la siguiente nodo
            }
                                       // Saldra del ciclo cuando llegue al ultimo nodo del arbol
        temp->right = nuevo;
        nuevo->index = height+=1;          // Inserta el nuevo nodo (nuevo) a la derecha del ultimo nodo, el cual pasa a ser el PEN-ULTUMO nodo. 
    }
    length++;                          // El largo del super string crece en 1 puesto que aumentamos en 1 caracter su largo
}

void super_string::juntar(super_string &s) {
    juntarRecursivo(s.root, *this);
    length += s.length;
    height = calcularAltura(root);
}

void super_string::juntarRecursivo(nodo* nodoActual, super_string &ss_total) {
    if (nodoActual == nullptr) return;

    juntarRecursivo(nodoActual->left, ss_total);
    ss_total.agregar(nodoActual->c);
    juntarRecursivo(nodoActual->right, ss_total);
}
//-----------------------------------------------------------------------------
void super_string::limpiar() {
    limpiarRecursivo(root);
    root = nullptr;
    height = 0;
    length = 0;
}

void super_string::limpiarRecursivo(nodo*& nodoActual){
    if (nodoActual != nullptr) {
        limpiarRecursivo(nodoActual->left);
        limpiarRecursivo(nodoActual->right);
        delete nodoActual;
        nodoActual = nullptr;
    }
}
//SOLO FUNCIONA ANTES DE RECORTAR----------------------------------------------
/* void super_string::separar(int i, super_string &a, super_string &despuesDe){
    if (i > length) return;
    super_string aux;
    nodo* temp = a.root;
    int round=0;
    while(temp!=nullptr){
        round++;
        if (round<=i){
            aux.agregar(temp->c);
        }
        else{
            despuesDe.agregar(temp->c);
        }
        temp=temp->right;
    }
    a=aux;
}
*/