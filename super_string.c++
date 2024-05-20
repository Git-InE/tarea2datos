#include <iostream>
#include <string>
using namespace std;
class super_string {
    private:

        struct nodo {                                               // Struct 

            nodo *left = nullptr, *right = nullptr;                 // Definimos *left y *raigth com puntero nulos
            int index;                                              // Indice
            char c;                                                 // Elemento
            nodo(int index, char c){}
            nodo(){}
            };

        int height = 0;                                             // Altura del árbol
        int length = 0;                                             // Largo del super-string
        nodo* root = nullptr;                                       // Raíz del super-string

    public:
        super_string(){};
        void limpiarRecursivo(nodo*& nodoActual);                   //nuevo
        void juntar(super_string &s);
        void agregar(char c);                                       // Insertar un caracter en la última posición
                                                                    // En la izquierda esta el super_string a y en la derecha el super_string b
        
        void Show();
        void separar(int i, super_string &a, super_string &b);

        
        void reverso();                                             // No debe cambiar la altura del árbol
        int recortar();                                             // Retorna this->height después de recortar
        string stringizar();                                        // Debe ser O(n)
        void stringizar(nodo* nodoActual, string &str);
        void limpiar();                                             // Se deben borrar todos los nodos del super-string
        


};
//terminado...

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
    super_string aux;
    nodo* temp = a.root;
    int round=0,nuevo_indice=0;
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
void super_string::juntar(super_string &s){
    super_string ss_total;
    nodo* temp1 = root;
    nodo* temp2 = s.root;
    while (temp1!= nullptr){
        ss_total.agregar(temp1->c);
        temp1 = temp1->right;
    }
    while (temp2!= nullptr){
        ss_total.agregar(temp2->c);
        temp2 = temp2->right;

    }
    root = ss_total.root; 
}

/*

void super_string::juntar(super_string &s) {
    nodo* temp = root;
    while (temp->right != nullptr){
        temp = temp->right;
    }
    temp->right = s.root;
}

void super_string::stringizar(nodo* n, string &str) {
    if(n){
        stringizar(n->left, str);
        str += n->c;
        stringizar(n->right, str);
    }
}



string super_string::stringizar(){
    string str;
    stringizar(root, str);
    cout << str;
    return str;
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
*/