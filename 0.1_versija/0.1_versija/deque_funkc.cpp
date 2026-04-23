#include "deque.h"
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

void isvesti_pazymius_d(StudentasD& s, int paz) {
	s.paz.push_back(paz);
}

double vidurkis_d(const std::vector<int>& paz) {
	if (paz.empty()) return 0.0;
	return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

double mediana_d(const std::vector<int>& paz) {
	if (paz.empty()) return 0.0;
	std::vector<int> temp = paz;
	std::sort(temp.begin(), temp.end());
	size_t n = temp.size();
	if (n % 2 == 0) {
		return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
	} else {
		return temp[n / 2];
	}
}	

void pasirinkimo_metodas_d(int tipas, std::deque<StudentasD>& studentai) {
	for (auto& s : studentai) {
		double x = (tipas == 1) ? vidurkis_d(s.paz) : mediana_d(s.paz);
		s.rez = galutinis_vid(x, s.egz);
	}
}

void skaitymas_is_failo_d(const std::string& filename, std::deque<StudentasD>& studentai) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);

    studentai.clear();
    std::string header, line;
    std::getline(file, header);

    int nr = 0;
    while (std::getline(file, line)) {
        ++nr;
        std::stringstream ss(line);
        StudentasD s;
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
    std::cout << "  Is viso nuskaityta: " << studentai.size() << " studentu\n";
}