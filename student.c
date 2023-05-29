#define _CRT_SECURE_NO_WARNINGS
#include "student.h"
#include <stdio.h>
#include <string.h>

void unosStudenta(Student* studenti, int* brojStudenata) {      //4.
	if (*brojStudenata >= MAX_STUDENTS) {
		printf("Dostignut je maksimalan broj studenata.\n");
		return;
	}

	Student noviStudent;

	printf("Unesite ime: ");
	scanf("%s", noviStudent.ime);

	printf("Unesite prezime: ");
	scanf("%s", noviStudent.prezime);

	printf("Unesite mjesto stanovanja: ");
	scanf("%s", noviStudent.mjestoStanovanja);

	printf("Unesite prosjek: ");
	scanf("%f", &noviStudent.prosjek);

	studenti[*brojStudenata] = noviStudent;
	(*brojStudenata)++;

	printf("Student je uspjesno dodan.\n");
}

void ispisSvihStudenata(Student* studenti, int brojStudenata) {
	if (brojStudenata == 0) {
		printf("Nema dostupnih studenata.\n");
		return;
	}

	printf("Podaci svih studenata:\n");
	for (int i = 0; i < brojStudenata; i++) {
		Student student = studenti[i];
		printf("Ime: %s\n", student.ime);
		printf("Prezime: %s\n", student.prezime);
		printf("Mjesto stanovanja: %s\n", student.mjestoStanovanja);
		printf("Prosjek: %.2f\n", student.prosjek);
		printf("------------------------\n");
	}
}

void pretraziStudenta(Student* studenti, int brojStudenata, const char* prezime) {
	int pronaden = 0;
	for (int i = 0; i < brojStudenata; i++) {
		if (strcmp(studenti[i].prezime, prezime) == 0) {
			pronaden = 1;
			printf("Pronaden student:\n");
			printf("Ime: %s\n", studenti[i].ime);
			printf("Prezime: %s\n", studenti[i].prezime);
			printf("Mjesto stanovanja: %s\n", studenti[i].mjestoStanovanja);
			printf("Prosjek: %.2f\n", studenti[i].prosjek);
			printf("------------------------\n");
		}
	}

	if (!pronaden) {
		printf("Student s prezimenom '%s' nije pronaden.\n", prezime);
	}
}

void obrisiStudenta(Student* studenti, int* brojStudenata, const char* prezime) {
	int pronaden = 0;
	for (int i = 0; i < *brojStudenata; i++) {
		if (strcmp(studenti[i].prezime, prezime) == 0) {
			pronaden = 1;
			for (int j = i; j < *brojStudenata - 1; j++) {
				studenti[j] = studenti[j + 1];
			}
			(*brojStudenata)--;
			printf("Student s prezimenom '%s' je obrisan.\n", prezime);
			break;
		}
	}

	if (!pronaden) {
		printf("Student s prezimenom '%s' nije pronaden.\n", prezime);
	}
}

void spremiStudente(Student* studenti, int brojStudenata, const char* nazivDatoteke) {
	FILE* datoteka = fopen(nazivDatoteke, "w");
	if (datoteka == NULL) {
		printf("Greska pri otvaranju datoteke '%s'.\n", nazivDatoteke);
		return;
	}

	for (int i = 0; i < brojStudenata; i++) {
		fprintf(datoteka, "%s %s %s %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].mjestoStanovanja, studenti[i].prosjek);
	}

	fclose(datoteka);
	printf("Studenti su uspjesno spremljeni u datoteku '%s'.\n", nazivDatoteke);
}

void ucitajStudente(Student* studenti, int* brojStudenata, const char* nazivDatoteke) {
	FILE* datoteka = fopen(nazivDatoteke, "r+");
	if (datoteka == NULL) {
		printf("Greska pri otvaranju datoteke '%s'.\n", nazivDatoteke);
		return;
	}

	*brojStudenata = 0;
	while ((*brojStudenata < MAX_STUDENTS) && (fscanf(datoteka, "%s %s %s %f", studenti[*brojStudenata].ime, studenti[*brojStudenata].prezime, studenti[*brojStudenata].mjestoStanovanja, &studenti[*brojStudenata].prosjek) == 4)) {
		(*brojStudenata)++;
	}

	fclose(datoteka);
	printf("Studenti su uspjesno ucitani iz datoteke '%s'.\n", nazivDatoteke);
}

