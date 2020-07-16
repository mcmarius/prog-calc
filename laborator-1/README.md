# Laboratorul 1

### ⚠ **Puneți cât mai multe întrebări! Nu există întrebări greșite.**

# Cuprins
## [Pregătirea mediului de lucru](#pregătirea-mediului-de-lucru-1)
## [Câteva programe simple](#câteva-programe-simple-1)
## [Exerciții](#exerciții-1)
## [Întrebări, erori și orice nu a fost acoperit deja](#întrebări-erori-diverse-1)

---

## Pregătirea mediului de lucru

Avem nevoie de un compilator pentru limbajul C și un editor de text. Puteți sări peste acest pas dacă aveți instalat Code::Blocks și vă funcționează un program de test și debugger-ul.

Pentru a simplifica procesul, este recomandat să instalați [Code::Blocks](http://www.codeblocks.org/downloads/26). Întrucât majoritatea dintre voi cel mai probabil folosiți sistemul de operare Windows, veți descărca executabilul cu numele `codeblocks-20.03mingw-setup.exe`, deoarece acesta include atât editorul de text, cât și compilatorul. Aveți câteva indicații în imaginile de mai jos; dați click pe imagini pentru a le vedea la rezoluție mai mare.

Dacă nu aveți drepturi de admin, descărcați `codeblocks-20.03mingw-nosetup.zip`. Creați un folder nou, apoi extrageți arhiva.

❕ *Dacă v-ați blocat sau aveți erori sau nu vă iese ceva, întrebați!*

![http://www.codeblocks.org/downloads/26](img/codeblocks-dl.png)

![](img/cb-dl.png)

Dacă folosiți Google Chrome, download-ul va apărea în bara de jos. La Firefox, e în dreapta sus:

![](img/ff-dl.png)

Ideal ar fi să selectați o instalare completă. Dacă nu aveți suficient spațiu pe calculator, găsim soluții alternative.

![](img/cb-install.png)

Dacă ați instalat Code::Blocks mai demult, probabil aveți versiunea pe 32 de biți. Puteți să lăsați și versiunea veche sau puteți să o dezinstalați.

---

🚧 De adăugat: Pas instalare compilator.

---

După ce s-a terminat de instalat, va trebui să alegeți compilatorul: dați click pe `GNU GCC Compiler` și faceți click pe `Set as default`, apoi `OK`:

![](img/compiler.png)

Când lansați Code::Blocks, folosiți fie shortcut-ul de pe Desktop, fie din meniu (mie, cel puțin, nu mi-a mers acel `CodeBlocks (Launcher)`):

![](img/launcher.png)

Dați click pe `Create a new project`. Pasul următor este opțional, dar vă va scuti de un click pe viitor 😀

---

💡 Pas opțional:

> Click dreapta pe `Console application`, apoi `Edit this script`:

![](img/edit-script.png)

La linia 14, modificăm `ConsoleLang <- 1` (pentru C++) în `ConsoleLang <- 0` (pentru C):

![](img/change-default.png)

Apoi salvăm apăsând `Ctrl`+`S` și închidem (click pe `x` din dreptul `wizard.script` sau `Ctrl`+`W`). Când am salvat, indicatorul galben din dreptul liniei modificate ar trebui să devină verde.

Acesta a fost pasul opțional.

---

Revenind la ce făceam înainte, creăm un nou proiect, dublu click pe `Console application` (sau click și apoi `Enter` sau `Go`). Pasul opțional va selecta automat limbajul C. Altfel, trebuie să selectați voi C în loc de C++ de fiecare dată când faceți un nou proiect.

❔ De ce? Pentru că vrem să fie folosit compilatorul de C și nu cel de C++.

![](img/language.png)

După ce terminați de creat proiectul, ar trebui să obțineți ceva asemănător cu ce vedeți mai jos.

Apăsăm acum pe butonul cu o rotiță și un buton verde de play sau tasta `F9` (sau `Meniu`->`Build`->`Build and run`) (⚙ compilează programul - adică transformă codul sursă de mai sus în cod mașină (0 și 1), ▶ execută programul compilat):

![](img/done-1-2.png)

Și ar trebui să obținem:

![](img/done-1-3.png)

Acesta a fost primul pas din laboratorul 1. Felicitări! ✔

---

## Câteva programe simple


---

## Exerciții


---

## Întrebări, erori, diverse:
* 🚧
