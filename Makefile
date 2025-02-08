CC=gcc
CFLAGS=-g -Wall
BINS=intercept.so

all: $(BINS)

%.so: %.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^ -ldl

clean:
	rm -f $(BINS)
