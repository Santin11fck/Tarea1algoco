#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream inputFile(filename);
    vector<vector<int>> matrix;
    int n;

    if (!inputFile) {
        cerr << "Error al abrir el archivo de entrada: " << filename << endl;
        exit(1);
    }

    inputFile >> n;
    matrix.resize(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();
    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Leer las matrices desde archivos de texto
    vector<vector<int>> A = readMatrixFromFile("matriz1000.txt");
    vector<vector<int>> B = readMatrixFromFile("matriz_nula1000.txt");

    auto start = chrono::high_resolution_clock::now();
    // Multiplicar las matrices
    vector<vector<int>> C = multiplyMatrices(A, B);

    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración
    chrono::duration<double> duration = end - start;
    cout << "Tiempo de ejecución de std::sort: " << duration.count() << " segundos" << endl;
    printMatrix(C);

    return 0;
}

