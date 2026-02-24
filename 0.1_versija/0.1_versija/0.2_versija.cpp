#include <iostream>
#include <limits>

void vectorFunkcija();
void arrayFunkcija();

int main()
{
    while (true) {
        std::cout << "Pasirinkite funkcija (1 - vector, 2 - array, 3 - baigimas):\n";
        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (std::cin.fail()) {
            std::cerr << "Neteisingas ivestis bandykite dar karta.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (pasirinkimas == 1) {
            vectorFunkcija();
            break;
        }
        if (pasirinkimas == 2) {
            arrayFunkcija();
            break;
        }
        if (pasirinkimas == 3) {
            std::cout << "Programa baigta.\n";
            break;
        }
        if (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3) {
            std::cerr << "Tokio pasirinkimo nera, bandykite dar karta.\n";
        }
    }
    return 0;
}
