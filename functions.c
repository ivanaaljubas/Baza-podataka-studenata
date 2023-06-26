#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "functions.h"
#include <string.h>

static int brojStudenata = 0;
void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {

		fp = fopen(ime, "wb");
		fwrite(&brojStudenata, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajStudenta(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje studenta u datoteku studenti.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojStudenata, sizeof(int), 1, fp);
	printf("Broj studenata: %d\n\n", brojStudenata);

	STUDENT temp = { 0 };
	temp.id = brojStudenata + 1;
	getchar();

	printf("Unesite ime studenta: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime studenta: ");
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite godine studenta: ");
	scanf("%d", &temp.godine);
	getchar();

	printf("Unesite adresu studenta: ");
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite smjer studenta: ");
	scanf("%10[^\n]", temp.smjer);


	fseek(fp, sizeof(STUDENT) * brojStudenata, SEEK_CUR);
	fwrite(&temp, sizeof(STUDENT), 1, fp);
	printf("Novi student dodan.\n\n");

	rewind(fp);
	brojStudenata++;

	fwrite(&brojStudenata, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajStudente(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje studenata iz studenti.txt");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojStudenata, sizeof(int), 1, fp);
	printf("Broj studenata: %d\n", brojStudenata);

	STUDENT* poljeStudenata = (STUDENT*)calloc(brojStudenata, sizeof(STUDENT));

	if (poljeStudenata == NULL) {
		perror("Zauzimanje memorije za studente");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeStudenata, sizeof(STUDENT), brojStudenata, fp);

	fclose(fp);

	printf("Svi studenti uspjesno ucitani.\n\n");

	return poljeStudenata;
}

void ispisiSveStudente(const STUDENT* const polje) {

	if (polje == NULL) {
		printf("Polje studenata prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojStudenata; i++) {
		printf("Student broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nAdresa: %s\nSmjer: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->adresa,
			(polje + i)->smjer);
	}
}

STUDENT* pretraziStudente(STUDENT* const polje) {

	if (polje == NULL) {
		printf("Polje studenata prazno\n");
		return NULL;
	}

	int i;

	int trazeniId;

	printf("Unesite ID studenta kojeg trazite: \n");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojStudenata) {
			printf("Student s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojStudenata);

	for (i = 0; i < brojStudenata; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Student pronaden.\n");

			return (polje + i);
		}
	}

	return NULL;
}

void uredivanjeStudenata(STUDENT* polje, const char* const ime) {

	if (brojStudenata == 0) {
		printf("Polje studenata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Azuriranje studenata");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID studenta kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 0 || trazeniId > brojStudenata) {
			printf("Student s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 0 || trazeniId > brojStudenata);

	STUDENT temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime studenta (trenutno ime: %s): ", (polje + trazeniId - 1)->ime);
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime studenta (trenutno prezime: %s): ", (polje + trazeniId - 1)->prezime);
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite godine studenta (trenutne godine: %d): ", (polje + trazeniId - 1)->godine);
	scanf("%d", &temp.godine);
	getchar();

	printf("Unesite adresu studenta (trenutna adresa: %s): ", (polje + trazeniId - 1)->adresa);
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite smjer studenta (trenutni smjer: %s): ", (polje + trazeniId - 1)->smjer);
	scanf("%10[^\n]", temp.smjer);

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(STUDENT) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(STUDENT), 1, fp);

	printf("Student uspjesno azuriran.\n");

	fclose(fp);
}

void brisanjeStudenta(STUDENT* const polje, const char* const ime) {

	if (brojStudenata == 0) {
		printf("Polje studenata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Brisanje studenta");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID studenta kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojStudenata) {
			printf("Student s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojStudenata);

	STUDENT* pomocnoPolje = (STUDENT*)calloc(brojStudenata - 1, sizeof(STUDENT));

	if (polje == NULL) {
		perror("Neuspjelo dinamicko zauzimanje memorije");
		exit(EXIT_FAILURE);
	}

	int c = 0;

	for (i = 0; i < brojStudenata; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + c) = *(polje + i);

			if ((pomocnoPolje + c)->id > trazeniId) {
				(pomocnoPolje + c)->id -= 1;
			}

			fwrite((pomocnoPolje + c), sizeof(STUDENT), 1, fp);
			c++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&c, sizeof(int), 1, fp);
	fclose(fp);

	printf("Student je uspjesno obrisan\n");
}

void zamjena(STUDENT* const veci, STUDENT* const manji) {
	STUDENT temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortirajPoGodinama(const STUDENT* polje) {

	int min = -1;
	for (int i = 0; i < brojStudenata - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojStudenata; j++)
		{
			if ((polje + j)->godine < (polje + min)->godine) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisPoGodinama(const STUDENT* polje) {

	if (polje == NULL) {
		printf("Polje studenata prazno\n");
		return;
	}

	int i;

	polje = sortirajPoGodinama(polje);

	for (i = 0; i < brojStudenata; i++) {
		printf("Student broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nAdresa: %s\nSmjer: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->adresa,
			(polje + i)->smjer);
	}
}

int izlazIzPrograma(STUDENT* polje) {

	free(polje);

	return 0;
}
