CFLAG = -Wall -g -3O -pedantic
CC = g++


add: main.o
	$(CC) main.o -o add

main.o: adder.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f *.o *.so *.dll *.exe
