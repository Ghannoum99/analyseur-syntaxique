int main(int argc, char * argv[])
{
	
	if (argc < 3)
	{
		
		fprintf(stderr,"Le programme prend 3 arguments\n");
		exit(EXIT_FAILURE);
		
	}
	
	file_read fr = read_file(argv[1]);
	print_grammar(fr.G);
	print_table(fr.t, fr.G);
	
	printf("\n");
	
	build_tree_analysis(fr.G, fr.t, argv[2],5);
	
	return 0;
}
