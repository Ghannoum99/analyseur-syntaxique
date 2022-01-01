/* Authors: Jihad GHANNOUM, Yoa TOIHIR  */

#ifndef ANALYSEUR_SYNTAXIQUE
#define ANALYSEUR_SYNTAXIQUE

#include <stdio.h>
#include <string.h>
#include "LRGrammar.h"

void build_tree_analysis(grammar G, table T, char* chaine);
int search_state_table(table t, int etatDepart, char caractereArechercher);
void print_tree_analysis(char* chaine, int tailleChaine, char* pile, int taillePile, size_t i);
void print_derivations(int* reductions, int tailleReductions, grammar G);

#endif
