# Laboratorul 7

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Pointeri la funcții](#programe-discutate)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Programe discutate

### [Sortarea cu `qsort`](#sortarea-cu-qsort-1)
### [Căutarea cu `bsearch`](#căutarea-cu-bsearch-1)
### [Despre pointerii la funcții](#despre-pointerii-la-funcții-1)
### [Recapitulare pentru test](#recapitulare-pentru-test-1)

### Sortarea cu [`qsort`](https://en.cppreference.com/w/c/algorithm/qsort)

Pentru a sorta un vector, fie implementăm noi sortarea, fie folosim o funcție de bibliotecă deja implementată care face asta pentru noi.

Programul de mai jos sortează descrescător un vector de numere folosind funcția `qsort` din `<stdlib.h>`: 
```c
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int A = *((const int*)a);
    int B = *((const int*)b);
    if(A < B) return 1;
    if(A > B) return -1;
    return 0;
}

void afis(int *v, int n)
{
    for(int i = 0; i < n; ++i)
        printf("%d ", v[i]);
    printf("\n");
}

int main(void)
{
    int v[] = {5, 3, 7, 3, 2, 8, 2, 0, 1, 9, -1, 4};
    int n = sizeof(v) / sizeof(v[0]);
    afis(v, n);
    qsort(v, n, sizeof(v[0]), cmp);
    afis(v, n);
    return 0;
}
```
Observații:
- funcția `qsort` are 4 parametri:
  - `v` este vectorul de numere pe care vrem să îl sortăm
  - `n` este numărul de elemente al vectorului `v`
  - al treilea argument este `sizeof`-ul unui element din vector: este necesar să specificăm acest lucru, deoarece `qsort` vede vectorul ca fiind de tip `void*`!
  - al patrulea argument este o funcție comparator, adică un **pointer la funcție**
    - altfel spus, este numele unei funcții, *fără paranteze*
    - de ce fără paranteze? dacă punem paranteze, înseamnă că *apelăm* funcția, dar cu ce argumente? 🤔
    - ... exact, nu are sens să o apelăm *noi*
    - numele oricărei funcții este automat un pointer la funcția respectivă
    - dacă nu înțelegeți ce se întâmplă, nu vă panicați 😌 aveți încredere: puneți numele funcției fără paranteze
- orice **funcție comparator** are următoarele proprietăți:
  - primește ca argumente doi pointeri `const void*`, să le spunem `a` și `b`
    - de ce? deoarece nu vrem să modificăm elementele atunci când le comparăm
    - desigur, nu e obligatoriu să facem cast la `const int*`, puteam folosi `int*` (dar nu e frumos...)
    - repet: **nu modificăm** elementele în funcția comparator
  - întoarce `int`:
    - un întreg negativ dacă `a` trebuie să fie înaintea lui `b` în vectorul sortat
    - un întreg pozitiv dacă `a` trebuie să fie după `b`
    - `0` dacă `a` este echivalent cu `b`
  - pentru două valori fixate, funcția trebuie să întoarcă **același** rezultat dacă este apelată de mai multe ori
- de ce să nu implementăm noi sortarea? pentru că ar trebui să fie mai simplu să folosim ceva gata făcut (dar nu dus la [extrem](https://devrant.com/rants/2477812/fucking-love-how-one-liner-packages-are-breaking-basically-the-entire-js-ecosyst))
- cu toate că funcția se numește `qsort`, standardul C nu obligă ca implementarea să folosească quick sort și, ce e și mai trist, nu garantează vreun nivel de complexitate (de exemplu `O(n logn)`; totuși, în general pare să fie o soluție mult mai eficientă decât o soluție scrisă de noi cu complexitate `O(n^2)` (2 `for`-uri)
- putem simplifica instrucțiunile de `return` din funcția comparator astfel: `return (A < B) - (A > B);`
  - nu vrem să facem scăderea direct `B - A`, deoarece există posibilitate de underflow/overflow
  - atenție la tipurile de date! `A` și `B` sunt întregi, nu pointeri către întregi: dacă folosim pointeri, posibil să avem nevoie de paranteze în plus pentru a nu scădea pointeri!

Sortarea unui vector de structuri după mai multe criterii:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    enum { AMAR, ACRU, SARAT, DULCE } gust;
    int calorii;
    char nume[16];
} Aliment;

int cmp_aliment(const void *a, const void *b)
{
    Aliment A = *((const Aliment*)a);
    Aliment B = *((const Aliment*)b);
    if(A.gust > B.gust)
        return -1;
    if(A.gust < B.gust)
        return 1;
    return strcmp(A.nume, B.nume);
}

const char* afis_gust(Aliment a)
{
    switch(a.gust)
    {
        case AMAR:  return "AMAR";
        case ACRU:  return "ACRU";
        case SARAT: return "SARAT";
        case DULCE: return "DULCE";
        default:    return "??";
    }
}

void afis(Aliment *v, int n)
{
    for(int i = 0; i < n; ++i)
        printf("%-15s gust %-6s %3d de calorii\n", v[i].nume, afis_gust(v[i]), v[i].calorii);
    printf("\n");
}

int main(void)
{
    Aliment v[] = {
        { .nume = "lamai",         .gust = ACRU,  .calorii = 100 },
        { .nume = "cirese amare",  .gust = AMAR,  .calorii = 200 },
        { .nume = "alune cu sare", .gust = SARAT, .calorii = 400 },
        { .nume = "portocale",     .gust = DULCE, .calorii =  90 },
        { .nume = "piersici",      .gust = DULCE, .calorii = 300 },
        { .nume = "lamai",         .gust = ACRU,  .calorii = 120 },
    };
    int n = 6;
    afis(v, n);
    qsort(v, n, sizeof(Aliment), cmp_aliment);
    afis(v, n);
    return 0;
}
```
Observații:
- nu este necesar să comparăm după toate câmpurile din structură: în exemplul de mai sus, am ignorat câmpul `calorii`
- la afișare, dacă știm lungimea maximă a ceea ce vrem să afișăm, putem să o specificăm în specificatorul de conversie
  - alternativ, putem să transmitem aceste lungimi ca parametri separați:
  - `printf("%*s gust %*s %*d de calorii\n", -15, v[i].nume, -6, afis_gust(v[i]), 3, v[i].calorii);`
  - putem calcula programatic aceste lungimi ca să nu fie nevoie să le hardcodăm
- nu am folosit `else if` în funcția comparator deoarece nu este necesar `else` dacă înainte avem `return`
- enumerarea din structură este anonimă, însă putem accesa din afara structurii câmpurile enumerării

Pentru a ordona doar o parte dintr-un vector (de structuri), putem proceda astfel:
```c
qsort(v, n/3, sizeof(Aliment), cmp_aliment);
qsort(v+n/2, n/2, sizeof(Aliment), alta_functie_comparator);
```
Observații:
- în prima situație, ordonăm doar prima parte a unui vector, specificând un număr mai mic de elemente
- în cea de-a doua situație, trebuie să avem grijă **să nu ieșim din vector**:
  - vectorul (de fapt pointerul) transmis la `qsort` începe de la jumătatea vectorului inițial
  - asta înseamnă că numărul de elemente nu poate fi mai mare de `n/2`
- atenție la rotunjiri! în exemplul de mai sus, s-a nimerit ca împărțirile să fie exacte
- nu am folosit `sizeof(v) / sizeof(v[0])`, deoarece dacă `v` este deja pointer, prin `sizeof(v)` am obține dimensiunea pointerului

### Căutarea cu [`bsearch`](https://en.cppreference.com/w/c/algorithm/bsearch)
[Înapoi la programe](#programe-discutate)

Pentru completitudine, menționez și funcția `bsearch`, tot din `<stdlib.h>`.

Vom completa primul program din secțiunea anterioară cu următoarele:
```c
void caut(int x, int *v, int n)
{
    int *rez = bsearch(&x, v, n, sizeof(int), cmp);
    if(rez)
        printf("Am gasit %d la adresa %p\n", x, (void*)rez);
    else
        printf("Nu am gasit %d!", x);
}
```
Iar în funcția `main`, **după sortare**:
```c
caut(2, v, n);
caut(6, v, n);
```
Observații:
- vectorul transmis funcției `bsearch` trebuie să fie sortat; în caz contrar, 💥
- funcția comparator trebuie să fie aceeași (sau echivalentă) cu cea cu care am sortat! nu este obligatoriu să sortăm cu `qsort`, însă criteriul de ordonare a elementelor trebuie să fie același; altfel, căutarea eficientă într-un vector sortat folosind un alt criteriu decât cel de la sortare nu are sens
- funcția întoarce un pointer către elementul găsit din vector sau `NULL` dacă elementul căutat nu a fost găsit
- la fel ca la `qsort`, cu toate că funcția se numește `bsearch`, nu este obligatoriu (conform standardului) ca implementarea să folosească un algoritm de căutare binară

### Despre pointerii la funcții
[Înapoi la programe](#programe-discutate)



### Recapitulare pentru test
[Înapoi la programe](#programe-discutate)



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
