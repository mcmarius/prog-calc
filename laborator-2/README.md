# Laboratorul 2

### ⚠ Puneți cât mai multe întrebări! Nu există întrebări greșite.
#### Semnalați orice fel de greșeli găsiți!

# Cuprins
## [Modificăm opțiunile compilatorului](#modificăm-opțiunile-compilatorului-1)
## [Programe discutate](#programe-discutate-1)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse)
## [Resurse recomandate](#resurse-recomandate-1)

## Modificăm opțiunile compilatorului

Ne dorim să scriem cod cât mai corect. Un prim pas în acest sens este să nu ignorăm mesajele de avertisment de la compilator.

Compilatorul nu ne va ajuta dacă nu îi cerem în mod explicit asta. Primul pas este să accesăm fereastra pentru setările compilatorului:

![Meniu -> Settings -> Compiler...](img/settings1.png)

Al doilea pas este să bifăm opțiunile dorite din rubrica `Warnings`: `-Wall`, `-Wextra` și `-pedantic`. Acel `-std=c99` este opțional.

![Compiler warning flags](img/settings2.png)

Pasul al treilea este să salvăm aceste setări apăsând butonul `OK`.

Ultimul pas, verificăm că opțiunile chiar sunt folosite. Aici nu ne interesează să executăm programul, ci doar să îl compilăm (⚙):

![Build (Ctrl+F9)](img/compile.png)

Dacă în zona de mesaje vă spune că nu e nimic de compilat și că `Target is up to date`:

![Target is up to date, nothing to be done](img/already.png)

Adăugați și ștergeți un spațiu ca să fie modificată sursa, apoi compilați din nou (⚙):

![Check Build Log for compiler flags set earlier](img/flags.png)

Verificați că vă apar `-Wall`, `-Wextra` și `-pedantic`; nu contează ordinea aici.

Mie îmi apare de două ori `-Wall` pentru că este setat și la nivel de proiect, și la nivel global (implicit pentru toate proiectele). Nu este ceva grav. Despre acel `-g` vom discuta mai târziu. Este folosit pentru depanare (debugging).

---
<details>
  <summary>Detalii despre standarde</summary>
  Puteți bifa și <code>-std=c99</code> din rubrica <code>General</code>, dacă nu folosiți Windows :smile: (încă nu este implementat). Din acest punct de vedere, mai sigur este <code>-std=c90</code> pentru cod cât mai portabil.
  Standardele C11 și C17 nu sunt implementate complet de multe compilatoare.
  <br><br>
  La laborator, vom încerca să folosim doar părțile din C99 care funcționează și pe Windows. Deși pare surprinzător, lucrurile stau astfel deoarece nu prea există cerere pentru îmbunătățirile aduse în noile standarde, din motive comerciale. Microsoft nu a considerat prioritară implementarea standardelor C mai noi de C90, concentrându-se pe implementarea standardelor de C++.
  <br><br>
  <details>
    <summary>Și mai multe detalii</summary>
    Le adaug numai dacă dorește cineva.
  </details>
</details>

## Programe discutate
[Înapoi la cuprins](#cuprins)

### [Instrucțiuni decizionale (iar)](#din-nou-if)
### [Sau, în unele situații, `switch`](#switch)
### [Instrucțiuni repetitive: `for`](#for)
### [Instrucțiuni repetitive: `while`](#while)
### [Instrucțiuni repetitive: `do`...`while`](#dowhile)
### [Operații pe biți](#operații-pe-biți-1)

### Din nou `if`



### `switch`
[Înapoi la programe](#programe-discutate)



### `for`
[Înapoi la programe](#programe-discutate)



### `while`
[Înapoi la programe](#programe-discutate)



### `do`...`while`
[Înapoi la programe](#programe-discutate)



### Operații pe biți
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

