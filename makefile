all: sharing.o
	gcc -o sharing sharing.o
sharing.o: sharing.c
	gcc -c sharing.c
run: all
	./sharing
