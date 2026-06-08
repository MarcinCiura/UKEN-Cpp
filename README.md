Laboratorium z programowania obiektowego
========================================

* Główny autor: Krzysztof Simiński

* Testy i poprawki: Marcin Ciura

Jak kompiluje się program w C++?
```
                funkcje.h
                void f();
                |      |
                |      |                        preprocesor
                |      |                        + definiuje i rozwija makra preprocesora #define
    main.cpp <--+      +---> funkcje.cpp        + wycina fragmenty kodu źródłowego #if #ifdef #ifndef #endif
    f();                     void f() {...}     + dołącza inne pliki do kodu źródłowego #include
    printf(...);                 |
        |                        |              kompilator
        |                        |              + analizuje kod źródłowy, gdy widzi błędy, to je zgłasza
        |                        |              + gdy kod źródłowy nie ma błędów, generuje z niego kod maszynowy
        |                        |
        V                        V
    Unix: main.o             funkcje.o                biblioteka funkcji - wiele plików .o/.obj sklejonych w 1 plik
    Windows: main.obj        funkcje.obj              libc.a            libc.so - biblioteki dynamiczne
    <<< f                    >>> f                    libc.lib          libc.dll
    <<< printf                   |                    >>> printf        >>> printf
    >>> main                     |                        |
        |                        V                        | linker (program łączący/konsolidujący)
        +------------------>  a.out  <--------------------+
                              main.exe                program wykonywalny

polecenie 'g++ main.cpp funkcje.cpp -o main.exe' albo 'cmake'
```
