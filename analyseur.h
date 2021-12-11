#ifndef ANALYSEUR
#define ANALYSEUR

#include <stdio.h>
#include "LRGrammar.h"

void build_tree_analysis(grammar G, table T, char* chaine, int tailleChaine);
int search_state_table(table t, int etatDepart, char caractereArechercher);
void print_tree_analysis(char* chaine, int tailleChaine, char* pile, int taillePile, int i);

#endif
