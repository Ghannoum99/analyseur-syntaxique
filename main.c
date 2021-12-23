#include <stdlib.h>
#include <stdio.h>
#include "LRGrammar.h"
#include "read_file.h"
#include "LRanalyzer.h"


// Remplacer le type des indices (size_t et pas int)


int main()
{
	file_read fr = read_file("./tests/test5");
	print_grammar(fr.G);
	print_table(fr.t, fr.G);
	
	printf("\n");
	
	build_tree_analysis(fr.G, fr.t, "aaabbbb", 7);
	
	return 0;
}
