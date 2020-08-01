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
[Înapoi la directive](#directive-de-preprocesare-1)

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

O altă întrebuințare a macro-urilor este cea a verificării codului folosind [`assert`](https://en.cppreference.com/w/c/error/assert) din `<assert.h>`.

`assert` este un macro care primește ca parametru o expresie și oprește execuția programului dacă expresia este falsă, indicând numele fișierului și linia la care a fost încălcată aserțiunea (cu ajutorul macro-urilor `__FILE__` și `__LINE__`). Deoarece nu avem nevoie de aceste verificări atunci când considerăm programul gata, avem nevoie de un mecanism prin care să dezactivăm `assert`. Standardul C specifică definirea constantei `NDEBUG` înainte să includem `<assert.h>`.

Ca exemplu, vom scrie niște teste pentru problema următoare.

Se citeṣte un caracter de la tastatură. Să se verifice dacă este literă mare. Dacă da, să se transforme în literă mică ṣi să se afiṣeze. Altfel, să se rescrie caracterul tastat.

Implementarea o veți scrie voi, testele le-am scris eu:
```c
#include <stdio.h>
// #define NDEBUG
#include <assert.h>

char transforma_litera(char c)
{
    return c;
}

void verifica(char intrare)
{
    char rezultat = transforma_litera(intrare);

    switch(intrare)
    {
        case 'A':
            assert(rezultat == 'a');
            break;
        case 'Z':
            assert(rezultat == 'z');
            break;
        default:
            assert(rezulat == intrare);
            break;
    }    
}

void test_1()
{
    verifica('A');
    verifica('Z');
    verifica('a');
}

void problema_1()
{
    char c;
    scanf("%c", &c);
    printf("Rezultatul este %c.\n, transforma_litera(c));
}

int main()
{
    // teste
    test_1();
    // utilizarea functiei in mod normal
    // problema_1();
    return 0;
}
```
Observații:
- urmând această abordare, nu trebuie să pierdem timpul cu introdus datele de la tastatură atunci când testăm ce am implementat; vom trece la citirea de la tastatură numai la sfârșit, pentru câteva ultime verificări
- în modul prezentat mai sus, `assert` are două mari dezavantaje:
  - nu are un argument suplimentar pentru a afișa un mesaj
    - putem remedia acest lucru folosind o expresie de forma `assert(expresie && mesaj);`
    - totuși, implementarea macro-ului `assert` pe MinGW nu indică și numele funcției prin intermediul variabilei speciale `__func__`; eventual putem să ne definim noi un macro pentru aserțiuni care să includă și această informație
  - aserțiunile au loc la momentul execuției programului
    - după cum am tot menționat, C11 încă nu poate fi folosit cu succes; acesta include aserțiuni care au loc la momentul compilării, folosind cuvântul cheie [`_Static_assert`](https://en.cppreference.com/w/c/language/_Static_assert) sau macro-ul `static_assert` din `<assert.h>`
    - [există alternative în acest sens](https://stackoverflow.com/questions/174356/ways-to-assert-expressions-at-build-time-in-c), care folosesc construcții greșite atunci când condiția nu este îndeplinită: de exemplu, vectori de lungime negativă sau câmpuri de biți de lungime negativă, tocmai pentru a cauza erori la momentul compilării; dificultatea utilizării acestora constă în folosirea unor construcții care să furnizeze mesaje de eroare ușor de înțeles
- comentați linia din main cu `test_1()` și decomentați linia cu `problema_1()` pentru programul final
  - pentru programe mai mari, vom avea aceste funcții în fișiere separate, astfel încât putem evita cu totul includerea lor în executabilul final, deoarece codul de test nu va fi "link-uit"
  - desigur, pentru proiecte și mai mari, există biblioteci specializate

#### [Compilare condiționată](https://en.cppreference.com/w/c/preprocessor/conditional)
[Înapoi la directive](#directive-de-preprocesare-1)

[Aceste directive](https://en.cppreference.com/w/c/preprocessor/conditional) sunt utile pentru compilarea de cod specific pentru fiecare platformă în parte, cu scopul de a folosi apeluri de sistem care nu sunt disponibile prin biblioteca C standard.

De exemplu, pe Windows ar fi folosite apeluri din WinAPI, iar pentru restul lumii (\*nix-based) există apeluri din biblioteca C POSIX. Desigur, lucrurile pot fi mult mai variate.

Un alt [exemplu](https://stackoverflow.com/questions/1041866/what-is-the-effect-of-extern-c-in-c) este folosirea de cod scris în C, dar care poate fi compilat atât cu un compilator de C, cât și unul de C++:
- verificăm dacă există constanta `__cplusplus`
- adăugăm codul într-un bloc `extern "C" { /*restul codului*/ }`
- acești pași sunt necesari deoarece în C++ există supraîncărcare de funcții, dar în C nu
```c
#ifdef __cplusplus
extern "C" {
#endif

int f();

#ifdef __cplusplus
}
#endif
```

Un ultim exemplu are legătură cu secțiunea anterioară și folosește compilarea condiționată pentru a rula instrucțiuni de debugging sau nu:
```c
#ifdef NDEBUG
    #define assertm(expr, message) ((void)0)
#else
    #define assertm(expr, message) (
        printf("%s in function %s:\n", message, __func__), assert(expr)
    )
#endif // NDEBUG
```
Observații:
- `__func__` nu este un macro, ci o variabilă predefinită ca șir de caractere de tip `static const char[]` și conține numele funcției curente
- macro-ul nu conține `;` la sfârșit pentru ca atunci când folosim macro-ul, acesta să apară ca un apel de funcție; o altă variantă folosind o construcție (mai puțin intuitivă) găsiți [aici](https://stackoverflow.com/questions/154136/why-use-apparently-meaningless-do-while-and-if-else-statements-in-macros)
  - exemplu de apel: `assertm(medie == 10, "expected medie to be 10");`
- într-un mod similar, am putea construi un macro pentru a avea aserțiuni la compilare (însoțite de un mesaj), care să dispară dacă definim o anumită constantă (`NDEBUG`)

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
