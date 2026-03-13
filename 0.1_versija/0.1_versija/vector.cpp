#include <limits>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

#include "struktura.h"
#include "vector.h"
#include "utils.h"

void vectorFunkcija() {
    std::srand(std::time(nullptr));

    while (true) {
        int pasirinkimas;

        std::cout << "\n-------------------------Meniu-------------------------\n";
        std::cout << "1 - ranka ivedimas\n";
        std::cout << "2 - generuoti tik pazymius\n";
        std::cout << "3 - generuoti studentu vardus, pavardes ir pazymius\n";
        std::cout << "4 - skaityti is failo\n";
        std::cout << "5 - baigti darba\n";
        std::cin >> pasirinkimas;

        if (std::cin.fail()) {
            std::cerr << "Neteisingas ivestis bandykite dar karta.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (pasirinkimas == 1) {
            std::vector<StudentasV> studentai;  
            int chosen_option = 1;

            do {
                StudentasV studentas;

                studentas.vardas = ivesti_varda_ar_pavarde("Iveskite varda: ");
                studentas.pavarde = ivesti_varda_ar_pavarde("Iveskite pavarde: ");

                std::cout << "Iveskite pazymi (0-10). Baigti -1\n";
                while (true) {
                    int paz = ivesties_tikrinimas("Pazymys: ");
                    if (paz == -1) break;
                    ivesti_pazymius(studentas, paz);
                }

                studentas.egz = ivesties_tikrinimas("Egzamino pazymys: ");

                studentai.push_back(studentas);  

                std::cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                std::cin >> chosen_option;
            } while (chosen_option == 1);

            if (!studentai.empty()) {
                int tipas = skaiciavimo_metodas();
                pasirinkimo_metodas(tipas, studentai);
                isvedimas(studentai, tipas);
            }

            break;
        }

        if (pasirinkimas == 2) {
            std::vector<StudentasV> studentai;
            int chosen_option = 1;

            do {
                StudentasV studentas;

                studentas.vardas = ivesti_varda_ar_pavarde("Iveskite varda: ");
                studentas.pavarde = ivesti_varda_ar_pavarde("Iveskite pavarde: ");

                int n_kiekis = ivesties_skaicius("Kiek generuoti namu darbu pazymiu? ");

                std::cout << "Sugeneruoti namu darbu pazymiai: ";
                for (int i = 0; i < n_kiekis; ++i) {
                    int paz = std::rand() % 10 + 1;
                    ivesti_pazymius(studentas, paz);
                    std::cout << paz << " ";
                }
                std::cout << "\n";

                studentas.egz = std::rand() % 10 + 1;
                std::cout << "Sugeneruotas egzamino pazymys: " << studentas.egz << "\n";

                studentai.push_back(studentas);

                std::cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                std::cin >> chosen_option;
            } while (chosen_option == 1);

            if (!studentai.empty()) {
                int tipas = skaiciavimo_metodas();
                pasirinkimo_metodas(tipas, studentai);
                isvedimas(studentai, tipas);
            }

            break;
        }

        if (pasirinkimas == 3) {
            std::vector<StudentasV> studentai;

            int studentu_skaicius = ivesties_skaicius("Kiek generuoti studentu? ");
            int n_kiekis = ivesties_skaicius("Kiek generuoti namu darbu pazymiu kiekvienam? ");

            for (int i = 0; i < studentu_skaicius; ++i) {
                StudentasV studentas;

                zmogus s = gen();
                studentas.vardas = s.vardas;
                studentas.pavarde = s.pavarde;

                std::cout << "\nStudentas: " << studentas.vardas << " " << studentas.pavarde << "\n";
                std::cout << "Namu darbu pazymiai: ";

                for (int j = 0; j < n_kiekis; ++j) {
                    int paz = gen().paz;
                    ivesti_pazymius(studentas, paz);
                    std::cout << paz << " ";
                }
                std::cout << "\n";

                studentas.egz = std::rand() % 10 + 1;
                std::cout << "Egzamino pazymys: " << studentas.egz << "\n";

                studentai.push_back(studentas);
            }

            int tipas = skaiciavimo_metodas();
            pasirinkimo_metodas(tipas, studentai);
            isvedimas(studentai, tipas);

            break;
        }

        if (pasirinkimas == 4) {
            std::vector<StudentasV> studentai;
            std::string failo_pavadinimas;

            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failo_pavadinimas;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try {
                auto start_read = std::chrono::high_resolution_clock::now();
                skaitymas_is_failo(failo_pavadinimas, studentai);
                auto end_read = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> read_time = end_read - start_read;

                if (studentai.empty()) {
                    throw std::runtime_error("Failas tuscias arba nepavyko nuskaityti");
                }

                cout << "Nuskaitymo laikas: " << read_time.count() << " sekundziu\n";

                int skaiciavimo_budas = skaiciavimo_metodas();
                int rusiavimas_studentu = pasirinkimas_rusiavimo_budo();
                int spausdinimo_budas = isvedimo_budas();

                pasirinkimo_metodas(skaiciavimo_budas, studentai);
                rusiavimas(studentai, rusiavimas_studentu);

                if (spausdinimo_budas == 2) {
                    auto start_output = std::chrono::high_resolution_clock::now();
                    std::string spausdinimo_failas;
                    std::cout << "Iveskite spausdinimo failo pavadinima: ";
                    std::cin >> spausdinimo_failas;
                    spausdinimas_i_faila(studentai, spausdinimo_failas);
                    auto end_output = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> output_time = end_output - start_output;
                    cout << "Spausdinimo laikas: " << output_time.count() << " sekundziu\n";
                }
                else {
                    auto start_output = std::chrono::high_resolution_clock::now();
                    isvedimas(studentai, skaiciavimo_budas);
                    auto end_output = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> output_time = end_output - start_output;
                    cout << "Isvedimo laikas: " << output_time.count() << " sekundziu\n";
                }
            }
            catch (const std::runtime_error& e) {
                std::cerr << "Klaida: " << e.what() << "\n";
                continue;
            }
            catch (const std::exception& e) {
                std::cerr << "Netiketa klaida: " << e.what() << "\n";
                continue;
            }

            break;
        }
        if (pasirinkimas == 5) {
            std::cout << "\n--- FAILU GENERATORIUS ---\n";
            std::cout << "1 - Generuoti visus testu failus (1k, 10k, 100k, 1M, 10M)\n";
            std::cout << "2 - Generuoti pasirinktini faila\n";
            std::cout << "3 - Atlikti testavima (TYRIMAS 2)\n";
            std::cout << "Jusu pasirinkimas: ";

            int sub_choice;
            std::cin >> sub_choice;

            if (sub_choice == 1) {
                generuoti_testu_failus();
            }
            else if (sub_choice == 2) {
                int skaicius;
                std::string pavadinimas;
                std::cout << "Kiek studentu generuoti? ";
                std::cin >> skaicius;
                std::cout << "Failo pavadinimas: ";
                std::cin >> pavadinimas;
                generuoti_faila(pavadinimas, skaicius, 5);
            }
            else if (sub_choice == 3) {
                atlikti_visus_testus();
            }

            break;
        }

        if (pasirinkimas == 6) {
            std::cout << "Programa baigta.\n";
            break;
        }

        if (pasirinkimas == 6) {
            std::cout << "Programa baigta.\n";
            break;
        }
        std::cerr << "Tokio pasirinkimo nera, bandykite dar karta.\n";
    }
}