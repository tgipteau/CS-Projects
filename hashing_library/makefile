CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined,



test: test.o hashmap.o
	$(CC) -o test test.o hashmap.o $(CFLAGS)

test.o: test.c
	$(CC) -c test.c -o test.o $(CFLAGS)

hashmap.o: hashmap.c hashmap.h
	$(CC) -c hashmap.c -o hashmap.o $(CFLAGS)

clean:
	rm -f *.o
