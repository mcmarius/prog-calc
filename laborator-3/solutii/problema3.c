#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
Se citesc x, y, două numere mari (fiecare având peste 20 de cifre).
Să se calculeze suma lor (folosind vectori).
    1. Numerele sunt naturale.
    2. Numerele sunt întregi.
*/

int charToInt(char a)
{
    if( a >= '0' && a <= '9')
        return a - '0';
    return 0;
}

void problema3()
{
    char numar1[30];
    char numar2[30];
    int rezultat[30];
    int lungimeNumar1, lungimeNumar2;
    int i, j, jStart, carry, semn1, semn2, lungimeMax, sum;
    printf("Primul numar: ");
    scanf("%29s", numar1);
    printf("\nAl doilea numar: ");
    scanf("%29s", numar2);

    semn1 = semn2 = 1;
    if(numar1[0] == '-')
    {
        semn1 = -1;
    }
    if(numar2[0] == '-')
    {
        semn2 = -1;
    }

    lungimeNumar1 = strlen(numar1);
    lungimeNumar2 = strlen(numar2);
    strrev(numar1);
    strrev(numar2);
    lungimeMax = lungimeNumar1;
    if(lungimeNumar1 < lungimeNumar2)
    {
        lungimeMax = lungimeNumar2;
    }

    carry = 0;
    for(i = 0; i < lungimeMax; i++)
    {
        if(lungimeNumar1 == lungimeNumar2 || (i < lungimeNumar1 && i < lungimeNumar2))
        {
            sum = carry + charToInt(numar1[i]) * semn1 + charToInt(numar2[i]) * semn2;
        }
        else if(i >= lungimeNumar1)
        {
            sum = carry + charToInt(numar2[i]) * semn2;
        }
        else if(i >= lungimeNumar2)
        {
            sum = carry + charToInt(numar1[i]) * semn1;
        }
        rezultat[i] = abs(sum % 10);
        carry = sum / 10;
    }
    if(carry > 0)
    {
        rezultat[i] = carry;
        i++;
    }

    printf("\nRezultat: ");
    jStart = 0;
    if(rezultat[i - 1] == 0)
    {
        printf("-");
        jStart = 1;
    }

    for(j = jStart; j < i; j++)
    {
        printf("%d", rezultat[i - j - 1]);
    }
}

/**
Explicații (prof Andrei Pătrașcu)

Am făcut o funcție ce convertește un char la int. Cifrele se află între 48 și 57 în codul ASCII. Dacă
iterăm prin aceste valori și convertim valoarea numerică a lui i în caracter, putem găsi cifra
reprezentată în variabila a și să returnăm valoarea acesteia ca fiind i-48.

Codul este deceptiv de simplu. Ținem cele două numere în 2 vectori de caractere. Le inversăm
pozițiile incă de la început (gândiți-vă la modul în care le citim). Le luăm lungimile și apoi luăm
lungimea maximă pentru a itera până la valoarea acesteia. Cât timp iteratorul i este mai mic decât
ambele lungimi, facem adunările corespunzătoare, altfel doar copiem valoarea din numărul 1 sau
numărul 2 în rezultat. La final păstrăm într-o variabilă carry excesul de la această adunare, pentru a
fi utilizat la urmatoarea iterație.

Trebuie să mai punem încă o dată adunarea excesului după acest for, apoi doar afișăm vectorul
rezultat, dar în mod invers pentru că am inversat la început, înainte să facem suma.
*/
