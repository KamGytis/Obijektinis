#include "array.h"  
#include "struktura.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

//Funkcija, kuri prideda pazymi i studento pazymiu masyva, jei reikia padidina masyvo talpa
void ivesti_pazymius(StudentasA& s, int paz)
{
    if (s.paz_talpa == 0)
    {
        s.paz_talpa = 4;
        s.paz = new int[s.paz_talpa];
    }
    if (s.paz_kiekis >= s.paz_talpa)
    {
        s.paz_talpa *= 2;
        int* naujas = new int[s.paz_talpa];

        for (int i = 0; i < s.paz_kiekis; ++i)
            naujas[i] = s.paz[i];

        delete[] s.paz;
        s.paz = naujas;
    }
    s.paz[s.paz_kiekis++] = paz;
}

double vidurkis(const int* paz, int paz_kiekis)
{
    if (paz_kiekis <= 0) return 0.00;

    double suma = 0.00;
    for (int i = 0; i < paz_kiekis; ++i)
        suma += paz[i];

    return suma / paz_kiekis;
}


double mediana(const int* paz, int paz_kiekis)
{
    if (paz_kiekis <= 0) return 0.00;

    int* temp = new int[paz_kiekis];

    std::copy(paz, paz + paz_kiekis, temp);
    std::sort(temp, temp + paz_kiekis);

    double rezultatas;

    if (paz_kiekis % 2 == 0)
        rezultatas = (temp[paz_kiekis / 2 - 1] + temp[paz_kiekis / 2]) / 2.00;
    else
        rezultatas = temp[paz_kiekis / 2];

    delete[] temp;
    return rezultatas;
}


//apskaiciuoja galutinius pazymius pagal galutini masyva ir pasirinkta metoda

void pasirinkimo_metodas(int skaiciavimo_metodas, int studentu_kiekis, StudentasA* studentai) {
    for (int i = 0; i < studentu_kiekis; i++) {
        double x;
        if (skaiciavimo_metodas == 1) {
            x = vidurkis(studentai[i].paz, studentai[i].paz_kiekis);
        }
        else if (skaiciavimo_metodas == 2) {
            x = mediana(studentai[i].paz, studentai[i].paz_kiekis);
        }
        else {
            std::cout << "Neteisingas pasirinkimas. Naudojamas vidurkis.\n";
            x = vidurkis(studentai[i].paz, studentai[i].paz_kiekis);
        }
        studentai[i].rez = galutinis_vid(x, studentai[i].egz);
    }
}

//printina studentus i lentele

void isvedimas(StudentasA* studentai, int studentu_kiekis, int metodas) {
    std::string rez = (metodas == 1) ? "Galutinis (vidurkis)" : "Galutinis (mediana)";
    std::cout << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(15) << "Pavarde"
        << std::right << std::setw(20) << rez << std::endl;
    for (int i = 0; i < studentu_kiekis; i++) {
        std::cout << std::left << std::setw(15) << studentai[i].vardas
            << std::setw(15) << studentai[i].pavarde
            << std::right << std::setw(20) << std::fixed
            << std::setprecision(2) << studentai[i].rez << std::endl;
    }
}

//prideda studenta i masyva

void studento_pridejimas(StudentasA*& arr, int& studentu_kiekis, const StudentasA& kitas)
{
    StudentasA* temp = new StudentasA[studentu_kiekis + 1];

    for (int i = 0; i < studentu_kiekis; ++i)
    {
        temp[i] = arr[i];
    }
    temp[studentu_kiekis] = kitas;

    delete[] arr;
    arr = temp;
    studentu_kiekis++;
}


void atlaisvinti(StudentasA* arr, int studentu_kiekis)
{
    for (int i = 0; i < studentu_kiekis; i++) {
        delete[] arr[i].paz;
    }
    delete[] arr;
}