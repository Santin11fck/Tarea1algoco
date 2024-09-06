#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo
vector<vector<int>> read_matrix(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    
    if (file.is_open()) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            vector<int> row;
            stringstream ss(line);
            int num;
            while (ss >> num) {
                row.push_back(num);
            }
            matrix.push_back(row);
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo " << filename << endl;
    }
    
    return matrix;
}


/*
// Función para realizar la multiplicación de matrices utilizando el algoritmo cúbico tradicional
vector<vector<int>> traditional(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();
    
    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    // Iteración cúbica adaptada para matrices no necesariamente cuadradas
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Función para transponer una matriz
vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

// Función para realizar la multiplicación de matrices optimizada transponiendo la segunda matriz
vector<vector<int>> optimized(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    // Transponer la segunda matriz para mejorar la localidad de los datos
    vector<vector<int>> matrix2T = transpose(matrix2);

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    // Iteración cúbica optimizada
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2T[j][k];
            }
        }
    }

    return result;
}

*/

// Función para sumar matrices, utilizada en el algoritmo de Strassen
vector<vector<int>> add_matrix(vector<vector<int>>& matrix_A, vector<vector<int>>& matrix_B, int split_index, int multiplier = 1) {
    vector<vector<int>> result = matrix_A;  // Crear una copia de la matriz A
    for (int i = 0; i < split_index; i++) {
        for (int j = 0; j < split_index; j++) {
            result[i][j] += multiplier * matrix_B[i][j];
        }
    }
    return result;
}

// Función Strassen para multiplicar matrices
vector<vector<int>> Strassen(vector<vector<int>>& matrix_A, vector<vector<int>>& matrix_B) {
    int col_1 = matrix_A[0].size();
    int row_1 = matrix_A.size();
    int col_2 = matrix_B[0].size();
    int row_2 = matrix_B.size();

    if (col_1 != row_2) {
        cout << "\nError: The number of columns in Matrix A must be equal to the number of rows in Matrix B\n";
        return {};
    }

    vector<int> result_matrix_row(col_2, 0);
    vector<vector<int>> result_matrix(row_1, result_matrix_row);

    if (col_1 == 1) {
        result_matrix[0][0] = matrix_A[0][0] * matrix_B[0][0];
    } else {
        int split_index = col_1 / 2;
        vector<int> row_vector(split_index, 0);

        vector<vector<int>> a00(split_index, row_vector);
        vector<vector<int>> a01(split_index, row_vector);
        vector<vector<int>> a10(split_index, row_vector);
        vector<vector<int>> a11(split_index, row_vector);
        vector<vector<int>> b00(split_index, row_vector);
        vector<vector<int>> b01(split_index, row_vector);
        vector<vector<int>> b10(split_index, row_vector);
        vector<vector<int>> b11(split_index, row_vector);

        for (int i = 0; i < split_index; i++) {
            for (int j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + split_index];
                a10[i][j] = matrix_A[split_index + i][j];
                a11[i][j] = matrix_A[i + split_index][j + split_index];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + split_index];
                b10[i][j] = matrix_B[split_index + i][j];
                b11[i][j] = matrix_B[i + split_index][j + split_index];
            }
        }

        // Evitar pasar rvalues, almacenar en variables intermedias
        vector<vector<int>> temp1 = add_matrix(b01, b11, split_index, -1);
        vector<vector<int>> p = Strassen(a00, temp1);

        vector<vector<int>> temp2 = add_matrix(a00, a01, split_index);
        vector<vector<int>> q = Strassen(temp2, b11);

        vector<vector<int>> temp3 = add_matrix(a10, a11, split_index);
        vector<vector<int>> r = Strassen(temp3, b00);

        vector<vector<int>> temp4 = add_matrix(b10, b00, split_index, -1);
        vector<vector<int>> s = Strassen(a11, temp4);

        vector<vector<int>> temp5a = add_matrix(a00, a11, split_index);
        vector<vector<int>> temp5b = add_matrix(b00, b11, split_index);
        vector<vector<int>> t = Strassen(temp5a, temp5b);

        vector<vector<int>> temp6a = add_matrix(a01, a11, split_index, -1);
        vector<vector<int>> temp6b = add_matrix(b10, b11, split_index);
        vector<vector<int>> u = Strassen(temp6a, temp6b);

        vector<vector<int>> temp7a = add_matrix(a00, a10, split_index, -1);
        vector<vector<int>> temp7b = add_matrix(b00, b01, split_index);
        vector<vector<int>> v = Strassen(temp7a, temp7b);

        // Combinando resultados
        vector<vector<int>> temp8 = add_matrix(t, s, split_index);
        vector<vector<int>> temp9 = add_matrix(temp8, u, split_index);
        vector<vector<int>> result_matrix_00 = add_matrix(temp9, q, split_index, -1);

        vector<vector<int>> result_matrix_01 = add_matrix(p, q, split_index);

        vector<vector<int>> result_matrix_10 = add_matrix(r, s, split_index);

        vector<vector<int>> temp10 = add_matrix(t, p, split_index);
        vector<vector<int>> temp11 = add_matrix(temp10, r, split_index, -1);
        vector<vector<int>> result_matrix_11 = add_matrix(temp11, v, split_index, -1);

        for (int i = 0; i < split_index; i++) {
            for (int j = 0; j < split_index; j++) {
                result_matrix[i][j] = result_matrix_00[i][j];
                result_matrix[i][j + split_index] = result_matrix_01[i][j];
                result_matrix[split_index + i][j] = result_matrix_10[i][j];
                result_matrix[i + split_index][j + split_index] = result_matrix_11[i][j];
            }
        }
    }
    return result_matrix;
}


    // Función para imprimir una matriz
    void print_matrix(const vector<vector<int>>& matrix) {
        for (const auto& row : matrix) {
            for (const auto& element : row) {
                cout << element << " ";  // Imprimir cada elemento seguido de un espacio
            }
            cout << endl;  // Nueva línea después de cada fila
        }
    }

