
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct student {      //2. 3. 10.
	int id;           
	char ime[25];
	char prezime[30];         //12.
	char smjer[30];
	float ocjena;           //1.
}STUDENT;

int izbornik();              //4.
int izbornikSrch();
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


#endif //FUNCTIONS_H

//6.
