#ifndef ANALYSEUR
#define ANALYSEUR

#include <stdio.h>
#include "LRGrammar.h"

void build_tree_analysis(grammar G, table T, char* chaine, int tailleChaine);
int search_state_table(grammar G, table t, int etatDepart, char caractereArechercher);

#endif
