programm : main.o matrix.o functions.o complex.o test.o
	gcc -o programm main.o matrix.o functions.o complex.o test.o
test : test.o testMatrix.o matrix.o functions.o complex.o
	g++ -o test testMatrix.o test.o matrix.o functions.o complex.o
main.o : main.c
	gcc -c main.c
test.o: test.c
	gcc -c test.c
testMatrix.o: testMatrix.c
	gcc -c testMatrix.c
matrix.o : matrix.c
	gcc -c matrix.c
complex.o : complex.c
	gcc -c complex.c
functions.o : functions.c
	gcc -c functions.c
clean :
	rm -f *.o programm test