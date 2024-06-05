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
    super_string ss1;
	
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
            super_string insertado, insHelp1, insHelp2;
            for(int o=0;o<s.length();o++){
                insertado.agregar(s[o]);
                }
            ss1.separar(i, insHelp1, insHelp2);
            insHelp1.juntar(insertado);
            insHelp1.juntar(insHelp2);
            ss1.limpiar();
            ss1.juntar(insHelp1);
            insertado.limpiar();
            insHelp1.limpiar();
            insHelp2.limpiar();

        }
        if (operacion == "ELIMINAR"){    //  Operacion ELIMINAR
            int l;                      //posicion l
            int r;                      //posicion r
            iss >> l >> r;
            super_string elim1, elim2, elim3, elim4;
            ss1.separar(l,elim1,elim2);     //se separa ss1 y se almacena la parte a borrar en ss2
            elim2.separar(r-l+1,elim3,elim4); //se separa los elementos a borrar de los que se deben mantener
            elim1.juntar(elim4);            //se junta ss1 con ss3
            ss1.limpiar();
            ss1.juntar(elim1);
            elim1.limpiar();
            elim2.limpiar();
            elim3.limpiar();
            elim4.limpiar();         
        }
        if (operacion == "REVERSO") {
            int l, r;
            super_string help1,help2,help3,help4;
            iss >> l >> r; // l y r son las posiciones de inicio y fin de la subcadena a invertir (inclusivas)
            if ((r < ss1.stringizar().length()-1) || (l > 0)){
            ss1.separar(r+1, help1, help2); 
            help1.separar(l, help3, help4);
            help4.reverso();
            help4.juntar(help2);
            help3.juntar(help4);
                if (ss1.esArbol){
                    ss1.limpiar();
                    ss1.juntar(help3);
                    ss1.recortar();
                }
                else {
                    ss1.limpiar();
                    ss1.juntar(help3);
                }
            }
            else ss1.reverso();
            help1.limpiar();
            help2.limpiar();
            help3.limpiar();
            help4.limpiar();
        }
        if (operacion == "RECORTAR"){
        cout << ss1.recortar() << endl;
 
        }
    }   
    archivo.close();
    return 0;
}
