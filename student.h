#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

typedef struct {            //3.
	char ime[50];
	char prezime[50];
	char mjestoStanovanja[100];
	float prosjek;
} Student;

void unosStudenta(Student* studenti, int* brojStudenata);
void ispisSvihStudenata(Student* studenti, int brojStudenata);
void pretraziStudenta(Student* studenti, int brojStudenata, const char* prezime);
void obrisiStudenta(Student* studenti, int* brojStudenata, const char* prezime);
void spremiStudente(Student* studenti, int brojStudenata, const char* nazivDatoteke);
void ucitajStudente(Student* studenti, int* brojStudenata, const char* nazivDatoteke);

#endif

