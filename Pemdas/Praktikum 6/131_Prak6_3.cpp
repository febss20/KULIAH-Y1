#include <iostream>
#include <fstream>

int main() {
    std::ifstream inputFile("file.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Gagal membuka file.txt" << std::endl;
        return 1;
    }

    int lineNumber = 1;  
    int total = 0;     

    while (!inputFile.eof()) {
        int number;
        inputFile >> number;

        if (lineNumber % 2 == 1) {
            total += number;
        }

        lineNumber++;
    }

    inputFile.close();

    std::cout << total << std::endl;

    return 0;
}
