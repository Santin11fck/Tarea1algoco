#include <bits/stdc++.h>
using namespace std;

// Función para generar una matriz identidad
vector<vector<int>> generate_identity_matrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        matrix[i][i] = 1;  // Colocar un 1 en la diagonal principal
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
        // Generar una matriz identidad de tamaño size x size
        vector<vector<int>> matrix = generate_identity_matrix(size);

        // Generar el nombre del archivo
        string filename = "matriz_identidad" + to_string(size) + ".txt";

        // Guardar la matriz en el archivo
        write_matrix_to_file(filename, matrix);
    }

    return 0;
}
