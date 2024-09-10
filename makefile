all:  tab_hash.o main.o
	gcc tab_hash.o main.o -o prog
	./prog

tab_hash.c:
	gcc -c tab_hash.c


main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog