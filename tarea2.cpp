#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "super_string.cpp"
using namespace std;

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
	
    if (!archivo.is_open()){
        cerr << "Error al abrir el archivo." << endl;
        return 1;
	}

    while (getline(archivo, linea)){
        istringstream iss(linea);
        string operacion;
        iss >> operacion;               // Pregunta por operacion
        if (operacion == "FIN"){
            archivo.close();
            return 0;
        }
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
        if (operacion == "REVERSO") {
            int l, r;
            iss >> l >> r; // l y r son las posiciones de inicio y fin de la subcadena a invertir (inclusivas)
            if ((r < ss1.stringizar().length()-1) || (l > 0)){
            ss1.separar(l, ss1, ss2); // ss2 contiene la parte antes de la subcadena a invertir
            ss2.separar(r-l+1, ss2, ss3);
            ss2.reverso();
            ss1.juntar(ss2);
            ss1.juntar(ss3);
            ss2.limpiar();
            ss3.limpiar();
            }
            else ss1.reverso();
        }
        if (operacion == "RECORTAR"){
        cout << ss1.recortar() << endl;
 
        }
    }   
    archivo.close();
    return 0;
}
