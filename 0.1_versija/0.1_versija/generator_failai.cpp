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

    out << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde";

    for (int i = 1; i <= nd_skaicius; i++) {
        out << std::setw(5) << ("ND" + std::to_string(i));
    }
    out << std::setw(5) << "Egz." << "\n";

    for (int i = 1; i <= studentu_skaicius; i++) {
        out << std::left << std::setw(20) << ("Vardas" + std::to_string(i))
            << std::setw(20) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < nd_skaicius; j++) {
            out << std::setw(5) << generuoti_pazymi();
        }