Laboratorium z programowania obiektowego
========================================

## Laboratorium 10: wątki i muteksy

### Wykład

#### Mutex (MUTual EXclusion)

Sekcja krytyczna (ang. *critical section*) to taki fragment programu,
w którym następuje dostęp do współdzielonego zasobu
(np. zmiennej, pliku, pamięci, bazy danych),
i który w danym momencie może być wykonywany tylko przez jeden wątek lub proces.

Gdyby wiele wątków spróbowało jednocześnie wykonać ten fragment kodu,
to mogłoby dojść do uszkodzenia danych, co w informatyce nazywamy wyścigiem
(ang. *race condition*).

Wyobraźmy sobie system bankowy. Masz konto z saldem 100 zł.
Dwa wątki próbują jednocześnie wpłacić pieniądze na to konto.

Sekcja krytyczna wygląda tak:

```cpp
// SEKCJA KRYTYCZNA
double stan_konta = konto.saldo(); // Krok 1: Odczytaj (100 zł)
stan_konta += wpłata;              // Krok 2: Dodaj
konto.setSaldo(stan_konta);        // Krok 3: Zapisz (50 zł)
```

Jeśli wątki wejdą do tej sekcji jednocześnie, może się stać coś takiego:

Wątek A odczytuje saldo: 100 zł.

Wątek B odczytuje saldo: 100 zł.

Wątek A dodaje 50 zł i zapisuje: 150 zł.

Wątek B dodaje 50 zł i zapisuje: 150 zł.

Efekt? Na konto wpłynęło łącznie 100 zł (dwa razy po 50 zł),
ale stan konta to 150 zł zamiast 200 zł.
Straciłeś pieniądze przez złą synchronizację.

Aby zapobiec takim sytuacjom, stosuje się wzajemne wykluczanie
(ang. *mutual exclusion* – w skrócie mutex).
Mutex działa jak klucz do toalety w Starbucksie: kto ma klucz,
ten wchodzi do środka (sekcji krytycznej) i zamyka za sobą drzwi.
Inni czekają w kolejce, aż ten ktoś wyjdzie i odda klucz.

W C++ zabezpiecza się sekcje krytyczne za pomocą
zmiennych typu `std::mutex` i `std::lock_guard`,
czyli strażnik.

```cpp
#include <mutex>

std::mutex mtx;

void wpłaćPieniądze() {
    // lock_guard automatycznie blokuje mutex przy utworzeniu
    // i zwalnia go, gdy blok się kończy
    std::lock_guard<std::mutex> blokada(mtx);
    // --- POCZĄTEK SEKCJI KRYTYCZNEJ ---
    double stan_konta = konto.saldo(); // Krok 1: Odczytaj
    stan_konta += wpłata;              // Krok 2: Dodaj
    konto.setSaldo(stan_konta);        // Krok 3: Zapisz
    // --- KONIEC SEKCJI KRYTYCZNEJ ---
}
```

#### Wątki

Program to zestaw instrukcji i danych w pliku, który jest oznaczony
jako wykonywalny.

Proces to środowisko, w którym program jest wykonywany.

Na podstawie jednego programu można zainicjować wiele współbieżnych procesów.

Wątki pozwalają procesowi robić wiele rzeczy jednocześnie.
Wątki działają wewnątrz procesu.

Uruchomienie nowego wątku zwykle trwa krócej niż uruchomienie nowego
procesu. O ile osobne procesy mogą się komunikować przez wspólne pliki, potoki,
kolejki komunikatów lub pamięć wspólną, o tyle osobne wątki mogą
korzystać z tych samych zmiennych, a to łatwiej zaprogramować.

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

Każdy proces zaczyna działać jako jeden wątek.
Każdy wątek może tworzyć wątki potomne.
Każdy wątek musi poczekać, aż jego wątki potomne się zakończą,
zanim sam się zakończy. Gdyby którykolwiek wątek się zakończył,
zanim zakończyły się jego wątki potomne, to proces
przerwałby się z błędem.

`std::thread` to klasa reprezentująca pojedyńczy wątek.
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
się zakończy.

```cpp
#include <iostream>
#include <thread>   // Obsługa wątków
#include <chrono>   // Pomiar czasu (uśpienia)

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
    std::thread wątek1(siekajWarzywa, "marchewki", 3);
    std::thread wątek2([]() {
        std::cout << "[Gotowanie] Nastawiam wodę\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "[Gotowanie] Woda się zagotowała :-)\n";
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
#include <chrono>   // Pomiar czasu

int main() {
    // Początek
    auto start = std::chrono::steady_clock::now();

    // Mierzymy czas działania tego fragmentu kodu
    for (int i = 0; i < 1'000'000'000; ++i) {  // Miliard
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

* Program ma utworzyć wektor liczb całkowitych `dane`.
  Niech liczba elementów wektora `dane` wynosi
  `ROZMIAR_WEKTORA = 200'000'000`, czyli dwieście milionów.
  Potem program ma wypełnić ten wektor
  losowymi liczbami całkowitymi z przedziału od 0 do 999.

* Wariant A: Program ma zsumować cały wektor `dane` od początku do końca 
  za pomocą jednej pętli, a potem
  wypisać wynik tego sumowania i to, ile milisekund zajęło to sumowanie.
  Proszę użyć funkcji `void sumuj_A(const vector<int>& dane, size_t początek, size_t koniec)`

* Wariant B:
  Program ma podzielić wektor `dane` na 8 fragmentów i utworzyć 8 wątków.
  Każdy wątek tego programu ma dodawać liczby w innym fragmencie
  do jednej, wspólnej zmiennej globalnej,
  a potem program ma wypisać obliczoną sumę liczb i czas pracy.
  Zmienna globalna **nie ma być zabezpieczona** muteksem.
  Proszę użyć funkcji `void sumuj_B(const vector<int>& dane, size_t początek, size_t koniec)`

* Wariant C:
  Program ma podzielić wektor `dane` na 8 fragmentów i utworzyć 8 wątków.
  Każdy wątek tego programu ma dodawać liczby w innym fragmencie do zmiennej lokalnej.
  Dopiero, gdy dany wątek skończy dodawać liczby z całego fragmentu,
  ma zablokować dla innych wątków dostęp do zmiennej globalnej,
  dodać swój wynik do tej zmiennej globalnej i skończyć działanie.
  Potem program ma wypisać obliczoną sumę liczb i czas pracy.
  Proszę użyć funkcji `void sumuj_C(const vector<int>& dane, size_t początek, size_t koniec)`

Proszę tak tworzyć wątki w wariantach B i C: 

```cpp
for (int i = 0; i < liczba_wątków; ++i) {
    wątki_B.push_back(std::thread(
        sumuj_B,
        std::ref(dane),
        ROZMIAR_WEKTORA * i / liczba_wątków,
        ROZMIAR_WEKTORA * (i + 1) / liczba_wątków));
}
```
Proszę najpierw nie wywoływać metody `join` na utworzonych wątkach.
Komputer się od tego nie zepsuje :-)
