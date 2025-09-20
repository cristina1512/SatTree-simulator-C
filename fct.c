/* CRETU Cristina - 311CB */

#include "struct_fct.h"

// eliminates whitespaces, newlines, carriage returns
void transform_line(char* line) {
  int len = strlen(line);
  while (len > 0 && (line[len - 1] == ' ' ||
        line[len - 1] == '\n' || line[len - 1] == '\r')) {
    line[len - 1] = '\0';
    len--;
  }
}

// extracts the frequency and the name in each line
void extract(char* line, char* p1, char* p2) {
    int j = 0;
    int k = 0;
    while (line[j] != ' ') {
        p1[k++] = line[j++];
    }
    j++;
    k = 0;
    while (line[j] != '\0') {
        p2[k++] = line[j++];
    }
}

// define the order for the 2 nodes for the minheap, considering the rules
// the function is inspired from the laboratory
int RelMinHeap(TTree h1, TTree h2) {
	if (h1->frequency != h2->frequency)
        return h1->frequency < h2->frequency;
    return strcmp(h1->name, h2->name) < 0;
}

// allocate memory for the heap
// the function is inspired from the laboratory
THeap* AllocateHeap(int nrMax, TFCmp comp) {
    THeap* h = (THeap*)malloc(sizeof(THeap));
    if (h == NULL) {
        return NULL;
    }
    h->v = malloc(nrMax * sizeof(TTree));
    if (h->v == NULL) {
		free(h);
		return NULL;
	}
    h->nrMax = nrMax;
    h->nrElem = 0;
    h->comp = comp;
    return h;
}

// creates a binary tree node with the given frequency and name
// the function is inspired from the laboratory
TTree ConstrFrBin(int f, const char *n) {
	TTree aux = (TTree)malloc(sizeof(TNode));
	if (aux == NULL)
        return NULL;
	aux->frequency = f;
    aux->name = malloc(strlen(n) + 1);
    if (aux->name == NULL) {
        free(aux);
        return NULL;
    }
    strcpy(aux->name, n);
    aux->st = aux->dr = NULL;
	return aux;
}

// inserts a node into the minheap
void InsertHeap(THeap *h, TTree node) {
    int current_pos = h->nrElem;
    h->nrElem++;
    while (current_pos > 0) {
        int parent = (current_pos - 1) / 2;
        if (h->comp(h->v[parent], node)) {
            break;
        }
        h->v[current_pos] = h->v[parent];
        current_pos = parent;
    }
    h->v[current_pos] = node;
}

// extracts the satelite with the biggest priority
// (the lowest frequency and the first alphabetically)
TTree ExtrHeap(THeap *h) {
    if (h->nrElem == 0)
        return NULL;
    TTree node = h->v[0];
    h->v[0] = h->v[h->nrElem - 1];
    h->nrElem--;
    int node_pos = 0;
    while (2 * node_pos + 1 < h->nrElem) {
        // left child
        int child_pos = 2 * node_pos + 1;
        // change to the right child if necessary
        if (child_pos + 1 < h->nrElem) {
            if (!h->comp(h->v[child_pos], h->v[child_pos + 1]))
                child_pos++;
        }
        if (h->comp(h->v[node_pos], h->v[child_pos])) {
            break;
        } else {
            // exchange node <-> child
            TTree aux = h->v[node_pos];
            h->v[node_pos] = h->v[child_pos];
            h->v[child_pos] = aux;
            node_pos = child_pos;
        }
    }
    return node;
}

// initialize the queue
// the function is inspired from the laboratory
TQueue* InitQ() {
    TQueue *q = malloc(sizeof(TQueue));
    if (q == NULL)
        return NULL;
    q->inc = NULL;
    q->sf = NULL;
    return q;
}

