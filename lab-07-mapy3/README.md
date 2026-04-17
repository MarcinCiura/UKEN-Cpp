Są nazwiska, które można pisać na dwa sposoby, np.
* Jaskólski, Jaskulski
* Drohomski, Drochomski
* Jerzyk, Jeżyk

Oba elementy par ó/u, h/ch, rz/ż czytamy tak samo.

Cel dzisiejszych zajęć to znaleźć wszystkie nazwiska, które można zapisywać
na więcej niż 1 sposób, posortować je wg liczby sposobów zapisu malejąco i wypisać.

1. Google: nazwiska polskie site:gov.pl
2. Ściągnąć plik CSV (comma-separated values)
3. Można w nim poszukać nazwisk swoich i znajomych :-)
4. Otworzyć plik CSV w edytorze i pozamieniać na małe litery: Ą -> a, Ć -> c, Ę -> e, Ł -> l, Ń -> n, Ó -> o, Ś -> s, Ź -> x, Ż -> z
Chodzi o to, żeby odróżniać o kreskowane (małe o) od dużego O itp. Zapisać plik :-)

Sposób rozwiązania:
<!-- end list -->

* napisać test funkcji `string zamien(const string& s, const string& co, const string& naco)`
```
ASSERT_EQ(zamien("margaryna", "a", "aa"), "maargaarynaa");
ASSERT_EQ(zamien("margaryna", "a", ""), "mrgryn");
ASSERT_EQ(zamien("margaryna", "ar", "x"), "mxgxyna");
```
* napisać funkcję zamien, która przechodzi ten test
* napisać resztę programu :-) kluczowa struktura danych: `map<string, vector<string>>` odwzorowuje "kanoniczną" postać nazwiska na jego różne zapisy. "Kanoniczna" postać nazwiska, czyli klucz mapy:
```
knazwisko = zamien(nazwisko, "o", "u");
knazwisko = zamien(knazwisko, "rz", "z");
knazwisko = zamien(knazwisko, "ch", "h");
```
* do tej mapy wczytać wszystkie nazwiska (bez przecinków i bez liczności)
* wyciągnąć z tej mapy wartości, czyli wektory jako vector&lt;vector&lt;string>>
* posortować te wektory według malejącej kolejności ich długości
* wypisać te wektory, które mają długość > 1
KONIEC
