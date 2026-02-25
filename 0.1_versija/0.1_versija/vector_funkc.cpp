#include "vector.h"
#include "struktura.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>
#include <fstream>
#include <sstream>



void ivesti_pazymius(StudentasV& s, int paz)
{
    s.paz.push_back(paz);  
}

double vidurkis(const std::vector<int>& paz)
{
    if (paz.empty()) return 0.00;

    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    return suma / paz.size();
}

double mediana(const std::vector<int>& paz)
{
    if (paz.empty()) return 0.00;

    std::vector<int> temp = paz; 
    std::sort(temp.begin(), temp.end());

    size_t n = temp.size();
    if (n % 2 == 0)
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    else
        return temp[n / 2];
}

void pasirinkimo_metodas(int tipas, std::vector<StudentasV>& studentai)
{
    for (auto& studentas : studentai) {  
        double x;
        if (tipas == 1) {
            x = vidurkis(studentas.paz);
        }
        else {
            x = mediana(studentas.paz);
        }
        studentas.rez = galutinis_vid(x, studentas.egz);
    }
}

void isvedimas(const std::vector<StudentasV>& studentai, int metodas)
{
    std::string rez = (metodas == 1) ? "Galutinis (vidurkis)" : "Galutinis (mediana)";
    std::cout << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(15) << "Pavarde"
        << std::right << std::setw(20) << rez << std::endl;

    for (const auto& studentas : studentai) {
        std::cout << std::left << std::setw(15) << studentas.vardas
            << std::setw(15) << studentas.pavarde
            << std::right << std::setw(20) << std::fixed
            << std::setprecision(2) << studentas.rez << std::endl;
    }
}

void skaitymas_is_failo(const std::string& filename, std::vector<StudentasV>& studentai) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << filename << "\n";
        return;
    }
	studentai.clear();

    std::string header;
    std::getline(file, header);

    std::string line;
    int line_number = 0;

    while (std::getline(file, line)) {
        line_number++;
        std::stringstream ss(line);
        StudentasV s;
        ss >> s.vardas >> s.pavarde;
        int value;
        while (ss >> value) {
            s.paz.push_back(value);
        }

        if (!s.paz.empty()) {
            s.egz = s.paz.back();
            s.paz.pop_back();
        }
        else {
            std::cerr << "Klaida eiluteje " << line_number
                << ": nera pazymiu\n";
            continue;
        }

        studentai.push_back(std::move(s));
        if (line_number % 10000 == 0) {
            std::cout << "Nuskaityta: " << line_number << " studentu...\n";
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Is viso nuskaityta: " << studentai.size() << " studentu\n";
}

bool pagal_varda(const StudentasV& a, const StudentasV& b) {
    return a.vardas < b.vardas;
}

bool paga_pavarde(const StudentasV& a, const StudentasV& b) {
    return a.pavarde < b.pavarde;
}
bool pagal_rez(const StudentasV& a, const StudentasV& b) {
    return a.rez < b.rez;
}

void rusiavimas(std::vector<StudentasV>& studentai, int rusiavimo_budas) {
    switch (rusiavimo_budas) {
    case 1:
        std::sort(studentai.begin(), studentai.end(), pagal_varda);
        break;
    case 2:
        std::sort(studentai.begin(), studentai.end(), paga_pavarde);
        break;
    case 3:
        std::sort(studentai.begin(), studentai.end(), pagal_rez);
        break;
    default:
        std::cerr << "Neteisingas rusiavimo budas. Nenaudojamas rusiavimas.\n";
        break;
    }
}

int pasirinkimas_rusiavimo_budo() {
    int pasirinkimas;
    std::cout << "Pasirinkite rusiavimo buda:\n";
    std::cout << "1 - pagal varda\n";
    std::cout << "2 - pagal pavarde\n";
    std::cout << "3 - pagal galutini rezultata\n";
    std::cin >> pasirinkimas;
    if (std::cin.fail() || pasirinkimas < 1 || pasirinkimas > 3) {
        std::cerr << "Neteisingas pasirinkimas. Nenaudojamas rusiavimas.\n";
        return 0; 
    }
    return pasirinkimas;
}