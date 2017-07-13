all:	BST

BST:	BST.o
	cc -o $@ $^

BST.o:	BST.c BST.h
	cc -c BST.c
clean:
	rm -f *.o BST
demo:	BST
	./BST
