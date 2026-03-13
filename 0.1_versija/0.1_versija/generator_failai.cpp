#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>

int generuoti_pazymi() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 10);
    return dis(gen);
}

void generuoti_faila(const std::string& filename, int studentu_skaicius, int nd_skaicius = 5) {
    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Nepavyko sukurti failo: " << filename << "\n";
        return;
    }