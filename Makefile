CC=gcc-11
CFLAGS=-Wall -Ofast -march=native


test: MMM.o
	$(CC) $(CFLAGS) -o test MMM.o

.PHONY: clean

clean:
	rm -f *.o *~ test
