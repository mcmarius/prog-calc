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

### Sortarea cu `qsort`

Pentru a sorta un vector, fie implementăm noi sortarea, fie folosim o funcție de bibliotecă deja implementată care face asta pentru noi:
```c
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int A = *((int*)a);
    int B = *((int*)b);
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
