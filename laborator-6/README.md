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

În limbajul C, funcția pentru a afla și a seta localizarea este [`setlocale`](https://en.cppreference.com/w/c/locale/setlocale) (header-ul `<locale.h>`):
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

Localizarea implicită a programului este `"C"` și reprezintă o localizare minimală. De obicei, caracterele sunt codificate cu coduri ASCII, iar în aceste situații, caracterele corespunzătoare valorilor 0-127 ar trebui să fie aceleași în toate programele. Nu ne putem baza pe ce reprezintă valorile 128-255.

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
[Înapoi la programe](#programe-discutate)

Pentru a determina dacă un caracter single-byte este mic sau mare, putem folosi funcțiile `islower` și `isupper` (`<ctype.h>`). Parametrul trebuie să poată fi reprezentat ca un `unsigned char`. Valoarea returnată este zero dacă condiția nu este îndeplinită.

Cu localizarea `"C"`, numai `abcdefghijklmnopqrstuvwxyz` sunt considerate litere mici și numai `ABCDEFGHIJKLMNOPQRSTUVWXYZ` sunt considerate litere mari. Alte localizări pot defini și alte caractere ca fiind litere mici sau mari.

De exemplu, litera `ă` nu este nici literă mică, nici literă mare în localizarea `"C"`.
```c
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>
#include <locale.h>

void lower_upper(unsigned char c)
{
    printf("islower(%c) (%#x): %d\n", c, c, islower(c));
    printf("isupper(%c) (%#x): %d\n", c, c, isupper(c));
    unsigned char conv;
    if(islower(c))
        conv = toupper(c);
    else if(isupper(c))
        conv = tolower(c);
    else
        return;
    printf("islower(%c) (%#x): %d\n", conv, conv, islower(conv));
    printf("isupper(%c) (%#x): %d\n", conv, conv, isupper(conv));

    unsigned char conv2;
    if(islower(conv))
        conv2 = toupper(conv);
    else
        conv2 = tolower(conv);
    printf("conv_back(%c): %c\n", conv, conv2);
}

int main()
{
    unsigned char c = '\xc3';
    lower_upper(c);
    puts(setlocale(LC_ALL, "romanian_Romania.1250"));
    lower_upper(c);
    lower_upper('\xaa');
    wchar_t wc = L'î';
    wprintf(L"mic? %d\nmare? %d\nwupper: %c\nwlower: %c\n", iswlower(wc), iswupper(wc), towupper(wc), towlower(wc));
    return 0;
}

```
Observații:
- caracterul `'\xc3'` corespunde caracterului `'Ă'` în codificarea ISO 8859-2 sau Windows-1250
- caracterul `ă` (`'\xe3'`) poate fi introdus direct în codul sursă doar dacă salvăm fișierul cu encoding-ul ISO 8859-2 sau Windows-1250; implicit, salvarea fișierelor se face cu codificarea UTF-8! dacă folosiți un sistem de operare mai vechi, aceasta este posibil să fie ISO 8859-1 sau Windows-1252
  - trebuie să faceți distincția între codificarea fișierului sursă și codificarea utilizată în program
- în cazul în care nu era deja evident, în codificarea ASCII nu putem avea decât valori între 0 și 127
- dacă scriem caracterul `ă` direct în sursă și salvăm fișierul cu codificarea UTF-8, atunci acesta va fi reprezentat prin 2 bytes: `'\xc4'` și `'\x83'`; totuși, dacă facem asta, `'ă'` nu mai este un caracter pe un singur byte, ci este un caracter multi-byte
  - sesizați problema? 🤔
  - funcțiile `isupper`/`islower` primesc ca argument un `unsigned char`!
  - asta înseamnă că nu putem determina dacă un caracter este mic sau mare
  - în acest scop, există caractere multi-byte și șiruri de caractere "late"
  - `wprintf(L"%c", towupper(L'ă'));`
    - trebuie incluse headere speciale (`<wchar.h>`, eventual `<wctype.h>`)
    - `L` în fața unui caracter literal `char`/șir de caractere literal `char*` îl transformă în literal "lat"
    - acestea corespund codificărilor folosite mai demult (ex: UTF-16), mai ales pe Windows
    - nu funcționează cu `ș` și `ț`!
    - `'\xaa'` este `ș` cu sedilă!
- totuși, din experimentele mele, nu am reușit să obțin ceva suficient de util cu caracterele "late", întrucât funcțiile de citire și scriere din biblioteca C standard nu par să funcționeze corect cu MinGW, ceea ce le face cam inutile
- ele există mai mult din motive istorice
- soluția:
  - pentru operații simple, mai bine ne implementăm noi funcționalitățile de care avem nevoie
  - pentru operații complicate, căutăm biblioteci specializate
  - funcțiile din biblioteca C standard sunt **inutile** pentru situații în care nu vrem să ne limităm la ASCII, adică în orice situație practică, dar probabil nu vă veți lovi de aceste probleme în timpul facultății
  - excepție: inevitabil, avem nevoie în aplicații care au fost făcute mai demult cu aceste concepte oribile

Alte observații:
- în codificările pe un singur byte, **nu avem caracterele `ș` și `ț`**, deoarece indivizii de la Unicode (inainte de 1999) și cei de la ISO/IEC care s-au ocupat de standardizări au considerat că pot fi folosite caracterele cu sedilă `ş` și `ţ`; au presupus că diferența este insesizabilă pe ecrane cu rezoluție mică și că cei care furnizează fonturile ar trebui să facă afișările în mod diferit, ceea ce nu s-a întâmplat în realitate
- astfel, pentru a putea folosi caracterele `ș` și `ț` (și variantele lor `Ș` și `Ț`), ar trebui să folosim codificarea UTF-8

### Clasificarea caracterelor
[Înapoi la programe](#programe-discutate)

În header-ul `<ctype.h>` avem o multitudine de funcții pentru clasificarea caracterelor după diverse criterii. Am văzut două dintre acestea în secțiunea precedentă. Menționez încă o dată că localizarea influențează comportamentul acestor funcții. În contextul UTF-8, trebuie folosite funcții echivalente din biblioteci specializate.

```c
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

void afis_clasificare()
{
    for (int ndx=0; ndx<=255; ndx++)
    {
        printf("%c %d (0x%02x):\t", ndx, ndx, ndx);
        if(isalnum(ndx)) printf("alnum\t");
        if(isalpha(ndx)) printf("alpha\t");
        if(islower(ndx)) printf("lower\t");
        if(isupper(ndx)) printf("upper\t");
        if(isdigit(ndx)) printf("digit\t");
        if(isxdigit(ndx)) printf("xdigit\t");
        if(iscntrl(ndx)) printf("cntrl\t");
        if(isgraph(ndx)) printf("graph\t");
        if(isspace(ndx)) printf("space\t");
        if(isblank(ndx)) printf("blank\t");
        if(isprint(ndx)) printf("print\t");
        if(ispunct(ndx)) printf("punct");
        printf("\n");
    }
}

int main()
{
    afis_clasificare();
    puts(setlocale(LC_ALL, "romanian_Romania.1250"));
    afis_clasificare();
    return 0;
}
```
Observații:
- pentru codificarea ASCII (localizarea `"C"`), nu există caractere cu valori după 127, motiv pentru care nu se afișează nimic
- funcția `isblank` este introdusă în standardul C99
- puteți citi [documentația](https://en.cppreference.com/w/c/string/byte) atunci când aveți nevoie de ceva specific
- în mod curios, caracterul `µ` (`'\xb5'`) în localizarea de mai sus este și caracter alfabetic, și semn de punctuație
- tot în localizarea de mai sus, caracterul tab `'\t'` (`'\x09'`) este considerat caracter printabil, dar în localizarea `"C"` nu

### Despre spații
[Înapoi la programe](#programe-discutate)

Am menționat în secțiunea precedentă funcțiile din biblioteca C standard care ne pot ajuta să detectăm caractere albe (whitespace). Totuși, acestea funcționează doar pentru caractere ASCII! În Unicode, există mult mai multe caractere pentru spații: vedeți lista [aici](https://en.wikipedia.org/wiki/Whitespace_character#Unicode).

În mod neașteptat, funcția [`iswspace`](https://en.cppreference.com/w/c/string/wide/iswspace) pare să funcționeze corect. Cu toate acestea, există unele caractere "dubioase" care nu sunt considerate de Unicode ca fiind caractere albe, consecința fiind că nu sunt considerate spații nici de funcția `iswspace`. Probabil cel mai întâlnit astfel de caracter este [ZWJ (zero-width joiner)](https://en.wikipedia.org/wiki/Zero-width_joiner), utilizat pentru combinarea a două caractere pentru a le afișa în mod diferit.

Câteva utilizări:
- combinarea a două emoji-uri (emoji-urile pot fi considerate caractere pe 4 bytes)
- combinarea unor caractere în unele limbi
- trimiterea de mesaje goale
- formatarea tabelelor Markdown pe GitHub

Partea mai puțin fericită este că aceste caractere albe pot cauza multe dificultăți în validarea datelor. Nu trebuie să vă preocupe rezolvarea acestor probleme acum, ci doar să știți ce să căutați când veți avea nevoie de asta.

### Conversii
[Înapoi la programe](#programe-discutate)

<!-- https://stackoverflow.com/questions/22865622/atoi-vs-atol-vs-strtol-vs-strtoul-vs-sscanf -->

### Modificări
[Înapoi la programe](#programe-discutate)



### Examinări
[Înapoi la programe](#programe-discutate)

<!-- https://en.wikipedia.org/wiki/Collation https://en.cppreference.com/w/c/string/byte/strcoll -->

### Diverse
[Înapoi la programe](#programe-discutate)



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
