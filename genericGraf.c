#include "graf.h"

TGL* alocG(int nr) {
    TGL* g = (TGL*)calloc(sizeof(TGL), 1);
    if (!g) return NULL;
    g->n = nr;
    g->x = (AArc*)calloc(sizeof(AArc), nr);
    int i;
    for (i = 0; i < nr; i++) {
        g->x[i] = NULL;
    }
    if (!g->x) {
        free(g);
        return NULL;
    }
    return g;
}

AArc alocCelula() {
    AArc celula = (AArc)calloc(sizeof(TCel),1);
    int i = 0;
    for (i = 0; i < 20; i++) {
        celula->cost[i] = 0;
    }
    strcpy(celula->dest, "");
    celula->nr_vecini = 0;
    celula->tronsoane = 0;
    celula->index_citire = 0;
    celula->urm = NULL;
    return celula;
}

void distrG(TGL** g) {
    int i;
    AArc p, aux;
    for (i = 0; i < (*g)->n; i++) {
        p = (*g)->x[i];
        while(p) {
            aux = p; 
            p = p->urm;
            free(aux);
        }
    }
    free((*g)->x);
    free(*g);
    *g = NULL;
}

char** allocStringVector (int noStrings) {
    char **stringVector = (char**)calloc(sizeof(char *), noStrings);
    int i;
    for (i = 0; i < noStrings; i++) {
        stringVector[i] = (char*)calloc(sizeof(char),20);
    }
    return stringVector;
}

void freeStringVector (char** stringVector, int noStrings) {
    int i;
    for (i = 0; i < noStrings; i++)
        free(stringVector[i]);
    free(stringVector);
}

int getIndex (AArc l, char** stringVector) {
    int i = 0;
    while(true) {
        if (strcmp(l->dest, stringVector[i]) == 0)
            return i;
        i++;
    }
}