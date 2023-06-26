#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct student {
	int id;
	char ime[25];
	char prezime[30];
	char smjer[30];
	float ocjena;
}STUDENT;

int izbornik();
void izbornikSrch();
int izbornikSrt();
void kreiranjeDat();
void dodavanjeStudenata();
void azuriranje();
void* ucitavanjeStudenata();
void ispisivanje(STUDENT*);
void* SearchIme(STUDENT*);
void* SearchPrezime(STUDENT*);
void* SearchSmjer(STUDENT*);
void* SearchOcjena(STUDENT*);
void zamjena(STUDENT*, STUDENT*);
void zamjena2(STUDENT*, STUDENT*);
void selectionSortOcjeneUzl(STUDENT*);
void selectionSortOcjeneSil(STUDENT*);
void brisanjeStudenata(STUDENT*);
void brisanjeBaze(STUDENT*);
void natrag();

#endif //FUNCTIONS_H