// add a new element to the queue
int AddQ(TQueue *q, TTree treenode) {
    TCellQ *new = malloc(sizeof(TCellQ));
    // addition failed
    if (new == NULL)
        return 0;
    new->node = treenode;
    new->urm = NULL;
    // if the queue is empty
    if (q->inc == NULL) {
        q->inc = q->sf = new;
    } else {
        q->sf->urm = new;
        q->sf = new;
    }
    // addition successed
    return 1;
}

// extract the first element of the queue
TTree ExtrQ(TQueue *q) {
    if (q == NULL)
        return NULL;
    TCellQ *aux = q->inc;
    q->inc = aux->urm;
    // if it was the only element in the queue
    if (q->inc == NULL)
        q->sf = NULL;
    TTree treenode = aux->node;
    free(aux);
    return treenode;
}

// destoy the memory allocated for the queue
void DestroyQ(TQueue *q) {
    while (q && q->inc)
        ExtrQ(q);
    free(q);
}

// destroy the memoty allocated for the tree
void DestroyT(TTree tree) {
    if (tree == NULL)
        return;
    DestroyT(tree->st);
    DestroyT(tree->dr);
    free(tree->name);
    free(tree);
}

// TASK 1
// inspired from the course
void DisplayOnLevels(FILE *fout, TTree tree) {
    if (tree == NULL)
        return;
    TQueue *q = InitQ();
    AddQ(q, tree);
    while (q->inc != NULL) {
        int nr_nodes_level = 0;
        // how many nodes are on the current level
        TCellQ *aux = q->inc;
        while (aux != NULL) {
            nr_nodes_level++;
            aux = aux->urm;
        }
        for (int i = 1; i <= nr_nodes_level; i++) {
            TTree node = ExtrQ(q);
            fprintf(fout, "%d-%s ", node->frequency, node->name);
            if (node->st)
                AddQ(q, node->st);
            if (node->dr)
                AddQ(q, node->dr);
        }
        // end of level
        fprintf(fout, "\n");
    }
    DestroyQ(q);
}

// TASK 2
void PrintSatelite(FILE *fout, TTree tree, char* code) {
    TTree node = tree;
    int i = 0;
    while (code[i] != '\0') {
        // if we are located in a leaf node
        if (node->st == NULL && node->dr == NULL) {
            fprintf(fout, "%s ", node->name);
            node = tree;
        }
        // go to the left
        if (code[i] == '0') {
            node = node->st;
        // go to the right
        } else if (code[i] == '1') {
            node = node->dr;
        }
        i++;
    }
    if (node->st == NULL && node->dr == NULL) {
        fprintf(fout, "%s ", node->name);
        node = tree;
    }
}

// TASK 3
int PrintCode(FILE *fout, char* code, int level,
            TTree current_node, char* satelite) {
    if (current_node == NULL)
        return 0;
    // if we found the satelite
    if (strcmp(current_node->name, satelite) == 0) {
            code[level] = '\0';
            fprintf(fout, "%s", code);
            return 1;
    }
    // first we try to get to it by going to the left
    code[level] = '0';
    if (PrintCode(fout, code, level + 1, current_node->st, satelite) == 1) {
        return 1;
    } else {
        // if it didn't work, we go to the right
        code[level] = '1';
        if (PrintCode(fout, code, level + 1, current_node->dr, satelite) == 1)
            return 1;
    }
    return 0;
}

// TASK 4
int FindParent(TTree current_node, TTree* parent, char** satelites, int nr) {
    if (current_node == NULL)
        return 0;
    int left_child = FindParent(current_node->st, parent, satelites, nr);
    int right_child = FindParent(current_node->dr, parent, satelites, nr);
    int ok = 0;
    // see if the current node is on the list
    for (int i = 0; i < nr; i++) {
        if (strcmp(current_node->name, satelites[i]) == 0) {
            ok = 1;
            break;
        }
    }
    /* if we found all the nodes in the leftsubtree, the right subtree
    and in the current node*/
    if (left_child + right_child + ok == nr) {
        if (*parent == NULL) {
            *parent = current_node;
        }
    }
    return left_child + right_child + ok;
}
