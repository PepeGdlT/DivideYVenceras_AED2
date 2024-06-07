#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <assert.h>
#include <fstream>
using namespace std;



bool charInVector(vector<char> v, char a) {
    for(char elem : v){
        if (a == elem) {
            return true;
        }
    }
    return false;
}


int dividirCadena(string cadena, string &subcadena1, string &subcadena2) {
    if(cadena.length() % 2 == 0){
        // cadena inicial par
        subcadena1 = cadena.substr(0, (cadena.length() / 2));
        subcadena2 = cadena.substr((cadena.length() / 2), cadena.length());

    }
    else{
        //cadena inicial impar
        subcadena1 = cadena.substr(0, (cadena.length() / 2));
        subcadena2 = cadena.substr((cadena.length() / 2) + 1, cadena.length());
        //si la cadena es impar devuelve el indice del caracter intermedio, para tenerlo en cuenta a la hora de combinar las soluciones de las subcadenas
        return (int) cadena.length() / 2;
    }
    //si son pares se devuelve -1
    return -1;
}

bool addcharToString(string &cadena, char a) {
    for (unsigned int i = 0; i < cadena.length(); i++) {
        if (cadena[i] == a) {
            return false;
        }
    }
    cadena = cadena + a;
    return true;
}



vector<int> resolverCasoBase(string C, vector<char> S, int numeroCaracterSol) {
    vector<int> resultados;
    if (charInVector(S, C[0]) && charInVector(S, C[1]) && charInVector(S, C[2])) {

        if ((C[0] != C[1]) && (C[0] != C[2]) && (C[1] != C[2])) {
            resultados.push_back(numeroCaracterSol + 1);
        }
    }
    if(C.length() == 4) {
        if (charInVector(S, C[1]) && charInVector(S, C[2]) && charInVector(S, C[3])) {

            if ((C[1] != C[2]) && (C[1] != C[3]) && (C[2] != C[3])) {
                resultados.push_back(numeroCaracterSol + 2);
            }
        }
    }
    return resultados;
}

