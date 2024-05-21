#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Funciones: 
#include "super_string.c++"


int main(){

    // Apertura de archivo
    ifstream archivo;
    archivo.open("prueba.txt",ios::in);

    // Definicion de variables
    string linea;

    // Creacion de objeto tipo super_string
    super_string ss1;
    super_string ss2;
    super_string ss3;
	
    // Desarrrollo
    if (!archivo.is_open()){
        cerr << "Error al abrir el archivo." << endl;
        return 1;
	}
    /*
    ss1.agregar('H');
    ss1.agregar('O');
    ss1.agregar('L');
    ss1.agregar('A');
    ss1.agregar('_');
    ss1.agregar('M');
    ss1.agregar('U');
    ss1.agregar('N');
    ss1.agregar('D');
    ss1.agregar('O');
    */

    
    while (getline(archivo, linea)){
        istringstream iss(linea);
        string operacion;
        iss >> operacion;               // Pregunta por operacion
        if (operacion == "MOSTRAR"){    // Operacion MOSTRAR
            cout << ss1.stringizar() << endl;  
        }
        if (operacion == "INSERTAR"){   // Operacion INSERTAR
            int i;                      //posicion i
            string s;                   //String que se quiere insertar
            iss >> i >> s;
            ss1.separar(i,ss1,ss2);
            for(int o=0;o<s.length();o++){
                ss1.agregar(s[o]);
                }
            ss1.juntar(ss2);
            ss2.limpiar();
        }
        if (operacion == "ELIMINAR"){    //  Operacion ELIMINAR
            int l;                      //posicion l
            int r;                      //posicion r
            iss >> l >> r;
            ss1.separar(l,ss1,ss2);     //se separa ss1 y se almacena la parte a borrar en ss2
            ss2.separar(r-l+1,ss2,ss3); //se separa los elementos a borrar de los que se deben mantener
            ss1.juntar(ss3);            //se junta ss1 con ss3
            ss2.limpiar();
            ss3.limpiar();        
        }
        if (operacion == "REVERSO"){ 
            int i;
            int j;
            iss >> i >> j;
            ss1.separar(i,ss1,ss2); // ss2 contiene la parte a revertir y la parte que no
            ss2.reverso(); // Se revierte ss2
            ss2.separar(i-j,ss2,ss3); // ss3 contiene la parte que no se revertirá
            ss1.juntar(ss3); // Se junta ss1 con la parte que no se revertió (ss3)  
            ss1.juntar(ss2); // Se junta ss1 con la parte revertida (ss2)
            ss3.limpiar();
            ss2.limpiar();
        }
    }
        
    archivo.close();
    return 0;
}