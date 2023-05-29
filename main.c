#define _CRT_SECURE_NO_WARNINGS
#include "student.h"
#include <stdio.h>

int main() {
	Student studenti[MAX_STUDENTS];
	int brojStudenata = 0;

	ucitajStudente(studenti, &brojStudenata, "studenti.txt");

	int izbor;
	char prezime[50];

	while (1) {                                    //8.
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