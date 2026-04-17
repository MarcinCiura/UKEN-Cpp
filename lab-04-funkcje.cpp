#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

int main ()
{
	// funkcje

	std::default_random_engine silnik; // silnik do generowania liczb losowych
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count()); // ustawienie ziarna silnika z użyciem aktualnego czasu

	std::normal_distribution<double> rozklad {50, 20};

// 	////////////////////////////////////////////
// 	// 0. rozgrzewka
// 	czolem();  // Funkcja pisze cos milego na ekranie
// 	
// 	////////////////////////////////////////////
// 	// 1. 
// 	double a = rozklad(silnik);
// 	double b = rozklad(silnik);
// 	// Funkcja maksimum zwraca wartosc wieksza z dwoch:
// 	double wieksza = maksimum(a, b);
// 	std::cout << "maksimum(" << a << ", " << b << ") == " << wieksza << std::endl;
// 	
// 	////////////////////////////////////////////
// 	// 2. 
// 	double c = rozklad(silnik);
// 	// Funkcja srodkowa zwraca wartosc srodkowa pod wzgledem wartosci.
//      // Na przyklad: srodkowa(5.0, 2.0, 5.5) == 5.0
// 	double wartosc_srodkowa = srodkowa(a, b, c);
// 	std::cout << "srodkowa(" << a << ", " << b << ", " << c << ") == " << wartosc_srodkowa << std::endl;
// 	
// 	////////////////////////////////////////////
// 	// 3.
//     	
// 	const int N { 10 };
//	const double SREDNIA { 170.0 };
//	const double ODCH_STD { 10.0 };
// 	std::vector<double> wektor;
// 	
// 	// Funkcja wypełnia wektor N wartościami pseudolosowymi
//	// o rozkładzie normalnym ze średnią SREDNIA i odchyleniem standardowym ODCH_STD.
// 	wypelnij(silnik, SREDNIA, ODCH_STD, N, &wektor);
// 	
// 	// Funkcja wypisuje wektor na ekran (użyć const std::vector<double>&)
// 	wypisz(wektor);
// 	
// 	////////////////////////////////////////////
// 	// 4. 
// 	// Funkcja zwraca wartosc srednia liczb w wektorze.
// 	auto srednia_z_wektora = srednia(wektor);
// 	
// 	std::cout << "srednia wektora: " << srednia_z_wektora << std::endl;
// 	
// 	////////////////////////////////////////////
// 	// 5. 
// 	// Funkcja zwraca odchylenie standardowe liczb w wektorze.
// 	auto odchylenie_z_wektora = odchylenie(wektor);
// 	
// 	std::cout << "odchylenie wektora: " << odchylenie_z_wektora << std::endl;
// 	
// 	////////////////////////////////////////////
// 	// 6. 
// 	wypisz(wektor);
// 	// Funkcja przesuwa wartosci wektora o jedna komorke w prawo.
//	// Ostatnia wartosc trafia do komorki zerowej.
// 	rotacja_w_prawo(&wektor);
// 	wypisz(wektor);
// 	
// 	for (int i = 0; i < 2 * N; i++)
// 	{
// 		rotacja_w_prawo(&wektor);
// 		wypisz(wektor);
// 	}
	return 0;	
}
