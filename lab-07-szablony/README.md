Laboratorium z programowania obiektowego
========================================

## Zadanie 7: szablony

Napisać szablon klasy `Stos`.
Ten szablon ma mieć jeden parametr.
Ten parametr ma być typem elementów stosu.
Klasy stworzone z tego szablonu mają mieć następujące metody:
* (opcjonalnie: konstruktor bez argumentów)
* `push` z 1 argumentem — kładzie element na szczycie stosu
* `pop` bez argumentów — usuwa element ze szczytu stosu i zwraca go
* `isEmpty` bez argumentów, `const` - zwraca `true`/`false` jeśli stos
  jest pusty/nie jest pusty.

ALE NAJPIERW napisać w funkcji `main` testy tego szablonu:
```cpp
Stos<int> st1;
st1.push(4);
... // Wywołać każdą z trzech metod klasy Stos<int>
Stos<string> st2;
... // Wywołać każdą z trzech metod klasy Stos<string>
```