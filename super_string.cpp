#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class super_string {
    private:

        struct nodo {                                               // Struct 

            nodo *left = nullptr, *right = nullptr;                 // Definimos *left y *right com puntero nulos
            int index;                                              // Indice
            char c;                                                 // Elemento
            nodo(int index, char c){}
            nodo(){}
            };
            
        int height = 0;                                             // Altura del árbol
        int length = 0;                                             // Largo del super-string
        nodo* root = nullptr;                                       // Raíz del super-string
        void reversoHelp(nodo* root);
        void limpiarRecursivo(nodo*& nodoActual);                   //nuevo
        void stringizarRecursivo(nodo* nodoActual, string &str);
        void juntarRecursivo(nodo* nodoActual, super_string &ss_total);
        void recorrerInorden(nodo* nodoActual, nodo** arreglo, int& indice);
        int calcularAltura(nodo* nodoActual);
        void recortarHelp(nodo*& nodoActual, nodo** arreglo, int inicio, int fin);
        void separarRecursivo(nodo* nodoActual, int i, int& count, super_string &a, super_string &b);
    public:
        super_string(){};
        void juntar(super_string &s);
        void agregar(char c);                                       // Insertar un caracter en la última posición
        void separar(int i, super_string &a, super_string &b);      // En la izquierda esta el super_string a y en la derecha el super_string b
        void limpiar();                                             // Se deben borrar todos los nodos del super-string
        void reverso();                                             // No debe cambiar la altura del árbol
        int recortar();                                             // Retorna this->height después de recortar
        string stringizar();                                        // Debe ser O(n)     
};
//REVISAR

int super_string::recortar() {
    if (root == nullptr) return 0;

    nodo** arreglo = new nodo*[length];
    int indice = 0;
    recorrerInorden(root, arreglo, indice);
    recortarHelp(root, arreglo, 0, length - 1);
    delete[] arreglo;
    return height=calcularAltura(root);
}

void super_string::recorrerInorden(nodo* nodoActual, nodo** arreglo, int& indice) { //lo mismo que stringizar pero en un arreglo ahora
    if (nodoActual == nullptr) return;
    recorrerInorden(nodoActual->left, arreglo, indice);
    arreglo[indice++] = nodoActual;
    recorrerInorden(nodoActual->right, arreglo, indice);
}

void super_string::recortarHelp(nodo*& nodoActual, nodo** arreglo, int inicio, int fin) {
    if (inicio > fin) {
        nodoActual = nullptr;
        return;
    }
    int medio = (inicio + fin) / 2;
    nodoActual = arreglo[medio];
    recortarHelp(nodoActual->left, arreglo, inicio, medio - 1);
    recortarHelp(nodoActual->right, arreglo, medio + 1, fin);
}

int super_string::calcularAltura(nodo* nodoActual) {
    if (nodoActual == nullptr) return 0;
    int alturaIzquierda = calcularAltura(nodoActual->left);
    int alturaDerecha = calcularAltura(nodoActual->right);
    return 1 + max(alturaIzquierda, alturaDerecha);
}
//anteriores
//REVISAR
//.......................................................................................................
//terminado...

void super_string::reverso(){
    if (root == nullptr) return;
    reversoHelp(root);
}

void super_string::reversoHelp(nodo* root) {
    if (root == nullptr) return;

    // Intercambiar los subárboles izquierdo y derecho
    nodo* temp = root->left;
    root->left = root->right;
    root->right = temp;
    //cout<< "nodo actual: " << root->c << endl;
    // Revertir los subárboles izquierdo y derecho recursivamente
    reversoHelp(root->left);
    reversoHelp(root->right);
}

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


void super_string::separarRecursivo(nodo* nodoActual, int i, int& count, super_string &a, super_string &b) {
    if (nodoActual == nullptr) {
        return;
    }
    
    if (count < i) {
        separarRecursivo(nodoActual->left, i, count, a, b);
        
        if (a.root == nullptr) {
            a.root = nodoActual;
            nodoActual->left = nullptr;
            nodoActual->right = nullptr;
        } else {
            nodo* last = a.root;
            while (last->right != nullptr) {
                last = last->right;
            }
            last->right = nodoActual;
            nodoActual->left = nullptr;
            nodoActual->right = nullptr;
        }
        a.length++;
        a.height = max(a.height, nodoActual->index + 1);
        
        count++;
        if (nodoActual->right != nullptr) {
            separarRecursivo(nodoActual->right, i, count, a, b);
            }
    } else {
        b.root = nodoActual;
        b.length = length - a.length;
        b.height = height;
        nodoActual->left = nullptr;
    }
}
//SOLO FUNCIONA ANTES DE RECORTAR----------------------------------------------
void super_string::separar(int i, super_string &a, super_string &b){
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
            b.agregar(temp->c);
        }
        temp=temp->right;
    }
    a=aux;
}
//-----------------------------------------------------------------------------
void super_string::juntar(super_string &s) {
    if (root == nullptr) {
        root = s.root;
        height = s.height;
        length = s.length;
        return;
    }

    if (s.root == nullptr) {
        return; // No hay nada que juntar
    }

    super_string ss_total;
    juntarRecursivo(root, ss_total);
    juntarRecursivo(s.root, ss_total);

    root = ss_total.root;
    height = ss_total.height;
    length = ss_total.length;
}

void super_string::juntarRecursivo(nodo* nodoActual, super_string &ss_total) {
    if (nodoActual == nullptr) return;

    nodo* left = nodoActual->left;
    nodo* right = nodoActual->right;

    // Disconnect the node from the original super_string
    nodoActual->left = nullptr;
    nodoActual->right = nullptr;

    juntarRecursivo(left, ss_total);
    ss_total.agregar(nodoActual->c);
    juntarRecursivo(right, ss_total);
}

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