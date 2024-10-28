#include "graf.h"

TGL* citireG(FILE* input_file, int nr_muchii, char*** stringVector, int *total_tronsoane) {
    int nr_noduri = 2 * nr_muchii;
    int nr_copii[100]={0};
    *total_tronsoane = 0;
    TGL *g = alocG(nr_noduri);
    int orase = 0;
    int citire = 0;
    // pentru toate cele nr_muchii rute
    while (nr_muchii) {
        char sursa[20];
        char dest[20];
        // se citesc sursa si destinatia
        fscanf(input_file, "%s %s", sursa, dest);  
        citire++;
        // se adauga sursa si destinatia in vectorul de stringuri in cazul in care nu exista deja
        int ok = 0; // variabila pentru a verifica daca stringul se afla sau nu in vector
        int i = 0;
        int index_sursa; // se pastreaza indexul sursei
        for (i = 0; i < nr_noduri; i++) {
            if (strcmp((*stringVector)[i], sursa) == 0) {
                ok = 1;
                index_sursa = i;
                break;
            }
        }
        if (ok == 0) { // daca orasul nu este deja in vector se adauga
            strcpy((*stringVector)[orase], sursa);
            index_sursa = orase;
            orase++;
        }

        // se procedeaza la fel si pentru destinatie
        ok = 0; // variabila pentru a verifica daca stringul se afla sau nu in vector
        int index_destinatie = 0; // se pastreaza indexul destinatiei
        for (i = 0; i < nr_noduri; i++) {
            if (strcmp((*stringVector)[i], dest) == 0) {
                ok = 1;
                index_destinatie = i;
                break;
            }
        }
        if (ok == 0) { // daca orasul nu este deja in vector se adauga
            strcpy((*stringVector)[orase], dest);
            index_destinatie = orase;
            orase++;
        }

        int nr_tronsoane;
        // se citeste numarul de tronsoane
        fscanf(input_file, "%d", &nr_tronsoane);
        // se declara un vector unde se vor retine tronsoanele
        int vector_tronsoane[nr_tronsoane];
        for (i = 0; i < nr_tronsoane; i++) {
            // se citeste pe rand fiecare tronson
            fscanf(input_file, "%d", &vector_tronsoane[i]);
        }
        *total_tronsoane += nr_tronsoane;

        // se adauga la graf muchia sursa-destinatie
        AArc* p = g->x + index_sursa; //  p primeste adresa lui x[index_sursa]
        while(*p != NULL) {
            p = &(*p)->urm; // p primeste adresa lui p->urmator
        }
        //AArc aux = (TCel*)calloc(sizeof(TCel), 1);
        AArc aux = alocCelula();
        strcpy(aux->dest, dest);
        //aux->cost = {0};
        for (i = 0; i < nr_tronsoane; i++) {
            aux->cost[i] = vector_tronsoane[i];
        }
        aux->tronsoane = nr_tronsoane;
        aux->index_citire = citire;
        aux->urm = *p;
        nr_copii[index_sursa]++;
        // se adauga numarul de vecini al nodului radacina din vectorul de adiacenta
        aux->nr_vecini = nr_copii[index_sursa];
        *p = aux;


        // se adauga destinatie-sursa
        AArc* p2 = g->x + index_destinatie;
        while(*p2 != NULL) {
            p2 = &(*p2)->urm;
        }
        // AArc aux2 = (TCel*)calloc(sizeof(TCel),1);
        AArc aux2 = alocCelula();
        aux2->urm = *p2;
        *p2 = aux2;
        strcpy(aux2->dest, sursa);
        aux2->tronsoane = nr_tronsoane;
        for (i = 0; i < nr_tronsoane; i++) {
            aux2->cost[i] = vector_tronsoane[nr_tronsoane - i - 1];
        }
        nr_copii[index_destinatie]++;
        g->x[index_destinatie]->nr_vecini = nr_copii[index_destinatie];
        nr_muchii--;
    }
    return g;
}

void afisareG(TGL* g, char** stringVector, int nr_rute, int grad_uzura, FILE* output_file) {
    AArc l;
    int i;
    int index_afisare = 1;
    int vector_tronsoane[nr_rute];
    for (i = 0; i < nr_rute; i++) {
        vector_tronsoane[i] = 0;
    }
    int index_vector = 0;
    while (true) {
        for (i = 0; i < g->n; i++) {
            l = g->x[i];
            if(!l) {
            } else {
                for (; l != NULL; l = l->urm) {
                    float suma = 0;
                    if (l->index_citire != 0) {
                        if(l->index_citire == index_afisare) {
                            fprintf(output_file, "%s ", stringVector[i]);
                            fprintf(output_file,"%s ", l->dest);
                            fprintf(output_file,"%d ",l->tronsoane);
                            int i;
                            for (i = 0; i < l->tronsoane; i++) {
                                fprintf(output_file, "%.2f ", l->cost[i]);
                                suma+=l->cost[i];
                            }
                            if (suma/l->tronsoane < grad_uzura) {
                                vector_tronsoane[index_vector] = l->index_citire;
                                index_vector++;
                            }
                            fprintf(output_file, "\n");
                            if (index_afisare == nr_rute) {
                                int j;
                                for (j = 0; j < index_vector; j++)
                                    fprintf(output_file, "%d ", vector_tronsoane[j]);
                                if(index_vector != 0)
                                    fprintf(output_file,"\n");
                                return;
                            }
                            index_afisare++;
                        }
                    }
                }
                    
            }
        }
    }
}

