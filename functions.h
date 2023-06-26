#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajStudenta(const char* const);
void* ucitajStudente(const char* const);
void ispisiSveStudente(const STUDENT* const);
STUDENT* pretraziStudente(STUDENT* const);
void uredivanjeStudenata(STUDENT*, const char* const);
void brisanjeStudenta(STUDENT* const, const char* const);
void ispisPoGodinama(const STUDENT*);
int izlazIzPrograma(STUDENT*);

#endif