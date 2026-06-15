Laboratorium z programowania obiektowego
========================================

## Laboratorium 5: Inteligentne wskaźniki

### Wykład

Tradycyjne zarządzanie pamięcią w C++ za pomocą operatorów `new`
i `delete` jest podatne na błędy. Najczęstsze z tych błędów to wycieki
pamięci (*memory leaks*) i odwołania do zwolnionych obszarów (*dangling
pointers*).

Inteligentne wskaźniki (dostępne w pliku nagłówkowym `<memory>`)
automatyzują proces zwalniania pamięci. Zasób jest zwalniany, gdy
inteligentny wskaźnik do tego zasobu kończy życie.

#### 1. Problemy ze zwykłymi wskaźnikami (*raw pointers*)

Spójrzmy na poniższy, klasyczny kod:

```cpp
void funkcja() {
    int* ptr = new int(10);
    // ... jakieś działania ...
    if (warunek) {
        return; // WYCIEK PAMIĘCI: delete zostało pominięte
    }
    delete ptr;
}

```

Jeśli program napotka sytuację wyjątkową lub wcześniejszy `return`,
pamięć przypisana do `ptr` nigdy nie zostanie zwolniona. Inteligentne
wskaźniki eliminują ten problem.

W C++ są cztery rodzaje inteligentnych wskaźników:
* `std::auto_ptr` – źle zaprojektowany, NIGDY NIE UŻYWAĆ!
* `std::unique_ptr`
* `std::shared_ptr`
* `std::weak_ptr` – do zadań specjalnych, nie omówię go.

#### 2. `std::unique_ptr` – wyłączna własność

`std::unique_ptr` reprezentuje **wyłączną własność** zasobu. W danym
momencie może istnieć tylko jeden wskaźnik zarządzający tym obiektem,
który reprezentuje zasób.

Kluczowe cechy `std::unique_ptr`:

* **Brak kopiowania:** Nie można przypisać jednego `unique_ptr` do drugiego.
* **Możliwość przenoszenia:** Można przekazać własność za pomocą `std::move`.
* **Wydajność:** Nie generuje żadnego narzutu pamięciowego ani czasowego
w porównaniu do surowego wskaźnika.

Przykład użycia:

```cpp
#include <iostream>
#include <memory>

struct Zasob {
    Zasob() { std::cout << "Zasób stworzony\n"; }
    ~Zasob() { std::cout << "Zasób usunięty\n"; }
};

int main() {
    // Tworzymy unique_ptr za pomocą zalecanej funkcji std::make_unique
    // Wywołujemy konstruktor typu Zasob bez argumentów
    std::unique_ptr<Zasob> ptr1 = std::make_unique<Zasob>();
    // BŁĄD KOMPILACJI: Kopiowanie std::unique_ptr jest zabronione
    // std::unique_ptr<Zasob> ptr2 = ptr1;
    // Przeniesienie własności. Wskaźnik ptr1 staje się pusty (nullptr)
    std::unique_ptr<Zasob> ptr2 = std::move(ptr1);
} // Tutaj kończy się ten blok, w którym zadeklarowaliśmy wskaźniki
// `ptr1` i `ptr2`, dlatego wywołują się destruktory obiektów `ptr1`
// i `ptr2`. Destruktor obiektu `ptr2` zwalnia pamięć wskazywaną przez
// wskaźnik `ptr2`.
```

#### 3. `std::shared_ptr` – Współdzielona własność

`std::shared_ptr` pozwala wielu wskaźnikom na zarządzanie **tym samym
zasobem**. Każdy obiekt typu `std::shared_ptr` posiada ukryty licznik
referencji (*reference counter*).

Kluczowe cechy `std::shared_ptr`:

* **Licznik referencji:** Każde skopiowanie wskaźnika zwiększa licznik
  o 1. Każde zniszczenie wskaźnika zmniejsza licznik o 1.
* **Automatyczne usuwanie:** Pamięć zostaje zwolniona dopiero wtedy,
  gdy licznik referencji spadnie do 0.
* **Narzut:** `shared_ptr` jest nieco wolniejszy od `unique_ptr`,
ponieważ operacje na liczniku referencji muszą być atomowe, czyli
bezpieczne także wtedy, gdy wiele wątków ma dostęp do wskaźnika.

Przykład użycia:

```cpp
#include <iostream>
#include <memory>

int main() {
    // Tworzymy shared_ptr za pomocą zalecanej funkcji std::make_shared
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::cout << "Licznik: " << ptr1.use_count() << "\n"; // Wynik: 1
    {
        std::shared_ptr<int> ptr2 = ptr1; // Kopiowanie jest dozwolone
        std::cout << "Licznik: " << ptr1.use_count() << "\n"; // Wynik: 2
    } // Kończy się ten blok, w którym zadeklarowaliśmy wskaźnik `ptr2`
    std::cout << "Licznik: " << ptr1.use_count() << "\n"; // Wynik: 1
} // Kończy się ten blok, w którym zadeklarowaliśmy wskaźnik `ptr1`,
// licznik referencji spada do 0, pamięć zostaje zwolniona.

```

Jeśli obiekt A zawiera `shared_ptr` na obiekt B, a obiekt B zawiera
`shared_ptr` na obiekt A, powstaje cykl. Licznik referencji nigdy nie
spadnie do zera, co spowoduje wyciek pamięci. Rozwiązanie to
zastąpienie przynajmniej jednego z tych wskaźników przez `weak_ptr`.

#### 4. Podsumowanie

Warto używać `std::unique_ptr`, gdy obiekt ma jednego, dobrze określonego
właściciela.

Warto używać `std::shared_ptr`, gdy zasób jest współdzielony przez wiele
obiektów i trudno określić, który z tych obiektów zginie ostatni.

**Złota zasada nowoczesnego C++:** Unikaj używania słowa kluczowego
    `new` oraz `delete`. Twórz wskaźniki za pomocą funkcji
    `std::make_unique` oraz `std::make_shared`.