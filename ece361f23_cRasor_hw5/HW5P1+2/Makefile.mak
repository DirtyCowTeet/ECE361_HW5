
output: bst_test.o bst_adt.o
	gcc -Wall -std=c99 -o BinarySearchTreeTest bst_adt.o bst_test.o

bst_test.o: bst_test.c
	gcc -Wall -std=c99 -c bst_test.c

bst_adt.o: bst_adt.c bst_adt.h
	gcc -Wall -std=c99 -c bst_adt.h bst_adt.c

clean:
	rm *.o output