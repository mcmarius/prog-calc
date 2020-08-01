# Laboratorul 5

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Împărțirea ecranului](#împărțirea-ecranului-1)
## [Programe discutate](#programe-discutate-1)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Împărțirea ecranului

## Programe discutate
[Înapoi la cuprins](#cuprins)

### [Directive de preprocesare](#directive-de-preprocesare-1)
### [Fișiere text](#fișiere-text-1)
### [Fișiere binare](#fișiere-binare-1)

### Directive de preprocesare
[Înapoi la programe](#programe-discutate-1)

Directivele de preprocesare care ne interesează sunt următoarele: [`#include`](#include), [`#define`](#define) și [compilarea condiționată](#compilare-condiționată).

#### `#include`

Această directivă este folosită pentru a copia conținutul fișierului dat ca parametru în fișierul curent.

Prima formă, cea cu paranteze ascuțite `<>`, va căuta în niște directoare predefinite, dependente de implementare, la care putem adăuga și noi alte directoare, folosind opțiunea `-Inume_director`.

Am compilat un fișier din linia de comandă cu `gcc -v main.c -Ilaborator-5` (remarcați rândul cu "laborator-5"):
```
ignoring duplicate directory "C:/Program Files/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/lib/gcc/../../lib/gcc/x86_64-w64-mingw32/8.1.0/include"
ignoring nonexistent directory "C:/mingw810/x86_64-810-win32-seh-rt_v6-rev0/mingw64C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/../../../../include"
ignoring duplicate directory "C:/Program Files/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/lib/gcc/../../lib/gcc/x86_64-w64-mingw32/8.1.0/include-fixed"
ignoring duplicate directory "C:/Program Files/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/lib/gcc/../../lib/gcc/x86_64-w64-mingw32/8.1.0/../../../../x86_64-w64-mingw32/include"
ignoring nonexistent directory "C:/mingw810/x86_64-810-win32-seh-rt_v6-rev0/mingw64/mingw/include"
#include "..." search starts here:
#include <...> search starts here:
 laborator-5
 C:/Program Files/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include
 C:/Program Files/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include-fixed
 C:/Program Files/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/../../../../x86_64-w64-mingw32/include
End of search list.
```
Din Code::Blocks, pașii sunt următorii:
1. Click dreapta pe numele proiectului
2. Selectăm `Build options...`
3. Selectăm tab-ul `Search directories`
4. Click pe butonul `Add`
5. Selectăm directorul care conține fișierele header de care avem nevoie
6. Ok, ok, repetăm pașii 4-6 până am adăugat toate directoarele necesare
7. Verificăm faptul că opțiunea este transmisă compilatorului: atunci când compilăm, verificăm ca în tab-ul `Build log` de jos să apară și opțiunea cu `-Inume_director`, unde `nume_director` este cel introdus la pasul 5.

Atenție! Acest proces selectează doar fișierele header, nu și implementarea! Pentru fișierele obiect corespunzătoare, dacă bibliotecile nu sunt de tip header-only, va trebui să ajutăm compilatorul să facă legăturile necesare, de exemplu prin opțiunea `-Lnume_director`, pe care le putem vedea în variabila `LIBRARY_PATH`. În plus, este posibil să fie necesară specificarea legăturilor cu opțiunea `-lnume_biblioteca` (L mic). Opțiunea `-L` doar îi spune linker-ului în ce directoare să caute fișierul obiect specificat cu opțiunea `-l`.

Pentru proiecte noi și complexe în C/C++ pentru care aveți nevoie de biblioteci externe, poate fi util [CMake](https://cmake.org/).

#### `#define`

[Această directivă](https://en.cppreference.com/w/c/preprocessor/replace) definește o constantă (cu valoare opțională) sau un macro de tip funcție.

În cazul constantelor, avantajele folosirii macro-urilor sunt:
- nu ocupă memorie în programul final
- pot fi "eliminate" cu `#undef` și eventual apoi redefinite
  - de exemplu, `true` este definit ca un macro, deoarece poate exista cod mai vechi care să definească această constantă în alt mod
- lipsa informației despre tip este atât un avantaj (putem obține cod mai generic), cât șî un dezavantaj, deoarece compilatorul nu ne poate ajuta
- pot fi folosite în instrucțiuni de tip `switch`
- putem declara vectori de lungime fixă:
  - dacă am folosi `const int n = 10; int v[n];`, atunci `v` ar fi un VLA, chiar dacă valoarea lui `n` este cunoscută la compilare

Ca dezavantaj care nu este precizat în curs:
- nu putem să le facem debugging cu debugger-ul, deoarece nu sunt generate simboluri de debugging
- [o alternativă](https://stackoverflow.com/questions/1674032/static-const-vs-define-vs-enum) este să folosim `enum` pentru astfel de constante, deși, în funcție de situație, `#define` are unele avantaje

O altă întrebuințare a macro-urilor este cea a verificării codului folosind [`assert`](https://en.cppreference.com/w/c/error/assert).

#### [Compilare condiționată](https://en.cppreference.com/w/c/preprocessor/conditional)

### Fișiere text
[Înapoi la programe](#programe-discutate-1)

### Fișiere binare
[Înapoi la programe](#programe-discutate-1)



## Exerciții
[Înapoi la cuprins](#cuprins)



## Întrebări, erori, diverse
[Înapoi la cuprins](#cuprins)

* 🚧

## Resurse recomandate
- [cppreference.com](https://en.cppreference.com/w/c)
- [StackOverflow](https://stackoverflow.com/questions/tagged/c?tab=Votes)
- [C FAQ](http://c-faq.com/questions.html)
- [C99 standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf) (doar să îl răsfoiți un pic)
