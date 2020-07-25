# Laboratorul 3

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Programe discutate](#programe-discutate-1)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Programe discutate

### Conversii

Conversiile de date sunt de două feluri: implicite și explicite.

#### [Conversii implicite](https://en.cppreference.com/w/c/language/conversion)

Acestea sunt realizate de compilator în mod automat, pe cât posibil **fără pierdere de informație**.

Tipuri de date întregi:
```c
char c      = 1;  // convertește întregul 1 la char cu posibila pierdere de informatie
short a     = 2;  // convertește întregul 1 la short cu posibila pierdere de informatie
int b       = 3;  // nu are loc conversie deoarece nu e nevoie
long c      = 4;  // tipul de date destinatie (long) este cel putin la fel de "incapator" ca int, deci nu are loc vreo schimbare
long long d = 5;  // la fel ca randul anterior
```

Ce conversii au loc aici?
```c
int f(short s, bool d)
{
    char c = s - d;
    return c;
}

// exemplu de apelare din main sau din alta functie:
long l = f('x', 4);
```
- la apelul funcției, fiecare argument este convertit la tipul de date al parametrilor formali: 'x' este convertit la `short`, 4 este convertit la `bool`
- în expresiile aritmetice, se face conversia la cel mai "mare" tip de date (mai multe detalii [aici](https://en.cppreference.com/w/c/language/conversion#Integer_promotions): este vorba de tipul de date cu rangul cel mai mare)
  - astfel, avem `short` - `bool`; întrucât aceste tipuri sunt mai mici ca rang decât `int`, expresia este convertită la `int`
  - după evaluarea expresiei, rezultatul de tip `int` se convertește la `char`, întrucât acesta e tipul de date al "destinației"
    - această conversie poate avea loc cu pierdere de informație!
- se mai face o conversie la `return`, deoarece funcția `f` "promite" că întoarce un `int`
- ultima conversie are loc pentru convertirea rezultatului primit de la funcție de tip `int` la tipul de date destinație `long`

Alte situații de luat în considerare:
- conversiile între tipuri de date întregi cu semn și întregi fără semn ("implementation-defined") de același rang sau de ranguri diferite
- operatorul modulo (`%`) are obligatoriu operanzi întregi
- au loc conversii implicite și la operațiile pe biți
- rotunjirile au loc *de obicei* către cea mai apropiată valoare care poate fi reprezentată de tipul către care se face conversia

Aflați mai multe detalii în [documentație](https://en.cppreference.com/w/c/language/conversion#Integer_conversions), deoarece sunt prea multe cazuri particulare pentru a le scrie și aici.

Conversii la/de la `bool` (mai corect este `_Bool`, dar presupunem că am inclus `<stdbool.h>`):
```c
int x = true;  // x devine 1
x = false;  // x devine 0
x = 0.5;    // x este 0

bool z;
z = 0.5;   // z este 1, adică true
z = 0.0;   // z este 0, adică false
z = NULL;  // z este 0
```
Așadar, orice nu este zero devine 1 pentru tipuri de date de tip `bool`. [Ca fapt divers](https://stackoverflow.com/questions/8014161/in-c-how-much-space-does-a-bool-boolean-take-up-is-it-1-bit-1-byte-or-someth), `sizeof(_Bool)` este cel puțin 1, dar `sizeof(true)` și `sizeof(false)` sunt egale cu `sizeof(int)`.

Excludem cazurile cu numere complexe, puteți citi despre ele în documentație. Conversiile cu numere reale au loc astfel:
- dacă un operand este `long double`, ceilalți operanzi sunt convertiți la `long double`
- altfel, dacă un operand este `double`, ceilalți operanzi sunt convertiți la `double`
- altfel, dacă un operand este `float`, ceilalți operanzi sunt convertiți la `float`
- constantele reale (de exemplu `1.0`) sunt implicit `double`
- dacă un operand este `NaN`, rezultatul este `NaN`
- `NaN` nu este egal cu `NaN`

#### [Conversii explicite](https://en.cppreference.com/w/c/language/cast)

Conversiile explicite se realizează cu ajutorul operatorului de conversie (cast) și sunt necesare în anumite situații.

Am văzut deja un prim exemplu atunci când am afișat un pointer în primul laborator: `printf("%p", (void*)&nr);`. În acest exemplu, operatorul de cast este `(void*)` și este aplicat asupra expresiei `&nr`. Conversia nu afectează `&nr`.

Un exemplu în care o conversie explicită produce modificări:
```c
int x = 5 * (short)1.5;  // x este 5, deoarece 1.5 este convertit la `short` și devine 1
x = 5 * 1.5; // x este 7
```

Observații:
- adunarea și înmulțirea (și celelalte operații matematice) sunt asociative de la stânga la dreapta
- dacă avem `a + b + c`, expresia va fi tratată ca `(a + b) + c`, iar `a`, `b` și `c` pot fi la rândul lor expresii
- `c` poate fi evaluată înaintea expresiei `a`
- cu toate acestea, conversiile au loc de la stânga la dreapta, ceea ce [poate cauza sau nu un overflow](https://stackoverflow.com/questions/31630953/the-order-of-multiplications):
  - `0 * INT_MAX * INT_MAX` întoarce 0 după cum e de așteptat
  - `INT_MAX * INT_MAX * 0` produce overflow, chiar dacă aparent întoarce tot 0 (primim și warning)
  - dacă avem `INT_MAX * (INT_MAX * 0)`, nu mai primim warning

### [Pointeri](https://en.cppreference.com/w/c/language/pointer)
[Înapoi la programe](#programe-discutate-1)

Pointerii sunt tipuri de date derivate care se pot referi la alte obiecte (variabile, funcții). Această referire se referă la adresa de memorie și se obține cu operatorul `&`. Obținerea "înapoi" a obiectului către care se face referire prin pointer se face cu operatorul de dereferențiere `*`.

Exemplu:
```c
#include <stdio.h>

void schimba(double *x)
{
    *x += 2.0;  // dereferențierea pointerului x
}

int main()
{
    double z = 1.0;
    printf("z este %.3f\n", z);
    schimba(&z);  // trimitem ca parametru adresa lui z, deoarece functia schimba primeste un double*, adica o adresa catre un double
    printf("z este %.3f\n", z);
    schimba(&z);
    schimba(&z);
    printf("z este %.3f\n", z);
    return 0;
}
```

Încă un exemplu:
```c
#include <stdio.h>

void schimba(double *x)
{
    *x += 2.0;
}

int main()
{
    double z = 1.0;
    double *adr;
    adr = &z;
    // sau
    // double z = 1.0, *adr;
    // adr = &z;
    // sau
    // double z = 1.0, *adr = &z;
    printf("z este %.3f\n", z);
    schimba(&z);
    printf("z este %.3f\n", z);
    schimba(adr);
    printf("z este %.3f\n", z);
    printf("*adr este %.3f\n", *adr);
    return 0;
}
```

Putem avea pointeri la pointeri (și tot așa):
```c
#include <stdio.h>

void schimba(double **x)
{
    **x += 2.0;
}

int main()
{
    double z = 1.0, *adr = &z;
    printf("z este %.3f\n", z);
    schimba(&adr);
    printf("z este %.3f\n", z);
    printf("*adr este %.3f\n", *adr);
    return 0;
}
```

Putem avea pointeri care nu arată către ceva anume și pointeri care arată către "nimic":
```c
#include <stdio.h>

int main()
{
    double *a;
    // if(a == NULL)   // si aici avem undefined behavior, accesam o variabila neinitializata!
    //    printf("a nu arata catre nimic\n");
    // else
    //    printf("a nu este initializat, dar este diferit de 0\n");
        // printf(" si contine intamplator valoarea %p", (void*)a);  // accesarea unei variabile neinitializate este comportament nedefinit!!!
    // dereferentierea unui pointer neinitializat este comportament nedefinit!!!
    // printf("*a poate fi %.3f\n", *a);

    a = NULL;
    // dereferentierea unui pointer NULL este comportament nedefinit!!!
    // printf("*a poate fi %.3f\n", *a);
    printf("Un pointer NULL are de obicei valoarea %p\n", (void*)a);
    return 0;
}
```
Observații:
- 💥 **Dereferențierea unui pointer neinițializat este comportament nedefinit!!!** 💥
- 💥 **Accesarea unei variabile neinițializate (pointer sau altceva) este comportament nedefinit!!!** 💥
- 💥 **Dereferențierea unui pointer `NULL` este comportament nedefinit!!!** 💥
- o variabilă neinițializată poate avea *orice* valoare, nu ne putem baza pe faptul că un pointer neinițializat este sau nu `NULL`
- un pointer de tip `void*` este convertit implicit la orice alt pointer
  - reciproca nu este adevărată, a se vedea `printf` cu `%p`
- `sizeof(int*)` nu este neapărat egal cu `sizeof(int)`
- pointerii către obiecte nu au neapărat același `sizeof` cu pointerii către funcții (despre pointeri la funcții vom vorbi prin laboratorul 8 sau 9)
- singurele garanții oferite de standardul C sunt: `sizeof(void*) == sizeof(char*)` și `sizeof(char) == 1`
- în situațiile întâlnite în facultate, pointerii către obiecte de tipuri diferite vor avea cel mai probabil același `sizeof`
  - ca particularizare pe Windows pe 64 de biți:
    - dacă aveți MinGW simplu, atunci `sizeof(void*) == 4`
    - dacă aveți mingw-w64, atunci `sizeof(void*) == 8`
  - sistemele de operare pe 32 de biți nu pot avea în mod normal mai mult de 4GB memorie RAM, deoarece `sizeof(void*) == 4` și 2^32 = 4.294.967.296 octeți

### Tablouri
[Înapoi la programe](#programe-discutate-1)



### Matrice
[Înapoi la programe](#programe-discutate-1)


<!--
Laboratorul 4:
### Structuri
### `typedef`
### Uniuni
### Câmpuri de biți
### Alocare dinamică

Laboratorul 5:
### Directive de preprocesare
### Fișiere text
### Fișiere binare

Laboratorul 6:
### Șiruri de caractere
### Generarea numerelor aleatoare

Laboratorul 7:
### Sortare cu qsort
### Căutare binară cu bsearch
### Recapitulare pentru test

// test 1

Laboratorul 8: // săpt 9
### Structuri autoreferite
### Funcții matematice

Laboratorul 9:
### Pointeri la funcții

Laboratorul 10:
### Recapitulare pentru test
sau
### Argumente din linia de comandă
### Variabile de mediu
### Funcții cu număr variabil de argumente

// test 2
-->

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
