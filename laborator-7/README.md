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
  - al treilea argument este `sizeof`-ul unui element din vector
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

Sortarea unui vector de structuri


### Căutarea cu `bsearch`
[Înapoi la programe](#programe-discutate)



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
