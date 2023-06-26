#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "functions.h"

static int brojStudenata = 0;

int izbornik(const char* const ime) {

	printf("\t\t_____________________________________________\n\n");
	printf("\t\tOdaberite jednu od ponudenih opcija: \n\n");
	printf("\t\t_____________________________________________\n\n");

	printf("\t\tOpcija 1: Kreiranje datoteke\n");
	printf("\t\tOpcija 2: Dodavanje studenata\n");
	printf("\t\tOpcija 3: Ucitaj sve studente\n");
	printf("\t\tOpcija 4: Ispisi podatke o svim studentima\n");
	printf("\t\tOpcija 5: Pretrazivanje studenata po ID-u\n");
	printf("\t\tOpcija 6: Uredivanje popisa studenata\n");
	printf("\t\tOpcija 7: Brisanje studenata\n");
	printf("\t\tOpcija 8: Sortiranje po godinama\n");
	printf("\t\tOpcija 9: Izlaz iz programa\n\n");


	printf("\t\t_____________________________________________\n\n");

	int uvjet = 0;

	static STUDENT* poljeStudenata = NULL;
	static STUDENT* pronadeniStudent = NULL;

	scanf("%d", &uvjet);

	switch (uvjet) {
	case 1:
		kreiranjeDatoteke(ime);
		break;
	case 2:
		dodajStudenta(ime);
		break;
	case 3:
		if (poljeStudenata != NULL) {
			free(poljeStudenata);
			poljeStudenata = NULL;
		}

		poljeStudenata = (STUDENT*)ucitajStudente(ime);

		if (poljeStudenata == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 4:
		ispisiSveStudente(poljeStudenata);
		break;
	case 5:
		pronadeniStudent = (STUDENT*)pretraziStudente(poljeStudenata);

		if (pronadeniStudent != NULL) {
			printf("ID: %d\n", pronadeniStudent->id);
			printf("Ime: %s\n", pronadeniStudent->ime);
			printf("Prezime: %s\n", pronadeniStudent->prezime);
			printf("Godine: %d\n", pronadeniStudent->godine);
			printf("Adresa: %s\n", pronadeniStudent->adresa);
			printf("Smjer: %s\n", pronadeniStudent->smjer);
		}
		else {
			printf("Ne postoji clan s tim ID-em.\n");
		}

		break;
	case 6:
		if (poljeStudenata != NULL) {
			free(poljeStudenata);
			poljeStudenata = NULL;
		}

		poljeStudenata = (STUDENT*)ucitajStudente(ime);

		uredivanjeStudenata(poljeStudenata, ime);
		break;
	case 7:
		if (poljeStudenata != NULL) {
			free(poljeStudenata);
			poljeStudenata = NULL;
		}

		poljeStudenata = (STUDENT*)ucitajStudente(ime);

		brisanjeStudenta(poljeStudenata, ime);
		break;
	case 8:
		ispisPoGodinama(poljeStudenata);
		break;
	case 9:
		uvjet = izlazIzPrograma(poljeStudenata);
		break;
	default:
		uvjet = 0;
	}

	return uvjet;
}