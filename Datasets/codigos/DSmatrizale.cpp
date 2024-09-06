#include <bits/stdc++.h>
using namespace std;

// Función para generar una matriz de enteros aleatorios
vector<vector<int>> generate_random_matrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);  // Números aleatorios entre 0 y 100

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}

// Función para escribir una matriz en un archivo
void write_matrix_to_file(const string& filename, const vector<vector<int>>& matrix) {
    ofstream file(filename);
    if (file.is_open()) {
        // Escribir la primera línea con el tamaño de la matriz
        int size = matrix.size();
        file << size << endl;

        // Escribir la matriz
        for (const auto& row : matrix) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i != row.size() - 1) file << " ";  // Separar los números con espacio
            }
            file << endl;  // Nueva línea para cada fila
        }
        file.close();
        cout << "Matriz guardada en: " << filename << endl;
    } else {
        cout << "No se pudo abrir el archivo " << filename << endl;
    }
}

// Función principal
int main() {
    int min_size = 50;   // Tamaño inicial de las matrices
    int max_size = 500;  // Tamaño máximo de las matrices
    int step = 75;       // Incremento del tamaño

    for (int size = min_size; size <= max_size; size += step) {
        // Generar una matriz aleatoria de tamaño size x size
        vector<vector<int>> matrix = generate_random_matrix(size, size);

        // Generar el nombre del archivo
        string filename = "matriz" + to_string(size) + ".txt";

        // Guardar la matriz en el archivo
        write_matrix_to_file(filename, matrix);
    }

    return 0;
}


