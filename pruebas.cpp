/*
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

// Función para verificar si una subcadena contiene tres elementos de S sin repetir
bool contieneSubcadena(const string& subcadena, const unordered_set<char>& S) {
    unordered_set<char> caracteres;
    for (char c : subcadena) {
        if (S.find(c) != S.end()) {
            caracteres.insert(c);
        }
    }
    return caracteres.size() == 3;
}

// Función principal que utiliza el enfoque de divide y conquista
void encontrarSubcadenas(const string& C, const unordered_set<char>& S, int inicio, int fin, unordered_set<string>& subcadenasEncontradas, vector<int>& resultados) {
    // Tamaño máximo de subproblema razonable
    if (fin - inicio <= 3) {
        // Resolver directamente el subproblema
        for (int i = inicio; i < fin - 2; ++i) {
            string subcadena = C.substr(i, 3);
            if (contieneSubcadena(subcadena, S) && subcadenasEncontradas.find(subcadena) == subcadenasEncontradas.end()) {
                resultados.push_back(i + 1);
                subcadenasEncontradas.insert(subcadena);
            }
        }
        return;
    }

    int mitad = inicio + (fin - inicio) / 2;

    // Resolver los subproblemas de ambas mitades
    encontrarSubcadenas(C, S, inicio, mitad, subcadenasEncontradas, resultados);
    encontrarSubcadenas(C, S, mitad, fin, subcadenasEncontradas, resultados);

    // Resolver subcadenas que cruzan la división de las mitades
    for (int i = mitad - 2; i >= inicio; --i) {
        string subcadena = C.substr(i, 3);
        if (contieneSubcadena(subcadena, S) && subcadenasEncontradas.find(subcadena) == subcadenasEncontradas.end()) {
            resultados.push_back(i + 1);
            subcadenasEncontradas.insert(subcadena);
        } else {
            break;
        }
    }

    for (int i = mitad + 1; i <= fin - 3; ++i) {
        string subcadena = C.substr(i, 3);
        if (contieneSubcadena(subcadena, S) && subcadenasEncontradas.find(subcadena) == subcadenasEncontradas.end()) {
            resultados.push_back(i + 1);
            subcadenasEncontradas.insert(subcadena);
        } else {
            break;
        }
    }
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    string C = "";
    ifstream file("C:\\Users\\pepeg\\CLionProjects\\proyectoPrueba\\message2.txt");

    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            C += line;
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    int n = C.size();
    unordered_set<char> S = {'a', 'b', 'c', 'd', 'e'};
    vector<int> resultados;
    unordered_set<string> subcadenasEncontradas;

    // Utilizar el enfoque de divide y conquista
    encontrarSubcadenas(C, S, 0, n, subcadenasEncontradas, resultados);

    // Imprimir resultados

    cout << endl;
    cout << "El numero de subcadenas es: " << resultados.size() << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << "La rutina demoro: " << duration_ms << " milisegundos." << endl;
    cout << "AED-DyV";

    return 0;
}
*/
/*
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

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

bool charInVector(vector<char> v, char a) {
    for(char elem : v){
        if (a == elem) {
            return true;
        }
    }
    return false;
}

vector<int> resolverCasoBase(string C, vector<char> S, int numeroCaracterSol) {
    vector<int> resultados;
    if (charInVector(S, C[0]) && charInVector(S, C[1]) && charInVector(S, C[2])) {

        if ((C[0] != C[1]) && (C[0] != C[2]) && (C[1] != C[2])) {
            resultados.push_back(numeroCaracterSol + 1);
        }
    }

    if (charInVector(S, C[1]) && charInVector(S, C[2]) && charInVector(S, C[3])) {

        if ((C[1] != C[2]) && (C[1] != C[3]) && (C[2] != C[3])) {
            resultados.push_back(numeroCaracterSol + 2);
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
    int n = (int) cadena.length();
    vector<int> resultados;
    //CASO BASE
    if (n == 4){
        //resultados.push_back(resolverCasoBase(cadena,S,fin-inicio));
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

    string cadena = "";
    ifstream file ("C:\\Users\\pepeg\\CLionProjects\\proyectoPrueba\\message1.txt");

    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            cadena += line;
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    int n = cadena.size();

    string caracteres = "abcde";


    auto start_time = chrono::high_resolution_clock::now();
    vector<char> conjunto;
    for (unsigned int i = 0; i < caracteres.length(); i++) {
        conjunto.push_back(caracteres[i]);
    }


    //bucle de resolucion con divide y venceras
    vector<int> resultados = DyV(cadena, conjunto, 0, (int) cadena.length() - 1);

    //mostramos la solucion
    cout << "Numero de resultados: " << resultados.size() <<"." <<endl;
    cout << "Situados en los caracteres -> ";
    for(int elem : resultados){
        if(resultados.size() == 1){
            cout << elem << "." <<endl;
        }
        else if (elem == resultados.back()) {
            cout << "y " << elem << "." << endl;
        }
        else if (elem == resultados.at(resultados.size() - 1)){
            cout << elem << " ";
        }
        else{
            cout << elem << ", ";
        }
    }

    auto end_time = chrono::high_resolution_clock::now();

    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << "La rutina demoro " << duration_ms << " milisegundos." << endl;

    return 0;
}


// con el '&' delante de una variable, conseguimos que en cada llamada a una funcion, no se le pase como parametro una copia
// de esa variable, sino que se le pase el objeto original para que, si se modifica, el cambio permanezca una vez termine la llamada a la funcion


*/
