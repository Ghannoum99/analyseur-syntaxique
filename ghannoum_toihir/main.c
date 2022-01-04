/* Authors: Jihad GHANNOUM, Yoa TOIHIR  */

#include <stdlib.h>
#include <stdio.h>
#include "LRGrammar.h"
#include "read_file.h"
#include "analyseur_syntaxique.h"


 // Ajouter des commentaires


int main(int argc, char* argv[])
{	
	if (argc < 3)
	{
		fprintf(stderr,"error: too few arguments\n");
		exit(EXIT_FAILURE);
	}
	
	file_read fr = read_file(argv[1]);
	//print_grammar(fr.G);
	//print_table(fr.t, fr.G);
	
	printf("\n");
	
	build_pile_AST(fr.G, fr.t, argv[2]);
	
	return 0;
}
