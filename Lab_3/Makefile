OBJECTS = gpio.o
CC = gcc
CFLAGS = -c -Wall -g
LIB = -lpthread

all: gpio

gpio: $(OBJECTS)
	$(CC) -o $@ $^  $(LIB)

gpio.o: gpio.c
	$(CC) $(CFLAGS) $^

clean:
	rm -f $(OBJECTS) gpio

