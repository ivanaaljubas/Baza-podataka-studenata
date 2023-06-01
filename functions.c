#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include "dataType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int brojStudenata = 0;                         // 1. 5.

void kreiranjeDatoteke(const char* ime) {             // 4.
	FILE* fp = fopen(ime, "rb");                      // 16.

	if (fp == NULL) {
		fp = fopen(ime, "wb");
		fwrite(&brojStudenata, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajStudenta(const char* ime) {
	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje studenta u datoteku studenti.bin"); // 19.
		exit(EXIT_FAILURE);
	}

	fread(&brojStudenata, sizeof(int), 1, fp);
	

	STUDENT temp = { 0 };
	temp.id = brojStudenata + 1;
	

	printf("Unesite ime studenta: ");
	scanf("%s", temp.ime);


	printf("Unesite prezime studenta: ");
	scanf("%s", temp.prezime);


	printf("Unesite mjesto stanovanja: ");
	scanf("%s", &temp.mjestoStanovanja);
	
	printf("Unesite prosjecnu ocijenu studenta: ");
	scanf("%lf", &temp.prosijecnaOcijena);
	
	fseek(fp, 0, SEEK_END);
	fwrite(&temp, sizeof(STUDENT), 1, fp);

	brojStudenata++;
	fseek(fp, 0, SEEK_SET);
	fwrite(&brojStudenata, sizeof(int), 1, fp);
	rewind(fp); // 17.

	fclose(fp);
}

void* ucitajStudenta(const char* ime) {
	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje studenta iz datoteke studenti.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojStudenata, sizeof(int), 1, fp);

	STUDENT* polje = malloc(brojStudenata * sizeof(STUDENT)); // 14.

	if (polje == NULL) {
		fclose(fp);
		fprintf(stderr, "Alokacija memorije za polje studenata: Not enough space\n");
		exit(EXIT_FAILURE);
	}

	fread(polje, sizeof(STUDENT), brojStudenata, fp);

	fclose(fp);

	return polje;
}

void ispisiSveStudente(const void* polje) {
	const STUDENT* studenti = (const STUDENT*)polje;

	printf("ID:", "Ime: ", "Prezime:", "Mjesto Stanovanja:", "Prosjecna Ocijena:");
	for (int i = 0; i < brojStudenata; i++) {
		printf("%-12d | %-20s | %-19s | %-8s | %.2lf \n", studenti[i].id, studenti[i].ime, studenti[i].prezime, studenti[i].mjestoStanovanja, studenti[i].prosijecnaOcijena);
	}
}

void pretraziStudenta() {
	if (brojStudenata == 0) {
		printf("Baza podataka je prazna.\n");
		return;
	}

	char prezime[MAX_NAME];
	printf("Unesite prezime studenta: ");
	scanf("%s", prezime);

	for (int i = 0; i < brojStudenata; i++) {
		struct Student student = brojStudenata[i];
		if (strcmp(student.prezime, prezime) == 0) {
			printf("Pronađen student:\n");
			printf("Ime: %s\n", student.ime);
			printf("Prezime: %s\n", student.prezime);
			printf("Mjesto stanovanja: %s\n", student.mjestoStanovanja);
			printf("Prosjek: %.2f\n", student.prosijekOcjena);
			return;
		}
	}

	printf("Student s prezimenom '%s' nije pronađen.\n", prezime);
}

void uredivanjePopisaStudenata(void* polje, const char* ime) {
	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Uredivanje studenata u datoteci studenti.bin");
		exit(EXIT_FAILURE);
	}

	STUDENT* studenti = (STUDENT*)polje;
	char trazeniStudent[25];
	printf("Unesite ime studenta za uredivanje: ");
	scanf("%24[^\n]", trazeniStudent);
	getchar();

	int pronadjen = 0;
	for (int i = 0; i < brojStudenata; i++) {
		if (strcmp(studenti[i].ime, trazeniStudent) == 0) {
			pronadjen = 1;

			printf("Unesite novo ime studenta: ");
			scanf("%[^\n]s", studenti[i].ime);

			printf("Unesite novo prezime studenta: ");
			scanf("%[^\n]s", studenti[i].prezime);

			printf("Unesite novo mjesto stanovanja studenta: ");
			scanf_s("%[^\n]s", &studenti[i].mjestoStanovanja);
			

			printf("Unesite novu ocijenu studenta: ");
			scanf_s("%[^\n]lf", &studenti[i].prosijecnaOcijena);
			

			fseek(fp, sizeof(int) + i * sizeof(STUDENT), SEEK_SET);
			fwrite(&studenti[i], sizeof(STUDENT), 1, fp);

			break;
		}
	}

	if (!pronadjen) {
		printf("Student '%s' nije pronadjen.\n", trazeniStudent);
	}

	fclose(fp);
}

