#include <vector>
#include <algorithm>
#include <random>
#include <fstream>

void generateRandomDataset(int size, const std::string& filename) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (int& num : data) {
        num = dis(gen);
    }

    std::ofstream file(filename);
    for (int num : data) {
        file << num << "\n";
    }
}

int main() {
    generateRandomDataset(100000000, "random_e8.txt");
    return 0;
}
