#ifndef LIST.h
#define LIST_H	

#include <string>
#include <vector>	
#include <list>

struct StudentasL {
	std::string vardas  = "";
	std::string pavarde = "";
	std::vector<int> paz;
	int    egz = 0;
	double rez = 0.00;
};

void ivesti_pazymius_l(StudentasL& s, int paz);
double vidurkis_l(const std::vector<int>& paz);
double mediana_l(const std::vector<int>& paz);


#endif // !list.h
