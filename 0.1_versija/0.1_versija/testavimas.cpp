#include "vector.h"
#include "list.h"
#include "deque.h"
#include "utils.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>

// -------------------------------------------------------
// Rezultatu struktura
// -------------------------------------------------------
struct TestRow {
    std::string konteineris;
    std::string failas;
    int    studentu_sk = 0;
    double skaitymas = 0.0;
    double rusiavimas = 0.0;
    double skirstymas = 0.0;
    double bendras = 0.0;
};

static void spausdinti_lentele(const std::vector<TestRow>& eilutes) {
    std::cout << "\n" << std::string(90, '=') << "\n";
    std::cout << std::left
        << std::setw(8) << "Kont."
        << std::setw(24) << "Failas"
        << std::right
        << std::setw(10) << "Stud."
        << std::setw(12) << "Skait.(s)"
        << std::setw(12) << "Rusi.(s)"
        << std::setw(12) << "Skirsti.(s)"
        << std::setw(12) << "Bendras(s)"
        << "\n" << std::string(90, '-') << "\n";

    for (const auto& r : eilutes) {
        std::cout << std::left
            << std::setw(8) << r.konteineris
            << std::setw(24) << r.failas
            << std::right << std::fixed << std::setprecision(6)
            << std::setw(10) << r.studentu_sk
            << std::setw(12) << r.skaitymas
            << std::setw(12) << r.rusiavimas
            << std::setw(12) << r.skirstymas
            << std::setw(12) << r.bendras
            << "\n";
    }
    std::cout << std::string(90, '=') << "\n";
}

// -------------------------------------------------------
// Individualus testai kiekvienam konteineriui
// -------------------------------------------------------
static TestRow testuoti_vector(const std::string& f) {
    TestRow r; r.konteineris = "vector"; r.failas = f;
    auto total = std::chrono::high_resolution_clock::now();

    std::vector<StudentasV> studentai;
    auto t0 = std::chrono::high_resolution_clock::now();
    skaitymas_is_failo(f, studentai);
    r.skaitymas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();
    r.studentu_sk = (int)studentai.size();

    pasirinkimo_metodas(1, studentai);

    t0 = std::chrono::high_resolution_clock::now();
    rusiavimas(studentai, 5);
    r.rusiavimas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

    std::vector<StudentasV> kieti, vargsai;
    t0 = std::chrono::high_resolution_clock::now();
    skirstymas_i_grupes(studentai, kieti, vargsai);
    r.skirstymas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

    r.bendras = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - total).count();
    return r;
}

static TestRow testuoti_list(const std::string& f) {
    TestRow r; r.konteineris = "list"; r.failas = f;
    auto total = std::chrono::high_resolution_clock::now();

    std::list<StudentasL> studentai;
    auto t0 = std::chrono::high_resolution_clock::now();
    skaitymas_is_failo_l(f, studentai);
    r.skaitymas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();
    r.studentu_sk = (int)studentai.size();

    pasirinkimo_metodas_l(1, studentai);

    t0 = std::chrono::high_resolution_clock::now();
    rusiavimas_l(studentai);
    r.rusiavimas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

    std::list<StudentasL> kieti, vargsai;
    t0 = std::chrono::high_resolution_clock::now();
    skirstymas_i_grupes_l(studentai, kieti, vargsai);
    r.skirstymas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

    r.bendras = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - total).count();
    return r;
}

static TestRow testuoti_deque(const std::string& f) {
    TestRow r; r.konteineris = "deque"; r.failas = f;
    auto total = std::chrono::high_resolution_clock::now();

    std::deque<StudentasD> studentai;
    auto t0 = std::chrono::high_resolution_clock::now();
    skaitymas_is_failo_d(f, studentai);
    r.skaitymas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();
    r.studentu_sk = (int)studentai.size();

    pasirinkimo_metodas_d(1, studentai);

    t0 = std::chrono::high_resolution_clock::now();
    rusiavimas_d(studentai);
    r.rusiavimas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

    std::deque<StudentasD> kieti, vargsai;
    t0 = std::chrono::high_resolution_clock::now();
    skirstymas_i_grupes_d(studentai, kieti, vargsai);
    r.skirstymas = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

    r.bendras = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - total).count();
    return r;
}

// -------------------------------------------------------
// Pagrindine funkcija - visi failai * visi konteineriai
// -------------------------------------------------------
void atlikti_visus_testus() {
    const std::vector<std::string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    std::vector<TestRow> rezultatai;
    std::cout << "\n########## PRADEDAMAS TESTAVIMAS ##########\n\n";

    for (const auto& f : failai) {
        std::cout << ">> vector  | " << f << "\n";
        try { rezultatai.push_back(testuoti_vector(f)); }
        catch (const std::exception& e) { std::cerr << "  KLAIDA: " << e.what() << "\n"; }

        std::cout << ">> list    | " << f << "\n";
        try { rezultatai.push_back(testuoti_list(f)); }
        catch (const std::exception& e) { std::cerr << "  KLAIDA: " << e.what() << "\n"; }

        std::cout << ">> deque   | " << f << "\n";
        try { rezultatai.push_back(testuoti_deque(f)); }
        catch (const std::exception& e) { std::cerr << "  KLAIDA: " << e.what() << "\n"; }
    }

    std::cout << "\n########## TESTAVIMAS BAIGTAS ##########\n";
    spausdinti_lentele(rezultatai);
}