Laboratorium z programowania obiektowego
========================================

## Zadanie 5: mapy

Proszę przeczytać ten plik README od początku do końca.

Ten plik README zawiera najpierw opis działania programu,
który wywołuje różne funkcje, a potem opis tego, jak testować
te funkcje i uruchomić ten program.

---------------------------------------

Program `main` kolejno:

1. Tworzy plik `studenci.txt` z losowymi danymi, na przykład taki:

```
Eryk    Klimek  903072088
Henryk  Wozniak 682759817
Henryk          Sobczak 229514245
Kornelia        Krol    295878274
```

2. Tworzy plik `oceny.txt` z losowymi danymi, na przykład taki:

```
295878274       mikroinformatyka        4.5     4       2
229514245       matematyka      4       3
903072088       filozofia       2       2       2.5
229514245       logika_rozmyta  4.5
```

3. Wczytuje  struktury typu `Student` z pliku `studenci.txt`
   W tych strukturach pole `oceny_z_przedmiotów` jest pustą mapą.

4. Wyznacza najpopularniejsze imię wśród studentów,
   a potem wypisuje je na wyjściu.

5. Wyznacza najpopularniejsze nazwisko wśród studentów,
   a potem wypisuje je na wyjściu wraz z częstością tego nazwiska.

Jeśli więcej niz jedno imię lub więcej niz jedno nazwisko
jest najbardziej popularne, to program wypisuje dowolne z tych
imion lub dowolne z tych nazwisk.

6. Wczytuje z pliku `oceny.txt` oceny studentów i dodaje je do pól
   `oceny_z_przedmiotów` struktur `Student` w mapie `studenci`.

7. Wypisuje dane studentów wraz z ich ocenami, na przykład:

```
Henryk Sobczak (229514245)
	logika_rozmyta	4.5
	matematyka	4 3
Kornelia Krol (295878274)
	mikroinformatyka	4.5 4 2
Henryk Wozniak (682759817)
Eryk Klimek (903072088)
	filozofia	2 2 2.5
```

8. Wypisuje, ilu studentów nie ma zadnej oceny.

---------------------------------------

W pliku `funkcje_test.cpp` jest 6 testów.

Proszę kolejno wykonywać te kroki:

1. wybrać jeden test z pliku `funkcje_test.cpp`

2. uzupełnić w pliku `funkcje.cpp` tę funkcję, której działanie
   jest testowane w tym teście

3. uruchomić testy - jeśli ktoś nie wie, jak uruchamiać testy,
   niech to głośno powie

4. jeśli test skończył się bez błędu - wrocić do kroku 1.

5. jeśli test skończył się z błędem - poprawić funkcję
   i wrocić do kroku 3.

Na koniec proszę uruchomić program `main`. Tadam :-) program działa.
