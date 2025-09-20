/* CRETU Cristina - 311CB */

#include "struct_fct.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }
    int nrtask = atoi(&argv[1][2]);

    FILE *fin, *fout;
    // input file
    fin = fopen(argv[2], "r");
    if (fin == NULL) {
        return 1;
    }

    // output file
    fout = fopen(argv[3], "w");
    if (fout == NULL) {
        fclose(fin);
        return 1;
    }

    // TASK 1
    THeap* minh = NULL;
    minh = AllocateHeap(1000000, RelMinHeap);
    char line[10000];
    // get the number of satelites
    int nr_satelites;
    fgets(line, sizeof(line), fin);
    transform_line(line);
    nr_satelites = atoi(line);
    // get the details of the satelites
    for (int i = 1; i <= nr_satelites; i++) {
        fgets(line, sizeof(line), fin);
        transform_line(line);
        char p1[3]="", name[16] = "";
        extract(line, p1, name);
        int frequency = atoi(p1);
        TTree node = ConstrFrBin(frequency, name);
        // insert the satelite in the minheap
        InsertHeap(minh, node);
    }
    TTree node1, node2;
    while (minh->nrElem > 1) {
        /* extract the 2 satelites with the lowest frequency
        (or first alfabetically) */
        node1 = ExtrHeap(minh);
        node2 = ExtrHeap(minh);
        // the frequency and name of the parent satelite
        int new_freq = node1->frequency + node2->frequency;
        int l = strlen(node1->name) + strlen(node2->name) + 1;
        char *new_name = malloc(l);
        new_name[0] = '\0';
        strcat(new_name, node1->name);
        strcat(new_name, node2->name);
        TTree new_node = ConstrFrBin(new_freq, new_name);
        // link the parent satelite with the 2 satelites
        new_node->st = node1;
        new_node->dr = node2;
        // insert the parent into the minheap
        InsertHeap(minh, new_node);
        free(new_name);
    }
    TTree tree = ExtrHeap(minh);
    if (nrtask == 1)
        DisplayOnLevels(fout, tree);

    // free the allocated memory
    if (nrtask == 1) {
        DestroyT(tree);
        for (int i = 0; i < minh->nrElem; i++) {
            DestroyT(minh->v[i]);
        }
        free(minh->v);
        free(minh);
    }

    // TASK 2
    if (nrtask == 2) {
        // get the number of codes
        fgets(line, sizeof(line), fin);
        transform_line(line);
        int nrcodes = atoi(line);
        for (int i = 0; i < nrcodes; i++) {
            // get each code
            fgets(line, sizeof(line), fin);
            transform_line(line);
            PrintSatelite(fout, tree, line);
            fprintf(fout, "\n");
        }
        // free the allocated memory
        DestroyT(tree);
        for (int i = 0; i < minh->nrElem; i++) {
            DestroyT(minh->v[i]);
        }
        free(minh->v);
        free(minh);

    // TASK 3
    } else if (nrtask == 3) {
        // get the muber of satelites
        fgets(line, sizeof(line), fin);
        transform_line(line);
        int nrsatelites = atoi(line);
        for (int i = 1; i <= nrsatelites; i++) {
            // get each satelite
            fgets(line, sizeof(line), fin);
            transform_line(line);
            char path[1000]="";
            PrintCode(fout, path, 0, tree, line);
        }

        // free the allocated memory
        DestroyT(tree);
        for (int i = 0; i < minh->nrElem; i++) {
            DestroyT(minh->v[i]);
        }
        free(minh->v);
        free(minh);

    // TASK 4
    } else if (nrtask == 4) {
        // get the number of satelites
        fgets(line, sizeof(line), fin);
        transform_line(line);
        int nrsatelites = atoi(line);
        // create an array for the satelites
        char** satelites = malloc(nrsatelites * sizeof(char*));
        for (int i = 0; i < nrsatelites; i++) {
            // get each satelite and pur it in the array
            fgets(line, sizeof(line), fin);
            transform_line(line);
            satelites[i] = malloc(strlen(line) + 1);
            strcpy(satelites[i], line);
        }
        TTree parent = NULL;
        FindParent(tree, &parent, satelites, nrsatelites);
        if (parent != NULL)
            fprintf(fout, "%s\n", parent->name);

        // free the allocated memory
        for (int i = 0; i < nrsatelites; i++) {
            free(satelites[i]);
        }
        free(satelites);
        DestroyT(tree);
        for (int i = 0; i < minh->nrElem; i++) {
            DestroyT(minh->v[i]);
        }
        free(minh->v);
        free(minh);
    }

    // close the input and output files
    fclose(fin);
    fclose(fout);
    return 0;
}
