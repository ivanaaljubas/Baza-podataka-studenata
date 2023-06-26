#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

static int brojStudenata = 0;

int main() {

	int opcijaBroj;
	char opcija[3];
	int rezultat = 0;
	static STUDENT* polje = NULL;

	int priv_var = 0;

	printf("Dobrodosli u aplikaciju!\nOdabirom jednih od opcija uredite, dodajte ili saznajte vise studentima FERIT-a.\n");
	printf("Pritiskom na redni broj opcije odaberite istu.\n");
	printf("' 1 ' Dodaj studenta\n");
	printf("' 2 ' Uredi postojeceg studenta\n");
	printf("' 3 ' Ispis studenata\n");
	printf("' 4 ' Trazilica studenata\n");
	printf("' 5 ' Sortiraj studente po ocjeni\n");
	printf("' 6 ' Brisanje studenata\n");
	printf("' 7 ' Izlaz iz programa\n");

	do {
		scanf("%s", opcija);
		rezultat = strlen(opcija);
		if (rezultat > 1) {
			printf("Krivi unos");
		}

	} while (rezultat > 1);
	opcija[3] = malloc(sizeof(2));

	switch (opcija[0]) {
	case '1':
		ucitavanjeStudenata();
		if (brojStudenata == 0) {
			kreiranjeDat();
		}
		dodavanjeStudenata();
		break;

	case '2':
		azuriranje();
		break;

	case '3':
		if (polje != NULL) {
			free(polje);
			polje = NULL;
		}
		polje = (STUDENT*)ucitavanjeStudenata();
		ispisivanje(polje);
		break;
	case '4':
			izbornikSrch();
		break;

	case '5':
			izbornikSrt();
		break;

	case '6':
		if (polje == NULL)
			printf("Baza podataka prazna.");
		else
			brisanjeStudenata(polje);
		break;

	case '7':
		brisanjeBaze(polje);
		break;

	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
		break;

	}
	return 0;
}