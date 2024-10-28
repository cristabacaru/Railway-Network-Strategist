#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct celula {
    char dest[20]; // destinatie muchie
    float cost[20]; // cost muchie
    int nr_vecini;
    int tronsoane;
    int index_citire;
    struct celula *urm; // adresa urmatorului adiacent
} TCel, *AArc;

typedef struct {
    int n; // numar de noduri
    AArc* x; // vector de pointeri catre listele de arce
} TGL;

typedef struct {
    int codificare;
    char nume[20];
}TCodificare;

// functii generice creare graf
TGL* alocG(int nr);
AArc alocCelula();
void distrG(TGL** g);
char** allocStringVector (int noStrings);
void freeStringVector (char** stringVector, int noStrings);
int getIndex (AArc l, char** stringVector);

// functii specifice Task 1
TGL* citireG(FILE* input_file, int nr_muchii, char*** stringVector, int *total_tronsoane);
void calculUzura(TGL* g, int nr_ani, char**stringVector, int nr_tronsoane);
void afisareG(TGL* g, char** stringVector, int nr_rute, int grad_uzura, FILE* output_file);