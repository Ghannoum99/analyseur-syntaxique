/* Authors: Jihad GHANNOUM, Yoa TOIHIR  */

#ifndef ANALYSEUR_SYNTAXIQUE
#define ANALYSEUR_SYNTAXIQUE

#include <stdio.h>
#include <string.h>
#include "LRGrammar.h"

typedef struct PILE{
  char* tab;
  int taillePile;
} PILE;

void build_pile_AST(grammar G, table T, char* chaine);
int search_state_table(table t, int etatDepart, char caractereArechercher);
void print_pile(char* chaine, int tailleChaine, PILE pile, size_t i);
void print_AST(grammar G, int* reductions, int tailleReductions, char* chaine, int i);

#endif