float calcMaxNeigh (AArc l) {
    float max = 0;
    for(; l!= NULL; l = l->urm) {
        if (l->cost[0] > max) {
            max = l->cost[0];
        }
    }
    return max;
}


void calculUzura(TGL* g, int nr_ani, char**stringVector, int nr_tronsoane) {
    AArc l;
    int i;
    float vector_tronsoane[nr_tronsoane * 2];
    int index_trons = 0;
    // printf("nr trons %d\n", nr_tronsoane * 2);
    // reperatm de un nr_ani ori
    while (nr_ani != 0) {
        int i;
        index_trons = 0;
        // pentru fiecare nod
        for (i = 0; i < g->n; i++) {
            // vectorul de adiacenta
            l = g->x[i];
            if (l != NULL) {
                // parcurgem vectorul de adiacenta
                for(; l != NULL; l = l->urm) {
                    float max_value1 = -1;
                    float max_value2 = -1;
                    // verificam daca in costul curent se gaseste 0 pe prima pozitie
                    if (l->tronsoane > 0) {
                        if (l->cost[0] == 0 ) {
                            // verific care e cea mai mare valoare vecina din sursa
                            AArc aux = g->x[i];
                            max_value1 = calcMaxNeigh(aux);
                            if (l->tronsoane > 1) {
                                if (max_value1 < l->cost[1]) {
                                    max_value1 = l->cost[1];
                                }
                            }
                        }

                        // verificam daca in costul curent se gaseste 0 pe ultima pozitie
                        if (l->cost[l->tronsoane - 1] == 0) { // 0 pe ultima pozitie
                            // verific care este cea mai mare valoare vecina din destinatie
                            int index = getIndex(l, stringVector);
                            AArc aux = g->x[index];
                            max_value2 = calcMaxNeigh(aux);
                            if (l->tronsoane > 1) {
                                if (max_value2 < l->cost[l->tronsoane - 2]) {
                                    max_value2 = l->cost[l->tronsoane - 2];
                                }
                            }
                        }
                        
                        // daca avem un singur tronson
                        if (l->tronsoane == 1) {
                            // daca acesta este 0
                            if (l->cost[0] == 0) {
                                // se calculeaza maximul dintre stanga si din dreapta
                                float max = max_value2;
                                if (max_value1 > max_value2)
                                    max = max_value1;
                                vector_tronsoane[index_trons] = max / 2;
                                index_trons++;
                            }
                            // daca nu e 0
                            if (l->cost[0] != 0) {
                                // se dubleaza valoare lui
                                if ((l->cost[0] * 2 )< 100) {
                                    vector_tronsoane[index_trons] = (l->cost[0] * 2);
                                }
                                // ne asiguram ca nu depaseste 100
                                else vector_tronsoane[index_trons] = 100;
                                index_trons++;
                            }
                        } 
                        // daca sunt mai multe tronsoane
                        if (l->tronsoane > 1){
                            // verificam daca primul este 0
                            if(l->cost[0] == 0) {
                                // adaugam in vector val_max / 2 
                                vector_tronsoane[index_trons] = max_value1/2;
                                index_trons++;
                            }
                            else { // daca nu este 0,  dublam valoarea si o adaugam in vector
                                if ((l->cost[0] * 2 )< 100) {
                                    vector_tronsoane[index_trons] = (l->cost[0] * 2);
                                }
                                // ne asiguram ca nu depaseste 100
                                else vector_tronsoane[index_trons] = 100;
                                index_trons++;
                            }
                            // manipulam valorile de mijloc
                            int j;
                            for (j = 1; j < l->tronsoane - 1; j++) {
                                // daca una dintre valori e 0
                                if (l->cost[j] == 0) {
                                    // calculam maximul dintre elem stg elem drept
                                    if(l->cost[j-1] >= l->cost[j+1]) {
                                        vector_tronsoane[index_trons] = (l->cost[j-1] / 2);
                                        index_trons++;
                                    }
                                    else {
                                        vector_tronsoane[index_trons] = (l->cost[j+1] / 2);
                                        index_trons++;
                                    }
                                } 
                                // daca nu este 0, dublam si adaugam la vector
                                if (l->cost[j] != 0) {
                                    if ((l->cost[j] * 2) < 100)
                                        vector_tronsoane[index_trons] = (l->cost[j]) * 2;
                                    else vector_tronsoane[index_trons] = 100;
                                    index_trons++;
                                }
                            }
                            // manipulam valoarea de sfarsit
                            if (l->cost[l->tronsoane - 1] == 0) {
                                vector_tronsoane[index_trons] = max_value2 / 2;
                                // printf("%d\n", vector_tronsoane[index_trons])
                                index_trons++;
                            } else {
                                if (l->cost[l->tronsoane - 1] * 2 < 100)
                                    vector_tronsoane[index_trons] = l->cost[l->tronsoane - 1] * 2;
                                // ne asiguram ca nu depaseste 100
                                else vector_tronsoane[index_trons] = 100;
                                index_trons++;
                            }
                        }
                    }
                }
            }
        }
        // decrementam nr de ani
        nr_ani--;
        l = NULL;
        index_trons = 0;
        // copiem costurile din vectorul de tronosane in tronosanele din graf
        for (i = 0; i < g->n; i++) {
            l = g->x[i];
            for(; l != NULL; l = l->urm) {
                int i;
                for (i = 0; i < l->tronsoane; i++) {
                    l->cost[i] = vector_tronsoane[index_trons];
                    index_trons++;
                }
            }
        }
    }
}
