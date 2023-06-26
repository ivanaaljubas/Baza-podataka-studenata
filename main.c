#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

int main(void) {

    int uvjet = 1;

    char* datoteka = "studenti.bin";

    while (uvjet) {
        uvjet = izbornik(datoteka);
    }

    printf("Kraj programa");

    return 0;
}
