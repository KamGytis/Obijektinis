#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <chrono>

#include "vector.h"
#include "list.h"
#include "deque.h"
#include "utils.h"

void generuoti_testu_failus();
void generuoti_faila(const std::string&, int, int);
void atlikti_visus_testus();

// Skaitymas is failo - kiekvienas konteineris

static void skaityti_vector() {
    std::string fn;
    std::cout << "Failo pavadinimas: "; std::cin >> fn;

    std::vector<StudentasV> studentai;
    try {
        auto t0 = std::chrono::high_resolution_clock::now();
        skaitymas_is_failo(fn, studentai);
        double dt = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();
        if (studentai.empty()) throw std::runtime_error("Failas tuscias");
        std::cout << "Skaitymas: " << dt << " s\n";
    }
    catch (const std::exception& e) { std::cerr << e.what() << "\n"; return; }

    int met = skaiciavimo_metodas();
    pasirinkimo_metodas(met, studentai);

    int rus = pasirinkimas_rusiavimo_budo();
    auto t0 = std::chrono::high_resolution_clock::now();
    rusiavimas(studentai, rus);
    std::cout << "Rusiavimas: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count() << " s\n";

    std::vector<StudentasV> kieti, vargsai;
    t0 = std::chrono::high_resolution_clock::now();
    skirstymas_i_grupes(studentai, kieti, vargsai);
    std::cout << "Skirstymas: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count() << " s\n";
    std::cout << "Kietiakai: " << kieti.size() << " | Vargsai: " << vargsai.size() << "\n";

    std::string base = fn.substr(0, fn.find_last_of('.'));
    isvedimas_i_faila(kieti, base + "_kietiakai.txt", "Kietiakai");
    isvedimas_i_faila(vargsai, base + "_vargsiukai.txt", "Vargsiukai");
}

