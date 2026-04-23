#include "list.h"
#include "utils.h"	

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>

void ivesti_pazymius_l(StudentasL& s, int paz) {
	s.paz.push_back(paz);
}

double vidurkis_l(const std::vector<int>& paz) {
	if (paz.empty()) return 0.0;
	return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

double mediana_l(const std::vector<int>& paz) {
	if (paz.empty()) return 0.0;
	std::vector<int> tmp = paz;
	std::sort(tmp.begin(), tmp.end());
	size_t n = tmp.size();
	return (n % 2 == 0) ? (tmp[n/2-1] + tmp[n/2]) / 2.0 : tmp[n/2];
}

void pasirinkimo_metodas_l(int tipas, std::list<StudentasL>& studentai) {
	for (auto& s : studentai) {
		double x = (tipas == 1) ? vidurkis_l(s.paz) : mediana_l(s.paz);
		s.rez = galutinis_vid(x, s.egz);
	}
}

void skaitymas_is_failo_l(const std::string& filename, std::list<StudentasL>& studentai) {
	std::ifstream
		file(filename);
	if (!file.is_open())
		throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
	
	studentai.clear();
	std::string header, line;
	std::getline(file, header);
	
	int nr = 0;
	while (std::getline(file, line)) {
		++nr;
		std::stringstream ss(line);
		StudentasL s;
		ss >> s.vardas >> s.pavarde;
		int v;
		while (ss >> v) s.paz.push_back(v);
		if (s.paz.empty()) continue;
		s.egz = s.paz.back();
		s.paz.pop_back();
		studentai.push_back(std::move(s));
		if (nr % 100000 == 0)
			std::cout << "  Nuskaityta: " << nr << " studentu...\n";
	}
	std::cout << "  Nuskaityta: " << nr << " studentu is failo: " << filename << "\n";
}


