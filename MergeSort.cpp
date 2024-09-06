#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void printList(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Leer los datos desde el archivo de entrada
    ifstream inputFile("reverse_e8.txt");
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
    // Ordenar la lista usando merge sort
    mergeSort(arr, 0, arr.size() - 1);


    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración
    chrono::duration<double> duration = end - start;
    cout << "Tiempo de ejecución de quicksort: " << duration.count() << " segundos" << endl;

    printList(arr);

    return 0;
}