int main() {
    for (int i = 50; i <= 50; i += 75) {
        // Generar el nombre del archivo
        string filename = "matriz" + to_string(i) + ".txt";
        // Leer la matriz del archivo
        vector<vector<int>> matrix1 = read_matrix(filename);
        vector<vector<int>> matrix2 = read_matrix(filename);

        if (matrix1.empty() || matrix2.empty()) continue;

        cout << "Procesando matriz de tamaño " << i << "x" << i << endl;

/*     // Medir tiempo de ejecución para la multiplicación tradicional
        auto start_traditional = high_resolution_clock::now();
        vector<vector<int>> result_traditional = traditional(matrix1, matrix2);
        auto end_traditional = high_resolution_clock::now();
        auto duration_traditional = duration_cast<milliseconds>(end_traditional - start_traditional);
        cout << "Tiempo de ejecución (Traditional): " << duration_traditional.count() << " milisegundos" << endl;

        // Medir tiempo de ejecución para la multiplicación optimizada
        auto start_optimized = high_resolution_clock::now();
        vector<vector<int>> result_optimized = optimized(matrix1, matrix2);
        auto end_optimized = high_resolution_clock::now();
        auto duration_optimized = duration_cast<milliseconds>(end_optimized - start_optimized);
        cout << "Tiempo de ejecución (Optimized): " << duration_optimized.count() << " milisegundos" << endl;
*/
        // Medir tiempo de ejecución para la multiplicación con Strassen
        auto start_strassen = high_resolution_clock::now();
        vector<vector<int>> result_strassen = Strassen(matrix1, matrix2);
        auto end_strassen = high_resolution_clock::now();
        auto duration_strassen = duration<double>(end_strassen - start_strassen);
        cout << "Tiempo de ejecución (Strassen): " << duration_strassen.count() << " segundos" << endl;

        cout << "-------------------------------------" << endl;

        // Imprimir la matriz resultante
        cout << "Matriz resultante de Strassen:" << endl;
        print_matrix(result_strassen);
    }

    return 0;
}