vector<int> combinar(string C, vector<char> v, int n, int caracteresPorDetras) {
    //3 elementos seguidos de C, que contengan elementos de v NO REPETIDOS
    string posibleResultado = "";
    int numeroCaracter = 0;
    //int numeroSoluciones = 0;
    vector<int> caracteres;

    //bucle principal
    int i = 0;
    while (i < n) {
        //si el caracter no pertenece al conjunto v, simplemente dejamos la cadena solución a """.
        if (!charInVector(v, C[i])) {
            posibleResultado = "";
        }
            //si la longitud es 0, introducimos el char a la cadena, como primer caracter de una posible solucion
        else if (charInVector(v, C[i]) && posibleResultado.empty()) {
            addcharToString(posibleResultado, C[i]);
            numeroCaracter = i;
        }
            //si ya hay un char metido, se comprueba si el siguiente pertenece a v, y en en ese caso, si se puede añadir a posibleResultado
            //simplemente seguimos. En otro caso, se tendrá que reiniciar el procedimiento y buscar otra solucion
        else if (charInVector(v, C[i]) && posibleResultado.length() == 1) {
            if (addcharToString(posibleResultado, C[i])) {
                i++;
                continue;
            } else {
                posibleResultado = C[i];
                numeroCaracter = i;
            }
        }
            //si ya hay dos char, hacemos la misma comprobacion que cuando habia uno, si se cumple y encima el caracter se puede añadir
            //a posibleResultado, damos la solucion, y reiniciamos las variables de posibles resultados
        else if (charInVector(v, C[i]) && posibleResultado.length() == 2) {
            if (addcharToString(posibleResultado, C[i])) {
                //numeroSoluciones++;
                caracteres.push_back((numeroCaracter + 1) + caracteresPorDetras);
            }
            //por si se da el caso abcd, siendo abc y bcd soluciones válidas, reiniciamos la cadena solucion
            //con el caracter que ha dado la sol. + 1.
            i = numeroCaracter + 1;
            posibleResultado = C[i];
            numeroCaracter = i;
        }

        i++;
    }
    return caracteres;
}
vector<int> DyV(string cadena, vector<char> S, int inicio, int fin){
    assert(S.size() == 5 );

    int n = (int) cadena.length();
    vector<int> resultados;
    //CASO BASE

    if(n < 3){
        return resultados;
    }

    else if (n == 3 || n == 4){
        resultados = resolverCasoBase(cadena, S, inicio);
        return resultados;
    }



    //DIVISION DEL PROBLEMA
    //si la cadena es impar, dividiremos dejando el caracterIntermedio fuera
    string subcadena1 = "";
    string subcadena2 = "";
    int caracterIntermedio = dividirCadena(cadena, subcadena1, subcadena2);




    //RESOLUCION DE AMBAS PARTES
    int mitad = inicio + ((fin-inicio)/2);
    vector<int> resultados1;
    if(caracterIntermedio != -1){
        //el valor de la mitad para cadenas impares es exacto (porque fin es par), situandose en el indice de caracterIntermedio.
        //por ello el fin de la subcadena1 sera mitad - 1
        resultados1 = DyV(subcadena1, S, inicio, mitad - 1);
    }
    else{
        //el valor de la mitad para cadenas pares se redondea hacia abajo (porque fin es impar), situandose en el indice del ultimo caracter de subcadena1.
        //por ello el fin de subacdena1 es mitad
        resultados1 = DyV(subcadena1, S, inicio, mitad);
    }
    //mitad contiene la posicion de caracterIntermedio (cadena original impar), o del ultimo elemento de subcadena1 (cadena original par), en cualquier caso el primer caracter de la
    //subcadena 2 comenzara en mitad + 1
    vector<int> resultados2 = DyV(subcadena2, S, mitad + 1, fin);


    //RESOLUCION INTERMEDIA (combinar), para ello se cogeran los DOS ULTIMOS caracteres de la cadena 1, y los DOS PRIMEROS de la cadena 2,
    //y el caracter intermedio en caso de que la cadena inicial fuera de longitud impar
    string cadenaIntermedia = "";
    vector<int> resultadosIntermedios;

    if (caracterIntermedio != -1) {
        cadenaIntermedia.push_back(subcadena1[subcadena1.length() - 2]);
        cadenaIntermedia.push_back(subcadena1[subcadena1.length() - 1]);
        cadenaIntermedia.push_back(cadena[caracterIntermedio]);
        cadenaIntermedia.push_back(subcadena2[0]);
        cadenaIntermedia.push_back(subcadena2[1]);
        resultadosIntermedios = combinar(cadenaIntermedia, S, (int) cadenaIntermedia.length(), mitad-2);    //mitad -2, porque en los resultados
        // intermedios la cadena se genera con los dos ultimos caracteres de la subcadena1, que se encuentran 2 posiciones por detras de la mitad.
    }
    else {
        cadenaIntermedia.push_back(subcadena1[subcadena1.length() - 2]);
        cadenaIntermedia.push_back(subcadena1[subcadena1.length() - 1]);
        cadenaIntermedia.push_back(subcadena2[0]);
        cadenaIntermedia.push_back(subcadena2[1]);
        resultadosIntermedios = combinar(cadenaIntermedia, S, (int) cadenaIntermedia.length(), mitad-1);    //porque al no haber caracterIntermedio,
        //el valor de la mitad es el del ultimo caracter de la subcadena1, y por tanto para los resultadosIntermedios solo debemos restarle 1 (para que incluya el penultimo elemento de subcadena)
    }


    //combinamos los tres vectores
    for (int elem : resultados1){
        resultados.push_back(elem);
    }
    for (int elem : resultadosIntermedios){
        resultados.push_back(elem);
    }
    for (int elem : resultados2){
        resultados.push_back(elem);
    }


    return resultados;
}

int main() {
    string nombreArch;
    cout << "Nombre del archivo (favorable.txt, desfavorable.txt, promedio.txt): " << endl;
    cin >> nombreArch;

    string conjuntoSt;
    int longitud;
    string cadena;

    // Abrir el archivo para lectura
    ifstream archivo(nombreArch);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Leer conjunto de caracteres del archivo
    if (!(archivo >> conjuntoSt)) {
        cerr << "Error al leer el conjunto de caracteres del archivo." << endl;
        archivo.close();
        return 1;
    }

    // Leer la longitud del archivo
    if (!(archivo >> longitud)) {
        cerr << "Error al leer la longitud del archivo." << endl;
        archivo.close();
        return 1;
    }

    // Leer la cadena del archivo
    if (!(archivo >> cadena)) {
        cerr << "Error al leer la cadena del archivo." << endl;
        archivo.close();
        return 1;
    }

    archivo.close();

    // Convertir el conjunto de caracteres a un vector<char>
    vector<char> conjunto;
    for (char c : conjuntoSt) {
        conjunto.push_back(c);
    }



    // Ejecutar el algoritmo con los datos leídos del archivo
    auto start_time = chrono::high_resolution_clock::now();
    vector<int> resultados = DyV(cadena, conjunto, 0, longitud - 1);
    auto end_time = chrono::high_resolution_clock::now();

    // Mostrar resultados
    cout << "Numero de resultados: " << resultados.size() << "." << endl;
    cout << "Situados en los caracteres -> ";
    for (int i = 0; i < resultados.size(); ++i) {
        if (i == resultados.size() - 1) {
            cout << "y ";
        }
        cout << resultados[i] << ((i == resultados.size() - 1) ? ".\n" : ", ");

    cout << endl;
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "La rutina demoro " << duration_ms << " milisegundos." << endl;

    return 0;
}




