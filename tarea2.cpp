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

    ss1.agregar('H');
    ss1.agregar('O');
    ss1.agregar('L');
    ss1.agregar('A');
    ss1.agregar('_');
    ss1.agregar('.');
    ss1.agregar('C');
    ss1.agregar('O');
    ss1.agregar('M');
    ss1.agregar('O');

    
    while (getline(archivo, linea)){
        istringstream iss(linea);
        string operacion;
        iss >> operacion;               // Pregunta por operacion
        if (operacion == "INSERTAR"){   // Operacion INSERTAR
            int i;                      //posicion i
            string s;                   //String que se quiere insertar
            iss >> i >> s;
            ss1.separar(i,ss1,ss2);

            for(int o=0;o<s.length();o++){
                ss1.agregar(s[o]);
            }
            ss1.juntar(ss2);
            
        }
        if (operacion == "MOSTRAR"){    // Operacion MOSTRAR
            ss1.Show();  
        }
        }

    archivo.close();
    return 0;
}