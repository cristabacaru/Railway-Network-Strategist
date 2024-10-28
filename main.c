#include"graf.h"

int main(int argc, char *argv[]) {
    int task = atoi(argv[1]);
    FILE *input_file = fopen("tema3.in", "rt");

    // se verifica daca fisierul a fost deschis cu succes
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    // se deschide fisierul in care se scrie
    FILE *output_file = fopen("tema3.out", "wt");

    // se verifica daca fisierul a fost deschis cu succes
    if (output_file == NULL) {
        printf("Error opening output file\n");
        fclose(input_file);
        return 1;
    }

    if (task == 1) {
        int nr_rute;
        // Se citeste numarul de rute
        fscanf(input_file, "%d", &nr_rute);

        int ani;
        // Se citeste numarul de ani
        fscanf(input_file, "%d", &ani);

        int grad_uzura;
        // Se citeste gradul de uzura acceptat
        fscanf(input_file, "%d", &grad_uzura);

        // se aloca un vector de stringuri unde se pastreaza nodurile grafului
        char** stringVector = allocStringVector(nr_rute * 2);

        // variabila pentru calcului totalului de tronsoane
        int total_tronsoane = 0;

        // se citeste si se construieste graful
        TGL* g = citireG(input_file, nr_rute, &stringVector, &total_tronsoane);

        // se calculeaza uzura dupa nr_ani ani
        calculUzura(g, ani, stringVector, total_tronsoane);

        // se afiseaza noile rute si rutele care respecta gradul de uzura
        afisareG(g, stringVector, nr_rute, grad_uzura, output_file);

        // se elibereaza memoria alocata
        distrG(&g);
        freeStringVector(stringVector, nr_rute*2);
        
        fclose(output_file);
        fclose(input_file);
        return 0;
    }

    if (task == 2) {
        fclose(output_file);
        fclose(input_file);
        return 0;
    }
    
   
}