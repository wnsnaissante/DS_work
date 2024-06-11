CC = clang
OBJS = calc.o bst.o main.o calculator.out

calculator.out : main.o bst.o calc.o
	$(CC) -o calculator.out main.o bst.o calc.o -lm

main.o : calc.h bst.h main.c
	$(CC) -c -o main.o main.c

calc.o : calc.h calc.c
	$(CC) -c -o calc.o calc.c

bst.o : bst.h bst.c
	$(CC) -c -o bst.o bst.c

clean:
	rm -f $(OBJS)