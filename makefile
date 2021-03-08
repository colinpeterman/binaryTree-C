#By: Colin Peterman
#all trargets in the makefile
all: lab3.zip binarytree


lab3.zip: makefile readme binarytree.c testfile
	zip lab3.zip makefile readme binarytree.c testfile

binarytree: binarytree.o
	gcc binarytree.o -o binarytree

binarytree.o: binarytree.c
	gcc -ansi -pedantic -g -c binarytree.c
