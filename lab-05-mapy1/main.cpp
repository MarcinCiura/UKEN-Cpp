#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "funkcje.h"

using namespace std;

static void zglos_blad(const string& nazwa_pliku) {
    cerr << "Nie udało się otworzyć pliku " << nazwa_pliku << endl;
    cerr << "Przyczyna: " << strerror(errno) << endl;
    exit(1);
}

static ifstream otworz_plik_do_odczytu(const string& nazwa_pliku) {
    auto strumien = ifstream(nazwa_pliku);
    if (!strumien) {
        zglos_blad(nazwa_pliku);
    }
    return strumien;
}

static ofstream otworz_plik_do_zapisu(const string& nazwa_pliku) {
    auto strumien = ofstream(nazwa_pliku);
    if (!strumien) {
      zglos_blad(nazwa_pliku);
    }
    return strumien;
}

int main() {
    const string NAZWA_PLIKU_STUDENCI{"studenci.txt"};
    const string NAZWA_PLIKU_OCENY{"oceny.txt"};
    const int LICZBA_STUDENTOW{1000};
    vector<int> pesele;
    map<int, Student> studenci;
    {
        ofstream strumien = otworz_plik_do_zapisu(NAZWA_PLIKU_STUDENCI);
        pesele = tworz_studentow(strumien, LICZBA_STUDENTOW);
        strumien.close();
    }
    {
        ofstream strumien = otworz_plik_do_zapisu(NAZWA_PLIKU_OCENY);
        tworz_oceny(pesele, strumien);
        strumien.close();
    }
    {
        ifstream strumien = otworz_plik_do_odczytu(NAZWA_PLIKU_STUDENCI);
        studenci = wczytaj_studentow(strumien);
        strumien.close();
    }
    string najpopularniejsze_imie = wyznacz_najpopularniejsze_imie(studenci);
    cout << "najpopularniejsze imie: " << najpopularniejsze_imie << endl;

    auto [najpopularniejsze_nazwisko, liczba_osob] = wyznacz_najpopularniejsze_nazwisko(studenci);
    cout << "najpopularniejsze nazwisko: " << najpopularniejsze_nazwisko << '\t' << liczba_osob
         << endl;
    {
        ifstream strumien = otworz_plik_do_odczytu(NAZWA_PLIKU_OCENY);
        wczytaj_oceny(strumien, &studenci);
        strumien.close();
    }
    wypisz_studentow_i_ich_oceny(studenci, cout);
    cout << "liczba studentow bez ocen: " << policz_studentow_bez_ocen(studenci) << endl;
}
