#define _CRT_SECURE_NO_WARNINGS
#include "struktura.h"


zmogus gen() {
    zmogus a;

    switch (rand() % 10) {
    case 0: a.vardas = "Irma"; break;
    case 1: a.vardas = "Alma"; break;
    case 2: a.vardas = "Irena"; break;
    case 3: a.vardas = "Egle"; break;
    case 4: a.vardas = "Jolanta"; break;
    case 5: a.vardas = "Petras"; break;
    case 6: a.vardas = "Jonas"; break;
    case 7: a.vardas = "Ignas"; break;
    case 8: a.vardas = "Darius"; break;
    case 9: a.vardas = "Simas"; break;
    }
    switch (*a.vardas.rbegin()) {
    case 's':
        switch (rand() % 5) {
        case 0: a.pavarde = "Pavardenis1"; break;
        case 1: a.pavarde = "Pavardenis2"; break;
        case 2: a.pavarde = "Pavardenis3"; break;
        case 3: a.pavarde = "Pavardenis4"; break;
        case 4: a.pavarde = "Pavardenis5"; break;
        }
        break;
    default:
        switch (rand() % 5) {
        case 0: a.pavarde = "Pavardaite1"; break;
        case 1: a.pavarde = "Pavardaite2"; break;
        case 2: a.pavarde = "Pavardaite3"; break;
        case 3: a.pavarde = "Pavardaite4"; break;
        case 4: a.pavarde = "Pavardaite5"; break;
        }
        break;
    }
    a.paz = rand() % 10 + 1;
    return a;
}

zmogus gen_str_mas() {

    mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    int_distribution dist(0, 9);

    zmogus a;

    string vardai[10] = { "Irma","Alma","Irena","Egle","Jolanta","Petras","Jonas","Ignas","Darius","Simas" };
    string pavardes_m[10] = { "Pavardaite1","Pavardaite2","Pavardaite3","Pavardaite4","Pavardaite5","Pavardaite6","Pavardaite7","Pavardaite8","Pavardaite9","Pavardaite10" };
    string pavardes_v[] = { "Pavardenis1","Pavardenis2","Pavardenis3","Pavardenis4","Pavardenis5","Pavardenis6","Pavardenis7","Pavardenis8","Pavardenis9","Pavardenis10" };

    a.vardas = vardai[dist(mt)];

    switch (*a.vardas.rbegin()) {
    case 's':
        a.pavarde = pavardes_v[dist(mt)];
        break;
    default:
        a.pavarde = pavardes_m[dist(mt)];
        break;
    };
    a.paz = dist(mt) + 1;
    return a;
}

zmogus gen_map() {

    mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    int_distribution dist(100, 109);
    int_distribution dist2(200, 209);
    zmogus a;

    map<int, string> vardai, pavardes_m, pavardes_v;

    vardai[100] = "Irma";
    vardai[101] = "Alma";
    vardai[102] = "Irena";
    vardai[103] = "Egle";
    vardai[104] = "Jolanta";
    vardai[105] = "Petras";
    vardai[106] = "Jonas";
    vardai[107] = "Ignas";
    vardai[108] = "Darius";
    vardai[109] = "Simas";

    pavardes_m[200] = "Pavardaite1";
    pavardes_m[201] = "Pavardaite2";
    pavardes_m[202] = "Pavardaite3";
    pavardes_m[203] = "Pavardaite4";
    pavardes_m[204] = "Pavardaite5";
    pavardes_m[205] = "Pavardaite6";
    pavardes_m[206] = "Pavardaite7";
    pavardes_m[207] = "Pavardaite8";
    pavardes_m[208] = "Pavardaite9";
    pavardes_m[209] = "Pavardaite10";

    pavardes_v[300] = "Pavardenis1";
    pavardes_v[301] = "Pavardenis2";
    pavardes_v[302] = "Pavardenis3";
    pavardes_v[303] = "Pavardenis4";
    pavardes_v[304] = "Pavardenis5";
    pavardes_v[305] = "Pavardenis6";
    pavardes_v[306] = "Pavardenis7";
    pavardes_v[307] = "Pavardenis8";
    pavardes_v[308] = "Pavardenis9";
    pavardes_v[309] = "Pavardenis10";

    a.vardas = vardai[dist(mt)];

    switch (*a.vardas.rbegin()) {
    case 's':
        a.pavarde = pavardes_v[200 + dist(mt)];
        break;
    default:
        a.pavarde = pavardes_m[100 + dist(mt)];
        break;
    };
    a.paz = dist(mt) + 1 - 100;
    return a;
}

void output(vector <zmogus>& a) {
    FILE* F;
    F = fopen("mano.txt", "wb");
    string rib(49, '-');
    string rib_str(49, '=');
    cout << rib_str << endl << "|" << left << setw(15) << "Vardas" << "|" << left << setw(15) << "Pavarde" << "|" << right << setw(15) << "Pazymis" << "|" << endl << rib_str << endl;
    for (zmogus& i : a) {
        //cout<<"|"<<left<<setw(15)<<i.vardas<<"|"<<left<<setw(15)<<i.pavarde<<"|"<<right<<setw(15)<<i.paz<<"|"<<endl;
        printf("|%-15s|%15s|%15d|\n", i.vardas.c_str(), i.pavarde.c_str(), i.paz);
        fprintf(F, "|%-15s|%15s|%15d|\n", i.vardas.c_str(), i.pavarde.c_str(), i.paz);
        (i.pavarde == a.back().pavarde && i.vardas == a.back().vardas && i.paz == a.back().paz) ? cout << rib_str << endl : cout << rib << endl;

    }
    fclose(F);
}