#ifndef ARRAY_H
#define ARRAY_H

#include <string>

struct StudentasA {
    std::string vardas = "";
    std::string pavarde = "";
    int* paz = nullptr;
    int paz_kiekis = 0;
    int paz_talpa = 0;
    int egz = 0;
    double rez = 0.00;
};

void ivesti_pazymius(StudentasA& sk, int paz);
double vidurkis(const int* paz, int paz_kiekis);
double mediana(const int* paz, int paz_kiekis);
double galutinis_vid(double x, int egz);

int skaiciavimo_metodas();
void pasirinkimo_metodas(int tipas, int studentu_kiekis, StudentasA* studentai);
void isvedimas(StudentasA* studentai, int studentu_kiekis, int metodas);

void studento_pridejimas(StudentasA*& arr, int& studentu_kiekis, const StudentasA& naujas);
void atlaisvinti(StudentasA* arr, int studentu_kiekis);

#endif