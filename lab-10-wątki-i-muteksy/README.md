Laboratorium z programowania obiektowego
========================================

## Laboratorium 10: wątki i muteksy

### Wykład

#### Mutex (MUTual EXclusion)

Sekcja krytyczna (ang. *critical section*) to taki fragment programu,
w którym następuje dostęp do współdzielonego zasobu
(np. zmiennej, pliku, pamięci, bazy danych),
i który w danym momencie może być wykonywany tylko przez jeden wątek lub proces.

Jeśli dwa lub więcej wątków spróbowałoby jednocześnie wykonać ten fragment kodu.
to mogłoby dojść do uszkodzenia danych, co w informatyce nazywamy wyścigiem
(ang. *race condition*).

Wyobraźmy sobie system bankowy. Masz konto z saldem 100 zł.
Dwa wątki próbują jednocześnie wypłacić z niego pieniądze.

Sekcja krytyczna wygląda tak:

```cpp
// SEKCJA KRYTYCZNA
double stan_konta = konto.saldo(); // Krok 1: Odczytaj (100 zł)
stan_konta -= wypłata;             // Krok 2: Odejmij
konto.setSaldo(stan_konta);        // Krok 3: Zapisz (50 zł)
```

Jeśli wątki wejdą do tej sekcji jednocześnie, może się stać coś takiego:

Wątek A odczytuje saldo: 100 zł.

Wątek B odczytuje saldo: 100 zł.

Wątek A odejmuje 50 i zapisuje: 50 zł.

Wątek B odejmuje 50 i zapisuje: 50 zł.

Efekt? Z konta wypłacono łącznie 100 zł (dwa razy po 50),
ale stan konta to nadal 50 zł, zamiast 0 zł.
Bank właśnie stracił pieniądze przez złą synchronizację.

Aby zapobiec takim sytuacjom, stosuje się wzajemne wykluczanie
(ang. *mutual exclusion* – w skrócie mutex).
Mutex działa jak klucz do toalety w Starbucksie: kto ma klucz,
ten wchodzi do środka (sekcji krytycznej) i zamyka za sobą drzwi.
Inni muszą czekać w kolejce, aż ten ktoś wyjdzie i odda klucz.

W C++ zabezpiecza się sekcje krytyczne za pomocą
zmiennych typu std::mutex i std::lock_guard,
czyli strażnik.

```cpp
#include <mutex>

std::mutex mtx;

void wypłaćPieniądze() {
// lock_guard automatycznie blokuje mutex przy utworzeniu
// i zwalnia go, gdy pętla/funkcja się kończy
    std::lock_guard<std::mutex> blokada(mtx);
    // --- POCZĄTEK SEKCJI KRYTYCZNEJ ---
    double stan_konta = konto.saldo(); // Krok 1: Odczytaj
    stan_konta -= wypłata;             // Krok 2: Odejmij
    konto.setSaldo(stan_konta);        // Krok 3: Zapisz
    // --- KONIEC SEKCJI KRYTYCZNEJ ---
}
```

#### Wątki

Program to zestaw instrukcji i danych w pliku, który jest oznaczony
jako wykonywalny

Proces to środowisko, w którym program jest wykonywany

Na podstawie jednego programu można zainicjować wiele współbieżnych procesów

Wątki pozwalają procesowi robić wiele rzeczy jednocześnie.
Wątki działają wewnątrz procesu

Uruchomienie nowego procesu zwykle trwa dłużej niż uruchomienie nowego
wątku. Osobne procesy mogą się komunikować przez wspólne pliki, potoki,
kolejki komunikatów lub pamięć wspólną. Osobne wątki mogą
korzystać z tych samych zmiennych programu, co łatwiej zaprogramować.

Przykłady użycia wątków:
- Program indeksujący zasoby Internetu może pobierać każdy plik
  w osobnym wątku.
- Edytor tekstu może mieć kilka wątków. Inny wątek
  odczytuje znaki wprowadzane z klawiatury,
  inny wątek wyświetla tekst na ekranie,
  jeszcze inny wątek sprawdza pisownię tekstu.

Gdy wątków w systemie jest więcej niż rdzeni w procesorze,
rdzenie często zmieniają wykonywane przez siebie wątki,
dzięki czemu użytkownikowi komputera wydaje się,
że wiele wątków działa jednocześnie.

`std::thread`: Klasa reprezentująca pojedyńczy wątek.
Aby uruchomić wątek, wystarczy utworzyć obiekt tej klasy
i przekazać mu do wykonania funkcję (lub wyrażenie lambda)
i jej argumenty.

