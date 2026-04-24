#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include <list>

struct StudentasL {
    std::string vardas = "";
    std::string pavarde = "";
    std::vector<int> paz;
    int    egz = 0;
    double rez = 0.00;
};

void ivesti_pazymius_l(StudentasL& s, int paz);
double vidurkis_l(const std::vector<int>& paz);
double mediana_l(const std::vector<int>& paz);

void pasirinkimo_metodas_l(int tipas, std::list<StudentasL>& studentai);
void skaitymas_is_failo_l(const std::string& filename, std::list<StudentasL>& studentai);
void rusiavimas_l(std::list<StudentasL>& studentai);

// Originali strategija
double skirstymas_i_grupes_l(const std::list<StudentasL>& visi,
    std::list<StudentasL>& kieti,
    std::list<StudentasL>& vargsai);

// STRATEGIJA 1 du nauji konteineriai, originalas lieka nepakeistas
double skirstymas_s1_l(const std::list<StudentasL>& visi,
    std::list<StudentasL>& kieti,
	std::list<StudentasL>& vargsai);

// STRATEGIJA 2 vienas naujas konteineris + erase/remove if
double skirstymas_s2_l(std::list<StudentasL>& studentai,
    std::list<StudentasL>& vargsai);

// STRATEGIJA 3 splice - nulines kopijos
double skirstymas_s3_l(std::list<StudentasL>& studentai,
	std::list<StudentasL>& vargsai);

void isvedimas_i_faila_l(const std::list<StudentasL>& studentai,
    const std::string& filename,
    const std::string& kategorija);

#endif