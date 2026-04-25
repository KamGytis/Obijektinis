# Studentų programa v1.0
 
Programa skirta studentų duomenų nuskaitymui, rūšiavimui ir skirstymui į grupes naudojant `std::vector`, `std::list` ir `std::deque` konteinerius su skirtingomis skirstymo strategijomis.
 
---
 
## Turinys
1. [Reikalavimai](#reikalavimai)
2. [Įdiegimo instrukcija](#įdiegimo-instrukcija)
3. [Naudojimo instrukcija](#naudojimo-instrukcija)
4. [Testavimo sistema](#testavimo-sistema)
5. [Konteinerių tyrimas](#konteinerių-tyrimas)
6. [Strategijų tyrimas](#strategijų-tyrimas)
7. [Relizų aprašas](#relizų-aprašas)
---
 
## Reikalavimai
 
- C++17 kompiliatorius (`g++` arba MSVC 2019+)
- Windows / Linux / macOS
- `make` (Linux/macOS kompiliavimui)
---
 
## Įdiegimo instrukcija
 
### Linux / macOS
 
```bash
git clone https://github.com/KamGytis/StudentuProgramaV1.git
cd StudentuProgramaV1
make
./studentai
```
### Makefile komandos (Linux / macOS)
 
```bash
make          # Kompiliuoti programą
make run      # Kompiliuoti ir paleisti
make clean    # Ištrinti sukompiliuotą failą
```
 
---
 
### Windows (Visual Studio)
 
Atidaryti `.sln` failą ir spausti **Build → Build Solution**, tada paleisti `studentai.exe`.
 
---
 
## Naudojimo instrukcija
 
```
======= STUDENTU PROGRAMA v1.0 =======
1 - Rankinis ivedimas
2 - Skaityti is failo (vector)
3 - Skaityti is failo (list)
4 - Skaityti is failo (deque)
5 - Testavimas (visi konteineriai)
6 - Generuoti studentu failus
7 - Baigti
```

 
- **1 parinktis** – rankinis duomenų įvedimas, studento vardo, pavardės, pažymių, egzamino įvedimas ir rezultato išvedimas.
- **2–4 parinktis** – skaitymas iš pasirinkto `.txt` failo su pasirinktu konteineriu, rūšiavimas ir skirstymas į grupes.
- **5 parinktis** – testavimas su failais: pasirenkamas konteinerio tipas, strategija; išvedami testo rezultatai (skaitymas, rūšiavimas, skirstymas, bendras laikas).
- **6 parinktis** – studentų failų generavimas (1k, 10k, 100k, 1M, 10M įrašų).
- **7 parinktis** – programos nutraukimas.
**Rekomenduojama tvarka:**
1. Pasirinkti **6 → 1** – sugeneruoti testų failus.
2. Pasirinkti **5** – atlikti lyginamąjį testavimą.
---
 
## Testavimo sistema
 
| Komponentas    | Parametrai                          |
|----------------|-------------------------------------|
| CPU            | AMD Ryzen 5 7600x 6-Core            |
| RAM            | 32GB DDR5 6000 MHz                  |
| Saugykla       | Samsung SSD 980 PRO 1TB             |
| OS             | Windows 11                          |
| Kompiliatorius | MSVC, Release x64, `-O2`            |
 
---
 
## Konteinerių tyrimas
 
Atlikta programos veikimo greičio analizė – išmatuota sparta kiekvienam žingsniui:
1. Duomenų nuskaitymas iš failų į konteinerį (failai visiems tyrimams tie patys).
2. Studentų rūšiavimas didėjimo tvarka (`sort`).
3. Studentų skirstymas į dvi grupes („kietiakai" ≥ 5.0, „vargšiukai" < 5.0).

| Studentai  | Konteineris | Skaitymas (s) | Rūšiavimas (s) | Skirstymas (s) | Bendras (s) |
|------------|-------------|---------------|----------------|----------------|-------------|
| 1 000      | vector      | 0.002609      | 0.000107       | 0.000109       | 0.002830    |
| 1 000      | list        | 0.002207      | 0.000084       | 0.000135       | 0.002498    |
| 1 000      | deque       | 0.001753      | 0.000118       | 0.000091       | 0.001976    |
| 10 000     | vector      | 0.018395      | 0.001073       | 0.001638       | 0.021167    |
| 10 000     | list        | 0.015906      | 0.000777       | 0.001041       | 0.017980    |
| 10 000     | deque       | 0.016473      | 0.001273       | 0.001041       | 0.018957    |
| 100 000    | vector      | 0.175295      | 0.008178       | 0.017766       | 0.201879    |
| 100 000    | list        | 0.161659      | 0.013382       | 0.012996       | 0.190517    |
| 100 000    | deque       | 0.162850      | 0.013137       | 0.019541       | 0.196922    |
| 1 000 000  | vector      | 1.621824      | 0.077341       | 0.183886       | 1.889302    |
| 1 000 000  | list        | 1.553251      | 0.187494       | 0.121529       | 1.887412    |
| 1 000 000  | deque       | 1.558698      | 0.176511       | 0.179653       | 1.930170    |
| 10 000 000 | vector      | 16.119043     | 0.918409       | 2.087955       | 19.186857   |
| 10 000 000 | list        | 15.443401     | 2.541169       | 1.288507       | 19.510578   |
| 10 000 000 | deque       | 15.695016     | 2.811430       | 1.880202       | 20.540037   |
 
---
 
## Strategijų tyrimas
 
### Skirstymo strategijos
 
**S1 strategija** – bendro konteinerio skaidymas į du naujus to paties tipo konteinerius: „vargšiukai" ir „kietiakai". Studentas yra **dvejuose** konteineriuose. Naudojamas `std::copy_if`.
- **Atmintis:** ~3× daugiau nei originalas.
**S2 strategija** – vargšiukai perkeliami į naują konteinerį ir **ištrinami** iš originalo. Po operacijos originale lieka tik kietiakai. Naudojamas `std::copy_if` + `std::remove_if` + `erase` (vector/deque), kilpa su `erase` (list).
- **Atmintis:** ~2× (efektyviau nei S1).
**S3 strategija** – optimizuota naudojant efektyvius algoritmus:
- `vector`/`deque`: `std::partition` – vienas praėjimas, minimalios kopijos.
- `list`: `splice` – tik rodyklių perkyšimas, **nulinės kopijos**, O(n).
### Skirstymo laikų palyginimas (s)
 
| Studentai  | Konteineris | S1       | S2       | S3       |
|------------|-------------|----------|----------|----------|
| 1 000      | vector      | 0.000255 | 0.000092 | 0.000106 |
| 1 000      | list        | 0.000090 | 0.000042 | 0.000005 |
| 1 000      | deque       | 0.000164 | 0.000065 | 0.000054 |
| 10 000     | vector      | 0.002146 | 0.001056 | 0.000460 |
| 10 000     | list        | 0.001698 | 0.000774 | 0.000076 |
| 10 000     | deque       | 0.002279 | 0.000933 | 0.000803 |
| 100 000    | vector      | 0.028025 | 0.011580 | 0.007358 |
| 100 000    | list        | 0.031456 | 0.010685 | 0.002550 |
| 100 000    | deque       | 0.026987 | 0.016232 | 0.012511 |
| 1 000 000  | vector      | 0.280911 | 0.089127 | 0.063245 |
| 1 000 000  | list        | 0.241856 | 0.094840 | 0.023933 |
| 1 000 000  | deque       | 0.286816 | 0.154911 | 0.125056 |
| 10 000 000 | vector      | 3.042673 | 1.075638 | 0.574258 |
| 10 000 000 | list        | 2.526808 | 1.045124 | 0.251553 |
| 10 000 000 | deque       | 3.072941 | 1.745837 | 1.323491 |
 
### Rezultatų komentarai
 
**S1** yra lėčiausia – reikalauja daugiausiai atminties (~3×) ir atlieka daugiausiai kopijų.
 
**S2** greitesnė už S1 – naudoja tik vieną naują konteinerį. `vector`/`deque` atveju `erase` yra "skausminga" – reikia perkelti likusius elementus. `list::erase` yra O(1), tad list kenčia mažiau.
 
**S3** greičiausia visais atvejais. `list` + `splice` ypač efektyvu – nereikia kopijuoti duomenų, tik perkeičiamos rodyklės. 10M įrašų: S1=2.53s vs S3=0.25s – **10× skirtumas**.
 
**Konteinerių išvados:**
- `vector` – geriausias rūšiavimui (cache-friendly, `std::sort`).
- `list` – geriausias skirstymui su S3 (`splice`).
- `deque` – kompromisas, bet niekur aiškiai geriausias.
---
 
## Relizų aprašas
 
### v1.0 galutinis
- Realizuotos 3 skirstymo strategijos (S1/S2/S3) visiems trims konteineriams.
- Naudojami STL algoritmai: `std::copy_if`, `std::remove_if`, `std::partition`, `list::splice`.
- Lyginamasis tyrimas: 3 konteineriai × 3 strategijos × 5 failų dydžiai.
- Pilnas README.md su tyrimo rezultatais ir instrukcijomis.
- Pridėtas `Makefile`.
### v1.0 pradinis
- Pridėti `std::list` ir `std::deque` konteineriai.
- Testavimas su visais 3 konteineriais (skaitymas, rūšiavimas, skirstymas).
- Rezultatai aprašyti README.md.
### v0.4
- Automatinis testinių failų generavimas (1k – 10M įrašų).
- Laiko matavimas kiekvienam žingsniui.
- Studentų skirstymas į „kietiakus" ir „vargšiukus".
### v0.3
- Kodas išskirstytas į `.h` ir `.cpp` failus.
- Pridėtas `try-catch` klaidų gaudymui.
- Rūšiavimas pagal vardą, pavardę, rezultatą.
### v0.2
- Pridėtas duomenų nuskaitymas iš išorinių failų.
- Pridėtas rezultatų išvedimas į failą.
### v0.1
- Sukurta studento struktūra.
- Realizuotas vidurkio ir medianos skaičiavimas.
- Pradinis įvesties patikrinimas.
 
