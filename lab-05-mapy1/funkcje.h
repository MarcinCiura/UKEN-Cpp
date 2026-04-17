#pragma once

// Deklaracje funkcji
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Struktura reprezentuje studenta i jego/jej oceny.
struct Student {
    std::string imie, nazwisko;
    std::map<std::string, std::vector<double>> oceny_z_przedmiotow;
};

// Funkcja generuje dane studentow i zapisuje je do strumienia.
// @param strumien strumień, do ktorego funkcja zapisuje dane studentów
// @param N ile danych zapisać?
// @return pesele z wygenerowanych danych
std::vector<int> tworz_studentow(std::ostream& strumien, const int N);

// Funkcja generuje oceny studentow i zapisuje je do strumienia.
// @param strumien strumień, do ktorego funkcja zapisuje oceny studentów
// @param pesele pesele studentów
void tworz_oceny(const std::vector<int>& pesele, std::ostream& strumien);

std::map<int, Student> wczytaj_studentow(std::istream& strumien);

void wczytaj_oceny(std::istream& strumien, std::map<int, Student>* studenci);

std::string wyznacz_najpopularniejsze_imie(const std::map<int, Student>& studenci);

std::pair<std::string, int> wyznacz_najpopularniejsze_nazwisko(
    const std::map<int, Student>& studenci);

void wypisz_studentow_i_ich_oceny(const std::map<int, Student>& studenci, std::ostream& strumien);

int policz_studentow_bez_ocen(const std::map<int, Student>& studenci);
