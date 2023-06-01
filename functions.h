#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void kreiranjeDatoteke(const char* ime);
void dodajStudenta(const char* ime);
void* ucitajStudenta(const char* ime);
void ispisiSveStudente(const void* polje);
void* pretraziStudente(const void* polje);
void uredivanjePopisaStudenta(void* polje, const char* ime);
void brisanjeStudnta(void* polje, const char* ime);
void sortirajPoOcjeni(void* polje);
void ispisPoOcijeni(const void* polje);
int izlazIzPrograma(void* polje);
int izbornik(const char* ime);
#endif