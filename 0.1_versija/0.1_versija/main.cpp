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

static void skaityti_list() {
    std::string fn;
    std::cout << "Failo pavadinimas: "; std::cin >> fn;

    std::list<StudentasL> studentai;
    try {
        auto t0 = std::chrono::high_resolution_clock::now();
        skaitymas_is_failo_l(fn, studentai);
        double dt = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();
        if (studentai.empty()) throw std::runtime_error("Failas tuscias");
        std::cout << "Skaitymas: " << dt << " s\n";
    }
    catch (const std::exception& e) { std::cerr << e.what() << "\n"; return; }

    pasirinkimo_metodas_l(1, studentai);

    auto t0 = std::chrono::high_resolution_clock::now();
    rusiavimas_l(studentai);
    std::cout << "Rusiavimas: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count() << " s\n";

    std::list<StudentasL> kieti, vargsai;
    t0 = std::chrono::high_resolution_clock::now();
    skirstymas_i_grupes_l(studentai, kieti, vargsai);
    std::cout << "Skirstymas: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count() << " s\n";
    std::cout << "Kietiakai: " << kieti.size() << " | Vargsai: " << vargsai.size() << "\n";

    std::string base = fn.substr(0, fn.find_last_of('.'));
    isvedimas_i_faila_l(kieti, base + "_kietiakai.txt", "Kietiakai");
    isvedimas_i_faila_l(vargsai, base + "_vargsiukai.txt", "Vargsiukai");
}

static void skaityti_deque() {
    std::string fn;
    std::cout << "Failo pavadinimas: "; std::cin >> fn;

    std::deque<StudentasD> studentai;
    try {
        auto t0 = std::chrono::high_resolution_clock::now();
        skaitymas_is_failo_d(fn, studentai);
        double dt = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();
        if (studentai.empty()) throw std::runtime_error("Failas tuscias");
        std::cout << "Skaitymas: " << dt << " s\n";
    }
    catch (const std::exception& e) { std::cerr << e.what() << "\n"; return; }

    pasirinkimo_metodas_d(1, studentai);

    auto t0 = std::chrono::high_resolution_clock::now();
    rusiavimas_d(studentai);
    std::cout << "Rusiavimas: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count() << " s\n";

    std::deque<StudentasD> kieti, vargsai;
    t0 = std::chrono::high_resolution_clock::now();
    skirstymas_i_grupes_d(studentai, kieti, vargsai);
    std::cout << "Skirstymas: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count() << " s\n";
    std::cout << "Kietiakai: " << kieti.size() << " | Vargsai: " << vargsai.size() << "\n";

    std::string base = fn.substr(0, fn.find_last_of('.'));
    isvedimas_i_faila_d(kieti, base + "_kietiakai.txt", "Kietiakai");
    isvedimas_i_faila_d(vargsai, base + "_vargsiukai.txt", "Vargsiukai");
}


// Rankinis ivedimas (vector) - is originalo

static void rankinis_ivedimas() {
    std::vector<StudentasV> studentai;
    int chosen = 1;
    do {
        StudentasV s;
        s.vardas = ivesti_varda_ar_pavarde("Vardas: ");
        s.pavarde = ivesti_varda_ar_pavarde("Pavarde: ");
        std::cout << "Pazymiai (0-10, -1 baigti):\n";
        while (true) {
            int p = ivesties_tikrinimas("Pazymys: ");
            if (p == -1) break;
            s.paz.push_back(p);
        }
        s.egz = ivesties_tikrinimas("Egzamino pazymys: ");
        studentai.push_back(s);
        std::cout << "Dar vienas? (1-taip, 0-ne): "; std::cin >> chosen;
    } while (chosen == 1);

    if (!studentai.empty()) {
        int t = skaiciavimo_metodas();
        pasirinkimo_metodas(t, studentai);
        isvedimas(studentai, t);
    }
}