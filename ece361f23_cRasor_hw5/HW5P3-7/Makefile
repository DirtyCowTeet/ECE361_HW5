
output: iom_bst_test.o bst_adt.o iom361_r2.o float_rndm.o
	gcc -Wall -std=c99 -o IomBstTest iom_bst_test.o bst_adt.o iom361_r2.o float_rndm.o

iom_bst_test.o: iom_bst_test.c
	gcc -Wall -std=c99 -c iom_bst_test.c

bst_adt.o: bst_adt.c bst_adt.h
	gcc -Wall -std=c99 -c bst_adt.h bst_adt.c

iom361_r2.o: iom361_r2.h iom361_r2.c float_rndm.o
	gcc -Wall -std=c99 -c iom361_r2.c iom361_r2.h float_rndm.o

float_rndm.o: float_rndm.c float_rndm.h
	gcc -Wall -std=c99 -c float_rndm.c float_rndm.h

clean:
	rm *.o output