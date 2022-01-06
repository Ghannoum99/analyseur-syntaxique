/* Authors: Jihad GHANNOUM et Yoa TOIHIR  */


#include "analyseur_syntaxique.h"
 
 
/*****************************************
 *  Fonction permettant d'allouer une pile
 * ***************************************/ 

PILE allouer_pile(int taille)
{
	PILE pile;
	
	pile.taillePile = taille;
	
	pile.tab = (char*) malloc(sizeof(char) * pile.taillePile);
	
	if (pile.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	return pile;
}
 
/*********************************************
 *  Fonction permettant de desallouer une pile
 * *******************************************/ 

void desallouer_pile(PILE pile)
{
	if (pile.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	free(pile.tab);
	
} 

char recuperer_element_pile(PILE pile, size_t indice)
{
	if (pile.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	return pile.tab[indice];
}

void empiler(PILE pile, char caractere)
{
	if (pile.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	pile.tab[pile.taillePile - 1] = caractere;
}


void depiler(PILE pile)
{
	if (pile.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	pile.tab[pile.taillePile - 1] = 0;
}


/*******************************************
 *  Fonction permettant d'allouer un tableau
 * ****************************************/ 
TAB_INT allouer_tab(int taille)
{
	TAB_INT tab;
	
	tab.tailleTab = taille;
	
	tab.tab = (int*) malloc(sizeof(int) * tab.tailleTab);
	
	if (tab.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	return tab;
}

/***********************************************
 *  Fonction permettant de desallouer un tableau
 * ********************************************/

void desallouer_tab(TAB_INT tab)
{
	if (tab.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	free(tab.tab);
} 
  

int lire_element_tab(TAB_INT tab, size_t indice)
{
	if (tab.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	return tab.tab[indice];
}
  
void ecrire_tab(TAB_INT tab, size_t indice, int val)
{
	if (tab.tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	tab.tab[indice] = val;
}

/*******************************************************
 *  Fonction permettant de construire une pile et un AST
 * ****************************************************/
 
void build_pile_AST(grammar G, table t, char* chaine) {
	
	size_t i;
	int k;
	unsigned int tailleChaine;
	int action;
	int etatDepart;
	char caractereTraite;
	PILE pile;
	TAB_INT reductions;
	
	pile.taillePile = 1;
	pile = allouer_pile(pile.taillePile);
	empiler(pile, '0');

	reductions.tailleTab = 0;
	reductions = allouer_tab(reductions.tailleTab);

	tailleChaine = strlen(chaine) + 1;
			
	printf("\n\t\tFlot\t\t|\t\tPile\n");
	printf("\t----------------------------------------------------\n");
	
	print_pile(chaine, tailleChaine, pile, 0);
	printf("\n");
	
	for (i=0; i<tailleChaine; i++) 
	{
		if (chaine[i] == 0) caractereTraite = '$';
		else caractereTraite = chaine[i];
		
		// On convertit le char en int
		etatDepart = recuperer_element_pile(pile, pile.taillePile - 1) - '0';
		// On va chercher l'état ou la règle à traiter
		action = search_state_table(t, etatDepart, caractereTraite);
		
		if (action == -127) {
			
			printf("\n	accepté\n");
			break;
			
		}
		else if (action == 0) {
			
			printf("\n	refusé\n");
			break;
			
		}
		else if (action > 0) {
			
			// On ajoute le caractère traité à la pile
			pile.taillePile++;
			pile.tab = (char *) realloc(pile.tab, pile.taillePile * sizeof(char));
			empiler(pile, caractereTraite);
		
			// On ajoute l'état suivant à la pile
			pile.taillePile++;
			pile.tab = (char *) realloc(pile.tab, pile.taillePile * sizeof(char));
			empiler(pile, action + '0');

			
			printf("  ");
			printf("d%d", action);
			
		}
		else {
			
			k=0;
			action = - action;
			
			// On supprime les k élements (correspondant au nombre d'élements à droite du non-terminal) de la pile
          	while(G.rules[-1+action].rhs[k]!='\0') k++;
         	
          	pile.taillePile = pile.taillePile - (k*2);
          	etatDepart = recuperer_element_pile(pile, pile.taillePile - 1) - '0';
          	
          	
          	// On ajoute le non-terminal à la pile
          	pile.taillePile++;
			pile.tab = (char *) realloc(pile.tab, pile.taillePile * sizeof(char));
			empiler(pile, G.rules[-1+action].lhs);
          	
          	// Le caractère traité est le non-terminal	
          	caractereTraite = recuperer_element_pile(pile, pile.taillePile - 1);
          	
          	// On ajoute l'état suivant à la pile
          	pile.taillePile++;
			pile.tab = (char *) realloc(pile.tab, pile.taillePile * sizeof(char));
			empiler(pile, search_state_table(t, etatDepart, caractereTraite)+'0');
			
			printf("  ");
			printf("r%d", action);
				
			reductions.tailleTab++;
			reductions.tab = (int *) realloc(reductions.tab, reductions.tailleTab * sizeof(int));
			ecrire_tab(reductions, reductions.tailleTab - 1, action);
			
			i = i-1;	
		}
		
		print_pile(chaine, tailleChaine, pile, i+1);
		printf("\n");	
		
	}
	
	// S'il n'y a pas d'erreur, on affiche l'AST
	if (action != 0) {
		printf("\n");
		print_AST(G, reductions, chaine, reductions.tailleTab-1);
		printf("\n");
	}
	
	desallouer_pile(pile);
	desallouer_tab(reductions);
	
}

/**************************************************************************
 *  Fonction permettant de chercher le statut dans un table d'analyse donné
 * ***********************************************************************/

int search_state_table(table t, int etatDepart, char caractereArechercher) {
	
	int state;
	size_t i, j;
	
	state = 0;

	i = etatDepart;
	j = caractereArechercher;

  	if(t.trans[256*i]) state = t.trans[256*i];

	if(t.trans[256*i+(256-j)]) state = t.trans[256*i+(256-j)];
		
    else if (t.trans[256*i+j]) state = t.trans[256*i+j];
    	 
  	return state;
}

/******************************************
 *  Fonction permettant d'afficher une pile
 * ***************************************/

void print_pile(char* chaine, int tailleChaine, PILE pile, size_t i) {
	
	size_t j;
	
	
	printf("	");
	
	for (j=i; j<tailleChaine; j++) 
	{
		printf("%c", chaine[j]);
	}
	
	printf("\t\t\t|\t\t");
	
	for (j=0; j<pile.taillePile; j++) 
	{
		printf("%c", recuperer_element_pile(pile, j));
	}
	
}

/****************************************
 *  Fonction permettant d'afficher un AST
 * *************************************/

void print_AST(grammar G, TAB_INT reductions, char* chaine, int i) {
	
	int k, ind, iBis;
	char * search;
	
	k = 0;
	
	// On récupère la ième règle 
	ind = lire_element_tab(reductions, i);
	
	printf("%c(", G.rules[-1+ind].lhs);
	
	// On parcourt les caractères de la règle
	while(G.rules[-1+ind].rhs[k]!='\0') 
	{
		// On vérifie si le caractère est terminal ou non
		search = strchr(chaine, G.rules[-1+ind].rhs[k]);
		if (search != NULL) printf("%c()", G.rules[-1+ind].rhs[k]);
		else {
			// Pour les caractères non-terminaux on va appeler récursivement la fonction 
			if (i >= 0) {
				iBis = i;
				iBis--;
				while (abs(G.rules[-1+ind].rhs[k]) != abs(G.rules[-1+lire_element_tab(reductions, iBis)].lhs)) {
					iBis--;
				}
				print_AST(G, reductions, chaine, iBis);
			}
		}

		k++;
	}
	printf(")");
}
