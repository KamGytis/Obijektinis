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

// STRATEGIJA 1 du nauji konteineriai, originalas lieka nepakeistas
double skirstymas_s1_d(const std::deque<StudentasD>& visi,
    std::deque<StudentasD>& kieti,
	std::deque<StudentasD>& vargsai);

// STRATEGIJA 2 vienas naujas konteineris + erase/remove if
double skirstymas_s2_d(std::deque<StudentasD>& studentai,
	std::deque<StudentasD>& vargsai);

// STRATEGIJA 3 std::partition
double skirstymas_s3_d(std::deque<StudentasD>& studentai,
	std::deque<StudentasD>& vargsai);

void isvedimas_i_faila_d(const std::deque<StudentasD>& studentai,
    const std::string& filename,
    const std::string& kategorija);

#endif