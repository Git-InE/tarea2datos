#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class super_string {
    private:

        struct nodo {                                               // Struct para representar un nodo en el árbol
            nodo *left = nullptr, *right = nullptr;                 // Punteros a los hijos izquierdo y derecho
            int index;                                              // Índice del nodo
            char c;                                                 // Carácter almacenado en el nodo
            nodo(int index, char c) {}                              // Constructor del nodo
            nodo() {}                                               // Constructor por defecto
        };
        
        int height = 0;                                             // Altura del árbol
        int length = 0;                                             // Longitud del super_string
        nodo* root = nullptr;                                       // Raíz del super_string

        void inordenArreglo(nodo* nodoActual, nodo** arreglo, int& indice);
        void inordenIndice(nodo* nodoActual, int& indice);
        void reversoHelp(nodo* root);
        void limpiarRecursivo(nodo*& nodoActual);
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

/*****
* int super_string::recortar()
******
* Crea un arreglo para almacenar los nodos para luego llama a las funciones auxiliares para recortar el arbol
******
* Input:
* Ninguno
******
* Returns:
* int, la altura del árbol después de recortar
*****/
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

/*****
* void super_string::inordenArreglo()
******
* Llena un arreglo con los nodos del árbol en recorrido inorden.
******
* Input:
* nodo* nodoActual: nodo actual que se va actualizando recursivamente
* nodo** arreglo: puntero a arreglo que se debe actualizar
* int& indice: índice para actualizar posición del arreglo
******
* Returns:
* Ninguno
*****/
void super_string::inordenArreglo(nodo* nodoActual, nodo** arreglo, int& indice) {
    if (nodoActual == nullptr) return;
    inordenArreglo(nodoActual->left, arreglo, indice);
    arreglo[indice++] = nodoActual;
    inordenArreglo(nodoActual->right, arreglo, indice);
}

/*****
* void super_string::recortarHelp()
******
* Función auxiliar para recortar el árbol y balancearlo.
******
* Input:
* nodo*& nodoActual: referencia al nodo actual
* nodo** arreglo: puntero al arreglo de nodos
* int inicio: índice de inicio del subarreglo
* int fin: índice de fin del subarreglo
******
* Returns:
* Ninguno
*****/
void super_string::recortarHelp(nodo*& nodoActual, nodo** arreglo, int inicio, int fin) {
    if (inicio > fin) {
        nodoActual = nullptr;
        return;
    }
    int medio = (inicio + fin) / 2;
    if (arreglo[medio] == nullptr) {
        return;
    }
    if (medio == 0) {
        nuevoNodo(arreglo[medio]->c, arreglo[medio]->index);
    }
    nodoActual = arreglo[medio];
    if (nodoActual == nullptr) {
        return;
    }
    recortarHelp(nodoActual->left, arreglo, inicio, medio - 1);
    recortarHelp(nodoActual->right, arreglo, medio + 1, fin);
}

/*****
* int super_string::calcularAltura()
******
* Calcula la altura del árbol.
******
* Input:
* nodo* nodoActual: nodo actual desde el cual se calcula la altura
******
* Returns:
* int, la altura del árbol
*****/
int super_string::calcularAltura(nodo* nodoActual) {
    if (nodoActual == nullptr) return 0;
    int alturaIzquierda = calcularAltura(nodoActual->left);
    int alturaDerecha = calcularAltura(nodoActual->right);
    return 1 + max(alturaIzquierda, alturaDerecha);
}

/*****
* void super_string::nuevoNodo()
******
* Crea un nuevo nodo con un carácter y un índice.
******
* Input:
* char c: carácter del nuevo nodo
* int index: índice del nuevo nodo
******
* Returns:
* Ninguno
*****/
void super_string::nuevoNodo(char c, int index) {
    nodo* nuevo = new nodo(index, c);
    nuevo->c = c;
    nuevo->index = index;
    return;
}

/*****
* void super_string::insertar()
******
* Inserta un nodo en el árbol en la posición indicada.
******
* Input:
* int index: índice donde se debe insertar el nodo
* char c: carácter del nuevo nodo
******
* Returns:
* Ninguno
*****/
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
        else // índice duplicado
            return;
    }

    if (index < padre->index)
        padre->left = nuevoNodo;
    else
        padre->right = nuevoNodo;

    length++;
    height = calcularAltura(root);
}

/*****
* void super_string::separar()
******
* Separa el super_string en dos partes, manteniendo la estructura del árbol.
******
* Input:
* int i: índice donde se debe separar el super_string
* super_string& izquierdo: referencia al super_string izquierdo
* super_string& derecho: referencia al super_string derecho
******
* Returns:
* Ninguno
*****/
void super_string::separar(int i, super_string& izquierdo, super_string& derecho) {
    if (i >= length) return;

    if (esArbol) {
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
    } else {
        if (i > length) return;
        super_string aux;
        nodo* temp = izquierdo.root;
        int round = 0;
        while (temp != nullptr) {
            round++;
            if (round <= i) {
                aux.agregar(temp->c);
            } else {
                derecho.agregar(temp->c);
            }
            temp = temp->right;
        }
        izquierdo = aux;
    }
}

