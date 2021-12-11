#include "analyseur.h"

void build_tree_analysis(grammar G, table t, char* chaine, int tailleChaine) {
	int i, j, k, taillePile, action, etatDepart;
	char caractereTraite;
	char* pile;
	taillePile = 0;
	pile = (char*) malloc(sizeof(char) * taillePile+1);
	pile[taillePile] = '0';
	
	//strcat("$", chaine);
	
	for (i=0; i<tailleChaine; i++) 
	{
		caractereTraite = chaine[i];
		etatDepart = pile[taillePile]-'0';
		action=search_state_table(G, t, etatDepart, caractereTraite)+'0';
		
		if (action == -1) break;
		else if (action > 0) {
			taillePile+=2;
			pile = (char *) realloc(pile, taillePile+1 * sizeof(char));
			pile[taillePile-2]=caractereTraite;
			pile[taillePile-1] = action;
		}
		else {
			k=0;
          	while(G.rules[action].rhs[k]!='\0') k++;
          	taillePile-=k;
          	pile = (char *) realloc(pile, taillePile * sizeof(char));
          	taillePile+=2;
          	pile = (char *) realloc(pile, taillePile+1 * sizeof(char));
          	pile[taillePile-2] = G.rules[-1-action].lhs; 	
          	etatDepart = pile[taillePile-3]-'0';
          	caractereTraite = G.rules[-1-action].lhs;
			pile[taillePile-1]=search_state_table(G, t, etatDepart, caractereTraite)+'0';
		}
	}
	
	for (i=0; i<tailleChaine; i++) 
	{
		printf("%c", pile[i]);
	}
	
	free(pile);
}

int search_state_table(grammar G, table t, int etatDepart, char caractereArechercher) {
	int state;
	
	int i, j;
	
	i = etatDepart;

  	if(t.trans[256*i]){
  		if(t.trans[256*i]==-127){
        	state = -1; // accepté
      	}
      	else{
        	state = -t.trans[256*i];
       	}
	}
	j = caractereArechercher;
   	if(caractereArechercher>=1 && caractereArechercher<128){
    	if(t.trans[256*i+j]){
        	if(t.trans[256*i+j]>0){
	       		state = t.trans[256*i+j];
	     	}
	     	else{
	       		state = -t.trans[256*i+j];
      		}
    	}
    }
    if(caractereArechercher>=128 && caractereArechercher<256){
    	if(t.trans[256*i+j]){
			state = t.trans[256*i+j];
      	}
  	}
  	
  	return state;
}
