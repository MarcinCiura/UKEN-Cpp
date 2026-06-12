Laboratorium z programowania obiektowego
========================================

## Laboratorium 7: szablony

### Wykład

#### 1. Po co nam szablony?

W tradycyjnym programowaniu często napotykamy powtarzający się kod.
Wyobraźmy sobie prostą funkcję, która znajduje większą z dwóch wartości:

```cpp
int max(int a, int b) {
    return (a > b) ? a : b;
}
```

Gdybyśmy potrzebowali tej samej logiki dla typów
`double`, `float` czy `std::string`,
musielibyśmy przeciążać tę funkcję
i kopiować ten sam kod,
co jest niezgodne z jedną z podstawowych zasad programowania — zasadą DRY
(Don't Repeat Yourself, czyli Nie powtarzaj się).

**Szablony (templates)** rozwiązują ten problem.
Szablony pozwalają nam parametryzować kod typem danych.
Na tym polega **polimorfizm statyczny**.

#### 2. Szablony funkcji

Szablon funkcji to jeszcze nie jest gotowa funkcja.
To przepis, z którego kompilator wygeneruje odpowiedni kod.

##### Składnia i przykład

```cpp
template <typename T> T myMax(T a, T b) {
    return (a > b) ? a : b;
}
```

* `template <typename T>` – informuje kompilator, że definiujemy szablon.
* `T` to nazwa parametru typu (zamiast `typename` można napisać `class`, co działa tak samo).

##### Dedukcja typów

Kompilator C++ umie się domyślić na podstawie przekazanych argumentów, czym jest `T`:

```cpp
int main() {
    auto r1 = myMax(5, 10);        // Kompilator dedukuje, że T to int
    auto r2 = myMax(3.14, 2.71);   // Kompilator dedukuje, że T to double
    
    // Błąd kompilacji: myMax(5, 3.14) -> niejednoznaczność (int czy double?)
    // Rozwiązanie: jawne wskazanie typu
    auto r3 = myMax<double>(5, 3.14); 
}
```

#### 3. Szablony klas

Klasy możemy parametryzować podobnie jak funkcje.

#### 4. Parametry nietypowe

Szablony mogą przyjmować jako parametry nie tylko typy,
ale też **wartości** znane w czasie kompilacji,
np. liczby całkowite, wskaźniki, a od C++20 również niektóre typy obiektowe.

Przykładem jest `std::array` z biblioteki standardowej:

```cpp
template <typename T, std::size_t Size> class array {
private:
    T data[Size]; // Rozmiar tablicy musi być znany w czasie kompilacji
public:
    std::size_t size() const { return Size; }
};

int main() {
    std::array<int, 10> tablica; // Rezerwuje na stosie pamięć na 10 intów
}
```

#### 5. Specjalizacja szablonów

Czasem ogólny kod szablonu nie działa z konkretnym typem danych tak, jak chcemy.
Wtedy z pomocą przychodzi specjalizacja.

##### Specjalizacja pełna

Załóżmy, że chcemy, aby funkcja `myMax` z argumentami typu `const char*`
porównywała zawartość napisów, a nie ich adresy w pamięci:

```cpp
#include <cstring>

// Specjalizacja pełna (zwróć uwagę na puste <>)
template <> const char* myMax<const char*>(const char* a, const char* b) {
    return (std::strcmp(a, b) > 0) ? a : b;
}
```

##### Specjalizacja częściowa

Dostępna **tylko dla szablonów klas**. Pozwala zawęzić działanie szablonu
do pewnych typów, np. wszystkich wskaźników:

```cpp
template <typename T>
class SmartPointer { /* ... ogólna implementacja ... */ };

// Specjalizacja częściowa dla dowolnego wskaźnika T*
template <typename T>
class SmartPointer<T*> {
    // Specjalna logika radzenia sobie z surowymi wskaźnikami
};
```

#### 6. Jak działają szablony?

1. **Szablony bezpośrednio nie generują kodu binarnego.**
2. **Instancjacja:**
Gdy kompilator zobaczy wywołanie funkcji `myMax(5, 10)`,
wygeneruje w pamięci funkcję `int myMax(int, int)`.
3. **Problem podziału na pliki `.h` i `.cpp`:**
Ponieważ w momencie użycia szablonu kompilator musi znać pełną definicję tego szablonu,
żeby wygenerować kod dla danego typu,
**szablony w C++ zwykle umieszcza się w całości w plikach nagłówkowych**
(`.hpp` / `.h`).

#### 7. Współczesny C++: Koncepty (Concepts) – C++20

Największym problemem tradycyjnych szablonów
były długie i nieczytelne błędy kompilacji,
gdy podano zły typ danych.
C++20 wprowadza **koncepty**,
czyli mechanizm nakładania ograniczeń na parametry szablonów.

Zamiast pozwalać na podstawienie dowolnego `T`, możemy z góry określić warunki:

```cpp
#include <concepts>

// Ten szablon zadziała tylko dla tych typów, które mają operator porównania i są liczbami
template <typename T>
requires std::integral<T> || std::floating_point<T>
T square(T value) {
    return value * value;
}

// Skrócona składnia w C++20:
auto add(std::integral auto a, std::integral auto b) {
    return a + b;
}
```

Jeśli spróbujemy przekazać do `square` obiekt klasy `std::string`,
kompilator wypisze czytelny błąd: *"std::string nie spełnia konceptu std::integral"*.

### Zadanie

Proszę napisać szablon klasy `Stos`.
Ten szablon ma mieć jeden parametr.
Ten parametr ma być typem elementów stosu.
Klasy stworzone z tego szablonu mają mieć następujące metody:
* (opcjonalnie: konstruktor bez argumentów)
* `push` z 1 argumentem — kładzie element na szczycie stosu
* `pop` bez argumentów — usuwa element ze szczytu stosu i zwraca go
* `isEmpty` bez argumentów, `const` - zwraca `true`/`false` jeśli stos
  jest pusty/nie jest pusty.

ALE NAJPIERW proszę napisać w funkcji `main` testy tego szablonu:
```cpp
Stos<int> st1;
st1.push(4);
... // Wywołać każdą z trzech metod klasy Stos<int>
Stos<string> st2;
... // Wywołać każdą z trzech metod klasy Stos<string>
```