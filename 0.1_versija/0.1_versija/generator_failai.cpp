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