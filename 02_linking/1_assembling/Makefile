foo.o: foo.s
	gcc -S foo.c -o foo.s
	as -o foo.o foo.s


main.o: main.c
	gcc -c main.c


all: foo.o main.o
	gcc -o main main.o foo.o
	./main

dis:
	objdump -d -S main > main_dis.s

