#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono> // Incluir la librería chrono para medir el tiempo

using namespace std;

int main() {
    // Leer los datos desde el archivo de entrada
    ifstream inputFile("reverse_e8.txt");
    vector<int> vec;
    int num;

    if (!inputFile) {
        cerr << "Error al abrir el archivo de entrada" << endl;
        return 1;
    }

    while (inputFile >> num) {
        vec.push_back(num);
    }
    inputFile.close();

    // Capturar el tiempo antes de ejecutar std::sort
    auto start = chrono::high_resolution_clock::now();

    // Ordenar el vector usando std::sort
    sort(vec.begin(), vec.end());

    // Capturar el tiempo después de ejecutar std::sort
    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración
    chrono::duration<double> duration = end - start;
    cout << "Tiempo de ejecución de std::sort: " << duration.count() << " segundos" << endl;

    
    for(int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}

