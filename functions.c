#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

static int brojStudenata = 0, i, j, br = 0;

int izbornik() {

	int opcija = 0;
	static STUDENT* polje = NULL;

	printf("Dobrodosli u aplikaciju!\nOdabirom jednih od opcija uredite, dodajte ili saznajte vise studentima FERIT-a.\n");
	printf("Pritiskom na redni broj opcije odaberite istu.\n");
	printf("' 1 ' Dodaj studenta\n");
	printf("' 2 ' Uredi postojeceg studenta\n");
	printf("' 3 ' Ispis studenata\n");
	printf("' 4 ' Trazilica studenata\n");
	printf("' 5 ' Sortiraj studente po ocjeni\n");
	printf("' 6 ' Brisanje studenata\n");
	printf("' 7 ' Izlaz iz programa\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		ucitavanjeStudenata();
		if (brojStudenata == 0) {
			kreiranjeDat();
		}
		dodavanjeStudenata();
		break;
	case 2:
		azuriranje();
		break;
	case 3:
		if (polje != NULL) {
			free(polje);
			polje = NULL;
		}
		polje = (STUDENT*)ucitavanjeStudenata();
		ispisivanje(polje);
		break;
	case 4:
		while (opcija != 90) {
			opcija = izbornikSrch();
		}
		break;
	case 5:
		while (opcija != 89)
			opcija = izbornikSrt();
		break;
	case 6:
		if (polje == NULL)
			printf("Baza podataka prazna.");
		else
			brisanjeStudenata(polje);
		break;
	case 7:
		brisanjeBaze(polje);
		return 99;
		break;
	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

izbornikSrch() {
	int opcija = 0;
	STUDENT* polje = NULL;
	polje = (STUDENT*)ucitavanjeStudenata();
	printf("Pretrazi po:\n");
	printf("\t' 1 ' Imenu\n");
	printf("\t' 2 ' Prezimenu\n");
	printf("\t' 3 ' Smjer\n");
	printf("\t' 4 ' Ocjena\n");
	printf("\t' 5 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		SearchIme(polje);
		break;
	case 2:
		SearchPrezime(polje);
		break;
	case 3:
		SearchSmjer(polje);
		break;
	case 4:
		SearchOcjena(polje);
		break;
	case 5:
		return 90;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

int izbornikSrt() {
	int opcija = 0;
	STUDENT* polje = NULL;
	polje = (STUDENT*)ucitavanjeStudenata();
	printf("Sortiraj prema:\n");
	printf("\t' 1 ' Broju ocjene uzlazno\n");
	printf("\t' 2 ' Broju ocjene silazno\n");
	printf("\t' 3 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		selectionSortOcjeneUzl(polje);
		break;
	case 2:
		selectionSortOcjeneSil(polje);
		break;
	case 3:
		return 89;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("studenti.bin", "wb");
	if (fp == NULL) {
		perror("Kreiranje");
	}
	fwrite(&brojStudenata, sizeof(int), 1, fp);
	fclose(fp);
}

void dodavanjeStudenata() {
	FILE* fp = NULL;
	fp = fopen("studenti.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");

	fread(&brojStudenata, sizeof(int), 1, fp);
	printf("Trenutni broj studenata: %d", brojStudenata);

	STUDENT studenti;
	studenti.id = brojStudenata;
	br++;
	getchar();
	printf("Unesite ime studenta: ");
	scanf("%24[^\n]", studenti.ime);
	getchar();
	printf("Unesite prezime studenta: ");
	scanf("%29[^\n]", studenti.prezime);
	getchar();
	printf("Unesite smjer studenta: ");
	scanf("%29[^\n]", studenti.smjer);
	getchar();
	printf("Unesite ocjenu studenta: ");
	scanf_s("%f[^\n]", &studenti.ocjena);
	getchar();
	fseek(fp, sizeof(STUDENT) * brojStudenata, SEEK_CUR);
	fwrite(&studenti, sizeof(STUDENT), 1, fp);
	rewind(fp);
	brojStudenata++;
	fwrite(&brojStudenata, sizeof(int), 1, fp);
	fclose(fp);
}

void azuriranje() {
	FILE* fp = NULL;
	int reload;
	fp = fopen("studenti.bin", "rb+");
	if (fp == NULL)
		printf("Niste unijeli niti jednog studenta.\n");
	else {
		printf("Unesi broj studenta kojeg zelite ispraviti:\n");
		scanf("%d", &reload);
		fseek(fp, sizeof(int) + (sizeof(STUDENT) * (reload - 1)), SEEK_SET);
		STUDENT ispravljenStudent;
		ispravljenStudent.id = reload;
		getchar();
		printf("Unesite ispravljeno ime studenta: ");
		scanf("%24[^\n]", ispravljenStudent.ime);
		getchar();
		printf("Unesite ispravljeno prezime studenta: ");
		scanf("%29[^\n]", ispravljenStudent.prezime);
		getchar();
		printf("Unesite ispravljen smjer studenta: ");
		scanf("%14[^\n]", ispravljenStudent.smjer);
		getchar();
		printf("Unesite ispravljenu ocjenu studenta: ");
		scanf("%f", &ispravljenStudent.ocjena);
		getchar();
		fwrite(&ispravljenStudent, sizeof(STUDENT), 1, fp);
		rewind(fp);
		fwrite(&brojStudenata, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void* ucitavanjeStudenata() {
	FILE* fp = fopen("studenti.bin", "rb");
	if (fp == NULL) {
		printf("Niste unijeli niti jednog studenta.\n");
		return NULL;
	}
	fread(&brojStudenata, sizeof(int), 1, fp);
	STUDENT* polje = NULL;
	polje = (STUDENT*)calloc(brojStudenata, sizeof(STUDENT));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(STUDENT), brojStudenata, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(STUDENT* polje) {
	for (i = 0; i < brojStudenata; i++) {
		printf("Ime:%s  Prezime:%s  Smjer:%s  Ocjena: %f\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
	}
}

void* SearchIme(STUDENT* polje) {
	char reqName[25];
	int br = 0;

	printf("Upisite ime trazenog studenta:\n");
	getchar();
	scanf("%24[^\n]", reqName);

	for (i = 0; i < brojStudenata; i++) {
		if (!strcmp(reqName, (polje + i)->ime)) {
			printf("\nIme:%s  Prezime:%s	Smjer:%s  Ocjena: %f\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
			br++;
		}
	}
	if (br == 0)
		printf("\nStudent pod ovim imenom nije pronaden.\n");
	return NULL;
}

void* SearchPrezime(STUDENT* polje) {
	char reqSurname[25];
	int br = 0;

	printf("Upisite prezime trazenog studenta:\n");
	getchar();
	scanf("%29[^\n]", reqSurname);

	for (i = 0; i < brojStudenata; i++) {
		if (!strcmp(reqSurname, (polje + i)->prezime)) {
			printf("\nIme:%s  Prezime:%s  Smjer:%s  Ocjena: %f\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
			br++;
		}
	}
	if (br == 0)
		printf("\nStudent pod ovim prezimenom nije pronaden.\n");
	return NULL;
}

void* SearchSmjer(STUDENT* polje) {
	char reqPosition[25];
	int br = 0;

	printf("Upisite poziciju koju trazite:\n");
	getchar();
	scanf("%29[^\n]", reqPosition);

	for (i = 0; i < brojStudenata; i++) {
		if (!strcmp(reqPosition, (polje + i)->smjer)) {
			printf("\nIme:%s  Prezime:%s  Smjer:%s  Ocjena: %f\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
			br++;
		}
	}
	if (br == 0)
		printf("\nNije unesen niti jedan student na ovom smjeru.\n");
	return NULL;
}

void* SearchOcjena(STUDENT* polje) {
	int reqNo, br = 0;

	printf("Unesite broj ocjene koju trazite:\n");
	scanf("%d", &reqNo);

	for (i = 0; i < brojStudenata; i++) {
		if (reqNo == (polje + i)->ocjena) {
			printf("\nIme:%s  Prezime:%s  Smjer:%s  Ocjena: %f\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena ocjena nije pronadjena.\n");
	return NULL;
}

void zamjena(STUDENT* veci, STUDENT* manji) {
	STUDENT temp = { 0 };
	temp = *veci;
	*veci = *manji;
	*manji = temp;
}

void zamjena2(STUDENT* manji, STUDENT* veci) {
	STUDENT temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortOcjeneUzl(STUDENT* polje) {
	for (int j = 0; j < brojStudenata; j++) {
		for (int i = 0; i < brojStudenata - 1; i++) {
			if (polje[i].ocjena > polje[i + 1].ocjena) {
				zamjena2((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojStudenata; i++) {
		printf("\nID: %d Ime:%s  Prezime:%s  Smjer:%s  Ocjena: %f\n", (polje + i)->id, (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
	}
	printf("\n");
}

void selectionSortOcjeneSil(STUDENT* polje) {
	for (int j = 0; j < brojStudenata; j++) {
		for (int i = 0; i < brojStudenata - 1; i++) {
			if (polje[i].ocjena < polje[i + 1].ocjena) {
				zamjena((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojStudenata; i++) {
		printf("\nID: %d Ime:%s  Prezime:%s  Smjer:%s  Ocjena: %f\n", (polje + i)->id, (polje + i)->ime, (polje + i)->prezime, (polje + i)->smjer, (polje + i)->ocjena);
	}
	printf("\n");
}

void brisanjeStudenata(STUDENT* polje) {
	FILE* fp = NULL;
	fp = fopen("studenti.bin", "wb");
	if (fp == NULL) {
		perror("Brisanje studenata");
	}
	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);

	int br = 0, reqstudenta;

	printf("Unesite ID studenta kojeg zelite obrisati:");
	scanf("%d", &reqstudenta);

	for (i = 0; i < brojStudenata; i++) {
		if (reqstudenta != (polje + i)->id) {
			fwrite((polje + i), sizeof(STUDENT), 1, fp);
			br++;
		}
	}
	rewind(fp);
	fwrite(&br, sizeof(int), 1, fp);
	fclose(fp);
}

void brisanjeBaze(STUDENT* polje) {
	printf("Zelite li pri izlasku programa izbrisati datoteku ili zadrzati?\n");
	printf("Ako zelite izbrisati datoteku napisite obrisi, ako ne zelite napisite zadrzi\n");

	char uvjet[7] = { '\0' };
	scanf("%6s", uvjet);
	if (!strcmp("obrisi", uvjet)) {
		remove("studenti.bin") == 0 ? printf("Izbrisali ste datoteku studenti.bin.\n") : printf("Datoteka neuspjesno izbrisani ili ona ne postoji.\n");
		printf("\nIzlaz iz programa.\n");
		free(polje);
	}
	else printf("\nZadrzali ste datoteku.\nIzlaz iz programa\n");
}