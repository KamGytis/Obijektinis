#include <limits>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

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
        std::cout << "4 - baigti darba\n";
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
            std::cout << "Programa baigta.\n";
            break;
        }

        std::cerr << "Tokio pasirinkimo nera, bandykite dar karta.\n";
    }
}