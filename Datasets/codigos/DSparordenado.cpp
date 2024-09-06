#include <vector>
#include <algorithm>
#include <random>
#include <fstream>


void generatePartiallySortedDataset(int size, int unsortedPercentage, const std::string& filename) {
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 1); // Llenar con números ordenados

    int unsortedSize = (size * unsortedPercentage) / 100;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(data.end() - unsortedSize, data.end(), gen); // Desordenar una parte

    std::ofstream file(filename);
    for (int num : data) {
        file << num << "\n";
    }
}

int main() {
    generatePartiallySortedDataset(100000000, 10, "partially_e8");
    return 0;
}
