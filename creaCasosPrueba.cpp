#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


char generarCaracterAleatorio() {
    static bool inicializado = false;
    if (!inicializado) {
        srand(time(nullptr));
        inicializado = true;
    }
    char letra = 'a' + rand() % 26;
    return letra;
}
bool charInVector(vector<char> v, char a) {
    for(char elem : v){
        if (a == elem) {
            return true;
        }
    }
    return false;
}

string crearCadena(int dificultad,vector<char> conj,int longitud){
    string cadena = "";
    switch (dificultad) {
        case (1):{ //favorable

            int i = 0;
            while( i < longitud){
                char car = generarCaracterAleatorio();
                if(!charInVector(conj,car) ){
                    cadena += car;
                    i++;
                }
            }
            break;
        }
        case(2): { //desfavorable

            int i = 0;
            while( i < longitud){
                char car = generarCaracterAleatorio();
                if(charInVector(conj,car) ){
                    cadena += car;
                    i++;
                }
            }
            break;
        }

        case(3): { //promedio

            int i = 0;
            while( i < longitud) {
                char car = generarCaracterAleatorio();
                cadena += car;
                i++;
            }
            break;
        }
    }
    return cadena;
}
int main(){
    int caso = 0;
    int longitud = 0;
    string caracteres = "";
    string nombreArch = "";

    cout << "Nombre archivo(favorable.txt, desfavorable.txt, promedio.txt): " << endl;
    cin >> nombreArch;
    if (nombreArch == "promedio.txt") {
        caso = 3;
    } else if (nombreArch == "desfavorable.txt") {
        caso = 2;
    } else if (nombreArch == "favorable.txt") {
        caso = 1;
    } else {
        cerr << " *Error: Nombre de archivo invalido." << endl;
        return 1;
    }

    cout << "Introduce conjunto de caracteres: (5)" << endl;
    cin >> caracteres;

    vector<char> conjunto;
    for (unsigned int i = 0; i < caracteres.length(); i++) {
        conjunto.push_back(caracteres[i]);
    }

    cout << "Introduce longitud:" << endl;
    cin >> longitud;

    string cadena = crearCadena(caso,conjunto,longitud);


    ofstream archivo(nombreArch);

    // Verificar si se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    archivo << caracteres << endl; // Conjunto de caracteres
    archivo << longitud << endl;   // Longitud de la cadena
    archivo << cadena << endl;     // La cadena en sí


    archivo.close();
    cout << "Se escribio en el archivo correctamente." << endl;
    return 0;
}
