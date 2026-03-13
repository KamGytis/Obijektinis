#include "vector.h"
#include "utils.h"
#include <chrono>
#include <iostream>
#include <iomanip>

struct TestResults {
    double skaitymo_laikas;
    double skirstymo_laikas;
    double isvedimo_laikas;
    double bendras_laikas;
    int studentu_skaicius;
    int kietuju_skaicius;
    int vargsu_skaicius;
};

TestResults testuoti_apdorojima(const std::string& input_file) {
    TestResults res = { 0, 0, 0, 0, 0, 0, 0 };

    std::cout << "\n--- Testuojamas failas: " << input_file << " ---\n";

    auto start_total = std::chrono::high_resolution_clock::now();

    try {
        
        std::vector<StudentasV> studentai;
        auto start_read = std::chrono::high_resolution_clock::now();

        skaitymas_is_failo(input_file, studentai);

        auto end_read = std::chrono::high_resolution_clock::now();
        res.skaitymo_laikas = std::chrono::duration<double>(end_read - start_read).count();
        res.studentu_skaicius = studentai.size();

        std::cout << "  [OK] Nuskaityta: " << studentai.size() << " studentu\n";

        auto start_calc = std::chrono::high_resolution_clock::now();
        pasirinkimo_metodas(1, studentai);  // Vidurkis
        auto end_calc = std::chrono::high_resolution_clock::now();
        double calc_time = std::chrono::duration<double>(end_calc - start_calc).count();

        std::cout << "  [OK] Apskaiciuoti rezultatai per: " << calc_time << " s\n";

        std::vector<StudentasV> kieti, vargsai;
        auto start_split = std::chrono::high_resolution_clock::now();

        skirstymas_i_grupes(studentai, kieti, vargsai);

        auto end_split = std::chrono::high_resolution_clock::now();
        res.skirstymo_laikas = std::chrono::duration<double>(end_split - start_split).count();
        res.kietuju_skaicius = kieti.size();
        res.vargsu_skaicius = vargsai.size();

        std::cout << "  [OK] Suskirstyta: " << kieti.size() << " kietuju, "
            << vargsai.size() << " vargsu\n";

      
        auto start_output = std::chrono::high_resolution_clock::now();

        std::string base_name = input_file.substr(0, input_file.find_last_of('.'));
        if (base_name.empty()) base_name = input_file;

        isvedimas_i_faila(kieti, base_name + "_kietiakai.txt", "Kietiakai");
        isvedimas_i_faila(vargsai, base_name + "_vargsiukai.txt", "Vargsiukai");

        auto end_output = std::chrono::high_resolution_clock::now();
        res.isvedimo_laikas = std::chrono::duration<double>(end_output - start_output).count();

        auto end_total = std::chrono::high_resolution_clock::now();
        res.bendras_laikas = std::chrono::duration<double>(end_total - start_total).count();

    }
    catch (const std::exception& e) {
        std::cerr << "  [KLAIDA] " << e.what() << "\n";
    }

    return res;
}

void spausdinti_rezultatus(const std::string& failas, const TestResults& res) {
    std::cout << "\n========== REZULTATAI: " << failas << " ==========\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Studentu: " << res.studentu_skaicius << "\n";
    std::cout << "  - Kietiakai (>= 5.0): " << res.kietuju_skaicius << "\n";
    std::cout << "  - Vargsiukai (< 5.0): " << res.vargsu_skaicius << "\n\n";
    std::cout << "Skaitymo laikas:   " << res.skaitymo_laikas << " s\n";
    std::cout << "Skirstymo laikas:  " << res.skirstymo_laikas << " s\n";
    std::cout << "Isvedimo laikas:   " << res.isvedimo_laikas << " s\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "BENDRAS laikas:    " << res.bendras_laikas << " s\n";
    std::cout << "==============================================\n";
}


void atlikti_visus_testus() {
    std::vector<std::string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    std::cout << "\n########## PRADEDAMAS TESTAVIMAS ##########\n";

    for (const auto& failas : failai) {
        auto res = testuoti_apdorojima(failas);
        spausdinti_rezultatus(failas, res);
    }

    std::cout << "\n########## TESTAVIMAS BAIGTAS ##########\n";
}