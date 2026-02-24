#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <chrono>
#include <random>


using std::string;
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::vector;
using std::map;
using std::mt19937;

using hrClock = std::chrono::high_resolution_clock;
typedef std::uniform_int_distribution<int>  int_distribution;

struct zmogus {
	string vardas, pavarde;
	int paz;
};

zmogus gen();
zmogus gen_str_mas();
zmogus gen_map();
void output(vector <zmogus>& a);