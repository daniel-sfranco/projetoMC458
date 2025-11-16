CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: vetores

vetores: vetores.c
	gcc $(CFLAGS) vetores.c -o vetores $(LDFLAGS)

clean:
	rm -f vetores