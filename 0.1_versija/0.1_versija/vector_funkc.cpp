#include "vector.h"
#include "struktura.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>

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
