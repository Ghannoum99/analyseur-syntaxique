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

typedef struct TAB_INT{
  int* tab;
  int tailleTab;
} TAB_INT;


/*******************************************
 *  Fonction permettant d'accéder à une pile
 ******************************************/
 
PILE allouer_pile(int taille);
PILE reallouer_pile(int taille);
void desallouer_pile(PILE pile);
char recuperer_element_pile(PILE pile);
void empiler(PILE pile, char caractere); 
void depiler(PILE pile);
 
/*********************************************
 *  Fonction permettant d'accéder à un tableau
 ********************************************/
 
TAB_INT allouer_tab(int taille);
void desallouer_tab(TAB_INT tab);
int lire(TAB_INT tab, size_t indice);
void ecrire(TAB_INT tab, size_t indice, int val);

/************************************************************
 *  Fonction permettant de construire un analyseur syntaxique
 ************************************************************/

void build_pile_AST(grammar G, table T, char* chaine);
int search_state_table(table t, int etatDepart, char caractereArechercher);
void print_pile(char* chaine, int tailleChaine, PILE pile, size_t i);
void print_AST(grammar G, TAB_INT reductions, char* chaine, int i);

#endif