void brisanjeStudenta(void* polje, const char* ime) {
	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Brisanje studenta iz datoteke studenti.bin");
		exit(EXIT_FAILURE);
	}

	STUDENT* studenti = (STUDENT*)polje;
	char trazeniStudent[25];
	printf("Unesite ime studenta za brisanje: ");
	scanf("%24[^\n]", trazeniStudent);
	getchar();

	int pronadjen = 0;
	for (int i = 0; i < brojStudenata; i++) {
		if (strcmp(studenti[i].prezime, trazeniStudent) == 0) {
			pronadjen = 1;

			for (int j = i; j < brojStudenata - 1; j++) {
				studenti[j] = studenti[j + 1];
			}

			brojStudenata--;
			fseek(fp, 0, SEEK_SET);
			fwrite(&brojStudenata, sizeof(int), 1, fp);

			fseek(fp, sizeof(int) + brojStudenata * sizeof(STUDENT), SEEK_SET); // 17.
			fwrite(NULL, sizeof(STUDENT), 1, fp);

			break;
		}
	}

	if (!pronadjen) {
		printf("Student '%s' nije pronadjen.\n", trazeniStudent);
	}

	fclose(fp);
}

void sortirajPoOcijeni(void* polje) {
	STUDENT* studenti = (STUDENT*)polje;

	for (int i = 0; i < brojStudenata - 1; i++) {
		for (int j = 0; j < brojStudenata - i - 1; j++) {
			if (studenti[j].prosijecnaOcijena > studenti[j + 1].prosijecnaOcijena) {
				STUDENT temp = studenti[j];
				studenti[j] = studenti[j + 1];
				studenti[j + 1] = temp;
			}
		}
	}
}

void ispisPoOcijeni(const void* polje) {
	const STUDENT* studenti = (const STUDENT*)polje;

	printf("ID", "Ime studenta", "Prezime", "Mjesto stanovanja", "Prosijecna ocijena");

	for (int i = 0; i < brojStudenata; i++) {
		printf("studenti[i].id, studenti[i].ime, studenti[i].prezime, studenti[i].mjestoStanovanja, studenti[i].prosijecnaOcijena");
	}
}

int izlazIzPrograma(void* polje) {
	STUDENT* studenti = (STUDENT*)polje;

	FILE* fp = fopen("studenti.bin", "rb+");

	if (fp == NULL) {
		perror("Brisanje studenata iz datoteke studenti.bin");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_SET);
	fwrite(&brojStudenata, sizeof(int), 1, fp);

	fwrite(studenti, sizeof(STUDENT), brojStudenata, fp);

	fclose(fp);

	free(studenti); 

	return 0;
}

int izbornik(const char* ime) {                    // 8. 
	int izbor;
	void* polje = NULL;

	kreiranjeDatoteke(ime);

	while (1) {
		printf("\n");
		printf("1. Dodaj studenta\n");
		printf("2. Ispisi sve studente\n");
		printf("3. Pretrazi studente\n");
		printf("4. Uredi podatke o studentima \n");
		printf("5. Izbrisi studenta\n");
		printf("6. Sortiraj studente po ocijeni\n");
		printf("7. Ispis studente sortirane po ocijeni\n");
		printf("8. Izlaz iz programa\n");
		printf("\n");
		printf("Unesite broj opcije: ");
		scanf("%d", &izbor);
		getchar();

		switch (izbor) {
		case 1:
			dodajStudenta(ime);
			break;
		case 2:
			polje = ucitajStudenta(ime);
			ispisiSveStudente(polje);
			free(polje);
			break;
		case 3:
			polje = ucitajStudenta(ime);
			pretraziStudente(polje);
			free(polje);
			break;
		case 4:
			polje = ucitajStudenta(ime);
			uredivanjePopisaStudenata(polje, ime);
			free(polje);
			break;
		case 5:
			polje = ucitajStudenta(ime);
			brisanjeStudenta(polje, ime);
			free(polje);
			break;
		case 6:
			polje = ucitajStudenta(ime);
			sortirajPoOcijeni(polje);
			printf("Studenti su sortirani po ocijeni.\n");
			polje = ucitajStudenta(ime);
			break;
		case 7:
			polje = ucitajStudenta(ime);
			ispisPoOcijeni(polje);
			free(polje);
			break;
		case 8:
			return izlazIzPrograma(polje);
		default:
			printf("Pogresan unos. Molimo unesite ponovno.\n");
			break;
		}
	}
}