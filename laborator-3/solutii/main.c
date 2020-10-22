/**
Anul universitar 2019-2020, actualizat 2020-2021
Programarea Calculatoarelor, anul I, semestrul 1
Laboratorul 3
Seria 15 (2019-2020), seria 16 (2020-2021)

Fișierul "Laborator 3_v2.pdf"
*/

#include <stdio.h>

#include "laborator3.h"

int main()
{
    problema1();
    //problema2();
    //problema3();
    //problema4();
    //problema5();
    //problema6();
    //problema7();
    //problema8();
    //ex();
    return 0;
}

void ex() {
    /*nr de biți de 1 din a*/
    int a, k;
    k = 0;
    scanf("%d", &a);
    while(a) {
        a = a & (a-1);
        k++;
    }
    printf("%d ", k);
}
