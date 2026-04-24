#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <vector>
#include <deque>

struct StudentasD {
    std::string vardas = "";
    std::string pavarde = "";
    std::vector<int> paz;
    int    egz = 0;
    double rez = 0.00;
};

void ivesti_pazymius_d(StudentasD& s, int paz);
double vidurkis_d(const std::vector<int>& paz);
double mediana_d(const std::vector<int>& paz);

void pasirinkimo_metodas_d(int tipas, std::deque<StudentasD>& studentai);
void skaitymas_is_failo_d(const std::string& filename, std::deque<StudentasD>& studentai);
void rusiavimas_d(std::deque<StudentasD>& studentai);

// Originali strategija
double skirstymas_i_grupes_d(const std::deque<StudentasD>& visi,
    std::deque<StudentasD>& kieti,
    std::deque<StudentasD>& vargsai);

void isvedimas_i_faila_d(const std::deque<StudentasD>& studentai,
    const std::string& filename,
    const std::string& kategorija);

#endif