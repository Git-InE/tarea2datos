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
    super_string ss;
	
    // Desarrrollo
    if (!archivo.is_open()){
        cerr << "Error al abrir el archivo." << endl;
        return 1;
	}

    while (getline(archivo, linea)){
        istringstream iss(linea);
        string operacion;
        iss >> operacion;               // Pregunta por operacion
        if (operacion == "INSERTAR"){   // Operacion INSERTAR
            int i;                      //posicion i
            string S;                   //String que se quiere insertar
            iss >> i >> S;
        }
        if (operacion == "MOSTRAR"){    // Operacion MOSTRAR
            cout<<ss.stringizar()<<endl;  
        }
        }
        
    archivo.close();
    return 0;
}