UWAGA: Gdy chcemy przekazać argument do wątku
przez referencję (`&`), trzeba opakować ten argument funkcją `std::ref()`,
np. `std::thread t(funkcja, std::ref(mojaZmienna));`, bo szablon klasy
`std::thread` kopiuje argumenty.

`join`: Metoda klasy `std::thread`. Gdy wątek-rodzic wywołuje
tę metodę na obiekcie klasy `std::thread`, który reprezentuje
jego wątek potomny, wątek-rodzic czeka, aż ten wątek potomny
zakończy swoje działanie. Gdy wątek-rodzic nie wywoła `join`
lub `detach` przed usunięciem obiektu wątku potomnego,
program zakończy działanie z błędem. Proszę spróbować,
komputer się od tego nie zepsuje :-)

```cpp
#include <iostream>
#include <thread>   // Główna biblioteka do obsługi wątków
#include <chrono>   // Potrzebna do odmierzania czasu (uśpienia)

void siekajWarzywa(const std::string& rodzajWarzywa, int ilosc) {
    for (int i = 1; i <= ilosc; ++i) {
        std::cout << "[Siekanie] Siekam " << rodzajWarzywa << " (" << i << "/" << ilosc << ")\n";
        // Symulacja czasu pracy - uśpienie wątku na 500 milisekund
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "[Siekanie] Warzywa posiekane :-)\n";
}

int main() {
    std::cout << "[Main] Zaczynamy przygotowanie obiadu.\n";
    std::thread watek1(siekajWarzywa, "marchewki", 3);
    std::thread wątek2([]() {
        std::cout << "[Gotowanie] Nastawiam wodę\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "[Gotowanie] Woda się zagotowała :-)\n"
    });
    wątek1.join();
    wątek2.join();
    std::cout << "[Main] Gotowe.\n";
}
```

#### Bonus: jak mierzyć czas w C++

Najlepszy, standardowy i najdokładniejszy sposób pomiaru czasu
w nowoczesnym C++ to użycie biblioteki `<chrono>`.

Zegar do pomiaru czasu wykonywania kodu to `std::chrono::steady_clock`.
Ten zegar nigdy się nie cofa, a inne zegary mogą się cofać.

Przykład:

```cpp
#include <iostream>
#include <chrono>   // Główna biblioteka do pomiaru czasu

int main() {
    // Początek
    auto start = std::chrono::steady_clock::now();

    // Mierzymy czas działania tego fragmentu kodu
    for (int i = 0; i < 1'000'000'000; ++i) {
        // Pusta pętla for
    }

    // Koniec
    auto end = std::chrono::steady_clock::now();

    // Obliczamy, ile czasu minęło od początku do końca.
    // Możemy wybrać jednostkę: nanoseconds, microseconds, milliseconds, seconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Czas wykonania: " << duration.count() << " ms" << std::endl;
    return 0;
}
```

### Zadanie

Proszę napisać program, który ma robić rzeczy wymienione w tych 4 punktach:

* Program ma utworzyć globalną tablicę liczb całkowitych `dane`.
  Niech tablica `dane` ma
  `ROZMIAR_TABLICY = 200'1000'1000` elementów. Potem program ma wypełnić tę tablicę
  losowymi liczbami całkowitymi z przedziału od 0 do 999.

* Wariant A: Program ma zsumować całą tablicę `dane` od początku do końca 
  za pomocą jednej pętli, a potem
  wypisać wynik tego sumowania i to, ile milisekund zajęło to sumowanie.

* Wariant B:
  Program ma podzielić tablicę `dane` na 8 fragmentów i utworzyć 8 wątków.
  Każdy wątek tego programu ma dodawać liczby w innym fragmencie
  do jednej, wspólnej zmiennej globalnej,
  a potem program ma wypisać obliczoną sumę liczb i czas pracy.

* Wariant C:
  Program ma podzielić tablicę `dane` na 8 fragmentów i utworzyć 8 wątków.
  Każdy wątek tego programu ma dodawać liczby w innym fragmencie do zmiennej lokalnej.
  Dopiero, gdy dany wątek skończy dodawać liczby z całego fragmentu,
  ma zablokować dla innych wątków dostęp do zmiennej globalnej,
  dodać swój wynik do tej zmiennej globalnej i skończyć działanie.
  Potem program ma wypisać obliczoną sumę liczb i czas pracy.

W wariantach B i C proszę tak tworzyć wątki: 

```cpp
for (int i = 0; i < liczba_wątków; ++i) {
    wątki_B.push_back(std::thread(
        sumuj_wariant_B,
        std::ref(dane),
        ROZMIAR_TABLICY * i / liczba_wątków,
        ROZMIAR_TABLICY * (i + 1) / liczba_wątków));
}
```