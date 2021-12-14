#include <stdlib.h>
#include <stdio.h>
#include "LRGrammar.h"
#include "read_file.h"
#include "analyseur.h"

int main()
{
	file_read fr = read_file("./tests/test4");
	print_grammar(fr.G);
	print_table(fr.t, fr.G);
	
	printf("\n");
	
	build_tree_analysis(fr.G, fr.t, "cbcac", 5);
	
	return 0;
}
