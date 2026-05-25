#include <iostream>
#include <random>
#include <chrono>
#include <limits>

int main ()
{
	// TABLICE 
	
	std::default_random_engine silnik; // silnik do generowania liczb losowych
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count()); // ustawienie ziarna silnika z użyciem aktualnego czasu

	std::normal_distribution<double> rozklad {12.3, 2.0};

	const int N { 10000 };
	double liczby[N];

	// wypelnienie tablicy liczbami pseudolosowymi:
	for (int i = 0; i < N; i++)
		liczby[i] = rozklad(silnik);
	
	/* 0. Prosze wypisac liczby z tablicy liczby na ekran. */
	
	std::cout << "liczby:" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << liczby[i] << " ";
	}
	std::cout << std::endl;

	return 0;

	// Zadania na czworke.

	/* 1. Prosze znalezc wartosc maksymalna w tablicy liczb. */
	double maksimum;


	
	std::cout << "maksimum: " << maksimum <<  std::endl;

	/* 2. Prosze wyznaczyc srednia wartosci w tablicy. */
	double srednia;



	std::cout << "srednia: " << srednia <<  std::endl;

	/* 3. Prosze odwrocic wartosci w tablicy */



	std::cout << "odwrocone:" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << liczby[i] << " ";
	}
	std::cout << std::endl;

	/* 4. Prosze wyznaczyc liczbe elementow o wartosci mniejszej niz PROG. */
	double PROG {10};
	int ile {0};



	std::cout << "ponizej progu " << PROG << ": " << ile <<  std::endl;
	
	/* 5. Prosze wpisac do tablicy skumulowane wartosci z tablicy liczby. */
	
	double skumulowane[N];



	std::cout << "liczby" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << liczby[i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "skumulowane" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << skumulowane[i] << " ";
	}
	std::cout << std::endl;
	
	/* 6. Prosze wyznaczyc liczbe elementow tablicy skumulowane zanim wartosc elementu przekroczy PROG. */
	PROG = 30;
	int pod_progiem = 0;



	std::cout << "przed progiem " << PROG << ": ";
	std::cout << pod_progiem << std::endl;
	
	/* 7. Prosze wypisac roznice miedzy kolejnymi elementami tablicy liczby. */	



	/* 8. Prosze wypisac najwieksza roznice miedzy kolejnymi elementami tablicy liczby. */	
	
	maksimum = std::numeric_limits<double>::lowest(); // najnizsza mozliwa wartosc



	std::cout << "maksimum: " << maksimum << std::endl;
	
	/* 9. Prosze liniowo przeskalowac wartosci w tablicy w ten sposob, ze wartosc najmniejsza przyjmie wartosc zero, najwieksza zas jeden. */



	// wypisane tablicy po przeskalowaniu
	std::cout << "przeskalowane" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << liczby[i] << " ";
	}
	std::cout << std::endl;

	// Zadania na piatke.
	
	/* 10. Prosze wypelnic tablice licznik w nastepujacy sposob:
	 komorka 0 zawiera liczbe liczb z przedzialu [0.0, 0.1)
	 komorka 1 zawiera liczbe liczb z przedzialu [0.1, 0.2)
	 komorka 2 zawiera liczbe liczb z przedzialu [0.2, 0.3)
	 ...
	 komorka 9 zawiera liczbe liczb z przedzialu [0.9, 1.0]
	 */

	const int L {10};
	int licznik[L] = { };



	// wypisanie tablicy licznik
	for (int i = 0; i < L; i++) {
		std::cout << i << ": " << licznik[i] << std::endl;
	}

	/* 11. Prosze wypisac w pionie tablice licznik i przy kazdym wierszu wypisac liczbe gwiazdek proporcjonalna do wartosic w tablicy licznik. Najwieksza wartosc w tablicy licznik ma G gwiazdek. */

	const int G { 70 };



	return 0;
}
