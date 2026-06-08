Laboratorium z programowania obiektowego
========================================

## Laboratorium 9: dziedziczenie

### Wykład

Dziedziczenie to jeden z filarów
programowania obiektowego (OOP).
W dużym skrócie: dzięki dziedziczeniu nowa klasa
(klasa pochodna) przejmuje atrybuty i metody
istniejącej klasy (klasy bazowej).

Dzięki dziedziczeniu można osiągnąć kilka kluczowych korzyści:

1. Ponowne użycie kodu (Code Reusability)
   To najbardziej oczywista zaleta.
   Zamiast pisać ten sam kod wiele razy
   dla różnych, ale podobnych obiektów,
   umieszcza się wspólne atrybuty i metody
   w klasie bazowej.

   Przykład: Jeśli istnieje klasa `Pojazd` z metodami
   `uruchomSilnik()` i `zatrzymaj()`, to klasy
   `Samochod` i `Motocykl` będą miały te metody
   i nie będzie trzeba pisać tych metod wiele razy.

2. Polimorfizm (Wielopostaciowość)
   Dziedziczenie to fundament *polimorfizmu podtypowego*.
   Dzięki dziedziczeniu możemy traktować obiekty
   klas pochodnych tak samo, jak obiekty klasy bazowej.
   Dzięki dziedziczeniu możemy pisać bardziej uniwersalny kod.

   Przykład: Możesz stworzyć listę obiektów typu
   `Zwierzak` i wywołać na każdym z tych obiektów
   metodę `wydajDzwiek()`. Jeśli na tej liście znajdą się
   `Pies` i `Kot` (które dziedziczą po klasie `Zwierzak`),
   to pies zaszczeka, a kot zamiauczy –
   program sam wie, którą wersję metody wywołać.

3. Łatwiejsze utrzymanie i rozbudowa kodu (Maintainability)
   Jeśli logika działania jakiejś wspólnej funkcji
   się zmieni, to wystarczy poprawić tylko jedno miejsce – 
   klasę bazową. Ta zmiana będzie widoczna we wszystkich
   klasach potomnych. W ten sposób ryzyko popełnienia błędu
   jest mniejsze, a refaktoryzacja kodu łatwiejsza.

4. Nadpisywanie metod (Overriding)
   Pisząc klasę potomną, nie musimy kopiować wszystkiego
   z klasy bazowej. Możemy zmienić zachowanie konkretnej 
   metody, aby lepiej pasowało do specyfiki klasy pochodnej, 
   zachowując interfejs metody, czyli nazwę, listę argumentów
   i typ wyniku.

5. Tworzenie logicznych hierarchii (Modelowanie rzeczywistości)
   Dzięki dziedziczeniu możemy odwzorować w kodzie programu 
   relacje typu "jest czymś" (is-a) występujące w świecie
   rzeczywistym. Dzięki temu łatwiej jest wyobrazić sobie 
   strukturę i działanie tego programu.

   Przykład: `Pracownik` to `Osoba`. `Kierownik` to `Pracownik`.

⚠️ Ważna uwaga (Dobra praktyka):

Choć dziedziczenie ma wiele zalet,
współczesne inżynieria oprogramowania
zaleca ostrożność.
Nadmierne lub zbyt głębokie dziedziczenie
prowadzi do powstania sztywnego kodu (tzw.
*problem kruchej klasy bazowej*).
Dlatego często stosuje się zasadę
"Składanie klas ponad dziedziczeniem"
(*Composition over inheritance*),
czyli budowanie obiektów z mniejszych klocków
zamiast tworzenia długich drzew genealogicznych klas.

### Zadanie

Plik `figury.cpp` zawiera trzy klasy:

`Figura` <- `Trojkat` <- `TrojkatZPodpisem`

Proszę dodać w tym pliku dwie klasy:

* Klasę `Prostokat`, która dziedziczy z klasy `Figura`.
  Konstruktor klasy `Prostokat` ma przyjmować argumenty
  `szerokosc`, `wysokosc`, `przesuniecie` i `znak`.

* Klasę `ProstokatZPodpisem`, która dziedziczy z klasy `Figura`.
  Konstruktor klasy `ProstokatZPodpisem` ma przyjmować
  argumenty `szerokosc`, `wysokosc`, `przesuniecie`, `znak`
  i `podpis`.

Ponadto proszę dodać w tym pliku przykład użycia tych klas
w funkcji `main`.
