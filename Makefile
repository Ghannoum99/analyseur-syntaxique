
LRanalyzer: main.o read_file.o LRGrammar.o analyseur_syntaxique.o
	gcc main.o read_file.o LRGrammar.o analyseur_syntaxique.o -o LRanalyzer
	
main.o: main.c
	gcc -c main.c
	
read_file.o: read_file.c read_file.h
	gcc -c read_file.c

LRGrammar.o: LRGrammar.c LRGrammar.h
	gcc -c LRGrammar.c
	
analyseur_syntaxique.o: analyseur_syntaxique.c analyseur_syntaxique.h
	gcc -c analyseur_syntaxique.c

clean:
	rm *.o LRanalyzer
