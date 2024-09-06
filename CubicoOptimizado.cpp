#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Transponer una matriz
vector<vector<int>> transposeMatrix(const vector<vector<int>>& B) {
    int n = B.size();
    vector<vector<int>> B_T(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B_T[j][i] = B[i][j];
        }
    }
    
    return B_T;
}

vector<vector<int>> multiplyMatricesOptimized(const vector<vector<int>>& A, const vector<vector<int>>& B_T) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B_T[j][k];
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
    vector<vector<int>> A = readMatrixFromFile("matriz100.txt");
    vector<vector<int>> B = readMatrixFromFile("matriz_nula100.txt");

    auto start = chrono::high_resolution_clock::now();
    // Transponer la matriz B antes de la multiplicación
    vector<vector<int>> B_T = transposeMatrix(B);

    // Multiplicar las matrices
    vector<vector<int>> C = multiplyMatricesOptimized(A, B_T);

    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración
    chrono::duration<double> duration = end - start;
    cout << "Tiempo de ejecución de std::sort: " << duration.count() << " segundos" << endl;


   // Imprimir la matriz resultado
    cout << "Matriz resultante C (Optimized):" << endl;
    printMatrix(C);

    return 0;
}

