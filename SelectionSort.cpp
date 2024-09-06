#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


using namespace std;

void selectionSort(vector<int>& arr) {
    int size = arr.size();
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Leer los datos desde el archivo de entrada
    ifstream inputFile("reverse_e5.txt");
    vector<int> arr;
    int num;

    if (!inputFile) {
        cerr << "Error al abrir el archivo de entrada" << endl;
        return 1;
    }

    while (inputFile >> num) {
        arr.push_back(num);
    }
    inputFile.close();


    auto start = chrono::high_resolution_clock::now();
    // Ordenar la lista usando selection sort
    selectionSort(arr);

    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración
    chrono::duration<double> duration = end - start;
    cout << "Tiempo de ejecución de quicksort: " << duration.count() << " segundos" << endl;

    printArray(arr);

    return 0;
}
