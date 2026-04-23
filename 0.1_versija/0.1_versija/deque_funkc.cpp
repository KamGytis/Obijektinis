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