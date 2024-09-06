#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    ifstream inputFile("random_e1.txt");
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

    // Ordenar la lista usando quicksort
    quickSort(arr, 0, arr.size() - 1);

    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración
    chrono::duration<double> duration = end - start;
    cout << "Tiempo de ejecución de quicksort: " << duration.count() << " segundos" << endl;

    printArray(arr);

    return 0;
}
