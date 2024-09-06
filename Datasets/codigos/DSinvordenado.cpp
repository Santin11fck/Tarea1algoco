#include <vector>
#include <algorithm>
#include <random>
#include <fstream>



void generateReverseSortedDataset(int size, const std::string& filename) {
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 1); // Llenar con números ordenados
    std::reverse(data.begin(), data.end()); // Invertir el orden

    std::ofstream file(filename);
    for (int num : data) {
        file << num << "\n";
    }
}

int main() {
    generateReverseSortedDataset(100000000, "reverse_e8.txt");
    return 0;
}
