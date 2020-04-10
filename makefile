all:	 program
program: program.o arg.o pair.o
	gcc -o program  program.o arg.o pair.o

arg.o : arg.c
	gcc -c	arg.c

pair.o : pair.c
	gcc -c	pair.c


program.o :program.c
	gcc -c	program.c

clear:
	rm *.o
