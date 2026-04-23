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