#include <stdlib.h>
#include <stdio.h>
#include "LRGrammar.h"
#include "read_file.h"
#include "analyseur.h"

int main()
{
	file_read fr = read_file("./tests/test");
	build_tree_analysis(fr.G, fr.t, "ab$", 3);
	
	return 0;
}
