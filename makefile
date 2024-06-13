OBJS = calc.o bst.o main.o calculator.out

calculator.out : main.o bst.o calc.o
	gcc -o calculator.out main.o bst.o calc.o -lm

main.o : calc.h bst.h main.c
	gcc -c -o main.o main.c

calc.o : calc.h calc.c
	gcc -c -o calc.o calc.c

bst.o : bst.h bst.c
	gcc -c -o bst.o bst.c

clean:
	rm -f $(OBJS)