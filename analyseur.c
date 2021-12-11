#include "analyseur.h"

void build_tree_analysis(grammar G, table t, char* chaine, int tailleChaine) {
	int i, j, k, taillePile, action, etatDepart;
	char caractereTraite;
	char* pile;
	char c[100] = "$";
	taillePile = 0;
	pile = (char*) malloc(sizeof(char) * taillePile+1);
	pile[taillePile] = '0';

	//strcat(chaine, c);
	
	printf("	Flot | Pile | Règle \n");
	printf("	-------------------\n");
	
	print_tree_analysis(chaine, tailleChaine, pile, taillePile, 0);
	printf("\n");
	
	for (i=0; i<tailleChaine; i++) 
	{
		caractereTraite = chaine[i];
		
		// On convertit le char en int
		etatDepart = pile[taillePile]-'0'; 
		
		// On va chercher l'état ou la règle à traiter
		action = search_state_table(t, etatDepart, caractereTraite);
		
		//printf("caractère = %c, étatDep = %d, action = %d\n", caractereTraite, etatDepart, action);
		
		print_tree_analysis(chaine, tailleChaine, pile, taillePile, i+1);
	
		if (action == -257) {
			printf("\n	accepté\n");
			break;
		}
		else if (action == -258) {
			printf("\n	refusé\n");
			break;
		}
		else if (action > 0) {
			// On ajoute le caractère traité à la pile
			taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
			pile[taillePile] = caractereTraite;
			
			// On ajoute l'état suivant à la pile
			taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
			pile[taillePile] = action + '0';
			
			printf(" | ");
			printf("d%d", action);
		}
		else {
			k=0;
			action = -action;
			
			// On supprime les k élements (correspondant au nombre d'élements à droite du non-terminal) de la pile
          	while(G.rules[-1+action].rhs[k]!='\0') k++;
          	taillePile-=k;
          	pile = (char *) realloc(pile, taillePile * sizeof(char));
          	
          	etatDepart = pile[taillePile]-'0';
          	
          	// On ajoute le non-terminal à la pile
          	taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
          	pile[taillePile] = G.rules[-1+action].lhs; 
          	
          	// Le caractère traité est le non-terminal	
          	caractereTraite = pile[taillePile];
          	
          	// On ajoute l'état suivant à la pile
          	taillePile++;
			pile = (char *) realloc(pile, taillePile * sizeof(char));
			pile[taillePile] = search_state_table(t, etatDepart, caractereTraite)+'0';
			
			printf(" | ");
			printf("r%d", action);
		}
		printf("\n");	
	}
	
	free(pile);
}

int search_state_table(table t, int etatDepart, char caractereArechercher) {
	int state, i, j;
	state = -258;

	i = etatDepart;
	j = caractereArechercher;

  	if(t.trans[256*i]){
  		if(t.trans[256*i]==-127){
        	state =  -257; // accepté
      	}
      	else{
        	state = t.trans[256*i];
       	}
	}

	if(t.trans[256*i+(256-j)]){
		state = t.trans[256*i+(256-j)];
    }
    else if (t.trans[256*i+j]){
    	state = t.trans[256*i+j];
	}
    
  	return state;
}

void print_tree_analysis(char* chaine, int tailleChaine, char* pile, int taillePile, int i) {
	int j;
	
	printf("	");
	for (j=i; j<tailleChaine; j++) 
	{
		printf("%c", chaine[j]);
	}
	if (i == tailleChaine) printf("%c", '$');
	printf(" | ");
	for (j=0; j<=taillePile; j++) 
	{
		printf("%c", pile[j]);
	}
}
