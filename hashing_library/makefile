CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined,

manip: manip.o hashmap.o
	$(CC) -o manip manip.o hashmap.o $(CFLAGS)

manip.o: manip.c hashmap.h
	$(CC) -c manip.c -o manip.o $(CFLAGS)

test: test.o hashmap.o
	$(CC) -o test test.o hashmap.o $(CFLAGS)

test.o: test.c hashmap.h
	$(CC) -c test.c -o test.o $(CFLAGS)

hashmap.o: hashmap.c hashmap.h
	$(CC) -c hashmap.c -o hashmap.o $(CFLAGS)

clean:
	rm -f *.o
