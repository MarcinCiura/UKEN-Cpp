Laboratorium z programowania obiektowego
========================================

## Laboratorium 10: wątki i procesy

### Wykład

#### Mutex (MUTual EXclusion)

Sekcja krytyczna (ang. critical section) to taki fragment programu,
w którym następuje dostęp do współdzielonego zasobu
(np. zmiennej, pliku, pamięci, bazy danych),
i który w danym momencie może być wykonywany tylko przez jeden wątek lub proces.

Jeśli dwa lub więcej wątków spróbowałoby jednocześnie wykonać ten fragment kodu.
to mogłoby dojść do uszkodzenia danych, co w informatyce nazywamy wyścigiem
(ang. race condition).

Wyobraźmy sobie system bankowy. Masz konto z saldem 100 zł.
Dwa wątki próbują jednocześnie wypłacić z niego pieniądze
(np. transakcja kartą i przelew automatyczny).

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
(ang. mutual exclusion – w skrócie mutex).
Mutex działa jak klucz do toalety w Starbucksie: kto ma klucz,
ten wchodzi do środka (sekcji krytycznej) i zamyka za sobą drzwi.
Inni muszą czekać w kolejce, aż ten ktoś wyjdzie i odda klucz.

W C++ zabezpiecza się sekcje krytyczne za pomocą
zmiennych typu std::mutex i std::lock_guard

```cpp
#include <mutex>

std::mutex mtx;

void wypłaćPieniądze() {
// lock_guard automatycznie blokuje mutex przy utworzeniu
// i zwalnia go, gdy pętla/funkcja się kończy (zasada RAII,
// czyli Resource Acquisition Is Initialization)
    std::lock_guard<std::mutex> blokada(mtx);
    // --- POCZĄTEK SEKCJI KRYTYCZNEJ ---
    double stan_konta = konto.saldo(); // Krok 1: Odczytaj (100 zł)
    stan_konta -= wypłata;             // Krok 2: Odejmij
    konto.setSaldo(stan_konta);        // Krok 3: Zapisz (50 zł)
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
wątku. Osobne procesy mogą się komunikować przez wspólne pliki, łącza
(potoki), kolejki komunikatów lub pamięć wspólną, a osobne wątki mogą
korzystać z tych samych zmiennych programu, co łatwiej zaprogramować.

Przykłady użycia wątków:
- robot indeksujący zasoby Internetu może pobierać każdy plik
  w osobnym wątku
- edytor tekstu może mieć kilka wątków, które odpowiadają za
  odczytywanie znaków wprowadzonych z klawiatury, wyświetlanie tekstu na
  ekranie, sprawdzanie pisowni

Jeśli wątków w systemie jest więcej niż rdzeni w procesorze,
rdzenie często zmieniają wykonywane przez siebie wątki,
dzięki czemu użytkownikowi komputera wydaje się,
że wiele wątków działa jednocześnie.

`std::thread`: Klasa reprezentująca pojedynczy wątek.
Aby uruchomić wątek, wystarczy utworzyć obiekt tej klasy
i przekazać mu do wykonania funkcję (lub wyrażenie lambda).

`join`: Metoda . Gdy wątek-rodzic wywołuje
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

UWAGA: Gdy chcemy przekazać do wątku
argument przez referencję (`&`), trzeba go jawnie opakować w `std::ref()`,
np. `std::thread t(funkcja, std::ref(mojaZmienna));`, bo szablon klasy
`std::thread` kopiuje argumenty.

#### Jak mierzyć czas w C++

Najlepszy, standardowy i najdokładniejszy sposób pomiaru czasu
w nowoczesnym C++ to użycie biblioteki `<chrono>`.

Zegar do pomiaru czasu wykonywania kodu to `std::chrono::steady_clock`.
Ten zegar nigdy się nie cofa, a inne zegary mogą się cofać.

Przykład:

```cpp
#include <iostream>
#include <chrono>   // Główna biblioteka do pomiaru czasu
#include <thread>   // Tylko do symulacji pracy (sleep_for)

int main() {
    // Początek
    auto start = std::chrono::steady_clock::now();

    // Mierzymy czas działania tego fragmentu kodu
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

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

Napisać program, który:

- utworzy globalną tablicę `200*1000*1000` liczb całkowitych.
  Proszę nazwać tę tablicę `dane`
- wypełni tablicę `dane` losowymi liczbami z zakresu 0-999
- zsumuje liczby w tablicy `dane` za pomocą funkcji
  `void sumuj_wariant_A(const std::vector<int>& dane, size_t start, size_t end)`
  z pojedynczą pętlą od `start` do `end-1`,
  a potem wypisze tę sumę i czas wykonywania tej pętli
- zsumuje liczby w tablicy `dane` w zmiennej globalnej za pomocą 8 wątków,
  a potem wypisze tę sumę i czas sumowania. Ta zmienna globalna
  nie ma być zabezpieczona muteksem. Każdy wątek ma wywoływać funkcję
  `void sumuj_wariant_B(const std::vector<int>& dane, size_t start, size_t end)`.
  Ta funkcja ma sumować liczby w tablicy `dane` od indeksu `start` do `end-1`.
- zsumuje liczby w tablicy `dane` w zmiennej globalnej za pomocą 8 wątków,
  a potem wypisze tę sumę i czas sumowania. Ta zmienna globalna
  **ma być zabezpieczona** muteksem. Każdy wątek ma wywoływać funkcję
  `void sumuj_wariant_C(const std::vector<int>& dane, size_t start, size_t end)`.
  Ta funkcja ma sumować liczby w tablicy `dane` od indeksu `start` do `end-1`.

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