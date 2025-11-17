CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: vetores arvore

vetores: vetores.c
	gcc $(CFLAGS) vetores.c -o vetores $(LDFLAGS)

arvore: arvore.c arvore_utils.c
	gcc $(CFLAGS) arvore.c -o arvore $(LDFLAGS)

clean:
	rm -f vetores arvore