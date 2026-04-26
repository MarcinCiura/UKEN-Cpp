// Testy funkcji z pliku funkcje.cpp

#include "funkcje.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

using namespace std;

namespace {

TEST(WczytajStudentowTest, WczytujePoprawnie) {
  stringstream wejscie{
      R"(Eryk    Klimek  903072088
Henryk  Wozniak 682759817
)"};
  map<int, Student> oczekiwane = {
      {903072088, {.imie = "Eryk", .nazwisko = "Klimek"}},
      {682759817, {.imie = "Henryk", .nazwisko = "Wozniak"}},
  };
  map<int, Student> wynik = wczytaj_studentow(wejscie);
  ASSERT_EQ(wynik.size(), oczekiwane.size());
  for (const auto [klucz, student] : wynik) {
    ASSERT_EQ(student.imie, oczekiwane[klucz].imie);
    ASSERT_EQ(student.nazwisko, oczekiwane[klucz].nazwisko);
    ASSERT_EQ(student.oceny_z_przedmiotow,
              oczekiwane[klucz].oceny_z_przedmiotow);
  }
}

TEST(WczytajOcenyTest, WczytujePoprawnie) {
  map<int, Student> studenci = {
      {903, {.imie = "Eryk", .nazwisko = "Klimek"}},
      {682, {.imie = "Henryk", .nazwisko = "Wozniak"}},
  };
  stringstream oceny{
      R"(682       sieci_komputerowe       4.5
        682       programowanie   2.5     3.5
)"};
  map<int, Student> oczekiwane = {
      {903, {"Eryk", "Klimek", {}}},
      {682,
       {"Henryk",
        "Wozniak",
        {
            {"sieci_komputerowe", {4.5}},
            {"programowanie", {2.5, 3.5}},
        }}},
  };
  wczytaj_oceny(oceny, &studenci);
  ASSERT_EQ(studenci.size(), oczekiwane.size());
  for (const auto [klucz, student] : studenci) {
    ASSERT_EQ(student.imie, oczekiwane[klucz].imie);
    ASSERT_EQ(student.nazwisko, oczekiwane[klucz].nazwisko);
    ASSERT_EQ(student.oceny_z_przedmiotow,
              oczekiwane[klucz].oceny_z_przedmiotow);
  }
}

TEST(WyznaczNajpopularniejszeImieTest, DzialaPoprawnie) {
  map<int, Student> studenci = {
      {903, {.imie = "Eryk", .nazwisko = "Klimek"}},
      {682, {.imie = "Henryk", .nazwisko = "Wozniak"}},
      {783, {.imie = "Eryk", .nazwisko = "Nowak"}},
  };
  ASSERT_EQ(wyznacz_najpopularniejsze_imie(studenci), "Eryk");
}

TEST(WyznaczNajpopularniejszeNazwiskoTest, DzialaPoprawnie) {
  map<int, Student> studenci = {
      {903, {.imie = "Eryk", .nazwisko = "Klimek"}},
      {682, {.imie = "Henryk", .nazwisko = "Wozniak"}},
      {384, {.imie = "Jan", .nazwisko = "Wozniak"}},
  };
  pair<string, int> oczekiwane{"Wozniak", 2};
  ASSERT_EQ(wyznacz_najpopularniejsze_nazwisko(studenci), oczekiwane);
}

TEST(WypiszStudentowIIchOcenyTest, WypisujePoprawnie) {
  map<int, Student> studenci = {
      {903, {"Eryk", "Klimek", {}}},
      {682,
       {"Henryk",
        "Wozniak",
        {
            {"sieci_komputerowe", {4.5}},
            {"programowanie", {2.5, 3.5}},
        }}},
  };
  stringstream wynik;
  wypisz_studentow_i_ich_oceny(studenci, wynik);
  string oczekiwane = "Henryk Wozniak (682)\n"
                      "\tprogramowanie\t2.5 3.5 \n"
                      "\tsieci_komputerowe\t4.5 \n"
                      "Eryk Klimek (903)\n";
  ASSERT_EQ(wynik.str(), oczekiwane);
}

TEST(PoliczStudentowBezOcenTest, DzialaPoprawnie) {
  map<int, Student> studenci = {
      {903, {"Eryk", "Klimek", {}}},
      {682,
       {"Henryk",
        "Wozniak",
        {
            {"sieci_komputerowe", {4.5}},
            {"programowanie", {2.5, 3.5}},
        }}},
  };
  ASSERT_EQ(policz_studentow_bez_ocen(studenci), 1);
}

} // namespace

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
