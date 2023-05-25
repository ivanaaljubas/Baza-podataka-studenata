#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char ime[50];
    char prezime[50];
    char mjestoStanovanja[100];
    float prosjek;
} Student;

void unosStudenta(Student* studenti, int* brojStudenata) {
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

    printf("Student je uspješno dodan.\n");
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
            printf("Pronaðen student:\n");
            printf("Ime: %s\n", studenti[i].ime);
            printf("Prezime: %s\n", studenti[i].prezime);
            printf("Mjesto stanovanja: %s\n", studenti[i].mjestoStanovanja);
            printf("Prosjek: %.2f\n", studenti[i].prosjek);
            printf("------------------------\n");
        }
    }

    if (!pronaden) {
        printf("Student s prezimenom '%s' nije pronaðen.\n", prezime);
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
        printf("Student s prezimenom '%s' nije pronaðen.\n", prezime);
    }
}

void spremiStudente(Student* studenti, int brojStudenata, const char* nazivDatoteke) {
    FILE* datoteka = fopen(nazivDatoteke, "w");
    if (datoteka == NULL) {
        printf("Greška pri otvaranju datoteke '%s'.\n", nazivDatoteke);
        return;
    }

    for (int i = 0; i < brojStudenata; i++) {
        fprintf(datoteka, "%s %s %s %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].mjestoStanovanja, studenti[i].prosjek);
    }

    fclose(datoteka);
    printf("Studenti su uspješno spremljeni u datoteku '%s'.\n", nazivDatoteke);
}

void ucitajStudente(Student* studenti, int* brojStudenata, const char* nazivDatoteke) {
    FILE* datoteka = fopen(nazivDatoteke, "r");
    if (datoteka == NULL) {
        printf("Greška pri otvaranju datoteke '%s'.\n", nazivDatoteke);
        return;
    }

    *brojStudenata = 0;
    while ((*brojStudenata < MAX_STUDENTS) && (fscanf(datoteka, "%s %s %s %f", studenti[*brojStudenata].ime, studenti[*brojStudenata].prezime, studenti[*brojStudenata].mjestoStanovanja, &studenti[*brojStudenata].prosjek) == 4)) {
        (*brojStudenata)++;
    }

    fclose(datoteka);
    printf("Studenti su uspješno uèitani iz datoteke '%s'.\n", nazivDatoteke);
}

int main() {
    Student studenti[MAX_STUDENTS];
    int brojStudenata = 0;

    ucitajStudente(studenti, &brojStudenata, "studenti.txt");

    int izbor;
    char prezime[50];

    while (1) {
        printf("-----------\n");
        printf("Izbornik:\n");
        printf("1 - Unos novog studenta\n");
        printf("2 - Ispis svih studenata\n");
        printf("3 - Pretraga studenata\n");
        printf("4 - Brisanje studenta\n");
        printf("5 - Spremi studente u datoteku\n");
        printf("6 - Izlaz iz programa\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            unosStudenta(studenti, &brojStudenata);
            break;
        case 2:
            ispisSvihStudenata(studenti, brojStudenata);
            break;
        case 3:
            printf("Unesite prezime studenta za pretragu: ");
            scanf("%s", prezime);
            pretraziStudenta(studenti, brojStudenata, prezime);
            break;
        case 4:
            printf("Unesite prezime studenta za brisanje: ");
            scanf("%s", prezime);
            obrisiStudenta(studenti, &brojStudenata, prezime);
            break;
        case 5:
            spremiStudente(studenti, brojStudenata, "studenti.txt");
            break;
        case 6:
            
            spremiStudente(studenti, brojStudenata, "studenti.txt");
            printf("Izlaz iz programa.\n");
            return 0;
        default:
            printf("Nepoznata opcija. Pokušajte ponovno.\n");
            break;
        }
    }

    return 0;
}
