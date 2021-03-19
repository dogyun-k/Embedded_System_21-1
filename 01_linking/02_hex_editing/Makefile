increment.o: increment.c
	gcc -c increment.c

decrement.o: decrement.c
	gcc -c decrement.c

main.s: main.c
	gcc -S main.c -o main.s

main.o: main.s
	as -o main.o main.s


all: decrement.o increment.o main.o
	gcc -o main main.o increment.o decrement.o
	./main

dis:
	objdump -d -S main > main_dis.s

