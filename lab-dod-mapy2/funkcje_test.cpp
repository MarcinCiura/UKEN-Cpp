#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "funkcje.h"

using namespace std;

namespace
{

    TEST(WczytajSlowaTest, WczytujePoprawnie)
    {
        stringstream wejscie{
            R"(los
            lot
            wylot)"};
        set<string> wynik = wczytaj_slowa(wejscie);
        set<string> oczekiwane{"los", "lot", "wylot"};
        ASSERT_EQ(wynik, oczekiwane);
    }

    TEST(PodzielSlowoTest, DzieliPoprawnie)
    {
        vector<pair<string, string>> oczekiwane{
            {"w", "yraz"}, {"wy", "raz"}, {"wyr", "az"}, {"wyra", "z"}};
        ASSERT_EQ(podziel_slowo("wyraz"), oczekiwane);
    }

    TEST(Dodaj1Test, DodajeGdyPoczatekIKoniecToSlowa)
    {
        set<string> zbior_slow = {"wy", "raz", "lot"};
        map<string, int> licznik_slow;
        dodaj_1_jesli_poczatek_i_koniec_to_slowa("wy", "raz", zbior_slow, &licznik_slow);
        map<string, int> oczekiwane{{"wy", 1}, {"raz", 1}};
        ASSERT_EQ(licznik_slow, oczekiwane);
    }

    TEST(Dodaj1Test, NieDodajeGdyPoczatekToNieSlowo)
    {
        set<string> zbior_slow = {"raz", "lot"};
        map<string, int> licznik_slow;
        dodaj_1_jesli_poczatek_i_koniec_to_slowa("wy", "raz", zbior_slow, &licznik_slow);
        map<string, int> oczekiwane{};
        ASSERT_EQ(licznik_slow, oczekiwane);
    }

    TEST(Dodaj1Test, NieDodajeGdyKoniecToNieSlowo)
    {
        set<string> zbior_slow = {"raz", "lot"};
        map<string, int> licznik_slow;
        dodaj_1_jesli_poczatek_i_koniec_to_slowa("lot", "nia", zbior_slow, &licznik_slow);
        map<string, int> oczekiwane{};
        ASSERT_EQ(licznik_slow, oczekiwane);
    }

    TEST(StworzWektor, TworzyPoprawnie)
    {
        map<string, int> licznik_slow{{"lot", 1}, {"raz", 1}, {"wy", 2}};
        vector<PunktySlowa> wynik = stworz_wektor(licznik_slow);
        vector<PunktySlowa> oczekiwane{{"lot", 1}, {"raz", 1}, {"wy", 2}};
        ASSERT_EQ(wynik.size(), oczekiwane.size());
        for (size_t i = 0; i < wynik.size(); ++i)
        {
            ASSERT_EQ(wynik[i].slowo, oczekiwane[i].slowo);
            ASSERT_EQ(wynik[i].punkty, oczekiwane[i].punkty);
        }
    }

    TEST(PosortujWgPunktowMalejacoTest, SortujePoprawnie)
    {
        vector<PunktySlowa> punkty_slow{{"lot", 1}, {"raz", 1}, {"wy", 2}};
        posortuj_wg_punktow_malejaco(&punkty_slow);
        vector<PunktySlowa> oczekiwane{{"wy", 2}, {"lot", 1}, {"raz", 1}};
        ASSERT_EQ(punkty_slow.size(), oczekiwane.size());
        for (size_t i = 0; i < punkty_slow.size(); ++i)
        {
            ASSERT_EQ(punkty_slow[i].slowo, oczekiwane[i].slowo);
            ASSERT_EQ(punkty_slow[i].punkty, oczekiwane[i].punkty);
        }
    }

    TEST(WypiszSlowaIPunktyTest, WypisujePoprawnie)
    {
        vector<PunktySlowa> punkty_slow{{"wy", 2}, {"lot", 1}, {"raz", 1}};
        stringstream wyjscie;
        wypisz_slowa_i_punkty(punkty_slow, wyjscie);
        string oczekiwane{"wy\t2\nlot\t1\nraz\t1\n"};
        ASSERT_EQ(wyjscie.str(), oczekiwane);
    }

} // namespace

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
