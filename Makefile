
LRanalyzer: main.o read_file.o LRGrammar.o LRanalyzer.o
	gcc main.o read_file.o LRGrammar.o LRanalyzer.o -o LRanalyzer
	
main.o: main.c
	gcc -c main.c
	
read_file.o: read_file.c read_file.h
	gcc -c read_file.c

LRGrammar.o: LRGrammar.c LRGrammar.h
	gcc -c LRGrammar.c
	
LRanalyzer.o: LRanalyzer.c LRanalyzer.h
	gcc -c LRanalyzer.c

clean:
	rm *.o LRanalyzer
