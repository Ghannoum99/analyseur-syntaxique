/* Authors: Jihad GHANNOUM, Yoa TOIHIR  */


#include "analyseur_syntaxique.h"
 

void build_tree_analysis(grammar G, table t, char* chaine) {
	
	size_t i;
	int k;
	unsigned int taillePile;
	unsigned int tailleChaine;
	unsigned int tailleReductions;
	int action;
	int etatDepart;
	char caractereTraite;
	char* pile;
	char* reductions;
	
	taillePile = 1;
	pile = (char*) malloc(sizeof(char) * taillePile);
	pile[taillePile-1] = '0';

	tailleReductions = 1;
	reductions = (char*) malloc(sizeof(char) * tailleReductions);

	tailleChaine = strlen(chaine) + 1;
			
	printf("\n\t\tFlot\t\t|\t\tPile\n");
	printf("\t----------------------------------------------------\n");
	
	print_tree_analysis(chaine, tailleChaine, pile, taillePile, 0);
	printf("\n");
	
	for (i=0; i<tailleChaine; i++) 
	{
		if (chaine[i] == 0) caractereTraite = '$';
		else caractereTraite = chaine[i];
		
		// On convertit le char en int
		etatDepart = pile[taillePile-1]-'0'; 
		
		// On va chercher l'état ou la règle à traiter
		action = search_state_table(t, etatDepart, caractereTraite);
		
		//printf("caractère = %c, étatDep = %d, action = %d\n", caractereTraite, etatDepart, action);
	
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
			taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
			pile[taillePile-1] = caractereTraite;
		
			// On ajoute l'état suivant à la pile
			taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
			pile[taillePile-1] = action + '0';
			
			printf("  ");
			printf("d%d", action);
			
		}
		else {
			
			k=0;
			action = -action;
			
			// On supprime les k élements (correspondant au nombre d'élements à droite du non-terminal) de la pile
          	while(G.rules[-1+action].rhs[k]!='\0') k++;
         
          	taillePile = taillePile - (k*2);
          	pile = (char *) realloc(pile, taillePile * sizeof(char));
          	
          	etatDepart = pile[taillePile-1]-'0';
          	
          	// On ajoute le non-terminal à la pile
          	taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
          	pile[taillePile-1] = G.rules[-1+action].lhs; 
          	
          	// Le caractère traité est le non-terminal	
          	caractereTraite = pile[taillePile-1];
          	
          	// On ajoute l'état suivant à la pile
          	taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
          	pile[taillePile-1] = search_state_table(t, etatDepart, caractereTraite)+'0';
			
			printf("  ");
			printf("r%d", action);
			
			reductions[tailleReductions-1] = caractereTraite;
			tailleReductions++;
			reductions = (char *) realloc(reductions, tailleReductions * sizeof(char));
			
			i = i-1;
			
		}
		
		print_tree_analysis(chaine, tailleChaine, pile, taillePile, i+1);
		printf("\n");	
		
	}
	
	printf("\n");
	print_derivations(reductions, tailleChaine-2, chaine, 0);
	printf("\n");
	
	free(pile);
	free(reductions);
	
}

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

void print_tree_analysis(char* chaine, int tailleChaine, char* pile, int taillePile, size_t i) {
	
	size_t j;
	
	printf("	");
	
	for (j=i; j<tailleChaine; j++) 
	{
		printf("%c", chaine[j]);
	}
	
	printf("\t\t\t|\t\t");
	
	for (j=0; j<taillePile; j++) 
	{
		printf("%c", pile[j]);
	}
	
}

void print_derivations(char* reductions, int tailleChaine, char* chaine, int i) {
	
	printf("%c(%c()", reductions[i], chaine[i]);
	if (i < tailleChaine) print_derivations(reductions, tailleChaine, chaine, i+1);
	printf(")");
}
