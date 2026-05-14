#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct PunktySlowa
{
    std::string slowo;
    int punkty;
};

std::set<std::string> wczytaj_slowa(std::istream &strumien);
std::vector<std::pair<std::string, std::string>> podziel_slowo(const std::string &slowo);
void dodaj_1_jesli_poczatek_i_koniec_to_slowa(
    const std::string &poczatek,
    const std::string &koniec,
    const std::set<std::string> &zbior_slow,
    std::map<std::string, int> *licznik_slow);
std::vector<PunktySlowa> stworz_wektor(const std::map<std::string, int> &licznik_slow);
void posortuj_wg_punktow_malejaco(std::vector<PunktySlowa> *punkty_slowa);
void wypisz_slowa_i_punkty(const std::vector<PunktySlowa> &punkty_slow, std::ostream &strumien);
