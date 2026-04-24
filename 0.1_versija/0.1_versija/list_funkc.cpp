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

//list rusiavimas pagal pavarde, varda
void rusiavimas_l(std::list<StudentasL>& studentai) {
	studentai.sort([](const StudentasL& a, const StudentasL& b) {
		if (a.pavarde != b.pavarde)
			return a.pavarde < b.pavarde;
		return a.vardas < b.vardas;
	});
}

// ============================================================
// STRATEGIJA 1 du nauji konteineriai, originalas lieka nepakeistas
// // Naudoja std::copy_if
// ============================================================

double skirstymas_i_grupes_l(const std::list<StudentasL>& visi,
	std::list<StudentasL>& kieti,
	std::list<StudentasL>& vargsai) {
	auto t0 = std::chrono::high_resolution_clock::now();
	
	kieti.clear();
	vargsai.clear();
	
	for (const auto& s : visi) {
		if (s.rez < 5.0)
			vargsai.push_back(s);
		else
			kieti.push_back(s);
	}
	
}

// ============================================================
// STRATEGIJA 2 vienas naujas konteineris (vargsai), originalas tampa kietiakai
// Naudoja iteracija su erase
// ============================================================
double skirstymas_s2_l(std::list<StudentasL>& studentai,
	std::list<StudentasL>& vargsai) {
	auto t0 = std::chrono::high_resolution_clock::now();

	vargsai.clear();

	for (auto it = studentai.begin(); it != studentai.end(); ) {
		if (it->rez < 5.0) {
			vargsai.push_back(*it);
			it = studentai.erase(it);  // list::erase - O(1), nekeicia kitu elementu
		} else {
			++it;
		}
	}

	return std::chrono::duration<double>(
		std::chrono::high_resolution_clock::now() - t0).count();
}
// ============================================================
// STRATEGIJA 3 splice - nulines kopijos
// Naudoja list::splice – nulines kopijos, O(n) iteracija
// ============================================================

double skirstymas_s3_d(std::list<StudentasL>& studentai,
	std::list<StudentasL>& vargsai) {
	auto t0 = std::chrono::high_resolution_clock::now();
	vargsai.clear();
	for (auto it = studentai.begin(); it != studentai.end(); ) {
		if (it->rez < 5.0) {
			vargsai.splice(vargsai.end(), studentai, it++);
		} else {
			++it;
		}
	}
	return std::chrono::duration<double>(
		std::chrono::high_resolution_clock::now() - t0).count();
}

void isvedimas_i_faila_l(const std::list<StudentasL>& studentai,
	const std::string& filename,
	const std::string& kategorija) {
	std::ofstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
	
	file << "Vardas Pavarde ";
	for (size_t i = 1; i <= 10; ++i)
		file << "Pazymys" << i << " ";
	file << "Egzaminas Rezultatas\n";
	
	for (const auto& s : studentai) {
		file << s.vardas << " " << s.pavarde << " ";
		for (size_t i = 0; i < s.paz.size(); ++i)
			file << s.paz[i] << " ";
		for (size_t i = s.paz.size(); i < 10; ++i)
			file << "0 ";
		file << s.egz << " " << std::fixed << std::setprecision(2) << s.rez << "\n";
	}
}