# Laboratorul 6

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Șiruri de caractere](#programe-discutate)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Programe discutate

### [Localizare](#localizare-1)
### [Caractere mici și mari](#caractere-mici-și-mari-1)
### [Clasificarea caracterelor](#clasificarea-caracterelor-1)
### [Despre spații](#despre-spații-1)
### [Conversii](#conversii-1)
### [Modificări](#modificări-1)
### [Examinări](#examinări-1)
### [Unicode și altele](#diverse)

### Localizare

[Localizarea](https://en.wikipedia.org/wiki/Locale_(computer_software)) reprezintă niște parametri care determină comportamentul pentru foarte multe dintre funcțiile de prelucrare a șirurilor de caractere. Concret, aceasta se referă, printre altele, la:
- traducerea unor mesaje într-o anumită limbă
- modul de ordonare al caracterelor ([collation](https://en.wikipedia.org/wiki/Collation))
- formatul în care sunt afișate datele calendaristice
- alegerea separatorului zecimal (punct sau virgulă)

În limbajul C, funcția pentru a afla și a seta localizarea este [`setlocale`](https://en.cppreference.com/w/c/locale/setlocale):
- primul argument este un macro pentru categoria de localizare; pentru toate categoriile, folosim `LC_ALL`
- al doilea argument este șirul de caractere pentru localizare
  - acesta conține limba și/sau setul de caractere/codificarea (depinde de sistemul de operare, compilator, mediu)
  - `NULL` întoarce localizarea curentă fără a modifica nimic
  - `""` întoarce localizarea implicită a sistemului
- întoarce localizarea curentă sub forma unui șir de caractere: cea existentă, cea setată sau `NULL` în caz de eroare
  - nu avem voie să modificăm șirul de caractere primit! 💥
  - putem să folosim șirul de caractere primit ca parametru pentru un apel ulterior la `setlocale`, de exemplu pentru a seta la loc valoarea inițială
- o problemă pe care o au funcțiile de localizare din limbajul C o reprezintă utilizarea unei stări globale!
  - astfel, sunt foarte dificil de scris și utilizat programe care doresc să folosească mai multe localizări, mai ales în programe care folosesc multiple fire de execuție (multi-threading)
  - deși probabil nu veți avea de-a face cu localizare în limbajul C, este bine să cunoașteți aceste aspecte, deoarece ele sunt valabile într-o oarecare măsură în multe alte contexte

Localizarea implicită a programului este `"C"` și reprezintă o localizare minimală. De obicei, caracterele sunt codificate cu coduri ASCII, iar în aceste situații, valorile 0-127 sunt aceleași în toate programele. Nu ne putem baza pe ce reprezintă valorile 128-255.

Categoriile de localizare:
- `LC_COLLATE` determină ordinea caracterelor: în codificarea implicită (`"C"`), ordinea este determinată de codurile ASCII
  - astfel, `a` este mai "mare" decât `A` în localizarea `"C"`, însă poate fi mai "mic" din punctul de vedere al omului
  - acest aspect este foarte relevant, deoarece puteți obține rezultate neintuitive atunci când aveți de ordonat diverse date
  - detalii în secțiunea următoare
- `LC_CTYPE` determină modul de clasificare al caracterelor: vedeți următoarele 3 secțiuni din laborator
- `LC_MONETARY` determină șirul de caractere afișat ca monedă
- `LC_NUMERIC` determină caracterul folosit pentru separatorul zecimal
- `LC_TIME` determină modul de afișare a datei și timpului

```c
#include <stdio.h>
#include <locale.h>
#include <time.h>

void detalii_loc()
{
    struct lconv *loc = localeconv();

    printf("Simbol moneda: %s\n", loc->currency_symbol);
    printf("Abreviere moneda: %s\n", loc->int_curr_symbol);
    printf("Separator zecimal: %s\n", loc->decimal_point);
    printf("Separator pentru mii: %s\n", loc->thousands_sep);

    time_t t = time(NULL);
    char buf[100];
    if(strftime(buf, sizeof(buf), "%A %c", localtime(&t)))
        printf("Timp local: %s\n", buf);
    else
        puts("Eroare afisare data/timp");
}

int main()
{
    printf("Localizarea initiala este %s\n", setlocale(LC_ALL, NULL));
    detalii_loc();

    printf("Localizarea implicita a sistemului este %s\n", setlocale(LC_ALL, ""));
    detalii_loc();

    puts(setlocale(LC_MONETARY, "American"));
    // sau "en_US.iso88591" in loc de "American"
    detalii_loc();

    puts(setlocale(LC_ALL, "Romanian"));
    //puts(setlocale(LC_ALL, "ro_RO.iso88592"));
    detalii_loc();
    return 0;
}
```
Observații:
- este dificil de obținut un cod portabil
- ca al doilea argument la `setlocale`, pentru codificări pe un singur byte avem:
  - pe sistemele Windows, codificările 125x (code pages): implicit, ar trebui să fie 1252; pentru română, avem 1250 (din terminal, `chcp 1250`); acestea corespund (oarecum) standardelor ISO/IEC 8859-1 și ISO/IEC 8859-2
  - pe sistemele Unix, ar trebui să transmitem limba și regiunea, urmată de `.` și de standardul ISO: vedeți comentariile
- în cazul UTF-8, ar trebui să putem folosi același șir de caractere indiferent de sistemul de operare
  - totuși, pe Windows, terminalul nu are fonturi disponibile pentru a afișa orice caractere din UTF-8
- trebuie să avem instalate localizările respective pentru ca programul să afișeze ceva în mod diferit
- am afișat ce întoarce `setlocale` pentru a verifica dacă argumentul al doilea este valid
- funcția `localeconv` ne întoarce o structură de tip `lconv`, cu ajutorul căreia putem folosi diverse elemente specifice unei localizări

### Caractere mici și mari

```c

```


### Clasificarea caracterelor
[Înapoi la programe](#programe-discutate-1)



### Despre spații
[Înapoi la programe](#programe-discutate-1)



### Conversii
[Înapoi la programe](#programe-discutate-1)



### Modificări
[Înapoi la programe](#programe-discutate-1)



### Examinări
[Înapoi la programe](#programe-discutate-1)



### Diverse
[Înapoi la programe](#programe-discutate-1)



## Exerciții
[Înapoi la cuprins](#cuprins)



## Întrebări, erori, diverse
[Înapoi la cuprins](#cuprins)

* 🚧

## Resurse recomandate
- **[un articol despre Unicode scris în 2003 de unul dintre cofondatorii StackOverflow](https://www.joelonsoftware.com/articles/Unicode.html)**
- [cppreference.com](https://en.cppreference.com/w/c)
- [StackOverflow](https://stackoverflow.com/questions/tagged/c?tab=Votes)
- [C FAQ](http://c-faq.com/questions.html)
- [C99 standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf) (doar să îl răsfoiți un pic)
