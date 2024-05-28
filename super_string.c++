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
        void recortarRecursivo(nodo*& nodoActual, const string& str, int inicio, int fin);
        void limpiarRecursivo(nodo*& nodoActual);                   //nuevo
        void stringizarRecursivo(nodo* nodoActual, string &str);
        void juntarRecursivo(nodo* nodoActual, super_string &ss_total);
    public:
        super_string(){};
        void juntar(super_string &s);
        void agregar(char c);                                       // Insertar un caracter en la última posición
        void separar(int i, super_string &a, super_string &b);      // En la izquierda esta el super_string a y en la derecha el super_string b
        void Show();
        void limpiar();                                             // Se deben borrar todos los nodos del super-string
        void reverso();                                             // No debe cambiar la altura del árbol
        int recortar();                                             // Retorna this->height después de recortar
        string stringizar();                                        // Debe ser O(n)     
};
//REVISAR
int super_string::recortar() {
    if (root == nullptr) return 0;
    // Obtener el string del árbol en inorden
    string str = stringizar();
    int largo = length;
    int altura = (length)>0 ? log2(length) + 1 : 0;
    // Reemplazar el árbol con un nuevo árbol que contenga el string
    limpiar();
    recortarRecursivo(root, str, 0, str.length());
    height = altura;
    return height;
}

void super_string::recortarRecursivo(nodo*& nodoActual, const string& str, int inicio, int fin) {
    if (inicio > fin) return;
    int medio = (inicio + fin) / 2; 
    nodo* nuevoNodo = new nodo(medio, str[medio]);
    nuevoNodo->c = str[medio];
    if (nodoActual == nullptr) {
        nodoActual = nuevoNodo;
    }
    if (fin - inicio <= 2){         //caso par (partiendo del 0)
        if (medio - 1 >= 0)
            {nodoActual->left = new nodo(medio - 1, str[medio - 1]);
            nodoActual->left->c = str[medio-1];
            }
        if (medio + 1 <= str.length()){
            nodoActual->right = new nodo(medio + 1, str[medio + 1]);
            nodoActual->right->c = str[medio+1];
            }
        return;
    }
    if (fin - inicio == -2){         //caso par (partiendo del 0)
        nodoActual->left = new nodo(medio, str[medio]);
        nodoActual->left->c = str[++medio];
        nodoActual->c = str[medio];
        if (medio + 1 <= str.length()){
            nodoActual->right = new nodo(medio + 1, str[medio + 1]);
            nodoActual->right->c = str[medio+1];
            }
        return;
        }
    
    // E-l-C-a-r-l-o-s-e-s-b-u-e-n-o
    recortarRecursivo(nodoActual->left, str, inicio, medio);
    recortarRecursivo(nodoActual->right, str, medio+1, fin);

}

//REVISAR
//.......................................................................................................
//terminado...

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

//Show esta listo

void super_string::Show(){
    nodo* temp=root;
    temp->index=0;
    cout<<temp->c;
    while (temp->right != nullptr){
        temp=temp->right; 
        cout<<temp->c; 
        //cout<<temp->c; 
    }
    cout<<endl;
    //cout<<length<<endl;
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


//Separar esta listo

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

    juntarRecursivo(nodoActual->left, ss_total);
    ss_total.agregar(nodoActual->c);
    juntarRecursivo(nodoActual->right, ss_total);
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
void super_string::reverso(){
    if (root == nullptr) return;
    reversoHelp(root);
}