/*****
* void super_string::reverso()
******
* Invierte el super_string.
******
* Input:
* Ninguno
******
* Returns:
* Ninguno
*****/
void super_string::reverso() {
    if (root == nullptr) return;
    reversoHelp(root);
    int indice = 0;
    inordenIndice(root, indice);
}

/*****
* void super_string::reversoHelp()
******
* Función auxiliar que invierte el super_string recursivamente.
******
* Input:
* nodo* root: nodo raíz del subárbol actual
******
* Returns:
* Ninguno
*****/
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

/*****
* void super_string::inordenIndice()
******
* Actualiza los índices de los nodos en un recorrido inorden.
******
* Input:
* nodo* nodoActual: nodo actual
* int& indice: índice actual
******
* Returns:
* Ninguno
*****/
void super_string::inordenIndice(nodo* nodoActual, int& indice) {
    if (nodoActual == nullptr) return;
    inordenIndice(nodoActual->left, indice);
    nodoActual->index = indice++;
    inordenIndice(nodoActual->right, indice);
}

/*****
* string super_string::stringizar()
******
* Convierte el super_string a una cadena de caracteres.
******
* Input:
* Ninguno
******
* Returns:
* string, representación en cadena del super_string
*****/
string super_string::stringizar() {
    string str;
    stringizarRecursivo(root, str);
    return str;
}

/*****
* void super_string::stringizarRecursivo()
******
* Función auxiliar para convertir el super_string a una cadena de caracteres recursivamente.
******
* Input:
* nodo* nodoActual: nodo actual
* string& str: referencia a la cadena de caracteres
******
* Returns:
* Ninguno
*****/
void super_string::stringizarRecursivo(nodo* nodoActual, string& str) {
    if (nodoActual == nullptr) return;
    stringizarRecursivo(nodoActual->left, str);
    str += nodoActual->c;
    stringizarRecursivo(nodoActual->right, str);
}

/*****
* void super_string::agregar()
******
* Agrega un carácter al final del super_string.
******
* Input:
* char c: carácter a agregar
******
* Returns:
* Ninguno
*****/
void super_string::agregar(char c) {
    if (c == '\0') return;
    nodo* nuevo = new nodo(length, c); // Creamos un espacio de memoria para el nuevo nodo
    nuevo->c = c;
    if (root == nullptr) {              // Caso en el que el árbol esté vacío
        root = nuevo;                   // El nodo será la raíz
    } else {                            // Caso en donde ya exista una raíz
        nodo* temp = root;
        while (temp->right) {           // Mientras haya un nodo a su derecha
            temp = temp->right;         // Va al siguiente nodo
        }
        // Saldra del ciclo cuando llegue al último nodo del árbol
        temp->right = nuevo;
        nuevo->index = height += 1;     // Inserta el nuevo nodo (nuevo) a la derecha del último nodo, el cual pasa a ser el penúltimo nodo.
    }
    length++;                           // El largo del super_string crece en 1 puesto que aumentamos en 1 carácter su largo
}

/*****
* void super_string::juntar()
******
* Junta otro super_string al final del actual.
******
* Input:
* super_string &s: referencia al super_string a juntar
******
* Returns:
* Ninguno
*****/
void super_string::juntar(super_string &s) {
    juntarRecursivo(s.root, *this);
    length += s.length;
    height = calcularAltura(root);
}

/*****
* void super_string::juntarRecursivo()
******
* Función auxiliar para juntar dos super_strings recursivamente.
******
* Input:
* nodo* nodoActual: nodo actual del super_string a juntar
* super_string &ss_total: referencia al super_string total
******
* Returns:
* Ninguno
*****/
void super_string::juntarRecursivo(nodo* nodoActual, super_string &ss_total) {
    if (nodoActual == nullptr) return;
    juntarRecursivo(nodoActual->left, ss_total);
    ss_total.agregar(nodoActual->c);
    juntarRecursivo(nodoActual->right, ss_total);
}

/*****
* void super_string::limpiar()
******
* Limpia todos los nodos del super_string.
******
* Input:
* Ninguno
******
* Returns:
* Ninguno
*****/
void super_string::limpiar() {
    limpiarRecursivo(root);
    root = nullptr;
    height = 0;
    length = 0;
}

/*****
* void super_string::limpiarRecursivo()
******
* Función auxiliar para limpiar recursivamente todos los nodos del super_string.
******
* Input:
* nodo*& nodoActual: referencia al nodo actual
******
* Returns:
* Ninguno
*****/
void super_string::limpiarRecursivo(nodo*& nodoActual) {
    if (nodoActual != nullptr) {
        limpiarRecursivo(nodoActual->left);
        limpiarRecursivo(nodoActual->right);
        delete nodoActual;
        nodoActual = nullptr;
    }
}
