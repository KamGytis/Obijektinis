#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <vector>

struct StudentasV {
    std::string vardas = "";
    std::string pavarde = "";
    std::vector<int> paz; 
    int egz = 0;
    double rez = 0.00;
};

void ivesti_pazymius(StudentasV& sk, int paz);
double vidurkis(const std::vector<int>& paz);
double mediana(const std::vector<int>& paz);

void pasirinkimo_metodas(int tipas, std::vector<StudentasV>& studentai);
void isvedimas(const std::vector<StudentasV>& studentai, int metodas);

void skaitymas_is_failo(const std::string& filename, std::vector<StudentasV>& studentai);
void rusiavimas(std::vector<StudentasV>& studentai, int rusiavimo_budas);
int pasirinkimas_rusiavimo_budo();
int isvedimo_budas();
void spausdinimas_i_faila(const std::vector<StudentasV>& studentai, const std::string& filename);

void skirstymas_i_grupes(
    const std::vector<StudentasV>& visi,
    std::vector<StudentasV>& kieti,
    std::vector<StudentasV>& vargsai
);

void isvedimas_i_faila(
    const std::vector<StudentasV>& studentai,
    const std::string& filename,
    const std::string& kategorija
);

void generuoti_faila(const std::string& filename, int studentu_skaicius, int nd_skaicius);
void generuoti_testu_failus();

#endif