/* Authors: Jihad GHANNOUM, Yoa TOIHIR  */

#include <stdlib.h>
#include <stdio.h>
#include "LRGrammar.h"
#include "read_file.h"
#include "LRanalyzer.h"


// Remplacer le type des indices (size_t et pas int)
 // si l atable ne correspond pas à la grammaire, le comportement de l'analyseur n'est pas défini
 // arbre d'analyse
 // à la fin de l'exécution, il dira si le texte est accepté ou pas
 // Ajouter des commentaires


int main(int argc, char* argv[])
{
	int fainChaine = 0;
	
	if (argc < 3)
	{
		fprintf(stderr,"L'analyseur prend 3 arguments\n");
		exit(EXIT_FAILURE);
	}
	
	file_read fr = read_file(argv[1]);
	print_grammar(fr.G);
	print_table(fr.t, fr.G);
	
	printf("\n");
	
	build_tree_analysis(fr.G, fr.t, argv[2]);
	
	
	
}
