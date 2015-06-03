# Techniki Kompilacji - Projekt - Interpreter języka skryptowego z wbudowanym typem macierzy
Projekt wykonany w ramach przedmiotu TKOM (Techniki Kompilacji) w semestrze 2015L (5 semestr), na kierunku Informatyka, specjalizacji Inżynieria Systemów Informacyjnych (ISI) na Wydziale Elektroniki i Technik Informacyjnych (EiTI) Politechniki Warszawskiej.

**Prowadzący projekt**: dr Piotr Gawkowski  
**Ocena**: 25/25

### Opis projektu
Ideą projektu jest stworzenie interpretera prostego języka skryptowego, wyposażonego w 
podstawowe instrukcje sterujące (instrukcja warunkowa i pętla), możliwość definiowania 
własnych funkcji oraz wbudowany typ macierzowy.

_(Reszta dostępna w [dokumentacji końcowej](https://github.com/mdziekon/eiti-tkom-interpreter/raw/master/docs/final-documentation.pdf))_

Kompilacja i uruchomienie
---

### Wymagania
* Kompilator wspierający standard **C++11** (``clang`` / ``gcc``)
* Narzędzie **Scons** (``scons``)

### Instrukcja
* Kompilacja: ``scons``
* Uruchomienie: ``./build/run``

### Testowane na:
* ``Ubuntu 14.10`` + ``Clang 3.5.0-4ubuntu2``

TODO (w tym propozycje od prowadzącego projekt)
---

* [ ] **(Lexer)** Usprawnienie hashowania słów kluczowych (hashowanie podczas odczytu, własna funkcja hashująca)
* [ ] **(Lexer/Parser)** Buforowanie odczytanego znaku zamiast używania metody ``.rewind()``
* [ ] **(Parser)** Odczytywanie tokenu EOF w metodzie ``Parser::parse`` zamast ``Parser::parseFunction()``
* [ ] **(Parser)** Zastąpienie konstrukcji ``.accept() + if`` na ``.peek()`` (niepotrzebne podwójne sprawdzanie tokenów)
* [ ] **(SemCheck)** Wykrywanie instrukcji ``break`` / ``continue`` poza pętlami ``while``
* [ ] **(SemCheck)** Wykrywanie braku instrukcji ``return`` (lub niekompletny zestaw w przypadku instrukcji warunkowych)
* [ ] **(SemCheck)** Kontynuacja analizy po wykryciu błędu
* [ ] **(SemCheck/Executor)** Wyświetlanie linii w której wystąpił błąd
* [ ] **(SemCheck/Executor)** Refaktoryzacja kodu
