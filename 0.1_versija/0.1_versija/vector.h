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


#endif